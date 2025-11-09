@echo off
REM Script para compilar con GCC en Windows (MSYS2/MinGW)
REM Requiere: MSYS2 con pacman -S mingw-w64-x86_64-gcc

echo === CONFIGURACION GCC PARA NumericRepresentations ===
echo Requiere: MSYS2/MinGW-w64 instalado
echo Ubicacion esperada: C:\msys64\mingw64\bin\gcc.exe

REM Verificar si GCC esta disponible
where gcc >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ❌ GCC no encontrado en PATH
    echo.
    echo INSTRUCCIONES DE INSTALACION:
    echo 1. Descargar MSYS2 desde https://www.msys2.org/
    echo 2. Instalar y ejecutar: pacman -S mingw-w64-x86_64-gcc
    echo 3. Agregar C:\msys64\mingw64\bin al PATH
    echo 4. Reiniciar terminal y ejecutar este script
    pause
    exit /b 1
)

echo Compilador: 
gcc --version | findstr gcc
echo.

REM Variables comunes
set INCLUDE_DIR=../include
set TESTS_DIR=../tests  
set OUTPUT_DIR=../tests
set GCC_FLAGS=-std=c++23 -Wall -Wextra -O2

echo 🧮 SUITE 1: OPERADORES ARITMETICOS
echo === Compilando Suite Aritmetica ===
gcc %GCC_FLAGS% -I%INCLUDE_DIR% %TESTS_DIR%/test_dig_t_arithmetic.cpp -o %OUTPUT_DIR%/test_dig_t_arithmetic_gcc.exe
if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilacion exitosa
    echo.
    echo === Ejecutando Suite Aritmetica ===
    %OUTPUT_DIR%\test_dig_t_arithmetic_gcc.exe
) else (
    echo ❌ Error en compilacion aritmetica
)
echo.

echo 🔍 SUITE 2: OPERADORES DE COMPARACION
echo === Compilando Suite Comparacion ===
gcc %GCC_FLAGS% -I%INCLUDE_DIR% %TESTS_DIR%/test_dig_t_comparison.cpp -o %OUTPUT_DIR%/test_dig_t_comparison_gcc.exe
if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilacion exitosa
    echo.
    echo === Ejecutando Suite Comparacion ===
    %OUTPUT_DIR%\test_dig_t_comparison_gcc.exe
) else (
    echo ❌ Error en compilacion comparacion
)
echo.

echo 🎲 SUITE 3: OPERADORES BITWISE/MATEMATICOS  
echo === Compilando Suite Bitwise ===
gcc %GCC_FLAGS% -I%INCLUDE_DIR% %TESTS_DIR%/test_dig_t_bitwise.cpp -o %OUTPUT_DIR%/test_dig_t_bitwise_gcc.exe
if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilacion exitosa
    echo.
    echo === Ejecutando Suite Bitwise ===
    %OUTPUT_DIR%\test_dig_t_bitwise_gcc.exe
) else (
    echo ❌ Error en compilacion bitwise
)
echo.

echo 📝 SUITE 4: OPERADORES I/O
echo === Compilando Suite I/O ===
gcc %GCC_FLAGS% -I%INCLUDE_DIR% %TESTS_DIR%/test_dig_t_io_simple.cpp -o %OUTPUT_DIR%/test_dig_t_io_simple_gcc.exe
if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilacion exitosa
    echo.
    echo === Ejecutando Suite I/O ===
    %OUTPUT_DIR%\test_dig_t_io_simple_gcc.exe
) else (
    echo ❌ Error en compilacion I/O
)
echo.

echo 🎯 SUITE 5: COMPREHENSIVE
echo === Compilando Suite Comprehensive ===
gcc %GCC_FLAGS% -I%INCLUDE_DIR% %TESTS_DIR%/test_dig_t_comprehensive.cpp -o %OUTPUT_DIR%/test_dig_t_comprehensive_gcc.exe
if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilacion exitosa
    echo.
    echo === Ejecutando Suite Comprehensive ===
    %OUTPUT_DIR%\test_dig_t_comprehensive_gcc.exe
) else (
    echo ❌ Error en compilacion comprehensive
)
echo.

echo 🏆 TODAS LAS SUITES GCC COMPLETADAS
pause