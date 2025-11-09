@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

echo.
echo === Compilando test_dig_t_io_simple.cpp ===
cl /EHsc /std:c++latest /I../include ../tests/test_dig_t_io_simple.cpp /Fo:../test_dig_t_io_simple.obj /Fe:../tests/test_dig_t_io_simple_msvc.exe

echo.
echo === Ejecutando suite de tests I/O simplificado ===
..\tests\test_dig_t_io_simple_msvc.exe
pause