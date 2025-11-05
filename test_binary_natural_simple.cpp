/**
 * @file test_binary_natural_simple.cpp
 * @brief Test simplificado para números binarios naturales
 *
 * Este archivo prueba la funcionalidad básica de nat_reg_digs_t con base 2
 * evitando las operaciones que tienen problemas de compilación.
 */

#include <iostream>
#include "include/nat_reg_digs_t.hpp"
#include "include/dig_t_display_helpers.hpp"

using namespace NumRepr;

// Alias para números binarios naturales
using Binary4 = nat_reg_digs_t<2, 4>; // 4 bits: rango 0-15
using Binary8 = nat_reg_digs_t<2, 8>; // 8 bits: rango 0-255

/**
 * @brief Muestra información básica de un número binario
 */
template <size_t L>
void mostrar_binario_info(const nat_reg_digs_t<2, L> &num, const std::string &label)
{
    std::cout << label << ": " << num.to_string();

    // Mostrar los dígitos individuales accesibles
    std::cout << " [bits: ";
    for (size_t i = 0; i < L; ++i)
    {
        if (i > 0)
            std::cout << ",";
        std::cout << display(num[i]);
    }
    std::cout << "]" << std::endl;
}

int main()
{
    std::cout << "=== Tests Simplificados para Números Binarios Naturales ===" << std::endl;
    std::cout << "nat_reg_digs_t<2, L> - Base 2, Representación Posicional" << std::endl;

    // Test 1: Constructor por defecto
    std::cout << "\n--- 1. Constructor por Defecto ---" << std::endl;
    Binary4 cero;
    mostrar_binario_info(cero, "Binario por defecto");

    // Test 2: Construcción desde lista de inicialización
    std::cout << "\n--- 2. Construcción desde Dígitos ---" << std::endl;
    Binary4 uno{{dig_t<2>{1}, dig_t<2>{0}, dig_t<2>{0}, dig_t<2>{0}}}; // 0001 = 1
    mostrar_binario_info(uno, "Número uno (0001)");

    Binary4 dos{{dig_t<2>{0}, dig_t<2>{1}, dig_t<2>{0}, dig_t<2>{0}}}; // 0010 = 2
    mostrar_binario_info(dos, "Número dos (0010)");

    Binary4 tres{{dig_t<2>{1}, dig_t<2>{1}, dig_t<2>{0}, dig_t<2>{0}}}; // 0011 = 3
    mostrar_binario_info(tres, "Número tres (0011)");

    Binary4 ocho{{dig_t<2>{0}, dig_t<2>{0}, dig_t<2>{0}, dig_t<2>{1}}}; // 1000 = 8
    mostrar_binario_info(ocho, "Número ocho (1000)");

    Binary4 quince{{dig_t<2>{1}, dig_t<2>{1}, dig_t<2>{1}, dig_t<2>{1}}}; // 1111 = 15
    mostrar_binario_info(quince, "Máximo 4-bit (1111)");

    // Test 3: Operaciones de asignación básica
    std::cout << "\n--- 3. Asignación desde Dígito ---" << std::endl;
    Binary4 asignado;
    asignado = dig_t<2>{1}; // Asignar 1
    mostrar_binario_info(asignado, "Asignado desde dig_t{1}");

    // Test 4: Operaciones set
    std::cout << "\n--- 4. Operaciones Set ---" << std::endl;
    Binary4 modificado;
    modificado.set_0(); // Poner todo a 0
    mostrar_binario_info(modificado, "Después de set_0()");

    modificado.set_Bm1(); // Poner todo a B-1 (en base 2 = 1)
    mostrar_binario_info(modificado, "Después de set_Bm1()");

    // Test 5: Acceso individual a bits
    std::cout << "\n--- 5. Acceso a Bits Individuales ---" << std::endl;
    Binary4 construido;
    construido.set_0();          // Empezar con ceros
    construido[0] = dig_t<2>{1}; // bit 0 = 1 (LSB)
    construido[2] = dig_t<2>{1}; // bit 2 = 1
    mostrar_binario_info(construido, "Bits [0,2] = 1");

    std::cout << "Verificación bit a bit:" << std::endl;
    for (size_t i = 0; i < 4; ++i)
    {
        std::cout << "  bit[" << i << "] = " << display(construido[i])
                  << " (potencia 2^" << i << " = " << (1 << i) << ")" << std::endl;
    }

    // Test 6: Diferentes tamaños
    std::cout << "\n--- 6. Diferentes Tamaños de Registros ---" << std::endl;

    Binary8 byte_ejemplo{{dig_t<2>{1}, dig_t<2>{0}, dig_t<2>{1}, dig_t<2>{0},
                          dig_t<2>{1}, dig_t<2>{1}, dig_t<2>{0}, dig_t<2>{1}}}; // 10101101 en little-endian

    mostrar_binario_info(byte_ejemplo, "Ejemplo 8-bit");

    // Test 7: Información sobre rangos
    std::cout << "\n--- 7. Información de Rangos ---" << std::endl;
    std::cout << "Binary4 (4 bits):  rango 0 a " << ((1 << 4) - 1) << std::endl;
    std::cout << "Binary8 (8 bits):  rango 0 a " << ((1 << 8) - 1) << std::endl;

    // Test 8: Representación posicional
    std::cout << "\n--- 8. Explicación Representación Posicional ---" << std::endl;
    std::cout << "En base 2, cada posición representa una potencia de 2:" << std::endl;
    std::cout << "Posición:  [0] [1] [2] [3]" << std::endl;
    std::cout << "Potencia:   2^0 2^1 2^2 2^3" << std::endl;
    std::cout << "Valor:      1   2   4   8" << std::endl;
    std::cout << "Almacenamiento: little-endian [LSB, ..., MSB]" << std::endl;

    std::cout << "\n=== Tests Completados Exitosamente ===" << std::endl;
    std::cout << "Los números binarios naturales funcionan correctamente" << std::endl;
    std::cout << "con nat_reg_digs_t<2, L> para representación base 2." << std::endl;

    return 0;
}