#!/bin/bash
# NumericRepresentations - Clang/GCC Build Script
# Compila usando Clang++ y G++ desde MSYS2 UCRT64

echo
echo "=========================================="
echo " NumericRepresentations - Clang/GCC Build"
echo "=========================================="
echo

# Configurar rutas
export PATH="/c/msys64/ucrt64/bin:$PATH"
UCRT64_BIN="/c/msys64/ucrt64/bin"

# Verificar compiladores
echo "Verificando compiladores disponibles..."
if [ -f "$UCRT64_BIN/clang++.exe" ]; then
    echo "✓ Clang++ encontrado: $($UCRT64_BIN/clang++.exe --version | head -n1)"
else
    echo "✗ Clang++ no encontrado en $UCRT64_BIN"
fi

if [ -f "$UCRT64_BIN/g++.exe" ]; then
    echo "✓ GCC encontrado: $($UCRT64_BIN/g++.exe --version | head -n1)"
else
    echo "✗ GCC no encontrado en $UCRT64_BIN"
fi

echo

# Función para compilar con un compilador específico
compile_with() {
    local compiler=$1
    local compiler_name=$2
    local output_suffix=$3
    
    echo "--- Compilando con $compiler_name ---"
    
    # Crear directorio de build
    mkdir -p "build_$output_suffix"
    
    # Flags comunes
    local flags="-std=c++23 -I./include -Wall -Wextra -pedantic"
    
    # Compilar dig_t.hpp individualmente
    echo "Probando compilación individual de dig_t.hpp..."
    if $compiler $flags -c include/dig_t.hpp -o "dig_t_${output_suffix}_test.o"; then
        echo "✓ dig_t.hpp compilado exitosamente con $compiler_name"
        rm -f "dig_t_${output_suffix}_test.o"
    else
        echo "✗ Error compilando dig_t.hpp con $compiler_name"
        return 1
    fi
    
    # Configurar proyecto con CMake
    cd "build_$output_suffix"
    echo "Configurando proyecto con CMake para $compiler_name..."
    
    if cmake -G "MSYS Makefiles" \
        -DCMAKE_CXX_COMPILER="$compiler" \
        -DCMAKE_BUILD_TYPE=Debug \
        ..; then
        echo "✓ Configuración CMake exitosa"
    else
        echo "✗ Error en configuración CMake"
        cd ..
        return 1
    fi
    
    # Compilar proyecto
    echo "Compilando proyecto completo..."
    if make -j$(nproc); then
        echo "✓ Compilación exitosa con $compiler_name"
    else
        echo "✗ Error en compilación con $compiler_name"
    fi
    
    cd ..
    echo
}

# Compilar con Clang si está disponible
if [ -f "$UCRT64_BIN/clang++.exe" ]; then
    compile_with "$UCRT64_BIN/clang++.exe" "Clang++" "clang"
fi

# Compilar con GCC si está disponible  
if [ -f "$UCRT64_BIN/g++.exe" ]; then
    compile_with "$UCRT64_BIN/g++.exe" "GCC" "gcc"
fi

echo "=========================================="
echo " Compilación Clang/GCC completada"
echo "=========================================="
echo

# Mostrar archivos generados
echo "Archivos generados:"
ls -la build_*/ 2>/dev/null | grep -E "\.(exe|o|a)$" || echo "No se encontraron archivos compilados"

read -p "Presiona Enter para continuar..."