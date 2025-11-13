@echo off
REM ===================================================================
REM Script de compilación para test_boolean_queries.cpp
REM Tests exhaustivos de las 16 funciones de consulta booleanas
REM ===================================================================

echo.
echo =====================================================
echo Compilando test_boolean_queries.cpp con MSVC
echo =====================================================
echo.

REM Configurar entorno MSVC si no está configurado
where cl >nul 2>&1
if errorlevel 1 (
    echo Configurando entorno Visual Studio...
    call setup_compilers.bat >nul 2>&1
)

REM Compilar con MSVC
cl /std:c++latest /W4 /EHsc /Fe:"test_boolean_queries_msvc.exe" tests\test_boolean_queries.cpp
if errorlevel 1 (
    echo.
    echo ERROR: La compilacion fallo
    exit /b 1
)

echo.
echo =====================================================
echo Compilacion exitosa. Ejecutando tests...
echo =====================================================
echo.

REM Ejecutar tests
test_boolean_queries_msvc.exe
if errorlevel 1 (
    echo.
    echo ERROR: Algunos tests fallaron
    exit /b 1
)

echo.
echo =====================================================
echo TODOS LOS TESTS PASARON EXITOSAMENTE
echo =====================================================
echo.
