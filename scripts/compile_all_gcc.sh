#!/bin/bash
# Script para compilar con GCC - todas las suites de testing
# Requiere: MSYS2 con GCC instalado

echo "=== CONFIGURACIÓN GCC PARA NumericRepresentations ==="
echo "Compilador: $(gcc --version | head -1)"
echo "Flags: -std=c++23 -Wall -Wextra -O2 -I../include"
echo

# Variables comunes
INCLUDE_DIR="../include"
TESTS_DIR="../tests"
OUTPUT_DIR="../tests"
GCC_FLAGS="-std=c++23 -Wall -Wextra -O2"

compile_and_run() {
    local test_file=$1
    local output_name=$2
    local description=$3
    
    echo "=== Compilando $description ==="
    echo "Archivo: $test_file"
    
    if gcc $GCC_FLAGS -I$INCLUDE_DIR $TESTS_DIR/$test_file -o $OUTPUT_DIR/${output_name}_gcc.exe; then
        echo "✅ Compilación exitosa"
        echo
        echo "=== Ejecutando $description ==="
        if $OUTPUT_DIR/${output_name}_gcc.exe; then
            echo "✅ Ejecución exitosa"
        else
            echo "❌ Error en ejecución"
        fi
    else
        echo "❌ Error en compilación"
    fi
    echo
}

echo "🧮 SUITE 1: OPERADORES ARITMÉTICOS"
compile_and_run "test_dig_t_arithmetic.cpp" "test_dig_t_arithmetic" "Suite Aritmética"

echo "🔍 SUITE 2: OPERADORES DE COMPARACIÓN"  
compile_and_run "test_dig_t_comparison.cpp" "test_dig_t_comparison" "Suite Comparación"

echo "🎲 SUITE 3: OPERADORES BITWISE/MATEMÁTICOS"
compile_and_run "test_dig_t_bitwise.cpp" "test_dig_t_bitwise" "Suite Bitwise/Matemáticos"

echo "📝 SUITE 4: OPERADORES I/O"
compile_and_run "test_dig_t_io_simple.cpp" "test_dig_t_io_simple" "Suite I/O Simplificado"

echo "🎯 SUITE 5: COMPREHENSIVE"
compile_and_run "test_dig_t_comprehensive.cpp" "test_dig_t_comprehensive" "Suite Comprehensive"

echo "🏆 TODAS LAS SUITES GCC COMPLETADAS"