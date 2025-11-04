cmake_minimum_required(VERSION 3.25)
project(NumericRepresentations CXX)

# C++23 Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler detection and configuration
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

# Compiler-specific flags
if(MSVC)
    # Visual Studio / MSVC
    message(STATUS "Configuring for MSVC")
    add_compile_options(
        /std:c++23
        /W4                    # High warning level
        /permissive-          # Strict standards compliance
        /EHsc                 # Exception handling
        /utf-8                # UTF-8 source files
        /Zc:__cplusplus       # Correct __cplusplus value
        /bigobj               # Large object files for templates
    )
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # GCC
    message(STATUS "Configuring for GCC")
    add_compile_options(
        -std=c++23
        -Wall -Wextra -Wpedantic
        -fconcepts-diagnostics-depth=512
        -ftemplate-backtrace-limit=0
        -march=native          # Optimize for current CPU
    )
    
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Clang
    message(STATUS "Configuring for Clang")
    add_compile_options(
        -std=c++23
        -Wall -Wextra -Wpedantic
        -ftemplate-backtrace-limit=0
        -march=native          # Optimize for current CPU
    )
    
else()
    message(WARNING "Unknown compiler: ${CMAKE_CXX_COMPILER_ID}")
    add_compile_options(-std=c++23 -Wall -Wextra)
endif()

# Debug/Release configurations
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug build")
    if(MSVC)
        add_compile_options(/Od /Zi)
        add_link_options(/DEBUG)
    else()
        add_compile_options(-g -O0 -DDEBUG)
    endif()
else()
    message(STATUS "Release build")
    if(MSVC)
        add_compile_options(/O2 /DNDEBUG)
    else()
        add_compile_options(-O3 -DNDEBUG)
    endif()
endif()

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Main executable
add_executable(NumericRepresentations 
    src/main.cpp 
    src/test_driver.cpp 
    src/get.cpp
)

# Test executables for improved components
add_executable(test_auxiliary_types 
    test_auxiliary_types.cpp
)

add_executable(test_auxiliary_functions
    test_auxiliary_functions.cpp
)

add_executable(test_basic
    test_basic.cpp
)

# Enable testing
enable_testing()
add_test(NAME auxiliary_types_test COMMAND test_auxiliary_types)
add_test(NAME auxiliary_functions_test COMMAND test_auxiliary_functions)
add_test(NAME basic_test COMMAND test_basic)
