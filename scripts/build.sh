#!/bin/bash
# NumericRepresentations - Universal Build Script
# Soporte para MSVC, Clang y GCC con modos Debug/Release

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Default values
COMPILER="gcc"
MODE="debug"
CLEAN_FIRST=false
VERBOSE=false
TEST_ONLY=false

# Paths
MSVC_PATH="D:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.44.35207/bin/Hostx64/x64"
UCRT64_PATH="C:/msys64/ucrt64/bin"
PROJECT_DIR=$(pwd)

# Functions
print_usage() {
    echo -e "${BLUE}NumericRepresentations Build Script${NC}"
    echo "Usage: $0 [OPTIONS]"
    echo ""
    echo "OPTIONS:"
    echo "  -c, --compiler COMPILER   Compilador: gcc, clang, msvc (default: gcc)"
    echo "  -m, --mode MODE          Modo: debug, release (default: debug)"
    echo "  -C, --clean              Limpiar antes de compilar"
    echo "  -t, --test-only          Solo probar headers (no compilar ejecutable)"
    echo "  -v, --verbose            Salida verbose"
    echo "  -h, --help               Mostrar esta ayuda"
    echo ""
    echo "EXAMPLES:"
    echo "  $0 -c gcc -m release     # Compilar con GCC en modo Release"
    echo "  $0 -c clang -C           # Compilar con Clang, limpiando primero"
    echo "  $0 -c msvc -t            # Solo probar headers con MSVC"
    echo "  $0 --clean               # Solo limpiar archivos de build"
}

log_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

log_success() {
    echo -e "${GREEN}[OK]${NC} $1"
}

log_warning() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

check_compiler() {
    local compiler=$1
    local path=""
    local exe=""
    
    case $compiler in
        "gcc")
            path="$UCRT64_PATH/g++.exe"
            exe="g++"
            ;;
        "clang")
            path="$UCRT64_PATH/clang++.exe"
            exe="clang++"
            ;;
        "msvc")
            path="$MSVC_PATH/cl.exe"
            exe="cl"
            ;;
        *)
            log_error "Compilador desconocido: $compiler"
            return 1
            ;;
    esac
    
    if [ -f "$path" ]; then
        log_success "$exe encontrado en: $path"
        return 0
    else
        log_error "$exe NO encontrado en: $path"
        return 1
    fi
}

setup_compiler_env() {
    local compiler=$1
    
    case $compiler in
        "gcc"|"clang")
            export PATH="$UCRT64_PATH:$PATH"
            ;;
        "msvc")
            # Para MSVC necesitamos configurar el entorno completo
            export PATH="$MSVC_PATH:$PATH"
            # Nota: En un entorno real necesitarías ejecutar vcvars64.bat
            ;;
    esac
}

get_compiler_flags() {
    local compiler=$1
    local mode=$2
    local flags=""
    
    case $compiler in
        "gcc")
            flags="-std=c++23 -I./include -Wall -Wextra -pedantic"
            if [ "$mode" == "debug" ]; then
                flags="$flags -g -O0 -DDEBUG"
            else
                flags="$flags -O3 -DNDEBUG -march=native"
            fi
            ;;
        "clang")
            flags="-std=c++23 -I./include -Wall -Wextra -pedantic"
            if [ "$mode" == "debug" ]; then
                flags="$flags -g -O0 -DDEBUG"
            else
                flags="$flags -O3 -DNDEBUG -march=native"
            fi
            ;;
        "msvc")
            flags="/std:c++23 /I./include /EHsc /W4 /permissive-"
            if [ "$mode" == "debug" ]; then
                flags="$flags /Od /Zi"
            else
                flags="$flags /O2 /DNDEBUG"
            fi
            ;;
    esac
    
    echo "$flags"
}

