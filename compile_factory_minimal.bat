@echo off
rem Compilador MSVC para test_int_factory_minimal.cpp
echo Configurando entorno MSVC...

rem Inicializar Visual Studio environment
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1

rem Si no funciona, probar otros paths comunes
if errorlevel 1 (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1
)

rem Verificar que cl está disponible
where cl >nul 2>&1
if errorlevel 1 (
    echo ERROR: Compilador MSVC no encontrado
    echo Por favor, ejecute desde Developer Command Prompt
    pause
    exit /b 1
)

echo Compilando test_int_factory_minimal.cpp...
cl /std:c++20 /EHsc /I"include" test_int_factory_minimal.cpp /Fe:test_int_factory_minimal.exe

if errorlevel 1 (
    echo ERROR: Compilacion fallida
    pause
    exit /b 1
) else (
    echo Compilacion exitosa!
    echo Ejecutando test_int_factory_minimal.exe...
    echo.
    test_int_factory_minimal.exe
)

pause