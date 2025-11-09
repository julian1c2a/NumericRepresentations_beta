@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

echo.
echo === Compilando test_dig_t_basic_construct.cpp ===
cl /EHsc /std:c++latest /I.\include tests\test_dig_t_basic_construct.cpp /Fe:tests\test_dig_t_basic_construct_msvc.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === Ejecutando test ===
    tests\test_dig_t_basic_construct_msvc.exe
) else (
    echo Error en compilacion
)

pause