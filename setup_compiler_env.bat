@echo off
REM Script para configurar el entorno de compiladores (g++, clang++, MSVC)
REM Uso: call setup_compiler_env.bat [g++|clang++|msvc]
setlocal
set COMPILER=%1
if "%COMPILER%"=="" set COMPILER=g++

if /I "%COMPILER%"=="g++" goto :gpp
if /I "%COMPILER%"=="clang++" goto :clang
if /I "%COMPILER%"=="msvc" goto :msvc

goto :error

:gpp
set "PATH=C:\mingw64\ucrt64\bin;%PATH%"
echo [setup] Entorno configurado para g++ (MinGW-w64 UCRT64)
goto :EOF

:clang
set "PATH=C:\mingw64\ucrt64\bin;%PATH%"
echo [setup] Entorno configurado para clang++ (MinGW-w64 UCRT64)
goto :EOF

:msvc
REM NOTA: Para MSVC, se recomienda abrir el Developer Command Prompt de Visual Studio.
echo [setup] Para MSVC, abre el Developer Command Prompt de Visual Studio.
goto :EOF

:error
echo Compilador no reconocido: %COMPILER%
echo Uso: call setup_compiler_env.bat [g++|clang++|msvc]
endlocal
exit /b 1
