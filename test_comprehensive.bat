@echo off
echo === Test Comprehensivo de Formato Dual I/O ===
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

echo.
echo === Compilando test_dual_format_comprehensive.cpp ===
cl /EHsc /std:c++latest /I.\include test_dual_format_comprehensive.cpp /Fe:test_dual_comprehensive.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === Ejecutando Test Comprehensivo ===
    test_dual_comprehensive.exe
) else (
    echo Error en compilacion
)

pause