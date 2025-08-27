@echo off
echo Building Hotel Management System with Qt6 GUI...

REM Create build directory
if not exist "build" mkdir build
cd build

REM Configure with CMake
echo Configuring project...
cmake -G "MinGW Makefiles" ..
if %ERRORLEVEL% neq 0 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

REM Build the project
echo Building project...
cmake --build . --config Release
if %ERRORLEVEL% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo Build completed successfully!
echo.
echo Executables created:
echo - hotel_management_console.exe (Console version)
echo - hotel_management_gui.exe (GUI version)
echo.
echo To run the GUI version: .\bin\hotel_management_gui.exe
echo To run the console version: .\bin\hotel_management_console.exe
echo.
pause
