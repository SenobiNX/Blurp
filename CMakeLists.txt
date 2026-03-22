cmake_minimum_required(VERSION 3.16)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/sys/cmake/toolchain.cmake")
project(Blurp VERSION 1.0 LANGUAGES ASM C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
 
include(config/config.cmake)
 
add_subdirectory(sys/hakkun)
add_subdirectory(lib/blurp)
add_subdirectory(sysmodules/boot2)
