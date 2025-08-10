@echo off
echo ========================================
echo Debug Compilation Issues
echo ========================================

echo Checking main.cpp content...
echo First 10 lines of main.cpp:
head -10 main.cpp 2>nul || (
    echo Cannot read main.cpp with head command, using type instead:
    type main.cpp | more
)

echo.
echo ========================================
echo Testing simple compilation
echo ========================================

echo Creating test.cpp...
echo #include ^<iostream^> > test.cpp
echo int main^(^) { std::cout ^<^< "Hello World"; return 0; } >> test.cpp

echo Compiling test.cpp...
g++ -std=c++11 test.cpp -o test.exe
if errorlevel 1 (
    echo ERROR: Even simple compilation fails!
    echo This indicates a compiler environment issue.
    pause
    exit /b 1
) else (
    echo Simple compilation successful!
    echo Running test...
    test.exe
    del test.exe test.cpp
)

echo.
echo ========================================
echo Testing main.cpp compilation with error output
echo ========================================

echo Attempting to compile main.cpp with error capture...
g++ -std=c++11 -Iinclude -c main.cpp -o main.o 2^>^&1
if errorlevel 1 (
    echo.
    echo Compilation of main.cpp failed.
    echo Let's check for common issues:
    echo.
    echo 1. Checking if main.cpp is readable:
    if exist main.cpp (
        echo    ✓ main.cpp exists
    ) else (
        echo    ✗ main.cpp not found!
        pause
        exit /b 1
    )
    
    echo 2. Checking include directory:
    if exist include (
        echo    ✓ include directory exists
        echo    Headers found:
        dir /b include
    ) else (
        echo    ✗ include directory not found!
    )
    
    echo 3. Trying compilation without includes:
    echo    Command: g++ -std=c++11 -c main.cpp -o main_noinclude.o
    g++ -std=c++11 -c main.cpp -o main_noinclude.o 2^>^&1
    if errorlevel 1 (
        echo    ✗ Failed even without includes - syntax error in main.cpp
        echo.
        echo Please check main.cpp for:
        echo - Missing semicolons
        echo - Unmatched braces {}
        echo - Missing #include statements
        echo - Typos in function names
    ) else (
        echo    ✓ Compiles without includes - header issue
        del main_noinclude.o
        echo.
        echo The problem is with header files.
        echo Let's check each header individually...
        
        for %%h in (include\*.h) do (
            echo Testing include of %%h...
            echo #include "%%~nxh" > test_header.cpp
            echo int main^(^) { return 0; } >> test_header.cpp
            g++ -std=c++11 -Iinclude -c test_header.cpp -o test_header.o 2^>nul
            if errorlevel 1 (
                echo    ✗ Problem with %%h
            ) else (
                echo    ✓ %%h is OK
                del test_header.o 2^>nul
            )
            del test_header.cpp 2^>nul
        )
    )
) else (
    echo ✓ main.cpp compiled successfully!
    del main.o
)

echo.
pause