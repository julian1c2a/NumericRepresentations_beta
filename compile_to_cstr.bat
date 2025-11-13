@echo off
REM Script de compilación para test_to_cstr.cpp
REM Tests de serialización consteval

REM Configurar entorno MSVC si no está configurado
where cl >nul 2>&1
if errorlevel 1 (
    echo Configurando entorno Visual Studio...
    call setup_compilers.bat >nul 2>&1
)

echo.
echo ╔═══════════════════════════════════════════════════════════════╗
echo ║         COMPILANDO TEST DE to_cstr() CONSTEVAL               ║
echo ╚═══════════════════════════════════════════════════════════════╝
echo.

REM Compilar con MSVC
cl /std:c++latest /W4 /EHsc /Fe:tests\test_to_cstr_msvc.exe tests\test_to_cstr.cpp /I.
if errorlevel 1 (
    echo.
    echo ❌ ERROR: La compilación falló
    exit /b 1
)

echo.
echo ✅ Compilación exitosa
echo.
echo ╔═══════════════════════════════════════════════════════════════╗
echo ║              EJECUTANDO TESTS DE to_cstr()                   ║
echo ╚═══════════════════════════════════════════════════════════════╝
echo.

REM Ejecutar tests
tests\test_to_cstr_msvc.exe
if errorlevel 1 (
    echo.
    echo ❌ Los tests fallaron
    exit /b 1
)

echo.
echo ✅ Todos los tests pasaron exitosamente
