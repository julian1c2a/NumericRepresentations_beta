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
    REM Buscar en ./tests si no se encuentra en el directorio actual
    if exist "tests\%SOURCE_FILE%" (
        set "SOURCE_FILE=tests\%SOURCE_FILE%"
    ) else (
        echo Error: No se encuentra el archivo %SOURCE_FILE% ni en tests\
        exit /b 1
    )
)

REM Configurar entorno
set "PATH=C:\msys64\ucrt64\bin;%PATH%"
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64 >nul 2>&1

echo ======================================================================
echo Compilando %SOURCE_FILE% con multiples compiladores
echo ======================================================================
echo.

set "COMMON_FLAGS=-std=c++20 -Wall -I.\include"
set "SUCCESS_COUNT=0"
set "TOTAL_COUNT=3"

REM Crear carpetas de salida si no existen
set "OUTDIR_MSVC=build_tests\msvc"
set "OUTDIR_GCC=build_tests\gcc"
set "OUTDIR_CLANG=build_tests\clang"
if not exist "build_tests" mkdir "build_tests"
if not exist "%OUTDIR_MSVC%" mkdir "%OUTDIR_MSVC%"
if not exist "%OUTDIR_GCC%" mkdir "%OUTDIR_GCC%"
if not exist "%OUTDIR_CLANG%" mkdir "%OUTDIR_CLANG%"

REM ===== MSVC =====
echo [1/3] MSVC (Visual Studio 2022)
echo ----------------------------------------------------------------------
REM Usar flags extendidos por defecto para template metaprogramming
set "MSVC_FLAGS=/EHsc /std:c++latest /Iinclude /constexpr:depth2048 /constexpr:steps1048576 /bigobj /permissive-"
echo [DEBUG] Ruta de include usada para MSVC: /Iinclude
set "EXE_MSVC=%OUTDIR_MSVC%\%BASE_NAME%.exe"
set "MSVC_SUCCESS=0"
cl %MSVC_FLAGS% "%SOURCE_FILE%" /Fe:"%EXE_MSVC%" >nul 2>&1
if exist "%EXE_MSVC%" (
    echo [OK] MSVC: Compilacion exitosa (flags extendidos)
    set "MSVC_SUCCESS=1"
) else (
    set "MSVC_FALLBACK=/EHsc /std:c++latest /Iinclude"
    cl !MSVC_FALLBACK! "%SOURCE_FILE%" /Fe:"%EXE_MSVC%" >nul 2>&1
    if exist "%EXE_MSVC%" (
        echo [OK] MSVC: Compilacion exitosa con flags fallback
        set "MSVC_SUCCESS=1"
    ) else (
        echo [ERROR] MSVC: Error de compilacion (MSVC)
        set "MSVC_SUCCESS=0"
        echo --- DEPURACION: Directorio actual ---
        cd
        echo --- DEPURACION: Contenido de include/core ---
        dir include\core
        cl !MSVC_FALLBACK! "%SOURCE_FILE%" /Fe:"%EXE_MSVC%"
    )
)
if %MSVC_SUCCESS% EQU 1 set /a SUCCESS_COUNT+=1
echo.

REM ===== GCC =====
echo [2/3] GCC (MinGW-w64 15.2.0)
echo ----------------------------------------------------------------------
set "GCC_FLAGS=-std=c++23 -Wall -Wextra -Iinclude -O2 -lstdc++"
echo [DEBUG] Ruta de include usada para GCC: -Iinclude
set "EXE_GCC=%OUTDIR_GCC%\%BASE_NAME%.exe"
g++ %GCC_FLAGS% "%SOURCE_FILE%" -o "%EXE_GCC%" >nul 2>&1
if exist "%EXE_GCC%" (
    echo [OK] GCC: Compilacion exitosa
    set /a SUCCESS_COUNT+=1
) else (
    g++ %GCC_FLAGS% "%SOURCE_FILE%" -o "%EXE_GCC%"
    if exist "%EXE_GCC%" (
        echo [OK] GCC: Compilacion exitosa (segundo intento)
        set /a SUCCESS_COUNT+=1
    ) else (
        echo [ERROR] GCC: Error de compilacion
    )
)
echo.

REM ===== Clang =====
echo [3/3] Clang (LLVM 21.1.4)
echo ----------------------------------------------------------------------
set "CLANG_FLAGS=-std=c++23 -Wall -Wextra -Iinclude -O2"
echo [DEBUG] Ruta de include usada para Clang: -Iinclude
set "EXE_CLANG=%OUTDIR_CLANG%\%BASE_NAME%.exe"
clang++ %CLANG_FLAGS% "%SOURCE_FILE%" -o "%EXE_CLANG%" >nul 2>&1
if exist "%EXE_CLANG%" (
    echo [OK] Clang: Compilacion exitosa
    set /a SUCCESS_COUNT+=1
) else (
    clang++ %CLANG_FLAGS% "%SOURCE_FILE%" -o "%EXE_CLANG%"
    if exist "%EXE_CLANG%" (
        echo [OK] Clang: Compilacion exitosa (segundo intento)
        set /a SUCCESS_COUNT+=1
    ) else (
        echo [ERROR] Clang: Error de compilacion
    )
)
echo.

REM ===== Resumen =====
echo ======================================================================
echo RESUMEN: %SUCCESS_COUNT%/%TOTAL_COUNT% compiladores exitosos
echo ======================================================================

if %SUCCESS_COUNT% EQU %TOTAL_COUNT% (
    echo [EXITO] Codigo compila en todos los compiladores
    echo.
    echo Ejecutables generados:
    if exist "%EXE_MSVC%" echo   - %EXE_MSVC%
    if exist "%EXE_GCC%" echo   - %EXE_GCC%
    if exist "%EXE_CLANG%" echo   - %EXE_CLANG%
    echo.
    echo Ejecutar tests? (S/N):
    set /p "RUN_TESTS="
    if /i "!RUN_TESTS!"=="S" (
        echo.
        echo === Ejecutando con MSVC ===
        if exist "%EXE_MSVC%" "%EXE_MSVC%"
        echo.
        echo === Ejecutando con GCC ===
        if exist "%EXE_GCC%" "%EXE_GCC%"
        echo.
        echo === Ejecutando con Clang ===
        if exist "%EXE_CLANG%" "%EXE_CLANG%"
    )
) else if %SUCCESS_COUNT% GTR 0 (
    echo [ADVERTENCIA] Compilacion parcial - algunos compiladores fallaron
) else (
    echo [ERROR] Error total - ningun compilador exitoso
)

echo.
pause