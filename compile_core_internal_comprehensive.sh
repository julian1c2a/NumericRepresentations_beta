#!/usr/bin/env bash
# Compila y ejecuta test_core_internal_comprehensive.cpp con el compilador especificado (msvc, g++, clang++)
# Uso: ./compile_core_internal_comprehensive.sh [msvc|g++|clang++]

SRC=tests/test_core_internal_comprehensive.cpp
EXE=tests/test_core_internal_comprehensive.exe
COMPILER=${1:-g++}
CATCH2_INC="/usr/include/catch2 /mingw64/include/catch2 /c/msys64/mingw64/include/catch2 /c/msys64/ucrt64/include/catch2"

find_catch2() {
  for d in $CATCH2_INC; do
    if [ -f "$d/catch_test_macros.hpp" ]; then
      echo "-I$d"
      return
    fi
  done
  echo ""
}

CATCH2_PATH=$(find_catch2)
if [ -z "$CATCH2_PATH" ]; then
  echo "[ERROR] No se encontró Catch2. Instala la cabecera o ajusta CATCH2_INC en el script."
  exit 1
fi

if [[ "$COMPILER" == "g++" ]]; then
  echo "Compilando con g++..."
  g++ -std=c++20 -O2 $CATCH2_PATH -Iinclude -Itests -o $EXE $SRC || exit 1
  $EXE
elif [[ "$COMPILER" == "clang++" ]]; then
  echo "Compilando con clang++..."
  clang++ -std=c++20 -O2 $CATCH2_PATH -Iinclude -Itests -o $EXE $SRC || exit 1
  $EXE
elif [[ "$COMPILER" == "msvc" ]]; then
  echo "Compilando con MSVC (cl.exe)..."
  cl /std:c++20 /EHsc $CATCH2_PATH /Iinclude /Itests /Fe:$EXE $SRC /link /out:$EXE || exit 1
  $EXE
else
  echo "Compilador no reconocido: $COMPILER"
  echo "Uso: $0 [msvc|g++|clang++]"
  exit 1
fi