get_compiler_exe() {
    local compiler=$1
    
    case $compiler in
        "gcc")
            echo "$UCRT64_PATH/g++.exe"
            ;;
        "clang")
            echo "$UCRT64_PATH/clang++.exe"
            ;;
        "msvc")
            echo "$MSVC_PATH/cl.exe"
            ;;
    esac
}

clean_build() {
    log_info "Limpiando archivos de build..."
    
    # Eliminar directorios de build
    for dir in build build_* obj Debug Release; do
        if [ -d "$dir" ]; then
            log_info "Eliminando directorio: $dir"
            rm -rf "$dir"
        fi
    done
    
    # Eliminar archivos objeto y ejecutables
    for pattern in "*.o" "*.obj" "*.exe" "*_test.o" "*_test.obj" "*.pdb" "*.ilk"; do
        find . -name "$pattern" -type f -delete 2>/dev/null || true
    done
    
    log_success "Limpieza completada"
}

test_headers() {
    local compiler=$1
    local flags="$2"
    local compiler_exe="$3"
    local success=0
    local total=0
    
    log_info "Probando compilación de headers con $compiler..."
    
    # Lista de headers para probar
    local headers=(
        "include/auxiliary_types.hpp"
        "include/auxiliary_functions.hpp" 
        "include/basic_types.hpp"
        "include/dig_t.hpp"
    )
    
    mkdir -p "test_build"
    
    for header in "${headers[@]}"; do
        if [ ! -f "$header" ]; then
            log_warning "Header no encontrado: $header"
            continue
        fi
        
        total=$((total + 1))
        local base_name=$(basename "$header" .hpp)
        local output_file="test_build/${base_name}_${compiler}_test"
        
        log_info "Probando: $header"
        
        if [ "$compiler" == "msvc" ]; then
            output_file="${output_file}.obj"
            if $VERBOSE; then
                "$compiler_exe" $flags /c "$header" /Fo:"$output_file"
            else
                "$compiler_exe" $flags /c "$header" /Fo:"$output_file" > /dev/null 2>&1
            fi
        else
            output_file="${output_file}.o"
            if $VERBOSE; then
                "$compiler_exe" $flags -c "$header" -o "$output_file"
            else
                "$compiler_exe" $flags -c "$header" -o "$output_file" > /dev/null 2>&1
            fi
        fi
        
        if [ $? -eq 0 ]; then
            log_success "✓ $header compilado exitosamente"
            success=$((success + 1))
        else
            log_error "✗ Error compilando $header"
        fi
    done
    
    log_info "Resultado: $success/$total headers compilados exitosamente"
    
    if [ $success -eq $total ]; then
        log_success "Todas las pruebas de headers pasaron con $compiler"
        return 0
    else
        log_error "Algunos headers fallaron con $compiler"
        return 1
    fi
}

