cmake_minimum_required(VERSION 3.25)
project(NumericRepresentationsTests)

# Enable testing
enable_testing()

# ===================================================================
# DIRECT EXECUTABLE TESTS - Using precompiled MSVC executables
# ===================================================================

# Test 1: int_reg_digs_t Ultra Minimal
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
    message(STATUS "✓ Configured: int_reg_digs_ultra_minimal")
else()
    message(STATUS "✗ Missing: test_int_ultra_minimal_extended.exe")
endif()

# Test 2: nat_reg_digs_t Basic Methods
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
    message(STATUS "✓ Configured: nat_reg_digs_basic_methods")
else()
    message(STATUS "✗ Missing: test_basic_methods_extended.exe")
endif()

# Test 3: Factory Methods
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test_factory_methods_extended.exe")
    add_test(
        NAME nat_reg_digs_factory_methods
        COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/test_factory_methods_extended.exe"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    set_tests_properties(nat_reg_digs_factory_methods PROPERTIES
        LABELS "nat_reg_digs_t;phase2;factory"
        TIMEOUT 30
    )
    message(STATUS "✓ Configured: nat_reg_digs_factory_methods")
else()
    message(STATUS "✗ Missing: test_factory_methods_extended.exe")
endif()

# Test 4: Arithmetic Operators
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
    message(STATUS "✓ Configured: nat_reg_digs_arithmetic_operators")
else()
    message(STATUS "✗ Missing: test_arithmetic_operators_extended.exe")
endif()

# Test 5: Comparison Operators
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
    message(STATUS "✓ Configured: nat_reg_digs_comparison_operators")
else()
    message(STATUS "✗ Missing: test_comparison_operators_extended.exe")
endif()

# Test 6: I/O Operations
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test_io_operations_extended.exe")
    add_test(
        NAME nat_reg_digs_io_operations
        COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/test_io_operations_extended.exe"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    set_tests_properties(nat_reg_digs_io_operations PROPERTIES
        LABELS "nat_reg_digs_t;phase8;io;strings"
        TIMEOUT 30
    )
    message(STATUS "✓ Configured: nat_reg_digs_io_operations")
else()
    message(STATUS "✗ Missing: test_io_operations_extended.exe")
endif()

message(STATUS "")
message(STATUS "═══════════════════════════════════════════════════")
message(STATUS "CTest Configuration Summary:")
message(STATUS "  Use: 'ctest --verbose' for detailed output")
message(STATUS "  Use: 'ctest -L nat_reg_digs_t' for natural numbers")
message(STATUS "  Use: 'ctest -L int_reg_digs_t' for signed integers")
message(STATUS "  Use: 'ctest -L phase1' for basic tests")
message(STATUS "═══════════════════════════════════════════════════")