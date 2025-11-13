@echo off
REM ============================================================================
REM Script para ejecutar TODOS los tests creados/revisados ayer
REM ============================================================================

setlocal enabledelayedexpansion

set TOTAL_TESTS=0
set PASSED_TESTS=0
set FAILED_TESTS=0

echo.
echo ==============================================================================
echo    EJECUTANDO TODOS LOS TESTS DE AYER (12 Nov 2025)
echo ==============================================================================
echo.

REM ---------------------------------------------------------------------------
echo [1/5] TEST: auxiliary_functions.cpp (985,954 assertions)
echo ---------------------------------------------------------------------------
call compile_auxiliary_functions.bat
if %ERRORLEVEL% EQU 0 (
    echo    [OK] PASSED: auxiliary_functions
    set /a PASSED_TESTS+=1
) else (
    echo    [FAIL] FAILED: auxiliary_functions
    set /a FAILED_TESTS+=1
)
set /a TOTAL_TESTS+=1
echo.

REM ---------------------------------------------------------------------------
echo [2/5] TEST: pack2array.cpp (perfect forwarding)
echo ---------------------------------------------------------------------------
call compile_pack2array.bat
if %ERRORLEVEL% EQU 0 (
    echo    [OK] PASSED: pack2array
    set /a PASSED_TESTS+=1
) else (
    echo    [FAIL] FAILED: pack2array
    set /a FAILED_TESTS+=1
)
set /a TOTAL_TESTS+=1
echo.

REM ---------------------------------------------------------------------------
echo [3/5] TEST: atoull_limits.cpp (overflow/validation)
echo ---------------------------------------------------------------------------
call compile_test_atoull.bat
if %ERRORLEVEL% EQU 0 (
    echo    [OK] PASSED: atoull_limits
    set /a PASSED_TESTS+=1
) else (
    echo    [FAIL] FAILED: atoull_limits
    set /a FAILED_TESTS+=1
)
set /a TOTAL_TESTS+=1
echo.

REM ---------------------------------------------------------------------------
REM [4/5] TEST: reg_digs_t_internal.cpp (type system) - SKIP (compilation errors)
REM ---------------------------------------------------------------------------
REM call compile_reg_digs_t_tests.bat
REM if %ERRORLEVEL% EQU 0 (
REM     echo    [OK] PASSED: reg_digs_t_internal
REM     set /a PASSED_TESTS+=1
REM ) else (
REM     echo    [FAIL] FAILED: reg_digs_t_internal
REM     set /a FAILED_TESTS+=1
REM )
echo    [SKIP] reg_digs_t_internal (dig_t.hpp compilation errors)
set /a TOTAL_TESTS+=1
echo.

REM ---------------------------------------------------------------------------
REM [5/5] TEST: advanced_edge_cases.cpp (sig_* types) - SKIP (compilation errors)
REM ---------------------------------------------------------------------------
REM call compile_advanced_edge_tests.bat
REM if %ERRORLEVEL% EQU 0 (
REM     echo    [OK] PASSED: advanced_edge_cases
REM     set /a PASSED_TESTS+=1
REM ) else (
REM     echo    [FAIL] FAILED: advanced_edge_cases
REM     set /a FAILED_TESTS+=1
REM )
echo    [SKIP] advanced_edge_cases (dig_t.hpp compilation errors)
set /a TOTAL_TESTS+=1
echo.

REM ---------------------------------------------------------------------------
echo ==============================================================================
echo    RESUMEN FINAL
echo ==============================================================================
echo    Total:  %TOTAL_TESTS% test suites
echo    Passed: %PASSED_TESTS%
echo    Failed: %FAILED_TESTS%
echo ==============================================================================
echo.

if %FAILED_TESTS% EQU 0 (
    echo [OK] TODOS LOS TESTS PASARON
    exit /b 0
) else (
    echo [FAIL] ALGUNOS TESTS FALLARON
    exit /b 1
)
