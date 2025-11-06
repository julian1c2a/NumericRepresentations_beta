# CTestTestfile.cmake - Tests para NumericRepresentations
# Configuración de tests usando ejecutables ya compilados con MSVC

# ===================================================================
# TESTS DE INT_REG_DIGS_T - Enteros con Signo
# ===================================================================

# Test 1: int_reg_digs_t Ultra Minimal (Fase 1)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test_int_ultra_minimal_extended.exe")
    add_test(
        NAME int_reg_digs_ultra_minimal
        COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/test_int_ultra_minimal_extended.exe"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    set_tests_properties(int_reg_digs_ultra_minimal PROPERTIES
        LABELS "int_reg_digs_t;phase1;basic;minimal"
        TIMEOUT 30
    )
endif()

# ===================================================================
# TESTS DE NAT_REG_DIGS_T - Números Naturales  
# ===================================================================

# Test 2: nat_reg_digs_t Basic Methods (Fase 1)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test_basic_methods_extended.exe")
    add_test(
        NAME nat_reg_digs_basic_methods
        COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/test_basic_methods_extended.exe"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    set_tests_properties(nat_reg_digs_basic_methods PROPERTIES
        LABELS "nat_reg_digs_t;phase1;basic;methods"
        TIMEOUT 45
    )
endif()

# Test 3: Factory Methods (Fase 2)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test_factory_methods_extended.exe")
    add_test(
        NAME nat_reg_digs_factory_methods
        COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/test_factory_methods_extended.exe"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    set_tests_properties(nat_reg_digs_factory_methods PROPERTIES
        LABELS "nat_reg_digs_t;phase2;factory;methods"
        TIMEOUT 30
    )
endif()

# Test 4: Constructors (Fase 3)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test_minimal_constructors_extended.exe")
    add_test(
        NAME nat_reg_digs_constructors
        COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/test_minimal_constructors_extended.exe"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    set_tests_properties(nat_reg_digs_constructors PROPERTIES
        LABELS "nat_reg_digs_t;phase3;constructors"
        TIMEOUT 30
    )
endif()

# Test 5: Set Operations (Fase 4)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test_set_operations_extended.exe")
    add_test(
        NAME nat_reg_digs_set_operations
        COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/test_set_operations_extended.exe"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    set_tests_properties(nat_reg_digs_set_operations PROPERTIES
        LABELS "nat_reg_digs_t;phase4;set_operations"
        TIMEOUT 30
    )
endif()

# Test 6: Assignment Operators (Fase 5)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test_assignment_operators_extended.exe")
    add_test(
        NAME nat_reg_digs_assignment_operators
        COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/test_assignment_operators_extended.exe"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    set_tests_properties(nat_reg_digs_assignment_operators PROPERTIES
        LABELS "nat_reg_digs_t;phase5;assignment;operators"
        TIMEOUT 30
    )
endif()

# Test 7: Arithmetic Operators (Fase 6)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test_arithmetic_operators_extended.exe")
    add_test(
        NAME nat_reg_digs_arithmetic_operators
        COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/test_arithmetic_operators_extended.exe"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    set_tests_properties(nat_reg_digs_arithmetic_operators PROPERTIES
        LABELS "nat_reg_digs_t;phase6;arithmetic;operators"
        TIMEOUT 45
    )
endif()

# Test 8: Comparison Operators (Fase 7)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test_comparison_operators_extended.exe")
    add_test(
        NAME nat_reg_digs_comparison_operators
        COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/test_comparison_operators_extended.exe"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    set_tests_properties(nat_reg_digs_comparison_operators PROPERTIES
        LABELS "nat_reg_digs_t;phase7;comparison;operators"
        TIMEOUT 30
    )
endif()

# Test 9: I/O Operations (Fase 8)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test_io_operations_extended.exe")
    add_test(
        NAME nat_reg_digs_io_operations
        COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/test_io_operations_extended.exe"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    set_tests_properties(nat_reg_digs_io_operations PROPERTIES
        LABELS "nat_reg_digs_t;phase8;io_operations;strings"
        TIMEOUT 30
    )
endif()

# ===================================================================
# INFORMACIÓN Y RESUMEN
# ===================================================================

message(STATUS "")
message(STATUS "═══════════════════════════════════════════════════════════")
message(STATUS "   CTEST CONFIGURATION - NumericRepresentations")
message(STATUS "═══════════════════════════════════════════════════════════")
message(STATUS "📊 Tests configurados usando ejecutables MSVC precompilados")
message(STATUS "")
message(STATUS "🔢 nat_reg_digs_t (Números Naturales) - 8 Fases:")
message(STATUS "   Phase 1: Basic Methods")
message(STATUS "   Phase 2: Factory Methods")  
message(STATUS "   Phase 3: Constructors")
message(STATUS "   Phase 4: Set Operations")
message(STATUS "   Phase 5: Assignment Operators")
message(STATUS "   Phase 6: Arithmetic Operators")
message(STATUS "   Phase 7: Comparison Operators")
message(STATUS "   Phase 8: I/O Operations")
message(STATUS "")
message(STATUS "🔢 int_reg_digs_t (Enteros con Signo):")
message(STATUS "   Phase 1: Ultra Minimal (Complemento a la Base)")
message(STATUS "")
message(STATUS "🚀 Comandos de uso:")
message(STATUS "   ctest --verbose                    # Todos los tests")
message(STATUS "   ctest -L nat_reg_digs_t           # Solo números naturales")
message(STATUS "   ctest -L int_reg_digs_t           # Solo enteros con signo")
message(STATUS "   ctest -L phase1                   # Solo tests básicos")
message(STATUS "   ctest -L operators                # Solo operadores")
message(STATUS "   ctest -R arithmetic               # Solo tests aritméticos")
message(STATUS "═══════════════════════════════════════════════════════════")