# CMakeLists.txt para el directorio 'tests'

# Añadir un ejecutable para las pruebas de auxiliary_functions
add_executable(AuxiliaryFunctionsTest test_auxiliary_functions.cpp)

# Incluir los directorios necesarios para que el compilador encuentre las cabeceras
target_include_directories(AuxiliaryFunctionsTest PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/core
    ${CMAKE_SOURCE_DIR}/include/core/internal
)

# Añadir la prueba a CTest
add_test(NAME AuxiliaryFunctionsTest COMMAND AuxiliaryFunctionsTest)

# Asignar etiquetas a la prueba para poder filtrarla
set_tests_properties(AuxiliaryFunctionsTest PROPERTIES
    LABELS "core;auxiliary"
)
