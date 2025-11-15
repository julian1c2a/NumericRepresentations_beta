@echo off
REM Script universal para compilar tests con gcc, clang o msvc
REM Uso: compile_test_universal.bat test_archivo.cpp [gcc|clang|msvc]

setlocal
set SRC=tests\%1
set COMPILER=%2
if "%COMPILER%"=="" set COMPILER=msvc
set BASE=%~n1
set "OUTDIR=build_tests_%COMPILER%"
set EXE=%OUTDIR%\%BASE%_%COMPILER%.exe
set OBJ=%OUTDIR%\%BASE%_%COMPILER%.obj
set CATCH_OBJ=%OUTDIR%\catch2_%COMPILER%.obj
set CATCH_LIB=%OUTDIR%\catch2_%COMPILER%.lib
set CATCH_SRC=local_libs\include\catch2\catch_all.hpp

if not exist %SRC% (
    echo Error: No se encuentra el archivo %SRC%
    exit /b 1
)
if not exist %OUTDIR% mkdir %OUTDIR%

REM === Compilar Catch2 si no existe ===
if not exist %CATCH_OBJ% (
    echo Compilando Catch2 para %COMPILER%...
    if /I "%COMPILER%"=="msvc" (
        cl /c /EHsc /std:c++latest /Ilocal_libs/include %CATCH_SRC% /Fo%CATCH_OBJ%
        lib /OUT:%CATCH_LIB% %CATCH_OBJ%
    ) else if /I "%COMPILER%"=="gcc" (
        g++ -std=c++23 -Ilocal_libs/include -c %CATCH_SRC% -o %CATCH_OBJ%
        ar rcs %CATCH_LIB% %CATCH_OBJ%
    ) else if /I "%COMPILER%"=="clang" (
        clang++ -std=c++23 -Ilocal_libs/include -c %CATCH_SRC% -o %CATCH_OBJ%
        ar rcs %CATCH_LIB% %CATCH_OBJ%
    ) else (
        echo Compilador no soportado
        exit /b 1
    )
)

REM === Compilar y linkar el test ===
if /I "%COMPILER%"=="msvc" (
    where cl.exe >nul 2>&1
    if %ERRORLEVEL% NEQ 0 call setup_compilers.bat
    cl /EHsc /std:c++latest /Iinclude /Ilocal_libs/include /Fe:%EXE% %SRC% %CATCH_LIB%
) else if /I "%COMPILER%"=="gcc" (
    where g++ >nul 2>&1
    if %ERRORLEVEL% NEQ 0 (
        echo Error: g++ no encontrado en PATH
        exit /b 1
    )
    g++ -std=c++23 -Iinclude -Ilocal_libs/include -o %EXE% %SRC% %CATCH_LIB%
) else if /I "%COMPILER%"=="clang" (
    where clang++ >nul 2>&1
    if %ERRORLEVEL% NEQ 0 (
        echo Error: clang++ no encontrado en PATH
        exit /b 1
    )
    clang++ -std=c++23 -Iinclude -Ilocal_libs/include -o %EXE% %SRC% %CATCH_LIB%
) else (
    echo Compilador no soportado
    exit /b 1
)

if %ERRORLEVEL% NEQ 0 exit /b 1
%EXE%
endlocal
