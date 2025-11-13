@echo off
REM ============================================================================
REM LISTADO DE TESTS CREADOS/REVISADOS - 12 Nov 2025
REM ============================================================================

echo.
echo ==============================================================================
echo   TESTS DE AYER - REVISION DE basic_types.hpp Y auxiliary_functions.hpp
echo ==============================================================================
echo.

echo ------------------------------------------------------------------------------
echo  1. TEST: auxiliary_functions.cpp
echo ------------------------------------------------------------------------------
echo     Archivo:    tests\test_auxiliary_functions.cpp
echo     Script:     compile_auxiliary_functions.bat
echo     Assertions: 985,954
echo     Tests:      floorsqrt, is_prime, gcd, lcm, newton_raphson, etc.
echo     Estado:     [OK] VALIDADO
echo ------------------------------------------------------------------------------
echo.

echo ------------------------------------------------------------------------------
echo  2. TEST: pack2array.cpp (NUEVO)
echo ------------------------------------------------------------------------------
echo     Archivo:    tests\test_pack2array.cpp
echo     Script:     compile_pack2array.bat
echo     Assertions: 34
echo     Test cases: 7
echo     Tests:      - Perfect forwarding
echo                 - Copias/movimientos con TrackedInt
echo                 - Compatibilidad con usos existentes
echo     Mejora:     50%% menos copias (lvalues)
echo                 100%% movimientos (rvalues)
echo     Estado:     [OK] VALIDADO
echo ------------------------------------------------------------------------------
echo.

echo ------------------------------------------------------------------------------
echo  3. TEST: atoull_limits.cpp
echo ------------------------------------------------------------------------------
echo     Archivo:    test_atoull_limits.cpp (raiz)
echo     Script:     compile_test_atoull.bat
echo     Tests:      - Limites (UINT64_MAX)
echo                 - Overflow detection
echo                 - Validacion atoull vs atoull_checked
echo     Estado:     [OK] VALIDADO
echo ------------------------------------------------------------------------------
echo.

echo ------------------------------------------------------------------------------
echo  4. TEST: reg_digs_t_internal.cpp
echo ------------------------------------------------------------------------------
echo     Archivo:    test_reg_digs_t_internal.cpp (raiz)
echo     Script:     compile_reg_digs_t_tests.bat
echo     Tests:      - Sistema de tipos (UINT_T, SIG_UINT_T, SIG_SINT_T)
echo                 - Constructores y operaciones de reg_digs_t
echo                 - Uso de sig_* type traits mejorados
echo     Estado:     [OK] VALIDADO
echo ------------------------------------------------------------------------------
echo.

echo ------------------------------------------------------------------------------
echo  5. TEST: advanced_edge_cases.cpp
echo ------------------------------------------------------------------------------
echo     Archivo:    test_advanced_edge_cases.cpp (raiz)
echo     Script:     compile_advanced_edge_tests.bat
echo     Tests:      - Limites de tipos uint_t para diferentes bases
echo                 - Operaciones con sig_uint_t y sig_sint_t
echo                 - Validacion de type traits refactorizados
echo     Estado:     [OK] VALIDADO
echo ------------------------------------------------------------------------------
echo.

echo ==============================================================================
echo   PARA EJECUTAR TODOS LOS TESTS:
echo   run_all_yesterday_tests.bat
echo ==============================================================================
echo.

pause
