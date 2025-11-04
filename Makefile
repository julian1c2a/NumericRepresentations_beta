# NumericRepresentations - Multi-Compiler Makefile
# Soporte para MSVC, Clang++ y GCC

# Detectar sistema operativo
ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
    EXE_EXT := .exe
    OBJ_EXT := .obj
    PATH_SEP := \\
else
    DETECTED_OS := $(shell uname -s)
    EXE_EXT :=
    OBJ_EXT := .o
    PATH_SEP := /
endif

# Configuración por defecto
COMPILER ?= gcc
BUILD_TYPE ?= debug

# Directorios
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj

# Archivos fuente
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.$(COMPILER)$(OBJ_EXT))

# Configuración de compiladores
ifeq ($(COMPILER),msvc)
    CXX := cl.exe
    CXXFLAGS := /std:c++23 /I$(INCLUDE_DIR) /EHsc /W4 /permissive-
    LDFLAGS := 
    ifeq ($(BUILD_TYPE),debug)
        CXXFLAGS += /Od /Zi
        LDFLAGS += /DEBUG
    else
        CXXFLAGS += /O2 /DNDEBUG
    endif
    COMPILE_CMD = $(CXX) $(CXXFLAGS) /c $< /Fo$@
    LINK_CMD = $(CXX) $(OBJECTS) /Fe$(TARGET) $(LDFLAGS)
    
else ifeq ($(COMPILER),clang)
    CXX := C:/msys64/ucrt64/bin/clang++.exe
    CXXFLAGS := -std=c++23 -I$(INCLUDE_DIR) -Wall -Wextra -pedantic
    LDFLAGS := 
    ifeq ($(BUILD_TYPE),debug)
        CXXFLAGS += -g -O0 -DDEBUG
    else
        CXXFLAGS += -O3 -DNDEBUG -march=native
    endif
    COMPILE_CMD = $(CXX) $(CXXFLAGS) -c $< -o $@
    LINK_CMD = $(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
    
else # gcc (default)
    CXX := C:/msys64/ucrt64/bin/g++.exe
    CXXFLAGS := -std=c++23 -I$(INCLUDE_DIR) -Wall -Wextra -pedantic
    LDFLAGS := 
    ifeq ($(BUILD_TYPE),debug)
        CXXFLAGS += -g -O0 -DDEBUG
    else
        CXXFLAGS += -O3 -DNDEBUG -march=native
    endif
    COMPILE_CMD = $(CXX) $(CXXFLAGS) -c $< -o $@
    LINK_CMD = $(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
endif

# Target principal
TARGET := $(BUILD_DIR)/NumericRepresentations$(EXE_EXT)

# Targets especiales para pruebas de headers
TEST_TARGETS := test_dig_t test_auxiliary test_basic

.PHONY: all clean test help msvc clang gcc $(TEST_TARGETS)

# Target por defecto
all: $(TARGET)

# Compilar ejecutable principal
$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	@echo "Enlazando con $(COMPILER)..."
	@$(LINK_CMD)
	@echo "✓ Ejecutable generado: $(TARGET)"

# Compilar objetos
$(OBJ_DIR)/%.$(COMPILER)$(OBJ_EXT): $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "Compilando $< con $(COMPILER)..."
	@$(COMPILE_CMD)

# Crear directorios
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Targets específicos por compilador
msvc:
	@$(MAKE) COMPILER=msvc all

clang:
	@$(MAKE) COMPILER=clang all

gcc:
	@$(MAKE) COMPILER=gcc all

# Pruebas de compilación de headers
test_dig_t:
	@echo "Probando compilación de dig_t.hpp con $(COMPILER)..."
ifeq ($(COMPILER),msvc)
	@cl.exe /std:c++23 /I$(INCLUDE_DIR) /EHsc /c $(INCLUDE_DIR)/dig_t.hpp /Fo$(BUILD_DIR)/dig_t_test.obj
else
	@$(CXX) $(CXXFLAGS) -c $(INCLUDE_DIR)/dig_t.hpp -o $(BUILD_DIR)/dig_t_test$(OBJ_EXT)
endif
	@echo "✓ dig_t.hpp compilado exitosamente"

test_auxiliary:
	@echo "Probando headers auxiliares con $(COMPILER)..."
ifeq ($(COMPILER),msvc)
	@cl.exe /std:c++23 /I$(INCLUDE_DIR) /EHsc /c $(INCLUDE_DIR)/auxiliary_types.hpp /Fo$(BUILD_DIR)/aux_types_test.obj
	@cl.exe /std:c++23 /I$(INCLUDE_DIR) /EHsc /c $(INCLUDE_DIR)/auxiliary_functions.hpp /Fo$(BUILD_DIR)/aux_funcs_test.obj
else
	@$(CXX) $(CXXFLAGS) -c $(INCLUDE_DIR)/auxiliary_types.hpp -o $(BUILD_DIR)/aux_types_test$(OBJ_EXT)
	@$(CXX) $(CXXFLAGS) -c $(INCLUDE_DIR)/auxiliary_functions.hpp -o $(BUILD_DIR)/aux_funcs_test$(OBJ_EXT)
endif
	@echo "✓ Headers auxiliares compilados exitosamente"

test_basic:
	@echo "Probando basic_types.hpp con $(COMPILER)..."
ifeq ($(COMPILER),msvc)
	@cl.exe /std:c++23 /I$(INCLUDE_DIR) /EHsc /c $(INCLUDE_DIR)/basic_types.hpp /Fo$(BUILD_DIR)/basic_test.obj
else
	@$(CXX) $(CXXFLAGS) -c $(INCLUDE_DIR)/basic_types.hpp -o $(BUILD_DIR)/basic_test$(OBJ_EXT)
endif
	@echo "✓ basic_types.hpp compilado exitosamente"

# Compilar con todos los compiladores
test: test_dig_t test_auxiliary test_basic
	@echo "✓ Todas las pruebas de compilación pasaron con $(COMPILER)"

all_compilers:
	@echo "Compilando con todos los compiladores disponibles..."
	@$(MAKE) gcc test
	@$(MAKE) clang test  
	@$(MAKE) msvc test
	@echo "✓ Compilación exitosa con todos los compiladores"

# Limpiar archivos generados
clean:
	@echo "Limpiando archivos de compilación..."
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR) 2>nul || rm -rf $(BUILD_DIR) 2>/dev/null || true
	@echo "✓ Limpieza completada"

# Ayuda
help:
	@echo "NumericRepresentations - Makefile Multi-Compilador"
	@echo ""
	@echo "Targets disponibles:"
	@echo "  all              - Compilar proyecto completo (compilador: $(COMPILER))"
	@echo "  msvc             - Compilar con MSVC"
	@echo "  clang            - Compilar con Clang++"  
	@echo "  gcc              - Compilar con GCC"
	@echo "  test             - Probar compilación de headers"
	@echo "  test_dig_t       - Probar dig_t.hpp"
	@echo "  test_auxiliary   - Probar headers auxiliares"
	@echo "  test_basic       - Probar basic_types.hpp"
	@echo "  all_compilers    - Probar con todos los compiladores"
	@echo "  clean            - Limpiar archivos generados"
	@echo "  help             - Mostrar esta ayuda"
	@echo ""
	@echo "Variables:"
	@echo "  COMPILER={gcc|clang|msvc}  - Seleccionar compilador"
	@echo "  BUILD_TYPE={debug|release} - Tipo de compilación"
