@echo off
REM Compila y ejecuta test_basic_types_comprehensive.cpp con el compilador especificado (msvc, g++, clang++)
REM Uso: compile_basic_types_comprehensive.bat [msvc|g++|clang++]
setlocal
set SRC=test_basic_types_comprehensive.cpp
set EXE=test_basic_types_comprehensive.exe
set OUT=tests\%EXE%
set COMPILER=%1
if "%COMPILER%"=="" set COMPILER=msvc

if /I "%COMPILER%"=="msvc" (
	set "CL_PATH=D:\program files\microsoft visual studio\2022\community\VC\Tools\MSVC\*\bin\Hostx64\x64"
	set "PATH=%CL_PATH%;%PATH%"
	echo Compilando con MSVC (cl.exe)...
	cl /std:c++20 /EHsc /Iinclude /Itests /Fe:%OUT% tests\%SRC% /link /out:%OUT%
	if errorlevel 1 exit /b 1
	%OUT%
	goto :EOF
)

if /I "%COMPILER%"=="g++" (
	set "GPP_PATH=C:\mingw64\ucrt64\bin"
	set "PATH=%GPP_PATH%;%PATH%"
	echo Compilando con g++...
	g++ -std=c++20 -Iinclude -Itests -o %OUT% tests\%SRC%
	if errorlevel 1 exit /b 1
	%OUT%
	goto :EOF
)

if /I "%COMPILER%"=="clang++" (
	set "CLANG_PATH=C:\mingw64\ucrt64\bin"
	set "PATH=%CLANG_PATH%;%PATH%"
	echo Compilando con clang++...
	clang++ -std=c++20 -Iinclude -Itests -o %OUT% tests\%SRC%
	if errorlevel 1 exit /b 1
	%OUT%
	goto :EOF
)

echo Compilador no reconocido: %COMPILER%
echo Uso: %0 [msvc|g++|clang++]
exit /b 1
endlocal
