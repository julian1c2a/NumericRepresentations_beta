@echo off
echo === Probando compilacion con GCC ===
c:\msys64\ucrt64\bin\g++.exe -std=c++20 -I.\include test_dual_verbose.cpp -o test_dual_verbose_gcc.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === Ejecutando test con GCC ===
    test_dual_verbose_gcc.exe
) else (
    echo Error en compilacion con GCC
)

pause