build_project() {
    local compiler=$1
    local mode=$2
    local flags="$3"
    local compiler_exe="$4"
    
    log_info "Compilando proyecto con $compiler en modo $mode..."
    
    # Crear directorio de build
    local build_dir="build_${compiler}_${mode}"
    mkdir -p "$build_dir"
    
    # Compilar archivos fuente
    local sources=(
        "src/main.cpp"
        "src/test_driver.cpp"
        "src/get.cpp"
    )
    
    local objects=()
    local compile_success=true
    
    for source in "${sources[@]}"; do
        if [ ! -f "$source" ]; then
            log_warning "Archivo fuente no encontrado: $source"
            continue
        fi
        
        local base_name=$(basename "$source" .cpp)
        local object_file=""
        
        if [ "$compiler" == "msvc" ]; then
            object_file="$build_dir/${base_name}.obj"
            log_info "Compilando: $source -> $object_file"
            if $VERBOSE; then
                "$compiler_exe" $flags /c "$source" /Fo:"$object_file"
            else
                "$compiler_exe" $flags /c "$source" /Fo:"$object_file" > /dev/null 2>&1
            fi
        else
            object_file="$build_dir/${base_name}.o"
            log_info "Compilando: $source -> $object_file"
            if $VERBOSE; then
                "$compiler_exe" $flags -c "$source" -o "$object_file"
            else
                "$compiler_exe" $flags -c "$source" -o "$object_file" > /dev/null 2>&1
            fi
        fi
        
        if [ $? -eq 0 ]; then
            log_success "✓ $source compilado"
            objects+=("$object_file")
        else
            log_error "✗ Error compilando $source"
            compile_success=false
        fi
    done
    
    if [ "$compile_success" = false ]; then
        log_error "Errores en la compilación"
        return 1
    fi
    
    # Enlazar ejecutable
    local executable="$build_dir/NumericRepresentations"
    if [ "$compiler" == "msvc" ]; then
        executable="${executable}.exe"
        log_info "Enlazando: $executable"
        if $VERBOSE; then
            "$compiler_exe" "${objects[@]}" /Fe:"$executable"
        else
            "$compiler_exe" "${objects[@]}" /Fe:"$executable" > /dev/null 2>&1
        fi
    else
        executable="${executable}.exe"
        log_info "Enlazando: $executable"
        if $VERBOSE; then
            "$compiler_exe" "${objects[@]}" -o "$executable"
        else
            "$compiler_exe" "${objects[@]}" -o "$executable" > /dev/null 2>&1
        fi
    fi
    
    if [ $? -eq 0 ]; then
        log_success "✓ Ejecutable generado: $executable"
        return 0
    else
        log_error "✗ Error en el enlazado"
        return 1
    fi
}

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -c|--compiler)
            COMPILER="$2"
            shift 2
            ;;
        -m|--mode)
            MODE="$2"
            shift 2
            ;;
        -C|--clean)
            CLEAN_FIRST=true
            shift
            ;;
        -t|--test-only)
            TEST_ONLY=true
            shift
            ;;
        -v|--verbose)
            VERBOSE=true
            shift
            ;;
        -h|--help)
            print_usage
            exit 0
            ;;
        clean)
            clean_build
            exit 0
            ;;
        *)
            log_error "Opción desconocida: $1"
            print_usage
            exit 1
            ;;
    esac
done

# Validate arguments
if [[ ! "$COMPILER" =~ ^(gcc|clang|msvc)$ ]]; then
    log_error "Compilador inválido: $COMPILER (debe ser: gcc, clang, msvc)"
    exit 1
fi

if [[ ! "$MODE" =~ ^(debug|release)$ ]]; then
    log_error "Modo inválido: $MODE (debe ser: debug, release)"
    exit 1
fi

# Main execution
echo -e "${BLUE}=========================================="
echo -e " NumericRepresentations Build Script"
echo -e " Compilador: $COMPILER | Modo: $MODE"
echo -e "==========================================${NC}"

# Clean if requested
if [ "$CLEAN_FIRST" = true ]; then
    clean_build
fi

# Check compiler availability
if ! check_compiler "$COMPILER"; then
    exit 1
fi

# Setup environment
setup_compiler_env "$COMPILER"

# Get compiler settings
COMPILER_FLAGS=$(get_compiler_flags "$COMPILER" "$MODE")
COMPILER_EXE=$(get_compiler_exe "$COMPILER")

log_info "Flags: $COMPILER_FLAGS"
log_info "Ejecutable: $COMPILER_EXE"

# Test headers first
if ! test_headers "$COMPILER" "$COMPILER_FLAGS" "$COMPILER_EXE"; then
    log_error "Pruebas de headers fallaron"
    exit 1
fi

# Build project if not test-only
if [ "$TEST_ONLY" = false ]; then
    if build_project "$COMPILER" "$MODE" "$COMPILER_FLAGS" "$COMPILER_EXE"; then
        log_success "Build completado exitosamente"
    else
        log_error "Build falló"
        exit 1
    fi
else
    log_info "Modo test-only: solo se probaron los headers"
fi

echo -e "${GREEN}=========================================="
echo -e " Build completado"
echo -e "==========================================${NC}"