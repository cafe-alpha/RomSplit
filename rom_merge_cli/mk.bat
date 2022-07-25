@echo off & setlocal EnableDelayedExpansion
set PATH=C:\MinGW\bin;%PATH%

@REM Set parameters re-used in several commands
set workdir="%cd%"

set cm=dummy
:start

echo -------------------------------------------- ROM Merge Tool
echo  Type `e' to end.
echo  Type `m' to make tool.
echo  Type `r' to rebuild tool.
echo  Type `t' to test tool.
echo  Type `rt' to rebuild then test.
echo  Type `mt' to make then test.
echo  Other: exec dos command.
set /P cm="Command: "

:parsecommand

@REM Parse command itself
If "%cm%" == "e"  goto end
If "%cm%" == "m"  goto do_make
If "%cm%" == "r"  goto do_rebuild
If "%cm%" == "t"  goto do_test
If "%cm%" == "rt" goto do_rebuild
If "%cm%" == "mt" goto do_make
%cm%
goto start


:do_make
make
if not exist ..\rom_merge_cli.exe goto start
echo Compile OK
If "%cm%" == "mt"  goto do_test
goto start

:do_rebuild
cls
make mrproper
make
if not exist ..\rom_merge_cli.exe goto start
echo Compile OK
If "%cm%" == "rt"  goto do_test
goto start

:do_test
if not exist ..\rom_merge_cli.exe goto start

..\rom_merge_cli.exe test_even.bin test_odd.bin test.bin
goto start

:end

