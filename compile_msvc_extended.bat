@echo off
REM ======================================================================
REM Script de compilación MSVC con flags extendidos para template metaprogramming
REM Aumenta límites de profundidad y iteraciones para templates complejos
REM ======================================================================

setlocal EnableDelayedExpansion

if "%1"=="" (
    echo Uso: compile_msvc_extended.bat ^<archivo.cpp^> [nombre_ejecutable]
    echo.
    echo Este script utiliza flags extendidos de MSVC para template metaprogramming:
    echo   /constexpr:depth2048     - Máxima profundidad de constexpr
    echo   /constexpr:backtrace64   - Marcos de backtrace constexpr
    echo   /constexpr:steps1048576  - Máximo pasos de evaluación constexpr
    echo   /bigobj                  - Objetos grandes (.obj)
    echo   /Zc:preprocessor         - Preprocesador conforme C++20
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

REM Configurar entorno MSVC
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64 >nul 2>&1

echo ======================================================================
echo Compilando %SOURCE_FILE% con MSVC - FLAGS EXTENDIDOS PARA TEMPLATES
echo ======================================================================
echo.

REM Flags básicos
set "BASIC_FLAGS=/EHsc /std:c++latest /I.\include"

REM Flags extendidos para template metaprogramming
set "EXTENDED_FLAGS=/constexpr:depth2048 /constexpr:backtrace64 /constexpr:steps1048576"

REM Flags adicionales de optimización y compatibilidad
set "EXTRA_FLAGS=/bigobj /Zc:preprocessor /permissive-"

REM Combinación completa
set "MSVC_FLAGS=%BASIC_FLAGS% %EXTENDED_FLAGS% %EXTRA_FLAGS%"

echo Flags utilizados:
echo   Básicos:     %BASIC_FLAGS%
echo   Templates:   %EXTENDED_FLAGS%  
echo   Extras:      %EXTRA_FLAGS%
echo.

echo Compilando con límites extendidos...
echo ----------------------------------------------------------------------

cl %MSVC_FLAGS% "%SOURCE_FILE%" /Fe:"%BASE_NAME%_msvc_extended.exe"
set "EXIT_CODE=!ERRORLEVEL!"

echo.
echo ======================================================================
if %EXIT_CODE% EQU 0 (
    echo ✅ ÉXITO: Compilación con flags extendidos exitosa
    echo.
    echo Ejecutable generado: %BASE_NAME%_msvc_extended.exe
    echo.
    echo ¿Ejecutar el programa? (S/N):
    set /p "RUN_PROGRAM="
    if /i "!RUN_PROGRAM!"=="S" (
        echo.
        echo === Ejecutando %BASE_NAME%_msvc_extended.exe ===
        "%BASE_NAME%_msvc_extended.exe"
    )
) else (
    echo ❌ ERROR: Compilación falló incluso con flags extendidos
    echo.
    echo El error indica que el problema puede ser:
    echo   1. Error interno del compilador (C1001) - Bug en MSVC
    echo   2. Template metaprogramming demasiado complejo para MSVC
    echo   3. Incompatibilidad específica con alguna construcción C++20/23
    echo.
    echo Recomendación: Considerar workarounds específicos para MSVC
)

echo ======================================================================
echo.
pause