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

REM Encadenar todos los comandos. Se añade "-G Ninja" para coincidir con CMakeSettings.json
cmd /c "%VCVARS_PATH% x64 && echo. && echo --- Limpiando y Configurando con Ninja --- && rmdir /s /q %BUILD_DIR% 2>nul & cmake -B %BUILD_DIR% -S . -G Ninja && echo. && echo --- Compilando --- && cmake --build %BUILD_DIR% --config Release && echo. && echo --- Probando --- && cd %BUILD_DIR% && ctest -C Release --output-on-failure"

ECHO.
ECHO Proceso completado.

ENDLOCAL
