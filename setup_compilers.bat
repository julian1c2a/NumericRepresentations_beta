@echo off
echo === Configurando entorno multi-compilador ===

REM Agregar MSYS2 al PATH
set "PATH=C:\msys64\ucrt64\bin;%PATH%"

echo === Versiones de compiladores disponibles ===
echo.
echo [MSVC] Configurando Visual Studio 2022...
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64 >nul 2>&1

echo MSVC:
cl 2>&1 | findstr "Compilador"

echo.
echo GCC:
gcc --version | head -1

echo.
echo Clang:
clang++ --version | head -1

echo.
echo === Entorno configurado ===
echo Compiladores disponibles: MSVC, GCC, Clang
echo Use compile_multi.bat para probar con todos los compiladores