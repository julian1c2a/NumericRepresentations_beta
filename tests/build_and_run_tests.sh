#!/bin/bash

# Build script para tests unitarios
# Compilar y ejecutar tests para los headers

echo "========================================"
echo " Building NumericRepresentations Tests"
echo "========================================"

# Directorio de trabajo
TEST_DIR="tests"
INCLUDE_DIR="../include"
BUILD_DIR="../build"

# Crear directorio de build si no existe
mkdir -p "$BUILD_DIR"

# Compilador y flags
CXX="g++"
CXXFLAGS="-std=c++23 -I$INCLUDE_DIR -Wall -Wextra -pedantic -g -O0 -DDEBUG"

# Lista de archivos de test
TEST_FILES=(
    "test_auxiliary_types"
    "test_auxiliary_functions" 
    "test_basic_types"
    "test_dig_t"
)

echo "Compilando tests con $CXX..."
echo "Flags: $CXXFLAGS"
echo ""

cd "$TEST_DIR" || exit 1

BUILD_SUCCESS=true

# Compilar cada test
for test_file in "${TEST_FILES[@]}"; do
    echo "Compilando: ${test_file}.cpp"
    
    if $CXX $CXXFLAGS -o "${test_file}.exe" "${test_file}.cpp"; then
        echo "✓ ${test_file} compilado exitosamente"
    else
        echo "✗ Error compilando ${test_file}"
        BUILD_SUCCESS=false
    fi
    echo ""
done

if [ "$BUILD_SUCCESS" = true ]; then
    echo "========================================"
    echo " Ejecutando Tests"
    echo "========================================"
    echo ""
    
    TOTAL_TESTS=0
    PASSED_TESTS=0
    
    # Ejecutar cada test
    for test_file in "${TEST_FILES[@]}"; do
        TOTAL_TESTS=$((TOTAL_TESTS + 1))
        echo "Ejecutando: ${test_file}.exe"
        
        if ./"${test_file}.exe"; then
            echo "✅ ${test_file} - PASSED"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        else
            echo "❌ ${test_file} - FAILED"
        fi
        echo ""
    done
    
    echo "========================================"
    echo " Resumen de Tests"
    echo "========================================"
    echo "Total: $TOTAL_TESTS"
    echo "Exitosos: $PASSED_TESTS"
    echo "Fallidos: $((TOTAL_TESTS - PASSED_TESTS))"
    
    if [ $PASSED_TESTS -eq $TOTAL_TESTS ]; then
        echo ""
        echo "🎉 TODOS LOS TESTS EXITOSOS! 🎉"
        exit 0
    else
        echo ""
        echo "💥 Algunos tests fallaron."
        exit 1
    fi
else
    echo "❌ Fallos en compilación - no se ejecutarán los tests"
    exit 1
fi