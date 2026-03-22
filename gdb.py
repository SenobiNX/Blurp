import gdb
import sys
import glob

def load_sysmodule():
    info = gdb.execute("mon get info", to_string = True)
    lines: list = list(map(str.strip, info.split('\n')))
    modules: list[str] = lines[lines.index("Modules:")+1:-1];
    for module in modules:
        start, _, _, name  = module.split()
        start = int(start, 16)
        filenames = glob.glob(f"build/**/{name}", recursive=True)
        if not filenames:
            print(f"warn: no file found for {name}", file=sys.stderr)
            continue
        print(f"{start:X}, {name}, {filenames[0]}")
        gdb.execute(f"add-symbol-file {filenames[0]} {start:#X}")

table = {
    "boot2": 0x024172663a330008
}

class WaitForSysmodule(gdb.Command):
    def __init__(self):
        print("hi")
        super().__init__("wfsys", gdb.COMMAND_USER)
    
    def invoke(self, arg: str, _):
        print(arg)
        if arg in table:
            arg = f"0x{table[arg]:x}"
        else:
            print("not a valid option", file=sys.stderr)
            return
        print(f"waiting for {arg}")
        info: str = gdb.execute(f"mon wait {arg}", to_string=True)
        print("got", info)
        start = info.index('0x')
        number = int(info[start:info.index('`', start)], 16)
        print(f"attaching to 0x{number:X}")
        gdb.execute(f"attach 0x{number:X}")
        load_sysmodule()

WaitForSysmodule()

print("blurp gdb loaded")
