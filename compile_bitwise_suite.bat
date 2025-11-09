@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

echo.
echo === Compilando test_dig_t_bitwise.cpp ===
cl /EHsc /std:c++latest /I.\include tests\test_dig_t_bitwise.cpp /Fe:tests\test_dig_t_bitwise_msvc.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === Ejecutando suite de tests bitwise/matematicos ===
    tests\test_dig_t_bitwise_msvc.exe
) else (
    echo Error en compilacion
)

pause