@echo off
REM Script para compilar con Clang usando la instalacion MSYS2 UCRT64
REM Ubicacion: c:\msys64\ucrt64\bin

echo === CONFIGURACION CLANG MSYS2 UCRT64 ===
echo Compilador: Clang 21.1.4 (MSYS2 UCRT64)
echo Ubicacion: c:\msys64\ucrt64\bin\clang++.exe

REM Verificar si Clang esta disponible
if not exist "c:\msys64\ucrt64\bin\clang++.exe" (
    echo ❌ Clang no encontrado en c:\msys64\ucrt64\bin\clang++.exe
    pause
    exit /b 1
)

echo Verificando version:
c:\msys64\ucrt64\bin\clang++.exe --version | findstr clang
echo.

REM Variables especificas
set CLANG_PATH=c:\msys64\ucrt64\bin
set INCLUDE_DIR=../include
set TESTS_DIR=../tests
set OUTPUT_DIR=../tests
set CLANG_FLAGS=-std=c++23 -Wall -Wextra -O2

echo 🧮 SUITE 1: OPERADORES ARITMETICOS
echo === Compilando Suite Aritmetica con Clang ===
"%CLANG_PATH%\clang++.exe" %CLANG_FLAGS% -I%INCLUDE_DIR% "%TESTS_DIR%\test_dig_t_arithmetic.cpp" -o "%OUTPUT_DIR%\test_dig_t_arithmetic_clang.exe"
if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilacion Clang exitosa
    echo.
    echo === Ejecutando Suite Aritmetica Clang ===
    "%OUTPUT_DIR%\test_dig_t_arithmetic_clang.exe"
) else (
    echo ❌ Error en compilacion aritmetica Clang
)
echo.

echo 🔍 SUITE 2: OPERADORES DE COMPARACION
echo === Compilando Suite Comparacion con Clang ===
"%CLANG_PATH%\clang++.exe" %CLANG_FLAGS% -I%INCLUDE_DIR% "%TESTS_DIR%\test_dig_t_comparison.cpp" -o "%OUTPUT_DIR%\test_dig_t_comparison_clang.exe"
if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilacion Clang exitosa
    echo.
    echo === Ejecutando Suite Comparacion Clang ===
%OUTPUT_DIR%	est_dig_t_comparison_clang.exe
) else (
    echo ❌ Error en compilacion comparacion Clang
)
echo.

echo 🎲 SUITE 3: OPERADORES BITWISE/MATEMATICOS  
echo === Compilando Suite Bitwise con Clang ===
"%CLANG_PATH%\clang++.exe" %CLANG_FLAGS% -I%INCLUDE_DIR% "%TESTS_DIR%\test_dig_t_bitwise.cpp" -o "%OUTPUT_DIR%\test_dig_t_bitwise_clang.exe"
if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilacion Clang exitosa
    echo.
    echo === Ejecutando Suite Bitwise Clang ===
    %OUTPUT_DIR%\test_dig_t_bitwise_clang.exe
) else (
    echo ❌ Error en compilacion bitwise Clang
)
echo.

echo 📝 SUITE 4: OPERADORES I/O
echo === Compilando Suite I/O con Clang ===
"%CLANG_PATH%\clang++.exe" %CLANG_FLAGS% -I%INCLUDE_DIR% "%TESTS_DIR%\test_dig_t_io_simple.cpp" -o "%OUTPUT_DIR%\test_dig_t_io_simple_clang.exe"
if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilacion Clang exitosa
    echo.
    echo === Ejecutando Suite I/O Clang ===
    %OUTPUT_DIR%\test_dig_t_io_simple_clang.exe
) else (
    echo ❌ Error en compilacion I/O Clang
)
echo.

echo 🎯 SUITE 5: COMPREHENSIVE
echo === Compilando Suite Comprehensive con Clang ===
"%CLANG_PATH%\clang++.exe" %CLANG_FLAGS% -I%INCLUDE_DIR% "%TESTS_DIR%\test_dig_t_comprehensive.cpp" -o "%OUTPUT_DIR%\test_dig_t_comprehensive_clang.exe"
if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilacion Clang exitosa
    echo.
    echo === Ejecutando Suite Comprehensive Clang ===
    %OUTPUT_DIR%\test_dig_t_comprehensive_clang.exe
) else (
    echo ❌ Error en compilacion comprehensive Clang
)
echo.

echo 🏆 TODAS LAS SUITES CLANG COMPLETADAS
echo Compilador: Clang 21.1.4 (MSYS2 UCRT64)
pause