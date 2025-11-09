@echo off
echo === Configuración Permanente de Entorno Multi-Compilador ===
echo.

REM Agregar MSYS2 al PATH del sistema de forma permanente
echo [1/3] Configurando PATH del sistema...
setx PATH "%PATH%;C:\msys2\ucrt64\bin" >nul 2>&1

REM Crear variables de entorno para los compiladores
echo [2/3] Configurando variables de entorno...
setx MSVC_PATH "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" >nul 2>&1
setx GCC_PATH "C:\msys2\ucrt64\bin\g++.exe" >nul 2>&1
setx CLANG_PATH "C:\msys2\ucrt64\bin\clang++.exe" >nul 2>&1

REM Verificar instalación
echo [3/3] Verificando compiladores...
echo.

echo Configurando entorno temporal para verificación...
set "PATH=C:\msys2\ucrt64\bin;%PATH%"
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64 >nul 2>&1

echo MSVC:
where cl >nul 2>&1 && echo   ✅ Encontrado en: & where cl || echo   ❌ No encontrado

echo.
echo GCC:  
where g++ >nul 2>&1 && echo   ✅ Encontrado en: & where g++ || echo   ❌ No encontrado

echo.  
echo Clang:
where clang++ >nul 2>&1 && echo   ✅ Encontrado en: & where clang++ || echo   ❌ No encontrado

echo.
echo === Configuración Completada ===
echo.
echo Entorno multi-compilador configurado exitosamente.
echo Reinicia la terminal para que los cambios surtan efecto.
echo.
echo Scripts disponibles:
echo   • compile_multi.bat - Compilación con múltiples compiladores
echo   • setup_compilers.bat - Configuración de entorno temporal
echo.

pause