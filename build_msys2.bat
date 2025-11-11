@echo off
SETLOCAL

REM --- CONFIGURACIÓN ---
REM Edita esta línea con la ruta a tu instalación de MSYS2
SET MSYS2_PATH=C:\msys64
SET COMPILER=%1
SET TEMP_SCRIPT_NAME=tmp_msys2_build.sh

IF NOT DEFINED COMPILER (
    ECHO Uso: %0 [gcc ^| clang]
    GOTO :EOF
)

ECHO Compilando con %COMPILER% en MSYS2...

SET CXX_COMPILER=%COMPILER%++
IF %COMPILER%==gcc (SET C_COMPILER=gcc)
IF %COMPILER%==clang (SET C_COMPILER=clang)

REM --- Crear el script de shell temporal ---
(
    ECHO #!/bin/bash
    ECHO set -e
    ECHO echo "--- Configurando y Compilando para %COMPILER% ---"
    ECHO BUILD_DIR="build-%COMPILER%"
    ECHO rm -rf "$BUILD_DIR"
    ECHO cmake -B "$BUILD_DIR" -S . -G "MinGW Makefiles" -D CMAKE_C_COMPILER=%C_COMPILER% -D CMAKE_CXX_COMPILER=%CXX_COMPILER%
    ECHO cmake --build "$BUILD_DIR"
    ECHO echo "--- Ejecutando Pruebas ---"
    ECHO cd "$BUILD_DIR"
    ECHO ctest --output-on-failure
) > %TEMP_SCRIPT_NAME%

REM --- Ejecutar el script de shell a través de MSYS2 ---
REM El shell de MSYS2 se inicia en el home, por lo que debemos cambiar al directorio del proyecto.
REM Pasamos la ruta de Windows directamente entre comillas simples, bash la interpreta correctamente.
SET "COMMAND_TO_RUN=cd '%CD%' && bash ./%TEMP_SCRIPT_NAME%"

%MSYS2_PATH%\mingw64.exe -c "%COMMAND_TO_RUN%"

REM --- Limpieza ---
IF EXIST %TEMP_SCRIPT_NAME% (
    DEL %TEMP_SCRIPT_NAME%
)

ECHO.
ECHO Proceso completado.

ENDLOCAL
