{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    fenix = {
      url = "github:nix-community/fenix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    self.submodules = true;
  };
  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
      fenix,
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [
            fenix.overlays.default
          ];
        };
        build = import ./sys/nix pkgs;
      in
      with pkgs;
      {
        inherit self;
        formatter = pkgs.nixfmt-tree;
        packages.build-sail = stdenv.mkDerivation {
          name = "build-sail";
          dontUnpack = true;
          nativeBuildInputs = [ makeWrapper ];
          installPhase = ''
            makeWrapper ${writeShellScript "build-sail-inner" ''
              cmake -S sys/hakkun/sail -B sys/hakkun/sail/build
              cmake --build sys/hakkun/sail/build --parallel
            ''} $out/bin/build-sail \
              --prefix PATH : ${
                lib.makeBinPath [
                  cmake
                  gnumake
                  llvmPackages_20.clang
                ]
              }
          '';
        };
        devShells = {
          default =
            mkShell.override
              {
                stdenv = llvmPackages_20.libcxxStdenv.override {
                  cc = llvmPackages_20.clang-unwrapped;
                };
              }
              {
                buildInputs = build.dependencies ++ [
                  inetutils
                  pkgs.fenix.complete.toolchain
                ];
                LD_LIBRARY_PATH = lib.makeLibraryPath [
                  llvmPackages_20.clang-unwrapped.lib
                ];
                NIX_CC_WRAPPER_SUPPRESS_TARGET_WARNING = true;
                
              };
        };
      }
    );
}
