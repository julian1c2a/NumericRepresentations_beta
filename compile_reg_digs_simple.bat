@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

echo.
echo === Compilando test_reg_digs_simple.cpp ===
cl /EHsc /std:c++latest /I.\include test_reg_digs_simple.cpp /Fe:test_reg_digs_simple_msvc.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === Ejecutando test simple de reg_digs ===
    test_reg_digs_simple_msvc.exe
) else (
    echo Error en compilacion
)

pause