@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

echo.
echo === Compilando test_advanced_edge_cases.cpp ===
cl /EHsc /std:c++latest /I.\include test_advanced_edge_cases.cpp /Fe:test_advanced_edge_cases_msvc.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === Ejecutando test avanzado de casos edge ===
    test_advanced_edge_cases_msvc.exe
) else (
    echo Error en compilacion
)

pause