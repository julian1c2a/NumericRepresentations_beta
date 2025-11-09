@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" x64

echo.
echo === Compilando test_auxiliary_functions.cpp ===
cl /EHsc /std:c++latest tests\\test_auxiliary_functions.cpp /Fe:build_test\\test_auxiliary_functions.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === Ejecutando test básico ===
    test_auxiliary_functions.exe
) else (
    echo Error en compilacion
)

pause