@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

echo.
echo === Compilando test_clean.cpp ===
cl /EHsc /std:c++latest test_clean.cpp /Fe:test_clean.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === Ejecutando test limpio ===
    test_clean.exe
) else (
    echo Error en compilacion
)

pause