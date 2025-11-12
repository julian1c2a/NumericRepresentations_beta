@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" x64

if not exist build_test mkdir build_test

echo.
echo === Compilando test_atoull_limits.cpp ===
cl /EHsc /std:c++latest /I include test_atoull_limits.cpp /Fe:build_test\\test_atoull_limits.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === EJECUTANDO TEST ===
    build_test\\test_atoull_limits.exe
) else (
    echo ERROR EN COMPILACION
    exit /b 1
)

pause
