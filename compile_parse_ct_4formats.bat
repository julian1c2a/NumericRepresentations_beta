@echo off
REM Test parse_impl_ct con 4 formatos

where cl >nul 2>&1
if errorlevel 1 (
    echo Configurando entorno Visual Studio...
    call setup_compilers.bat >nul 2>&1
)

echo.
echo ╔═══════════════════════════════════════════════════════════════╗
echo ║         TESTING parse_impl_ct - 4 FORMATOS                   ║
echo ╚═══════════════════════════════════════════════════════════════╝
echo.

cl /std:c++latest /EHsc /Fe:tests\test_parse_ct_4formats_msvc.exe tests\test_parse_ct_4formats.cpp /I.
if errorlevel 1 (
    echo ❌ Compilación falló
    exit /b 1
)

echo ✅ Compilación exitosa
echo.

tests\test_parse_ct_4formats_msvc.exe
if errorlevel 1 (
    echo ❌ Tests fallaron
    exit /b 1
)

echo.
echo ✅ Todos los tests pasaron
