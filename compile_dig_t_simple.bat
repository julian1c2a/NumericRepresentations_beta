@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

echo.
echo === Compilando test_very_simple.cpp ===
cl /EHsc /std:c++latest /I.\include tests\test_very_simple.cpp /Fe:tests\test_very_simple_msvc.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === Ejecutando test ===
    tests\test_very_simple_msvc.exe
) else (
    echo Error en compilacion
)

pause