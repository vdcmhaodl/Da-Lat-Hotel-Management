@echo off
echo ========================================
echo Fixing Compiler Environment
echo ========================================

:: Lưu lại PATH cũ
set "OLD_PATH=%PATH%"
set "PATH=C:\msys64\mingw64\bin;C:\Windows\System32;C:\Windows"

echo Using PATH:
echo %PATH%

:: Kiểm tra compiler
where g++ || (
    echo ERROR: g++ not found!
    set "PATH=%OLD_PATH%"
    pause
    exit /b 1
)

echo.
echo Compiling main.cpp...
g++ -std=c++11 -Iinclude -c main.cpp -o bin\main.o
if errorlevel 1 goto :error

if not exist bin mkdir bin

echo Compiling source files...
for %%f in (src\*.cpp) do (
    echo Compiling %%f...
    g++ -std=c++11 -Iinclude -c "%%f" -o "bin\%%~nf.o"
    if errorlevel 1 goto :error
)

echo Linking...
g++ -std=c++11 bin\*.o -o hotel_management.exe
if errorlevel 1 goto :error

echo.
echo ========================================
echo SUCCESS! Hotel Management System built!
echo Executable: hotel_management.exe
echo ========================================

set /p runchoice="Run the program? (y/n): "
if /i "%runchoice%"=="y" (
    hotel_management.exe
)

goto :end

:error
echo ERROR: Build failed!
:end
set "PATH=%OLD_PATH%"
pause