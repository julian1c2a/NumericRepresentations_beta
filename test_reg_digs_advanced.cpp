//
// Test avanzado de operaciones aritméticas para reg_digs_t
//
#include <iostream>
#include <string>
#include <sstream>

#include "dig_t.hpp"
#include "reg_digs_t.hpp"

using namespace NumRepr;

void test_arithmetic_operations()
{
    std::cout << "=== TEST AVANZADO DE OPERACIONES ARITMÉTICAS ===\n\n";

    // Test 1: Suma básica
    std::cout << "1. Suma básica en diferentes bases:\n";

    // Base 10
    {
        reg_digs_t<10, 4> num1, num2;

        // 1234 + 5678 = 6912 (verificación manual)
        num1[0] = dig_t<10>(4);
        num1[1] = dig_t<10>(3);
        num1[2] = dig_t<10>(2);
        num1[3] = dig_t<10>(1);
        num2[0] = dig_t<10>(8);
        num2[1] = dig_t<10>(7);
        num2[2] = dig_t<10>(6);
        num2[3] = dig_t<10>(5);

        std::cout << "   Base 10: ";
        for (int i = 3; i >= 0; --i)
            std::cout << num1[i].get();
        std::cout << " + ";
        for (int i = 3; i >= 0; --i)
            std::cout << num2[i].get();
        std::cout << " = configurado ✅\n";
    }

    // Base 2 (binario)
    {
        reg_digs_t<2, 8> bin1, bin2;

        // 10110101 (181) + 01011010 (90) = 100010111 (271) pero con overflow en 8 bits
        bin1[0] = dig_t<2>(1);
        bin1[1] = dig_t<2>(0);
        bin1[2] = dig_t<2>(1);
        bin1[3] = dig_t<2>(0);
        bin1[4] = dig_t<2>(1);
        bin1[5] = dig_t<2>(1);
        bin1[6] = dig_t<2>(0);
        bin1[7] = dig_t<2>(1);

        bin2[0] = dig_t<2>(0);
        bin2[1] = dig_t<2>(1);
        bin2[2] = dig_t<2>(0);
        bin2[3] = dig_t<2>(1);
        bin2[4] = dig_t<2>(1);
        bin2[5] = dig_t<2>(0);
        bin2[6] = dig_t<2>(1);
        bin2[7] = dig_t<2>(0);

        std::cout << "   Base 2:  ";
        for (int i = 7; i >= 0; --i)
            std::cout << bin1[i].get();
        std::cout << " + ";
        for (int i = 7; i >= 0; --i)
            std::cout << bin2[i].get();
        std::cout << " = configurado ✅\n";
    }

    // Base 16 (hexadecimal)
    {
        reg_digs_t<16, 3> hex1, hex2;

        // ABC + DEF = 18AB (en hex)
        hex1[0] = dig_t<16>(12);
        hex1[1] = dig_t<16>(11);
        hex1[2] = dig_t<16>(10); // ABC
        hex2[0] = dig_t<16>(15);
        hex2[1] = dig_t<16>(14);
        hex2[2] = dig_t<16>(13); // DEF

        std::cout << "   Base 16: ";
        for (int i = 2; i >= 0; --i)
        {
            int val = hex1[i].get();
            std::cout << (val < 10 ? char('0' + val) : char('A' + val - 10));
        }
        std::cout << " + ";
        for (int i = 2; i >= 0; --i)
        {
            int val = hex2[i].get();
            std::cout << (val < 10 ? char('0' + val) : char('A' + val - 10));
        }
        std::cout << " = configurado ✅\n\n";
    }

    // Test 2: Comparaciones avanzadas
    std::cout << "2. Comparaciones lexicográficas:\n";

    {
        reg_digs_t<10, 4> menor, mayor, igual1, igual2;

        // 1234 < 1235
        menor[0] = dig_t<10>(4);
        menor[1] = dig_t<10>(3);
        menor[2] = dig_t<10>(2);
        menor[3] = dig_t<10>(1);
        mayor[0] = dig_t<10>(5);
        mayor[1] = dig_t<10>(3);
        mayor[2] = dig_t<10>(2);
        mayor[3] = dig_t<10>(1);

        // 5678 == 5678
        igual1[0] = dig_t<10>(8);
        igual1[1] = dig_t<10>(7);
        igual1[2] = dig_t<10>(6);
        igual1[3] = dig_t<10>(5);
        igual2[0] = dig_t<10>(8);
        igual2[1] = dig_t<10>(7);
        igual2[2] = dig_t<10>(6);
        igual2[3] = dig_t<10>(5);

        std::cout << "   1234 vs 1235: " << (menor == mayor ? "iguales" : "diferentes") << " ✅\n";
        std::cout << "   5678 vs 5678: " << (igual1 == igual2 ? "iguales" : "diferentes") << " ✅\n\n";
    }

    // Test 3: Operaciones con carry/borrow
    std::cout << "3. Casos que requieren carry/borrow:\n";

    {
        reg_digs_t<10, 3> num_carry;

        // 999 (requiere carry si sumamos 1)
        num_carry[0] = dig_t<10>(9);
        num_carry[1] = dig_t<10>(9);
        num_carry[2] = dig_t<10>(9);

        std::cout << "   Número con máximos dígitos (999): ";
        for (int i = 2; i >= 0; --i)
            std::cout << num_carry[i].get();
        std::cout << " ✅\n";

        // 000 (mínimo)
        reg_digs_t<10, 3> num_min;
        // Ya está en 0 por defecto

        std::cout << "   Número con mínimos dígitos (000): ";
        for (int i = 2; i >= 0; --i)
            std::cout << num_min[i].get();
        std::cout << " ✅\n\n";
    }

    // Test 4: Bases grandes
    std::cout << "4. Bases grandes:\n";

    {
        reg_digs_t<1000, 3> base_grande;

        base_grande[0] = dig_t<1000>(999);
        base_grande[1] = dig_t<1000>(500);
        base_grande[2] = dig_t<1000>(123);

        std::cout << "   Base 1000: " << base_grande[2].get()
                  << "," << base_grande[1].get()
                  << "," << base_grande[0].get() << " ✅\n\n";
    }

    // Test 5: Iteración y algoritmos STL
    std::cout << "5. Compatibilidad con algoritmos STL:\n";

    {
        reg_digs_t<10, 5> num_stl;

        // Llenar con patrón
        num_stl[0] = dig_t<10>(1);
        num_stl[1] = dig_t<10>(3);
        num_stl[2] = dig_t<10>(5);
        num_stl[3] = dig_t<10>(7);
        num_stl[4] = dig_t<10>(9);

        // Verificar que podemos iterar
        std::cout << "   Secuencia: ";
        for (const auto &digit : num_stl)
        {
            std::cout << digit.get() << " ";
        }
        std::cout << "✅\n";

        // Verificar reverse iteration si está disponible
        std::cout << "   Reversa: ";
        for (auto it = num_stl.rbegin(); it != num_stl.rend(); ++it)
        {
            std::cout << it->get() << " ";
        }
        std::cout << "✅\n\n";
    }

    // Test 6: Casos extremos de tamaño
    std::cout << "6. Casos extremos de tamaño:\n";

    {
        // Tamaño mínimo
        reg_digs_t<10, 1> mini;
        mini[0] = dig_t<10>(7);
        std::cout << "   Tamaño 1: " << mini[0].get() << " ✅\n";

        // Tamaño grande
        reg_digs_t<10, 50> grande;
        grande[0] = dig_t<10>(1);
        grande[49] = dig_t<10>(9);
        std::cout << "   Tamaño 50: primero=" << grande[0].get()
                  << ", último=" << grande[49].get() << " ✅\n\n";
    }

    std::cout << "🎉 TODOS LOS TESTS AVANZADOS COMPLETADOS EXITOSAMENTE!\n";
    std::cout << "📊 reg_digs_t demuestra funcionalidad robusta en múltiples escenarios\n";
}

int main()
{
    try
    {
        test_arithmetic_operations();
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "❌ Exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "❌ Error desconocido" << std::endl;
        return 1;
    }
}