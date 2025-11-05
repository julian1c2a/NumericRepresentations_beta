@echo off
REM ======================================================================
REM SCRIPT DE COMPILACION ESTANDAR - NumericRepresentations 
REM MSVC con flags extendidos para template metaprogramming avanzado
REM ======================================================================

setlocal EnableDelayedExpansion

if "%1"=="" (
    echo.
    echo ======================================================================
    echo COMPILADOR MSVC EXTENDIDO - NumericRepresentations
    echo ======================================================================
    echo.
    echo Uso: compile_simple_extended.bat ^<archivo.cpp^> [nombre_salida]
    echo.
    echo Este compilador usa flags extendidos automaticamente para resolver:
    echo   * Error C1001 MSVC con template metaprogramming
    echo   * Limitaciones constexpr profundidad/pasos
    echo   * Restricciones objetos .obj complejos
    echo.
    echo Ejemplos:
    echo   compile_simple_extended.bat test_proyecto_final.cpp
    echo   compile_simple_extended.bat mi_codigo.cpp mi_programa
    echo.
    exit /b 1
)

set "SOURCE_FILE=%1"
set "OUTPUT_NAME=%~n1"
if not "%2"=="" set "OUTPUT_NAME=%2"

if not exist "%SOURCE_FILE%" (
    echo ERROR: No se encuentra el archivo %SOURCE_FILE%
    exit /b 1
)

echo.
echo ======================================================================
echo MSVC FLAGS EXTENDIDOS - Template Metaprogramming
echo ======================================================================
echo Archivo: %SOURCE_FILE%
echo Salida:  %OUTPUT_NAME%_extended.exe
echo.

REM Configurar MSVC
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64 >nul 2>&1

echo FLAGS UTILIZADOS:
echo   /constexpr:depth2048     - Profundidad constexpr (512 -^> 2048)
echo   /constexpr:steps1048576  - Pasos constexpr (~1M -^> 1,048,576)  
echo   /bigobj                  - Objetos grandes (sin limite simbolos)
echo   /permissive-             - Conformancia estricta C++
echo   /std:c++latest           - Caracteristicas C++20/23
echo.

REM Flags completos para template metaprogramming avanzado
set "EXTENDED_FLAGS=/EHsc /std:c++latest /I.\include /constexpr:depth2048 /constexpr:steps1048576 /bigobj /permissive-"

echo COMPILANDO...
echo ----------------------------------------------------------------------
cl %EXTENDED_FLAGS% "%SOURCE_FILE%" /Fe:"%OUTPUT_NAME%_extended.exe"
set "COMPILE_RESULT=!ERRORLEVEL!"

echo.
echo ======================================================================
if %COMPILE_RESULT% EQU 0 (
    echo ✓ EXITO: Compilacion exitosa con flags extendidos
    echo ✓ Ejecutable: %OUTPUT_NAME%_extended.exe
    echo.
    echo Para ejecutar usar: %OUTPUT_NAME%_extended.exe
    echo ======================================================================
) else (
    echo × ERROR: Compilacion fallo (Codigo: %COMPILE_RESULT%)
    echo.
    echo POSIBLES CAUSAS:
    echo   - Archivo fuente con errores de sintaxis
    echo   - Dependencias faltantes en include/
    echo   - Template metaprogramming demasiado complejo incluso con flags
    echo.
    echo RECOMENDACION: Verificar codigo fuente y dependencias
    echo ======================================================================
)