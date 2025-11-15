@echo off
REM Compila y ejecuta test_core_internal_comprehensive.cpp con el compilador especificado (msvc, g++, clang++)
REM Uso: compile_core_internal_comprehensive.bat [msvc|g++|clang++]
setlocal
set SRC=test_core_internal_comprehensive.cpp
set EXE=test_core_internal_comprehensive.exe
set OUT=tests\%EXE%
set COMPILER=%1
if "%COMPILER%"=="" set COMPILER=msvc

if /I "%COMPILER%"=="msvc" goto :msvc
if /I "%COMPILER%"=="g++" goto :gpp
if /I "%COMPILER%"=="clang++" goto :clang
goto :error

:msvc
REM Ruta típica de cl.exe (ajustar si es necesario)

set "CL_PATH=D:\program files\microsoft visual studio\2022\community\VC\Tools\MSVC\*\bin\Hostx64\x64"
set "PATH=%CL_PATH%;%PATH%"
echo Compilando con MSVC (cl.exe)...
cl /std:c++latest /EHsc /Iinclude /Itests /Ilocal_libs/include /Fe:%OUT% tests\%SRC% /link /out:%OUT%
if errorlevel 1 exit /b 1
%OUT%
goto :EOF

:gpp

set "GPP_PATH=C:\mingw64\ucrt64\bin"
set "PATH=%GPP_PATH%;%PATH%"
echo Compilando con g++...
g++ -std=c++23 -Iinclude -Itests -Ilocal_libs/include -o %OUT% tests\%SRC%
if errorlevel 1 exit /b 1
%OUT%
goto :EOF

:clang

set "CLANG_PATH=C:\mingw64\ucrt64\bin"
set "PATH=%CLANG_PATH%;%PATH%"
echo Compilando con clang++...
clang++ -std=c++23 -Iinclude -Itests -Ilocal_libs/include -o %OUT% tests\%SRC%
if errorlevel 1 exit /b 1
%OUT%
goto :EOF

:error
echo Compilador no reconocido: %COMPILER%
echo Uso: %0 [msvc|g++|clang++]
exit /b 1
endlocal
