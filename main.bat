@echo off
set BOILERPLATE=^
-nostdlib -ffreestanding -fno-builtin ^
-mno-stack-arg-probe -fno-asynchronous-unwind-tables ^
-Wl,--entry,entry_point -Wl,--subsystem,console -Xlinker --stack=0x200000,0x200000

set DEBUG=-Og -gdwarf-5 -gstrict-dwarf -g3
set RELEASE=-O2 -s

set CFLAGS= -Wall -Wextra %RELEASE%
set LFLAGS=  -lntdll -lkernel32 -luser32 -lgdi32 -lucrt

@echo on
gcc %BOILERPLATE% %CFLAGS% -o main.exe main.c %LFLAGS% && .\main.exe