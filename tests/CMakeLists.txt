# CMakeLists.txt para el directorio 'tests'

# Determinar el directorio de salida específico del compilador
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(COMPILER_DIR "gcc")
elseif(CMAKE_CXX_COMPiler_ID MATCHES "Clang")
    set(COMPILER_DIR "clang")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(COMPILER_DIR "msvc")
else()
    set(COMPILER_DIR "unknown")
endif()

# Establecer el directorio de salida para los ejecutables de prueba en un subdirectorio de la carpeta de compilación
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build_tests/${COMPILER_DIR}")

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
