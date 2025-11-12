@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" x64

if not exist build_test mkdir build_test

echo.
echo === Compilando test_atoull_ct.cpp ===
cl /EHsc /std:c++latest /W4 /I include test_atoull_ct.cpp /Fe:build_test\test_atoull_ct.exe

if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Compilacion fallida
    pause
    exit /b 1
)

echo.
echo === Ejecutando test ===
.\build_test\test_atoull_ct.exe

echo.
pause
