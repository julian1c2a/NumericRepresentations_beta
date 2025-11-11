#!/bin/bash

# Script de shell para compilar con GCC o Clang en MSYS2

# --- Argumentos ---
COMPILER=$1

if [[ -z "$COMPILER" || ("$COMPILER" != "gcc" && "$COMPILER" != "clang") ]]; then
    echo "Uso: $0 <gcc|clang>"
    echo "Ejemplo: ./build.sh clang"
    exit 1
fi

# --- Lógica Principal ---

# Salir si ocurre un error
set -e

echo "--- Preparando para compilar con $COMPILER ---"

BUILD_DIR="build-$COMPILER"

# Determinar el nombre correcto del compilador de C++
if [ "$COMPILER" == "gcc" ]; then
    CXX_COMPILER_NAME="g++"
else
    CXX_COMPILER_NAME="${COMPILER}++"
fi

# En MSYS2 UCRT64, los compiladores pueden tener un sufijo.
# Este find busca el compilador correcto
echo "Buscando el compilador '${CXX_COMPILER_NAME}'..."
CXX_PATH=$(which ${CXX_COMPILER_NAME} 2>/dev/null || which ucrt64-${CXX_COMPILER_NAME} 2>/dev/null)
echo "Ruta encontrada para el compilador: '${CXX_PATH}'"

if [[ -z "$CXX_PATH" ]]; then
    echo "Error: No se pudo encontrar el compilador ${CXX_COMPILER_NAME}."
    echo "Asegurate de que este instalado con pacman (ej. 'pacman -S mingw-w64-ucrt-x86_64-gcc')."
    exit 1
fi

# Extraer el nombre del ejecutable del compilador
CXX_COMPILER=$(basename "$CXX_PATH")
C_COMPILER=${CXX_COMPILER/++/} # Reemplaza '++' con nada para obtener el compilador de C
# Corregir para g++ -> gcc
if [ "$CXX_COMPILER" == "g++" ]; then
    C_COMPILER="gcc"
fi

echo "Directorio de compilación: $BUILD_DIR"
echo "Compilador CXX a usar: $CXX_COMPILER"
echo "Compilador C a usar: $C_COMPILER"


# Solo configurar si el directorio de compilación no existe.
# `cmake --build` se encargará de re-configurar si los CMakeLists.txt cambian.
if [ ! -d "$BUILD_DIR" ]; then
    echo "--- Configurando el proyecto por primera vez para $COMPILER ---"
    cmake -B "$BUILD_DIR" -S . -G "MinGW Makefiles" -D CMAKE_C_COMPILER=$C_COMPILER -D CMAKE_CXX_COMPILER=$CXX_COMPILER
fi

echo "--- Compilando (solo los archivos modificados) ---"
cmake --build "$BUILD_DIR"

echo "--- Ejecutando Pruebas ---"
# Entrar al directorio de compilación para correr ctest
pushd "$BUILD_DIR" > /dev/null
ctest --output-on-failure
popd > /dev/null

echo "--- Proceso completado con éxito ---"
