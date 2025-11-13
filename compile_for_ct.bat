@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

echo.
echo === Compilando test_for_ct.cpp ===
cl /EHsc /std:c++latest /Iinclude /Itests tests\test_for_ct.cpp tmp\Catch2\extras\catch_amalgamated.cpp /Fe:test_for_ct_msvc.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === Ejecutando tests de for_ct ===
    test_for_ct_msvc.exe
) else (
    echo ERROR: Compilacion fallida
)

pause
