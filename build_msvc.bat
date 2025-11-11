@echo off
SETLOCAL

REM --- build_msvc.bat (Versión 4.0 - Usando Ninja) ---

ECHO --- Buscando el entorno de Visual Studio... ---

REM Localizar vswhere.exe
SET VSWHERE_PATH="%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
IF NOT EXIST %VSWHERE_PATH% (
    ECHO Error: No se pudo encontrar vswhere.exe.
    GOTO :EOF
)

REM Localizar vcvarsall.bat usando vswhere
FOR /f "usebackq tokens=*" %%i IN (`%VSWHERE_PATH% -latest -property installationPath`) DO (
    SET VS_INSTALL_PATH=%%i
)
SET VCVARS_PATH="%VS_INSTALL_PATH%\VC\Auxiliary\Build\vcvarsall.bat"
IF NOT EXIST %VCVARS_PATH% (
    ECHO Error: No se encontro vcvarsall.bat.
    GOTO :EOF
)

ECHO --- Preparando la cadena de comandos para MSVC (x64) con Ninja... ---
SET BUILD_DIR=build-msvc

REM Encadenar todos los comandos. La configuración solo se ejecuta si el directorio no existe.
cmd /c "%VCVARS_PATH% x64 && echo. && (if not exist %BUILD_DIR% (echo --- Configurando para Ninja por primera vez --- && cmake -B %BUILD_DIR% -S . -G Ninja)) && echo. && echo --- Compilando (solo los archivos modificados) --- && cmake --build %BUILD_DIR% --config Release && echo. && echo --- Probando --- && cd %BUILD_DIR% && ctest -C Release --output-on-failure"

ECHO.
ECHO Proceso completado.

ENDLOCAL
