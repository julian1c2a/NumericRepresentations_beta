@echo off
REM Script universal header-only para compilar tests con gcc, clang o msvc y Catch2 header-only
REM Uso: compile_test_headeronly.bat test_archivo.cpp [gcc|clang|msvc]

setlocal
set SRC=tests\%1
set COMPILER=%2
if "%COMPILER%"=="" set COMPILER=msvc
set BASE=%~n1
set "OUTDIR=build_tests_%COMPILER%"
set EXE=%OUTDIR%\%BASE%_%COMPILER%.exe

if not exist %SRC% (
    echo Error: No se encuentra el archivo %SRC%
    exit /b 1
)
if not exist %OUTDIR% mkdir %OUTDIR%

if /I "%COMPILER%"=="msvc" (
    where cl.exe >nul 2>&1
    if %ERRORLEVEL% NEQ 0 call setup_compilers.bat
    cl /EHsc /std:c++latest /Iinclude /Ilocal_libs/include /Fe:%EXE% %SRC%
) else if /I "%COMPILER%"=="gcc" (
    where g++ >nul 2>&1
    if %ERRORLEVEL% NEQ 0 (
        echo Error: g++ no encontrado en PATH
        exit /b 1
    )
    g++ -std=c++20 -Wall -Iinclude -Ilocal_libs/include -o %EXE% %SRC%
) else if /I "%COMPILER%"=="clang" (
    where clang++ >nul 2>&1
    if %ERRORLEVEL% NEQ 0 (
        echo Error: clang++ no encontrado en PATH
        exit /b 1
    )
    clang++ -std=c++20 -Wall -Iinclude -Ilocal_libs/include -o %EXE% %SRC%
) else (
    echo Compilador no soportado
    exit /b 1
)

if %ERRORLEVEL% NEQ 0 exit /b 1
%EXE%
endlocal
