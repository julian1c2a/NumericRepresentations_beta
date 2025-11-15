@echo off
REM Script de compilación para test_make_digit.cpp (MSVC)

echo.
echo ========================================================================
echo           TEST FUNCIONES LIBRES make_digit()
echo ========================================================================
echo.

REM Verificar si cl.exe está disponible
where cl.exe >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo No se encontro cl.exe, configurando Visual Studio...
    call setup_compilers.bat
)

echo Compilando test_make_digit.cpp...
cl /std:c++latest /EHsc /W4 /I"include" /I"include/core" ^
   /Fe"tests\test_make_digit_msvc.exe" ^
   /Fo"tests\\" ^
   tests\test_make_digit.cpp

if %ERRORLEVEL% EQU 0 (
    echo ✓ Compilación exitosa
    echo.
    echo Ejecutando tests...
    tests\test_make_digit_msvc.exe
    
    if %ERRORLEVEL% EQU 0 (
        echo.
        echo ✓ Todos los tests pasaron
    ) else (
        echo.
        echo ✗ Los tests fallaron
        exit /b 1
    )
) else (
    echo ✗ Error de compilación
    exit /b 1
)
