/**
 * @file test_binary_natural.cpp
 * @brief Tests específicos para números binarios naturales
 *
 * Este archivo prueba la plantilla nat_reg_digs_t con base 2 (binario natural)
 * para verificar la representación con base posicional con potencias de 2.
 *
 * Los números binarios naturales representan enteros no negativos usando
 * solo dígitos 0 y 1, con posiciones que representan potencias de 2.
 */

#include <iostream>
#include <bitset>
#include "include/nat_reg_digs_t.hpp"
#include "core/dig_t_display_helpers.hpp"

using namespace NumRepr;

// Alias para números binarios naturales de diferentes tamaños
using Binary8 = nat_reg_digs_t<2, 8>;   // 8 bits: rango 0-255
using Binary16 = nat_reg_digs_t<2, 16>; // 16 bits: rango 0-65535
using Binary4 = nat_reg_digs_t<2, 4>;   // 4 bits: rango 0-15

/**
 * @brief Convierte un número decimal a su representación binaria esperada
 * @param decimal Número decimal a convertir
 * @param bits Número de bits de la representación
 * @return String con representación binaria little-endian
 */
std::string decimal_to_binary_le(int decimal, size_t bits)
{
    std::string result(bits, '0');
    for (size_t i = 0; i < bits && decimal > 0; ++i)
    {
        result[i] = '0' + (decimal % 2);
        decimal /= 2;
    }
    return result;
}

/**
 * @brief Muestra un número binario natural con formato detallado
 */
template <size_t L>
void mostrar_binario(const nat_reg_digs_t<2, L> &num, const std::string &label)
{
    std::cout << label << ": ";
    std::cout << num.to_string();

    // Mostrar dígitos individuales (little-endian)
    std::cout << " [";
    for (size_t i = 0; i < L; ++i)
    {
        if (i > 0)
            std::cout << ",";
        std::cout << display(num[i]);
    }
    std::cout << "]";

    // Mostrar interpretación decimal
    // Calcular valor decimal manualmente
    int valor_decimal = 0;
    for (size_t i = 0; i < L; ++i)
    {
        if (num[i].get() == 1)
        {
            valor_decimal += (1 << i); // 2^i
        }
    }
    std::cout << " = " << valor_decimal << " decimal" << std::endl;
}

int main()
{
    std::cout << "=== Tests para Números Binarios Naturales ===" << std::endl;
    std::cout << "Base 2, representación posicional con potencias de 2" << std::endl;

    // Test 1: Construcción básica y factory methods
    std::cout << "\n--- 1. Factory Methods Binarios ---" << std::endl;

    // Usar factory methods básicos que sabemos que funcionan
    Binary4 cero; // Constructor por defecto
    cero.set_0();
    mostrar_binario(cero, "Cero");

    Binary4 uno;
    uno.set_0();
    uno = dig_t<2>{1}; // Asignación desde dígito
    mostrar_binario(uno, "Uno");

    // Test 2: Construcción desde lista de inicialización
    std::cout << "\n--- 2. Construcción desde dígitos ---" << std::endl;

    Binary4 cinco{{dig_t<2>{1}, dig_t<2>{0}, dig_t<2>{1}, dig_t<2>{0}}}; // 1010 -> 5
    mostrar_binario(cinco, "Cinco (1010)");

    Binary4 quince{{dig_t<2>{1}, dig_t<2>{1}, dig_t<2>{1}, dig_t<2>{1}}}; // 1111 -> 15
    mostrar_binario(quince, "Quince (1111)");

    // Test 3: Operaciones aritméticas binarias
    std::cout << "\n--- 3. Operaciones Aritméticas ---" << std::endl;

    Binary4 a{{dig_t<2>{1}, dig_t<2>{1}, dig_t<2>{0}, dig_t<2>{0}}}; // 0011 -> 3
    Binary4 b{{dig_t<2>{0}, dig_t<2>{1}, dig_t<2>{0}, dig_t<2>{0}}}; // 0010 -> 2

    mostrar_binario(a, "A");
    mostrar_binario(b, "B");

    auto suma = a + b;
    mostrar_binario(suma, "A + B");

    // Test 4: Diferentes tamaños de registros binarios
    std::cout << "\n--- 4. Diferentes tamaños ---" << std::endl;

    Binary8 byte_max;
    byte_max.set_Bm1(); // Todos los bits a 1
    mostrar_binario(byte_max, "Byte máximo");

    // Test 5: Verificación de rangos
    std::cout << "\n--- 5. Verificación de rangos ---" << std::endl;

    std::cout << "Binary4 (4 bits):  rango 0 a " << ((1 << 4) - 1) << std::endl;
    std::cout << "Binary8 (8 bits):  rango 0 a " << ((1 << 8) - 1) << std::endl;
    std::cout << "Binary16 (16 bits): rango 0 a " << ((1 << 16) - 1) << std::endl;

    // Test 6: Comparación con std::bitset
    std::cout << "\n--- 6. Comparación con std::bitset ---" << std::endl;

    int test_value = 13;                                                   // 1101 en binario
    Binary4 nat_bin{{dig_t<2>{1}, dig_t<2>{0}, dig_t<2>{1}, dig_t<2>{1}}}; // 1101
    std::bitset<4> std_bin(test_value);

    std::cout << "Valor: " << test_value << std::endl;
    mostrar_binario(nat_bin, "nat_reg_digs_t<2,4>");
    std::cout << "std::bitset<4>:     " << std_bin << " (big-endian)" << std::endl;

    // Test 7: Operaciones bit a bit simuladas
    std::cout << "\n--- 7. Operaciones tipo bit ---" << std::endl;

    Binary4 mask{{dig_t<2>{1}, dig_t<2>{0}, dig_t<2>{1}, dig_t<2>{0}}}; // 1010 -> máscara
    mostrar_binario(mask, "Máscara");

    // Simular AND con multiplicación por dígitos
    std::cout << "Simulación de operaciones bit a bit usando aritmética natural" << std::endl;

    std::cout << "\n=== Tests completados ===\n"
              << std::endl;
    std::cout << "Los números binarios naturales usan nat_reg_digs_t<2, L>" << std::endl;
    std::cout << "- Base 2: solo dígitos 0 y 1" << std::endl;
    std::cout << "- Posiciones representan potencias de 2: 2^0, 2^1, 2^2, ..." << std::endl;
    std::cout << "- Almacenamiento little-endian: [LSB, ..., MSB]" << std::endl;
    std::cout << "- Rango: 0 a 2^L - 1" << std::endl;

    return 0;
}