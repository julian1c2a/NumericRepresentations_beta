@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

echo.
echo === Compilando test_mult_inv_optimized.cpp ===
cl /EHsc /std:c++latest /W4 /I"include/core" /I"include/core/internal" tests\test_mult_inv_optimized.cpp /Fe:tests\test_mult_inv_optimized_msvc.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === Compilacion exitosa ===
    echo Ejecutando test...
    echo.
    tests\test_mult_inv_optimized_msvc.exe
    echo.
    if %ERRORLEVEL% EQU 0 (
        echo === Test completado exitosamente ===
    ) else (
        echo === Test FAILED con codigo %ERRORLEVEL% ===
    )
) else (
    echo Error en compilacion
)

pause
