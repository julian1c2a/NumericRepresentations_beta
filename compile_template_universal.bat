@echo off
REM Universal compile script: compile_template_universal.bat <fuente.cpp> [gcc|clang|msvc]
REM Si no se especifica compilador, usa MSVC por defecto

setlocal
set SRC=tests\%1
set COMPILER=%2
if "%COMPILER%"=="" set COMPILER=msvc
set BASE=%~n1
set EXE=%BASE%_%COMPILER%.exe

if not exist %SRC% (
    echo Error: No se encuentra el archivo %SRC%
    exit /b 1
)

if /I "%COMPILER%"=="msvc" goto :msvc
if /I "%COMPILER%"=="gcc" goto :gcc
if /I "%COMPILER%"=="clang" goto :clang
goto :error

:msvc
REM Configurar entorno MSVC si es necesario
where cl.exe >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo Configurando entorno Visual Studio...
    call setup_compilers.bat
)
cl /std:c++latest /EHsc /Iinclude /W4 /Fe:%EXE% %SRC%
if %ERRORLEVEL% NEQ 0 exit /b 1
%EXE%
goto :EOF

:gcc
where g++ >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo Error: g++ no encontrado en PATH
    exit /b 1
)
g++ -std=c++23 -Wall -Iinclude -o %EXE% %SRC%
if %ERRORLEVEL% NEQ 0 exit /b 1
%EXE%
goto :EOF

:clang
where clang++ >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo Error: clang++ no encontrado en PATH
    exit /b 1
)
clang++ -std=c++23 -Wall -Iinclude -o %EXE% %SRC%
if %ERRORLEVEL% NEQ 0 exit /b 1
%EXE%
goto :EOF

:error
echo Compilador no reconocido: %COMPILER%
exit /b 1
endlocal
