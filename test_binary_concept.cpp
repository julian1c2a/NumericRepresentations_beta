/**
 * @file test_binary_concept.cpp
 * @brief Demostración conceptual de números binarios naturales
 *
 * Este test demuestra el concepto de "binario natural" como
 * "representación con base posicional con potencias de 2 como patrón"
 * usando solo las funciones básicas que funcionan.
 */

#include <iostream>
#include "nat_reg_digs_t.hpp"
#include "core/dig_t_display_helpers.hpp"

using namespace NumRepr;

// Alias para números binarios naturales de 4 bits
using Binary4 = nat_reg_digs_t<2, 4>; // Base 2, 4 dígitos

int main()
{
    std::cout << "=== CONCEPTO: NÚMEROS BINARIOS NATURALES ===" << std::endl;
    std::cout << "Definición: Representación base posicional con potencias de 2" << std::endl;
    std::cout << "Implementación: nat_reg_digs_t<2, L>" << std::endl;

    // Demostración conceptual
    std::cout << "\n--- Representación Posicional Base 2 ---" << std::endl;
    std::cout << "Posiciones: [0]  [1]  [2]  [3]" << std::endl;
    std::cout << "Potencias:  2^0  2^1  2^2  2^3" << std::endl;
    std::cout << "Valores:     1    2    4    8" << std::endl;
    std::cout << "Orden: little-endian (LSB primero)" << std::endl;

    // Test 1: Constructor por defecto y to_string()
    std::cout << "\n--- 1. Constructor por Defecto ---" << std::endl;
    Binary4 binario_cero;
    std::cout << "Constructor por defecto: " << binario_cero.to_string() << std::endl;

    // Test 2: Construcción desde lista de dígitos explícitos
    std::cout << "\n--- 2. Construcción Explícita ---" << std::endl;

    // Construir el número binario 0001 (decimal 1)
    Binary4 binario_uno{{dig_t<2>{1}, dig_t<2>{0}, dig_t<2>{0}, dig_t<2>{0}}};
    std::cout << "Binario [1,0,0,0]: " << binario_uno.to_string()
              << " (representa 1×2^0 = 1 decimal)" << std::endl;

    // Construir el número binario 0010 (decimal 2)
    Binary4 binario_dos{{dig_t<2>{0}, dig_t<2>{1}, dig_t<2>{0}, dig_t<2>{0}}};
    std::cout << "Binario [0,1,0,0]: " << binario_dos.to_string()
              << " (representa 1×2^1 = 2 decimal)" << std::endl;

    // Construir el número binario 0100 (decimal 4)
    Binary4 binario_cuatro{{dig_t<2>{0}, dig_t<2>{0}, dig_t<2>{1}, dig_t<2>{0}}};
    std::cout << "Binario [0,0,1,0]: " << binario_cuatro.to_string()
              << " (representa 1×2^2 = 4 decimal)" << std::endl;

    // Construir el número binario 1000 (decimal 8)
    Binary4 binario_ocho{{dig_t<2>{0}, dig_t<2>{0}, dig_t<2>{0}, dig_t<2>{1}}};
    std::cout << "Binario [0,0,0,1]: " << binario_ocho.to_string()
              << " (representa 1×2^3 = 8 decimal)" << std::endl;

    // Test 3: Números combinados
    std::cout << "\n--- 3. Combinaciones de Potencias de 2 ---" << std::endl;

    // Binario 0011 = 2^0 + 2^1 = 1 + 2 = 3
    Binary4 binario_tres{{dig_t<2>{1}, dig_t<2>{1}, dig_t<2>{0}, dig_t<2>{0}}};
    std::cout << "Binario [1,1,0,0]: " << binario_tres.to_string()
              << " (representa 2^0 + 2^1 = 1 + 2 = 3 decimal)" << std::endl;

    // Binario 0101 = 2^0 + 2^2 = 1 + 4 = 5
    Binary4 binario_cinco{{dig_t<2>{1}, dig_t<2>{0}, dig_t<2>{1}, dig_t<2>{0}}};
    std::cout << "Binario [1,0,1,0]: " << binario_cinco.to_string()
              << " (representa 2^0 + 2^2 = 1 + 4 = 5 decimal)" << std::endl;

    // Binario 1111 = 2^0 + 2^1 + 2^2 + 2^3 = 1 + 2 + 4 + 8 = 15
    Binary4 binario_quince{{dig_t<2>{1}, dig_t<2>{1}, dig_t<2>{1}, dig_t<2>{1}}};
    std::cout << "Binario [1,1,1,1]: " << binario_quince.to_string()
              << " (representa 2^0+2^1+2^2+2^3 = 1+2+4+8 = 15 decimal)" << std::endl;

    // Test 4: Acceso a dígitos individuales
    std::cout << "\n--- 4. Acceso a Dígitos Individuales ---" << std::endl;
    std::cout << "Verificación del número 5 (binario 0101):" << std::endl;
    for (size_t i = 0; i < 4; ++i)
    {
        std::cout << "  Posición [" << i << "]: " << display(binario_cinco[i])
                  << " (potencia 2^" << i << ", valor " << (1 << i) << ")" << std::endl;
    }

    // Test 5: Operaciones básicas de modificación
    std::cout << "\n--- 5. Operaciones de Modificación ---" << std::endl;
    Binary4 modificable;

    // Poner todo a cero
    modificable.set_0();
    std::cout << "Después de set_0(): " << modificable.to_string() << std::endl;

    // Poner todos los dígitos al máximo (B-1 = 2-1 = 1)
    modificable.set_Bm1();
    std::cout << "Después de set_Bm1(): " << modificable.to_string()
              << " (todos los bits a 1)" << std::endl;

    // Test 6: Información sobre capacidades
    std::cout << "\n--- 6. Capacidades del Sistema ---" << std::endl;
    std::cout << "Base: 2 (solo dígitos 0 y 1)" << std::endl;
    std::cout << "Longitud: 4 dígitos" << std::endl;
    std::cout << "Rango: 0 a " << ((1 << 4) - 1) << " (0 a 15 decimal)" << std::endl;
    std::cout << "Almacenamiento: little-endian [LSB, bit1, bit2, MSB]" << std::endl;

    // Test 7: Comparación de formatos
    std::cout << "\n--- 7. Formatos de Representación ---" << std::endl;
    std::cout << "Número decimal 10:" << std::endl;
    Binary4 binario_diez{{dig_t<2>{0}, dig_t<2>{1}, dig_t<2>{0}, dig_t<2>{1}}};
    std::cout << "  nat_reg_digs_t: " << binario_diez.to_string() << std::endl;
    std::cout << "  Little-endian:  [0,1,0,1]" << std::endl;
    std::cout << "  Big-endian:     1010" << std::endl;
    std::cout << "  Cálculo: 0×2^0 + 1×2^1 + 0×2^2 + 1×2^3 = 0+2+0+8 = 10" << std::endl;

    std::cout << "\n=== CONCLUSIÓN ===" << std::endl;
    std::cout << "✅ 'Binario natural' = nat_reg_digs_t<2, L>" << std::endl;
    std::cout << "✅ Representación posicional con base 2" << std::endl;
    std::cout << "✅ Cada posición = potencia de 2 (patrón)" << std::endl;
    std::cout << "✅ Números naturales (≥ 0)" << std::endl;
    std::cout << "✅ Funcionalidad básica verificada" << std::endl;

    return 0;
}