@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

echo.
echo === Compilando test_dig_array.cpp ===
cl /EHsc /std:c++latest /I.\include test_dig_array.cpp /Fe:test_dig_array_msvc.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === Ejecutando test de dig_t como building block ===
    test_dig_array_msvc.exe
) else (
    echo Error en compilacion
)

pause