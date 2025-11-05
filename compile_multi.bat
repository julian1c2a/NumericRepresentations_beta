@echo off
REM ======================================================================
REM Script de compilación multi-compilador para NumericRepresentations
REM Prueba el código con MSVC, GCC y Clang
REM ======================================================================

setlocal EnableDelayedExpansion

if "%1"=="" (
    echo Uso: compile_multi.bat ^<archivo.cpp^> [nombre_ejecutable]
    echo.
    echo Ejemplos:
    echo   compile_multi.bat test_dig_comprehensive.cpp
    echo   compile_multi.bat test_advanced_edge_cases.cpp
    echo.
    exit /b 1
)

set "SOURCE_FILE=%1"
set "BASE_NAME=%~n1"
if not "%2"=="" set "BASE_NAME=%2"

if not exist "%SOURCE_FILE%" (
    echo Error: No se encuentra el archivo %SOURCE_FILE%
    exit /b 1
)

REM Configurar entorno
set "PATH=C:\msys64\ucrt64\bin;%PATH%"
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64 >nul 2>&1

echo ======================================================================
echo Compilando %SOURCE_FILE% con múltiples compiladores
echo ======================================================================
echo.

set "COMMON_FLAGS=-std=c++20 -Wall -I.\include"
set "SUCCESS_COUNT=0"
set "TOTAL_COUNT=3"

REM ===== MSVC =====
echo [1/3] MSVC (Visual Studio 2022)
echo ----------------------------------------------------------------------
set "MSVC_FLAGS=/EHsc /std:c++latest /I.\include"
cl %MSVC_FLAGS% "%SOURCE_FILE%" /Fe:"%BASE_NAME%_msvc.exe" >nul 2>&1
if !ERRORLEVEL! EQU 0 (
    echo ✅ MSVC: Compilación exitosa
    set /a SUCCESS_COUNT+=1
) else (
    echo ❌ MSVC: Error de compilación
    cl %MSVC_FLAGS% "%SOURCE_FILE%" /Fe:"%BASE_NAME%_msvc.exe"
)
echo.

REM ===== GCC =====
echo [2/3] GCC (MinGW-w64 15.2.0)
echo ----------------------------------------------------------------------
set "GCC_FLAGS=-std=c++20 -Wall -Wextra -I.\include -O2 -lstdc++"
g++ %GCC_FLAGS% "%SOURCE_FILE%" -o "%BASE_NAME%_gcc.exe" >nul 2>&1
if !ERRORLEVEL! EQU 0 (
    echo ✅ GCC: Compilación exitosa
    set /a SUCCESS_COUNT+=1
) else (
    echo ❌ GCC: Error de compilación
    g++ %GCC_FLAGS% "%SOURCE_FILE%" -o "%BASE_NAME%_gcc.exe"
)
echo.

REM ===== Clang =====
echo [3/3] Clang (LLVM 21.1.4)
echo ----------------------------------------------------------------------
set "CLANG_FLAGS=-std=c++20 -Wall -Wextra -I.\include -O2"
clang++ %CLANG_FLAGS% "%SOURCE_FILE%" -o "%BASE_NAME%_clang.exe" >nul 2>&1
if !ERRORLEVEL! EQU 0 (
    echo ✅ Clang: Compilación exitosa
    set /a SUCCESS_COUNT+=1
) else (
    echo ❌ Clang: Error de compilación  
    clang++ %CLANG_FLAGS% "%SOURCE_FILE%" -o "%BASE_NAME%_clang.exe"
)
echo.

REM ===== Resumen =====
echo ======================================================================
echo RESUMEN: %SUCCESS_COUNT%/%TOTAL_COUNT% compiladores exitosos
echo ======================================================================

if %SUCCESS_COUNT% EQU %TOTAL_COUNT% (
    echo 🎉 ¡EXCELENTE! Código compila en todos los compiladores
    echo.
    echo Ejecutables generados:
    if exist "%BASE_NAME%_msvc.exe" echo   • %BASE_NAME%_msvc.exe
    if exist "%BASE_NAME%_gcc.exe" echo   • %BASE_NAME%_gcc.exe  
    if exist "%BASE_NAME%_clang.exe" echo   • %BASE_NAME%_clang.exe
    echo.
    echo ¿Ejecutar tests? (S/N):
    set /p "RUN_TESTS="
    if /i "!RUN_TESTS!"=="S" (
        echo.
        echo === Ejecutando con MSVC ===
        if exist "%BASE_NAME%_msvc.exe" "%BASE_NAME%_msvc.exe"
        echo.
        echo === Ejecutando con GCC ===  
        if exist "%BASE_NAME%_gcc.exe" "%BASE_NAME%_gcc.exe"
        echo.
        echo === Ejecutando con Clang ===
        if exist "%BASE_NAME%_clang.exe" "%BASE_NAME%_clang.exe"
    )
) else if %SUCCESS_COUNT% GTR 0 (
    echo ⚠️ Compilación parcial - algunos compiladores fallaron
) else (
    echo ❌ Error total - ningún compilador exitoso
)

echo.
pause