@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

echo.
echo === Compilando test_iostream_only.cpp ===
cl /EHsc /std:c++latest tests\test_iostream_only.cpp /Fe:tests\test_iostream_only_msvc.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === Ejecutando test ===
    tests\test_iostream_only_msvc.exe
) else (
    echo Error en compilacion
)

pause