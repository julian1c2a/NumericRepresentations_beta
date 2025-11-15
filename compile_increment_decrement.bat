@echo off
REM Test operadores de incremento y decremento (++ y --)

where cl >nul 2>&1
if errorlevel 1 (
    echo Configurando entorno Visual Studio...
    call setup_compilers.bat >nul 2>&1
)

echo.
echo ╔═══════════════════════════════════════════════════════════════╗
echo ║       TESTING OPERADORES ++ Y -- (PRE Y POST)                ║
echo ╚═══════════════════════════════════════════════════════════════╝
echo.

cl /std:c++latest /EHsc /Fe:tests\test_increment_decrement_msvc.exe tests\test_increment_decrement.cpp /I.
if errorlevel 1 (
    echo ❌ Compilación falló
    exit /b 1
)

echo ✅ Compilación exitosa
echo.

tests\test_increment_decrement_msvc.exe
if errorlevel 1 (
    echo ❌ Tests fallaron
    exit /b 1
)

echo.
echo ✅ Todos los tests pasaron
