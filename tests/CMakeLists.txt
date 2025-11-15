# CMakeLists.txt para el directorio 'tests'

# Determinar el directorio de salida específico del compilador (insensible a mayúsculas)
string(TOLOWER "${CMAKE_CXX_COMPILER_ID}" COMPILER_ID_LOWER)
if(COMPILER_ID_LOWER MATCHES "gnu")
    set(COMPILER_DIR "gcc")
elseif(COMPILER_ID_LOWER MATCHES "clang")
    set(COMPILER_DIR "clang")
elseif(COMPILER_ID_LOWER MATCHES "msvc")
    set(COMPILER_DIR "msvc")
else()
    set(COMPILER_DIR "unknown")
endif()

# Establecer el directorio de salida para los ejecutables de prueba en un subdirectorio de la carpeta de compilación
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build_tests/${COMPILER_DIR}")






# Listado manual de tests que solo dependen de core/ y core/internal/
set(CORE_TESTS
    test_core_only.cpp
    test_core_internal_comprehensive.cpp
    test_auxiliary_functions.cpp
    test_auxiliary_functions_comprehensive.cpp
    test_dig_t.cpp
    test_dig_t_simple.cpp
    test_dig_t_basic_construct.cpp
    test_dig_t_simple_construct.cpp
    test_dig_t_arithmetic.cpp
    test_dig_t_bitwise.cpp
    test_dig_t_comparison.cpp
    test_dig_t_comparison_debug.cpp
    test_dig_t_constructors.cpp
    test_dig_t_io.cpp
    test_dig_t_io_simple.cpp
    test_dig_t_operations.cpp
    test_dig_t_comprehensive.cpp
    test_boolean_queries.cpp
    test_fast_exponentiation.cpp
)

foreach(test_src ${CORE_TESTS})
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${test_src}")
        get_filename_component(test_name ${test_src} NAME_WE)
        add_executable(${test_name} ${test_src})
        # Incluir solo la raíz include/ y la carpeta de headers externos
        target_include_directories(${test_name} PUBLIC
            ${CMAKE_SOURCE_DIR}/include
            ${CMAKE_CURRENT_SOURCE_DIR}/external
        )
        add_test(NAME ${test_name} COMMAND ${test_name})
        set_tests_properties(${test_name} PROPERTIES LABELS "auto")
    endif()
endforeach()
