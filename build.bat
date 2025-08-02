@echo off
echo Compiling...

g++ main.cpp src\*.cpp -Iinclude -o main.exe

if %errorlevel% neq 0 (
    echo Build failed.
    exit /b %errorlevel%
)

echo Build succeeded. Output: main.exe