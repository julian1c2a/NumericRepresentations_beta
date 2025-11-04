@echo off
REM NumericRepresentations - MSVC Build Script
REM Configura y compila usando Visual Studio Community 2022

echo.
echo ==========================================
echo  NumericRepresentations - MSVC Build
echo ==========================================
echo.

REM Configurar entorno de Visual Studio
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: No se pudo configurar el entorno de Visual Studio
    pause
    exit /b 1
)

echo Entorno de Visual Studio configurado correctamente.
echo.

REM Crear directorio de build si no existe
if not exist "build_msvc" mkdir build_msvc
cd build_msvc

echo Configurando proyecto con CMake para MSVC...
cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Debug ..
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Fallo en la configuración de CMake
    cd ..
    pause
    exit /b 1
)

echo.
echo Compilando proyecto...
cmake --build . --config Debug
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Fallo en la compilación
    cd ..
    pause
    exit /b 1
)

echo.
echo ==========================================
echo  Compilación MSVC completada exitosamente
echo ==========================================
echo.

cd ..

REM Probar compilación individual de dig_t.hpp
echo Probando compilación individual de dig_t.hpp...
cl /std:c++23 /I.\include /EHsc /W4 /permissive- /c include\dig_t.hpp /Fo:dig_t_msvc_test.obj
if %ERRORLEVEL% EQU 0 (
    echo ✓ dig_t.hpp compilado exitosamente con MSVC
    del dig_t_msvc_test.obj
) else (
    echo ✗ Error compilando dig_t.hpp con MSVC
)

echo.
pause