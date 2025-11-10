# CMakeLists.txt para el directorio 'tests'

# Encontrar el paquete Catch2, que ahora está instalado localmente
find_package(Catch2 3.6.0 REQUIRED)

# Añadir un ejecutable para las pruebas de auxiliary_functions
add_executable(AuxiliaryFunctionsTest test_auxiliary_functions.cpp)

# Incluir los directorios necesarios para que el compilador encuentre las cabeceras
target_include_directories(AuxiliaryFunctionsTest PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/core
    ${CMAKE_SOURCE_DIR}/include/core/internal
)

# Enlazar la biblioteca Catch2 con nuestro ejecutable de prueba
target_link_libraries(AuxiliaryFunctionsTest PRIVATE Catch2::Catch2WithMain)

# Añadir la prueba a CTest
add_test(NAME AuxiliaryFunctionsTest COMMAND AuxiliaryFunctionsTest)

# Asignar etiquetas a la prueba para poder filtrarla
set_tests_properties(AuxiliaryFunctionsTest PROPERTIES
    LABELS "core;auxiliary"
)
