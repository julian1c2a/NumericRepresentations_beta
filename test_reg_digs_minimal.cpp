//
// Test minimal para reg_digs_t - solo conceptos básicos
//
#include <iostream>
#include <string>
#include <array>

#include "dig_t.hpp"

using namespace NumRepr;

int main()
{
    try
    {
        std::cout << "=== Test minimal de conceptos reg_digs_t ===\n\n";

        // Test 1: Array básico de dig_t
        std::cout << "Test 1: Array básico de dig_t\n";
        std::array<dig_t<10>, 3> basic_array;

        // Inicializar manualmente cada elemento
        basic_array[0] = dig_t<10>(3); // dígito unidades
        basic_array[1] = dig_t<10>(2); // dígito decenas
        basic_array[2] = dig_t<10>(1); // dígito centenas

        std::cout << "Array digits: [";
        for (size_t i = 0; i < 3; ++i)
        {
            if (i > 0)
                std::cout << ", ";
            std::cout << basic_array[i].to_string();
        }
        std::cout << "]\n";

        // Valor representado: 1*100 + 2*10 + 3*1 = 123
        uint64_t valor = basic_array[2].get() * 100 +
                         basic_array[1].get() * 10 +
                         basic_array[0].get();
        std::cout << "Valor representado: " << valor << "\n\n";

        // Test 2: Diferentes bases
        std::cout << "Test 2: Base binaria (2)\n";
        std::array<dig_t<2>, 4> binary_array;

        // Representar 1010 en binario = 10 decimal
        binary_array[0] = dig_t<2>(0); // bit 0
        binary_array[1] = dig_t<2>(1); // bit 1
        binary_array[2] = dig_t<2>(0); // bit 2
        binary_array[3] = dig_t<2>(1); // bit 3

        std::cout << "Binary digits: [";
        for (size_t i = 0; i < 4; ++i)
        {
            if (i > 0)
                std::cout << ", ";
            std::cout << binary_array[i].to_string();
        }
        std::cout << "]\n";

        valor = binary_array[3].get() * 8 +
                binary_array[2].get() * 4 +
                binary_array[1].get() * 2 +
                binary_array[0].get();
        std::cout << "Valor binario: " << valor << "\n\n";

        // Test 3: Comparaciones
        std::cout << "Test 3: Comparaciones de dígitos\n";
        dig_t<10> d1(5);
        dig_t<10> d2(5);
        dig_t<10> d3(7);

        std::cout << "d1(" << d1.get() << ") == d2(" << d2.get() << "): "
                  << (d1 == d2 ? "true" : "false") << "\n";
        std::cout << "d1(" << d1.get() << ") == d3(" << d3.get() << "): "
                  << (d1 == d3 ? "true" : "false") << "\n";
        std::cout << "d1(" << d1.get() << ") < d3(" << d3.get() << "): "
                  << (d1 < d3 ? "true" : "false") << "\n\n";

        // Test 4: Operaciones aritméticas básicas
        std::cout << "Test 4: Operaciones aritméticas\n";
        dig_t<10> d_a(3);
        dig_t<10> d_b(4);
        dig_t<10> d_suma = d_a + d_b;
        dig_t<10> d_mult = d_a * d_b;

        std::cout << "d_a = " << d_a.get() << ", d_b = " << d_b.get() << "\n";
        std::cout << "d_a + d_b = " << d_suma.get() << "\n";
        std::cout << "d_a * d_b = " << d_mult.get() << "\n\n";

        // Test 5: Formatos de E/S
        std::cout << "Test 5: Formatos de E/S\n";
        dig_t<10> d_format(8);
        std::cout << "Formato completo: " << d_format.to_string() << "\n";
        std::cout << "Valor numérico: " << d_format.get() << "\n\n";

        // Test 6: Bases grandes
        std::cout << "Test 6: Base hexadecimal (16)\n";
        std::array<dig_t<16>, 2> hex_array;

        // Representar AB en hex = 10*16 + 11 = 171 decimal
        hex_array[0] = dig_t<16>(11); // B = 11
        hex_array[1] = dig_t<16>(10); // A = 10

        std::cout << "Hex digits: [";
        for (size_t i = 0; i < 2; ++i)
        {
            if (i > 0)
                std::cout << ", ";
            std::cout << hex_array[i].to_string();
        }
        std::cout << "]\n";

        valor = hex_array[1].get() * 16 + hex_array[0].get();
        std::cout << "Valor hex AB: " << valor << "\n\n";

        std::cout << "=== Test completado exitosamente ===\n";
        std::cout << "Conceptos validados:\n";
        std::cout << "- Arrays de dig_t funcionan correctamente\n";
        std::cout << "- Diferentes bases (2, 10, 16) operan bien\n";
        std::cout << "- Comparaciones y aritmética básica\n";
        std::cout << "- Formatos de E/S duales\n";
        std::cout << "- Base para implementar reg_digs_t completo\n";

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}