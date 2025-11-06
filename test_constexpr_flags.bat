@echo off
REM ======================================================================
REM INVESTIGACION DE FLAGS CONSTEXPR ADICIONALES
REM ======================================================================

set ARCHIVO=test_constexpr_flags.cpp
set FLAGS_BASE=/std:c++latest /permissive- /bigobj /constexpr:depth2048 /constexpr:steps1048576

echo.
echo ======================================================================
echo PROBANDO FLAGS CONSTEXPR ADICIONALES
echo ======================================================================
echo Archivo: %ARCHIVO%
echo.

REM Configurar MSVC (misma línea que compile_simple_extended.bat)
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64 >nul 2>&1

REM Probar flag /constexpr:frame
echo.
echo PROBANDO: /constexpr:frame
echo ----------------------------------------------------------------------
cl %FLAGS_BASE% /constexpr:frame %ARCHIVO% /Fe:test_frame.exe 2>&1
if %errorlevel% EQU 0 (
    echo ✅ /constexpr:frame EXISTE y funciona
) else (
    echo ❌ /constexpr:frame no reconocido
)

REM Probar flag /constexpr:backtrace
echo.
echo PROBANDO: /constexpr:backtrace
echo ----------------------------------------------------------------------
cl %FLAGS_BASE% /constexpr:backtrace %ARCHIVO% /Fe:test_backtrace.exe 2>&1
if %errorlevel% EQU 0 (
    echo ✅ /constexpr:backtrace EXISTE y funciona
) else (
    echo ❌ /constexpr:backtrace no reconocido
)

REM Probar flag /constexpr:trace
echo.
echo PROBANDO: /constexpr:trace
echo ----------------------------------------------------------------------
cl %FLAGS_BASE% /constexpr:trace %ARCHIVO% /Fe:test_trace.exe 2>&1
if %errorlevel% EQU 0 (
    echo ✅ /constexpr:trace EXISTE y funciona
) else (
    echo ❌ /constexpr:trace no reconocido
)

REM Probar flag /constexpr:frame1024
echo.
echo PROBANDO: /constexpr:frame1024
echo ----------------------------------------------------------------------
cl %FLAGS_BASE% /constexpr:frame1024 %ARCHIVO% /Fe:test_frame1024.exe 2>&1
if %errorlevel% EQU 0 (
    echo ✅ /constexpr:frame1024 EXISTE y funciona
) else (
    echo ❌ /constexpr:frame1024 no reconocido
)

echo.
echo ======================================================================
echo INVESTIGACION COMPLETADA
echo ======================================================================

pause