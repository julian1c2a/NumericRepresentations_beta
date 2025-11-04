@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

echo.
echo === Compilando test_basic.cpp ===
cl /EHsc /std:c++latest test_basic.cpp /Fe:test_basic.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === Ejecutando test básico ===
    test_basic.exe
) else (
    echo Error en compilacion
)

pause