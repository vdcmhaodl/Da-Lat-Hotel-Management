@echo off
echo ========================================
echo Fixing Compiler Environment
echo ========================================

echo Current PATH:
echo %PATH%

echo.
echo Current working directory:
cd

echo.
echo Checking available compilers:
where gcc 2>nul
where g++ 2>nul
where cl 2>nul

echo.
echo ========================================
echo Method 1: Using Windows native paths
echo ========================================

echo Creating simple test with echo...
echo #include ^<iostream^> > test.cpp
echo using namespace std; >> test.cpp  
echo int main^(^) ^{ cout ^<^< "Hello World" ^<^< endl; return 0; ^} >> test.cpp

echo Test file created:
type test.cpp

echo.
echo Trying compilation with full path...
C:\msys64\mingw64\bin\g++.exe -std=c++11 test.cpp -o test.exe
if errorlevel 1 (
    echo Method 1 failed, trying Method 2...
    goto method2
) else (
    echo Method 1 SUCCESS! Running test...
    test.exe
    del test.exe test.cpp
    goto compile_project
)

:method2
echo ========================================
echo Method 2: Clean environment compilation
echo ========================================

:: Set clean environment
set OLD_PATH=%PATH%
set PATH=C:\msys64\mingw64\bin;C:\Windows\System32;C:\Windows

echo Trying with clean PATH...
g++ -std=c++11 test.cpp -o test.exe
if errorlevel 1 (
    echo Method 2 failed, trying Method 3...
    set PATH=%OLD_PATH%
    goto method3
) else (
    echo Method 2 SUCCESS! Running test...
    test.exe
    del test.exe test.cpp
    set PATH=%OLD_PATH%
    goto compile_project
)

:method3
echo ========================================
echo Method 3: Using CMD instead of BASH
echo ========================================

echo Please try running this from Windows CMD (not Git Bash):
echo.
echo 1. Open Windows Command Prompt (cmd)
echo 2. Navigate to: %CD%
echo 3. Run: compile_project.bat
echo.

echo Creating compile_project.bat...
echo @echo off > compile_project.bat
echo echo Compiling Hotel Management System... >> compile_project.bat
echo. >> compile_project.bat
echo REM Create test >> compile_project.bat
echo echo #include ^<iostream^> ^> test.cpp >> compile_project.bat
echo echo int main^(^) ^{ std::cout ^<^< "Hello"; return 0; ^} ^>^> test.cpp >> compile_project.bat
echo. >> compile_project.bat
echo REM Test compiler >> compile_project.bat
echo g++ test.cpp -o test.exe >> compile_project.bat
echo if errorlevel 1 ^( >> compile_project.bat
echo     echo Compiler still not working >> compile_project.bat
echo     pause >> compile_project.bat
echo     exit /b 1 >> compile_project.bat
echo ^) >> compile_project.bat
echo. >> compile_project.bat
echo echo Compiler working! Cleaning up... >> compile_project.bat
echo del test.exe test.cpp >> compile_project.bat
echo. >> compile_project.bat
echo REM Compile main project >> compile_project.bat
echo echo Compiling main.cpp... >> compile_project.bat
echo g++ -std=c++11 -Iinclude -c main.cpp -o main.o >> compile_project.bat
echo if errorlevel 1 ^( >> compile_project.bat
echo     echo Error in main.cpp >> compile_project.bat
echo     pause >> compile_project.bat
echo     exit /b 1 >> compile_project.bat
echo ^) >> compile_project.bat
echo. >> compile_project.bat
echo if not exist bin mkdir bin >> compile_project.bat
echo. >> compile_project.bat
echo echo Compiling source files... >> compile_project.bat
echo for %%%%f in ^(src\*.cpp^) do ^( >> compile_project.bat
echo     echo Compiling %%%%f... >> compile_project.bat
echo     g++ -std=c++11 -Iinclude -c "%%%%f" -o "bin\%%%%~nf.o" >> compile_project.bat
echo     if errorlevel 1 ^( >> compile_project.bat
echo         echo Error compiling %%%%f >> compile_project.bat
echo         pause >> compile_project.bat
echo         exit /b 1 >> compile_project.bat
echo     ^) >> compile_project.bat
echo ^) >> compile_project.bat
echo. >> compile_project.bat
echo echo Linking... >> compile_project.bat
echo g++ -std=c++11 main.o bin\*.o -o hotel_management.exe >> compile_project.bat
echo if errorlevel 1 ^( >> compile_project.bat
echo     echo Linking failed >> compile_project.bat
echo     pause >> compile_project.bat
echo     exit /b 1 >> compile_project.bat
echo ^) >> compile_project.bat
echo. >> compile_project.bat
echo echo SUCCESS! Executable: hotel_management.exe >> compile_project.bat
echo pause >> compile_project.bat

echo.
echo compile_project.bat created!
echo Please run it from Windows CMD, not Git Bash.
echo.
goto end

:compile_project
echo ========================================
echo Compiling Hotel Management Project
echo ========================================

echo Compiling main.cpp...
g++ -std=c++11 -Iinclude -c main.cpp -o main.o
if errorlevel 1 (
    echo ERROR: main.cpp compilation failed
    echo This might be due to header file issues.
    goto end
)

if not exist bin mkdir bin

echo Compiling source files...
for %%f in (src\*.cpp) do (
    echo Compiling %%f...
    g++ -std=c++11 -Iinclude -c "%%f" -o "bin\%%~nf.o"
    if errorlevel 1 (
        echo ERROR: Failed to compile %%f
        goto end
    )
)

echo Linking...
g++ -std=c++11 main.o bin\*.o -o hotel_management.exe
if errorlevel 1 (
    echo ERROR: Linking failed
    goto end
)

echo.
echo ========================================
echo SUCCESS! Hotel Management System built!
echo Executable: hotel_management.exe
echo ========================================

set /p choice="Run the program? (y/n): "
if /i "%choice%"=="y" (
    hotel_management.exe
)

:end
del test.cpp test.exe 2>nul
pause