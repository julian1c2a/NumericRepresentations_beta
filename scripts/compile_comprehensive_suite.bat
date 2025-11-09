@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

echo.
echo === Compilando test_dig_t_comprehensive.cpp ===
cl /EHsc /std:c++latest /I../include ../tests/test_dig_t_comprehensive.cpp /Fo:../test_dig_t_comprehensive.obj /Fe:../tests/test_dig_t_comprehensive_msvc.exe

echo.
echo === Ejecutando suite comprehensive final ===
..\tests\test_dig_t_comprehensive_msvc.exe
pause