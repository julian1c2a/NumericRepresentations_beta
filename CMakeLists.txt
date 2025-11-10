# CMakeLists.txt (Raíz del proyecto)

# Versión mínima de CMake y nombre del proyecto
cmake_minimum_required(VERSION 3.16)
project(NumericRepresentations VERSION 1.0 LANGUAGES CXX)

# Establecer el estándar de C++ a C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Habilitar el sistema de pruebas CTest
enable_testing()

# Añadir el subdirectorio 'tests' donde se configurarán las pruebas
add_subdirectory(tests)
