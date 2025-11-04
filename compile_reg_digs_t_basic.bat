@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

echo.
echo === Compilando test_reg_digs_t_basic.cpp ===
cl /EHsc /std:c++latest /I.\include test_reg_digs_t_basic.cpp /Fe:test_reg_digs_t_basic_msvc.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === Ejecutando test suite basico de reg_digs_t ===
    test_reg_digs_t_basic_msvc.exe
) else (
    echo Error en compilacion
)

pause