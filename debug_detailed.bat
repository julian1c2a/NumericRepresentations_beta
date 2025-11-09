@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

echo.
echo === Compilando debug_parsing_detailed.cpp ===
cl /EHsc /std:c++latest /I.\include debug_parsing_detailed.cpp /Fe:debug_parsing_detailed_msvc.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === Ejecutando investigación detallada ===
    debug_parsing_detailed_msvc.exe
) else (
    echo Error en compilacion
)

pause