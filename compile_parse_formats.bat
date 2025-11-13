@echo off
REM Script de compilación para test_parse_formats.cpp
REM Configura el entorno MSVC y compila/ejecuta el test

REM Configurar entorno MSVC si no está configurado
where cl >nul 2>&1
if errorlevel 1 (
    echo Configurando entorno Visual Studio...
    call setup_compilers.bat >nul 2>&1
)

echo.
echo ╔═══════════════════════════════════════════════════════════════╗
echo ║           COMPILANDO TEST DE FORMATOS DE PARSING             ║
echo ╚═══════════════════════════════════════════════════════════════╝
echo.

REM Compilar el test
cl /EHsc /std:c++latest /Fe:tests\test_parse_formats_msvc.exe tests\test_parse_formats.cpp /I. 2>&1

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ❌ ERROR: La compilación falló
    exit /b 1
)

echo.
echo ✅ Compilación exitosa
echo.
echo ╔═══════════════════════════════════════════════════════════════╗
echo ║                EJECUTANDO TESTS DE PARSING                    ║
echo ╚═══════════════════════════════════════════════════════════════╝
echo.

REM Ejecutar el test
tests\test_parse_formats_msvc.exe

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ❌ Los tests fallaron
    exit /b 1
)

echo.
echo ✅ Todos los tests pasaron exitosamente
