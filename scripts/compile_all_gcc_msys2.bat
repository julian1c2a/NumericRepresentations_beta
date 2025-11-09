@echo off
REM Script para compilar con GCC usando la instalacion MSYS2 UCRT64
REM Ubicacion: c:\msys64\ucrt64\bin

echo === CONFIGURACION GCC MSYS2 UCRT64 ===
echo Compilador: GCC 15.2.0 (MSYS2 UCRT64)
echo Ubicacion: c:\msys64\ucrt64\bin\gcc.exe

REM Verificar si GCC esta disponible
if not exist "c:\msys64\ucrt64\bin\gcc.exe" (
    echo ❌ GCC no encontrado en c:\msys64\ucrt64\bin\gcc.exe
    pause
    exit /b 1
)

echo Verificando version:
c:\msys64\ucrt64\bin\gcc.exe --version | findstr gcc
echo.

REM Variables especificas
set GCC_PATH=c:\msys64\ucrt64\bin
set INCLUDE_DIR=../include
set TESTS_DIR=../tests
set OUTPUT_DIR=../tests
set GCC_FLAGS=-std=c++23 -Wall -Wextra -O2

echo 🧮 SUITE 1: OPERADORES ARITMETICOS
echo === Compilando Suite Aritmetica con GCC ===
"%GCC_PATH%\g++.exe" %GCC_FLAGS% -I%INCLUDE_DIR% "%TESTS_DIR%\test_dig_t_arithmetic.cpp" -o "%OUTPUT_DIR%\test_dig_t_arithmetic_gcc.exe"
if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilacion GCC exitosa
    echo.
    echo === Ejecutando Suite Aritmetica GCC ===
    %OUTPUT_DIR%\test_dig_t_arithmetic_gcc.exe
) else (
    echo ❌ Error en compilacion aritmetica GCC
)
echo.

echo 🔍 SUITE 2: OPERADORES DE COMPARACION
echo === Compilando Suite Comparacion con GCC ===
"%GCC_PATH%\g++.exe" %GCC_FLAGS% -I%INCLUDE_DIR% "%TESTS_DIR%\test_dig_t_comparison.cpp" -o "%OUTPUT_DIR%\test_dig_t_comparison_gcc.exe"
if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilacion GCC exitosa
    echo.
    echo === Ejecutando Suite Comparacion GCC ===
    %OUTPUT_DIR%\test_dig_t_comparison_gcc.exe
) else (
    echo ❌ Error en compilacion comparacion GCC
)
echo.

echo 🎲 SUITE 3: OPERADORES BITWISE/MATEMATICOS  
echo === Compilando Suite Bitwise con GCC ===
"%GCC_PATH%\g++.exe" %GCC_FLAGS% -I%INCLUDE_DIR% "%TESTS_DIR%\test_dig_t_bitwise.cpp" -o "%OUTPUT_DIR%\test_dig_t_bitwise_gcc.exe"
if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilacion GCC exitosa
    echo.
    echo === Ejecutando Suite Bitwise GCC ===
    %OUTPUT_DIR%\test_dig_t_bitwise_gcc.exe
) else (
    echo ❌ Error en compilacion bitwise GCC
)
echo.

echo 📝 SUITE 4: OPERADORES I/O
echo === Compilando Suite I/O con GCC ===
"%GCC_PATH%\g++.exe" %GCC_FLAGS% -I%INCLUDE_DIR% "%TESTS_DIR%\test_dig_t_io_simple.cpp" -o "%OUTPUT_DIR%\test_dig_t_io_simple_gcc.exe"
if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilacion GCC exitosa
    echo.
    echo === Ejecutando Suite I/O GCC ===
    %OUTPUT_DIR%\test_dig_t_io_simple_gcc.exe
) else (
    echo ❌ Error en compilacion I/O GCC
)
echo.

echo 🎯 SUITE 5: COMPREHENSIVE
echo === Compilando Suite Comprehensive con GCC ===
"%GCC_PATH%\g++.exe" %GCC_FLAGS% -I%INCLUDE_DIR% "%TESTS_DIR%\test_dig_t_comprehensive.cpp" -o "%OUTPUT_DIR%\test_dig_t_comprehensive_gcc.exe"
if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilacion GCC exitosa
    echo.
    echo === Ejecutando Suite Comprehensive GCC ===
    %OUTPUT_DIR%\test_dig_t_comprehensive_gcc.exe
) else (
    echo ❌ Error en compilacion comprehensive GCC
)
echo.

echo 🏆 TODAS LAS SUITES GCC COMPLETADAS
echo Compilador: GCC 15.2.0 (MSYS2 UCRT64)
pause