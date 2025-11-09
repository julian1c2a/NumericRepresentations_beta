@echo off
REM Script para compilar con Clang en Windows
REM Requiere: LLVM/Clang instalado desde https://llvm.org/

echo === CONFIGURACION CLANG PARA NumericRepresentations ===
echo Requiere: LLVM/Clang instalado
echo Ubicaciones esperadas: 
echo - C:\Program Files\LLVM\bin\clang.exe
echo - Agregado al PATH del sistema

REM Verificar si Clang esta disponible
where clang >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ❌ Clang no encontrado en PATH
    echo.
    echo INSTRUCCIONES DE INSTALACION:
    echo 1. Descargar LLVM desde https://llvm.org/builds/
    echo 2. Ejecutar instalador y marcar "Add LLVM to PATH"
    echo 3. Reiniciar terminal y ejecutar este script
    echo.
    echo ALTERNATIVA - Visual Studio:
    echo 1. Instalar "Clang compiler for Windows" desde Visual Studio Installer
    echo 2. Usar Developer Command Prompt
    pause
    exit /b 1
)

echo Compilador: 
clang --version | findstr clang
echo.

REM Variables comunes
set INCLUDE_DIR=../include
set TESTS_DIR=../tests  
set OUTPUT_DIR=../tests
set CLANG_FLAGS=-std=c++23 -Wall -Wextra -O2

echo 🧮 SUITE 1: OPERADORES ARITMETICOS
echo === Compilando Suite Aritmetica ===
clang++ %CLANG_FLAGS% -I%INCLUDE_DIR% %TESTS_DIR%/test_dig_t_arithmetic.cpp -o %OUTPUT_DIR%/test_dig_t_arithmetic_clang.exe
if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilacion exitosa
    echo.
    echo === Ejecutando Suite Aritmetica ===
    %OUTPUT_DIR%\test_dig_t_arithmetic_clang.exe
) else (
    echo ❌ Error en compilacion aritmetica
)
echo.

echo 🔍 SUITE 2: OPERADORES DE COMPARACION
echo === Compilando Suite Comparacion ===
clang++ %CLANG_FLAGS% -I%INCLUDE_DIR% %TESTS_DIR%/test_dig_t_comparison.cpp -o %OUTPUT_DIR%/test_dig_t_comparison_clang.exe
if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilacion exitosa
    echo.
    echo === Ejecutando Suite Comparacion ===
    %OUTPUT_DIR%\test_dig_t_comparison_clang.exe
) else (
    echo ❌ Error en compilacion comparacion
)
echo.

echo 🎲 SUITE 3: OPERADORES BITWISE/MATEMATICOS  
echo === Compilando Suite Bitwise ===
clang++ %CLANG_FLAGS% -I%INCLUDE_DIR% %TESTS_DIR%/test_dig_t_bitwise.cpp -o %OUTPUT_DIR%/test_dig_t_bitwise_clang.exe
if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilacion exitosa
    echo.
    echo === Ejecutando Suite Bitwise ===
    %OUTPUT_DIR%\test_dig_t_bitwise_clang.exe
) else (
    echo ❌ Error en compilacion bitwise
)
echo.

echo 📝 SUITE 4: OPERADORES I/O
echo === Compilando Suite I/O ===
clang++ %CLANG_FLAGS% -I%INCLUDE_DIR% %TESTS_DIR%/test_dig_t_io_simple.cpp -o %OUTPUT_DIR%/test_dig_t_io_simple_clang.exe
if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilacion exitosa
    echo.
    echo === Ejecutando Suite I/O ===
    %OUTPUT_DIR%\test_dig_t_io_simple_clang.exe
) else (
    echo ❌ Error en compilacion I/O
)
echo.

echo 🎯 SUITE 5: COMPREHENSIVE
echo === Compilando Suite Comprehensive ===
clang++ %CLANG_FLAGS% -I%INCLUDE_DIR% %TESTS_DIR%/test_dig_t_comprehensive.cpp -o %OUTPUT_DIR%/test_dig_t_comprehensive_clang.exe
if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilacion exitosa
    echo.
    echo === Ejecutando Suite Comprehensive ===
    %OUTPUT_DIR%\test_dig_t_comprehensive_clang.exe
) else (
    echo ❌ Error en compilacion comprehensive
)
echo.

echo 🏆 TODAS LAS SUITES CLANG COMPLETADAS
pause