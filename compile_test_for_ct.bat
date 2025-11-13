@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

echo.
echo === Compilando test_dig_t_basic_construct.cpp ===
cl /EHsc /std:c++latest /W4 /I"include/core" /I"include/core/internal" tests\test_dig_t_basic_construct.cpp /Fe:tests\test_dig_t_basic_construct_msvc.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === Compilacion exitosa ===
    echo Ejecutando test...
    echo.
    tests\test_dig_t_basic_construct_msvc.exe
) else (
    echo Error en compilacion
)

pause
