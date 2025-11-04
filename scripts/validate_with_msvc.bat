@echo off
REM Script para ejecutar validacion desde Developer Command Prompt
echo === Configurando entorno Visual Studio ===
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

echo.
echo === Ejecutando validacion multi-compilador ===  
call validate_all_compilers.bat