@echo off
REM Script debug para ver errores de compilacion GCC
echo === DEBUG COMPILACION GCC ===

echo Probando compilacion simple con GCC...
echo Comando: c:\msys64\ucrt64\bin\g++.exe -std=c++20 -I../include ../tests/test_dig_t_arithmetic.cpp -o ../tests/test_debug_gcc.exe

c:\msys64\ucrt64\bin\g++.exe -std=c++20 -I../include ../tests/test_dig_t_arithmetic.cpp -o ../tests/test_debug_gcc.exe

echo Error level: %ERRORLEVEL%
echo.

if exist "../tests/test_debug_gcc.exe" (
    echo ✅ Compilacion exitosa! Ejecutando...
    ..\tests\test_debug_gcc.exe
) else (
    echo ❌ Compilacion fallo
)

pause