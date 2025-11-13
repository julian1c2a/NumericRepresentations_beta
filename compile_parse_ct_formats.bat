@echo off
REM ============================================================================
REM Script de compilación para test_parse_ct_formats.cpp
REM Objetivo: Verificar los 4 formatos de parse_impl_ct (compile-time parser)
REM ============================================================================

REM Configurar entorno MSVC si no está configurado
where cl >nul 2>&1
if errorlevel 1 (
    echo Configurando entorno Visual Studio...
    call setup_compilers.bat >nul 2>&1
)

echo.
echo ╔═══════════════════════════════════════════════════════════════╗
echo ║      COMPILANDO TEST DE parse_impl_ct (4 FORMATOS)           ║
echo ╚═══════════════════════════════════════════════════════════════╝
echo.

REM Compilar con MSVC
cl /std:c++latest /W4 /EHsc /Fe:tests\test_parse_ct_formats_msvc.exe tests\test_parse_ct_formats.cpp /I.
if errorlevel 1 (
    echo.
    echo ❌ ERROR: La compilación falló
    exit /b 1
)

echo.
echo ✅ Compilación exitosa
echo.
echo ╔═══════════════════════════════════════════════════════════════╗
echo ║         EJECUTANDO TESTS DE parse_impl_ct (4 FORMATOS)       ║
echo ╚═══════════════════════════════════════════════════════════════╝
echo.

REM Ejecutar tests
tests\test_parse_ct_formats_msvc.exe
if errorlevel 1 (
    echo.
    echo ❌ Los tests fallaron
    exit /b 1
)

echo.
echo ✅✅✅ TODOS LOS TESTS PASARON EXITOSAMENTE ✅✅✅
