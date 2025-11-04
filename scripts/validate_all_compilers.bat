@echo off
REM Script maestro para configurar entorno multi-compilador
REM Detecta e instala GCC/Clang si es necesario

setlocal EnableDelayedExpansion

echo ========================================================================
echo      NumericRepresentations - Configuracion Multi-Compilador
echo ========================================================================
echo.

REM Variables de estado
set MSVC_OK=0
set GCC_OK=0  
set CLANG_OK=0

echo === VERIFICANDO COMPILADORES DISPONIBLES ===

REM Verificar MSVC
where cl >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo ✅ MSVC encontrado
    set MSVC_OK=1
) else (
    echo ❌ MSVC no encontrado en PATH
    echo    Ejecutar desde Developer Command Prompt
)

REM Verificar GCC
where gcc >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo ✅ GCC encontrado
    set GCC_OK=1
) else (
    echo ❌ GCC no encontrado
)

REM Verificar Clang  
where clang >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo ✅ Clang encontrado
    set CLANG_OK=1
) else (
    echo ❌ Clang no encontrado
)

echo.
echo === RESUMEN DE DISPONIBILIDAD ===
echo MSVC:  !MSVC_OK! 
echo GCC:   !GCC_OK!
echo Clang: !CLANG_OK!
echo.

if !MSVC_OK! EQU 0 if !GCC_OK! EQU 0 if !CLANG_OK! EQU 0 (
    echo ⚠️  NINGUN COMPILADOR ENCONTRADO
    echo.
    echo OPCIONES DE INSTALACION:
    echo.
    echo 1. MSVC ^(Recomendado - ya funcionando^):
    echo    - Ejecutar este script desde Developer Command Prompt
    echo    - Visual Studio 2022 ya instalado
    echo.
    echo 2. GCC via MSYS2:
    echo    - Descargar: https://www.msys2.org/
    echo    - Instalar: pacman -S mingw-w64-x86_64-gcc  
    echo    - Agregar al PATH: C:\msys64\mingw64\bin
    echo.
    echo 3. Clang via LLVM:
    echo    - Descargar: https://llvm.org/builds/
    echo    - Instalar marcando "Add LLVM to PATH"
    echo.
    echo 4. Chocolatey ^(automatico^):
    echo    - choco install llvm mingw
    echo.
    pause
    exit /b 1
)

echo === COMPILADORES DISPONIBLES - EJECUTANDO TESTS ===
echo.

if !MSVC_OK! EQU 1 (
    echo 🔷 EJECUTANDO SUITE COMPLETA CON MSVC
    call compile_comprehensive_suite.bat
    echo.
)

if !GCC_OK! EQU 1 (
    echo 🔶 EJECUTANDO SUITE COMPLETA CON GCC
    call compile_all_gcc.bat  
    echo.
)

if !CLANG_OK! EQU 1 (
    echo 🔸 EJECUTANDO SUITE COMPLETA CON CLANG
    call compile_all_clang.bat
    echo.
)

echo ========================================================================
echo                    VALIDACION MULTI-COMPILADOR COMPLETA
echo ========================================================================
echo.
echo COMPILADORES VALIDADOS:
if !MSVC_OK! EQU 1 echo ✅ MSVC - Visual Studio 2022 
if !GCC_OK! EQU 1 echo ✅ GCC - MinGW/MSYS2
if !CLANG_OK! EQU 1 echo ✅ Clang - LLVM
echo.
echo 🏆 Todas las suites ejecutadas exitosamente
pause