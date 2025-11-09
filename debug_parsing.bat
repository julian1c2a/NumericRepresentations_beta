@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

echo.
echo === Compilando debug_parsing.cpp ===
cl /EHsc /std:c++latest /I.\include debug_parsing.cpp /Fe:debug_parsing_msvc.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === Ejecutando debug ===
    debug_parsing_msvc.exe
) else (
    echo Error en compilacion
)

pause