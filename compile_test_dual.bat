@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

echo.
echo === Compilando test_dual_format.cpp ===
cl /EHsc /std:c++latest /I.\include test_dual_format.cpp /Fe:test_dual_format.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === Ejecutando test ===
    test_dual_format.exe
) else (
    echo Error en compilacion
)

pause