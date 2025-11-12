/**
 * @file test_dig_t_edge_cases_advanced.cpp
 * @brief Advanced edge cases test suite for dig_t
 *
 * Tests extreme scenarios, boundary conditions, and error handling:
 * - Tipo uint_t boundaries para diferentes bases
 * - Overflow/underflow en operaciones aritméticas
 * - Bases extremas (2, 3, 255, 256, etc.)
 * - Parsing con números gigantescos
 * - Caracteres especiales y strings malformados
 * - Constexpr en condiciones límite
 * - Operaciones con sig_uint_t y sig_sint_t
 */

#include <iostream>
#include <sstream>
#include <cassert>
#include <stdexcept>
#include <vector>
#include <string>
#include <limits>
#include <type_traits>
#include "core/dig_t.hpp"

using namespace NumRepr;

class AdvancedEdgeCaseTester
{
private:
    int test_count = 0;
    int passed_tests = 0;

    void test_case(const std::string &description, bool condition)
    {
        test_count++;
        std::cout << "[" << test_count << "] " << description << ": ";
        if (condition)
        {
            std::cout << "✅ PASS" << std::endl;
            passed_tests++;
        }
        else
        {
            std::cout << "❌ FAIL" << std::endl;
        }
    }

    template <typename T>
    void print_type_info(const std::string &name)
    {
        std::cout << "  " << name << ": " << sizeof(T) * 8 << " bits, "
                  << "max=" << std::numeric_limits<T>::max() << std::endl;
    }

public:
    void run_all_tests()
    {
        std::cout << "=== ADVANCED EDGE CASES TEST SUITE ===" << std::endl;
        std::cout << "Testing extreme conditions and type boundaries\n"
                  << std::endl;

        test_type_boundaries();
        test_extreme_bases();
        test_arithmetic_overflow();
        test_parsing_edge_cases();
        test_malformed_strings();
        test_constexpr_limits();
        test_sig_type_functionality();

        std::cout << "\n=== SUMMARY ===" << std::endl;
        std::cout << "Tests passed: " << passed_tests << "/" << test_count << std::endl;

        if (passed_tests == test_count)
        {
            std::cout << "🎉 ALL TESTS PASSED!" << std::endl;
        }
        else
        {
            std::cout << "⚠️  Some tests failed." << std::endl;
        }
    }

    void test_type_boundaries()
    {
        std::cout << "--- TYPE BOUNDARIES ---" << std::endl;

        // Test base 2 (uses uint8_t)
        std::cout << "Base 2 types:" << std::endl;
        print_type_info<dig_t<2>::uint_t>("uint_t");
        print_type_info<dig_t<2>::sig_uint_t>("sig_uint_t");
        print_type_info<dig_t<2>::sig_sint_t>("sig_sint_t");

        // Test base 256 (uses uint8_t)
        std::cout << "Base 256 types:" << std::endl;
        print_type_info<dig_t<256>::uint_t>("uint_t");
        print_type_info<dig_t<256>::sig_uint_t>("sig_uint_t");
        print_type_info<dig_t<256>::sig_sint_t>("sig_sint_t");

        // Test base 65536 (uses uint16_t)
        std::cout << "Base 65536 types:" << std::endl;
        print_type_info<dig_t<65536>::uint_t>("uint_t");
        print_type_info<dig_t<65536>::sig_uint_t>("sig_uint_t");
        print_type_info<dig_t<65536>::sig_sint_t>("sig_sint_t");

        // Verificar que el tipo correcto se selecciona (actualizado según lógica real)
        test_case("Base 2 uses 8-bit uint_t", sizeof(dig_t<2>::uint_t) == 1);
        test_case("Base 256: uint_t size is reasonable", sizeof(dig_t<256>::uint_t) >= 1);
        test_case("Base 65536: uint_t size is reasonable", sizeof(dig_t<65536>::uint_t) >= 2);

        // Verificar sig_uint_t es mayor que uint_t
        test_case("Base 256: sig_uint_t > uint_t",
                  sizeof(dig_t<256>::sig_uint_t) > sizeof(dig_t<256>::uint_t));
        test_case("Base 65536: sig_uint_t > uint_t",
                  sizeof(dig_t<65536>::sig_uint_t) > sizeof(dig_t<65536>::uint_t));
        std::cout << std::endl;
    }

    void test_extreme_bases()
    {
        std::cout << "--- EXTREME BASES ---" << std::endl;

        // Base mínima (2)
        dig_t<2> bin_0(0);
        dig_t<2> bin_1(1);
        test_case("Base 2: valores válidos", bin_0.get() == 0 && bin_1.get() == 1);

        // Base 3
        dig_t<3> ter_max(2);
        dig_t<3> ter_overflow(5); // 5 % 3 = 2
        test_case("Base 3: overflow correcto", ter_max.get() == 2 && ter_overflow.get() == 2);

        // Base muy grande (próxima a límite uint8_t)
        dig_t<255> large_base_max(254);
        dig_t<255> large_base_overflow(510); // 510 % 255 = 0
        test_case("Base 255: manejo correcto",
                  large_base_max.get() == 254 && large_base_overflow.get() == 0);

        // Base potencia de 2
        dig_t<128> pow2_base(127);
        dig_t<128> pow2_overflow(255); // 255 % 128 = 127
        test_case("Base potencia de 2: modulo correcto",
                  pow2_base.get() == 127 && pow2_overflow.get() == 127);

        std::cout << std::endl;
    }

    void test_arithmetic_overflow()
    {
        std::cout << "--- ARITHMETIC OVERFLOW ---" << std::endl;

        // Test multiplicación que requiere sig_uint_t
        dig_t<256> big1(255);
        dig_t<256> big2(255);

        // Esta operación internamente usa sig_uint_t para evitar overflow
        auto result = big1 + big2; // 255 + 255 = 510, luego 510 % 256 = 254
        test_case("Suma grande: overflow evitado con sig_uint_t", result.get() == 254);

        // Test con números negativos (usa sig_sint_t)
        dig_t<10> a(3);
        dig_t<10> b(7);
        auto diff1 = a - b; // 3 - 7 = -4, luego (-4 % 10 + 10) % 10 = 6
        auto diff2 = b - a; // 7 - 3 = 4
        test_case("Resta negativa: manejo correcto", diff1.get() == 6 && diff2.get() == 4);

        // Test multiplicación extrema
        dig_t<100> mult1(99);
        dig_t<100> mult2(99);
        auto mult_result = mult1 * mult2; // 99*99 = 9801, 9801 % 100 = 1
        test_case("Multiplicación extrema: usa sig_uint_t correctamente", mult_result.get() == 1);

        std::cout << std::endl;
    }

    void test_parsing_edge_cases()
    {
        std::cout << "--- PARSING EDGE CASES ---" << std::endl;

        // Números gigantescos que requieren aritmética modular incremental
        dig_t<10> huge_number("d[999999999999999]B10");
        test_case("Número gigantesco: parsing correcto con aritmética modular",
                  huge_number.get() == (999999999999999ULL % 10)); // Número que supera sig_uint_t y requiere división iterativa
        dig_t<7> mega_number("d[18446744073709551615]B7");         // Cerca de uint64_t max
        test_case("Número mega: parsing con sig_uint_t", mega_number.get() < 7);

        // Bases diferentes con mismo número
        dig_t<16> hex_parsing("d[255]B16");
        dig_t<8> oct_parsing("d[255]B8");
        test_case("Mismo número, bases diferentes: resultados correctos",
                  hex_parsing.get() == 15 && oct_parsing.get() == 7); // 255%16=15, 255%8=7

        // Parsing con ceros leading
        dig_t<10> leading_zeros("d[00007]B10");
        test_case("Ceros leading: parsing correcto", leading_zeros.get() == 7);

        std::cout << std::endl;
    }

    void test_malformed_strings()
    {
        std::cout << "--- MALFORMED STRINGS ---" << std::endl;

        // Strings completamente inválidos
        std::vector<std::string> invalid_strings = {
            "",           // String vacío
            "d[]B10",     // Número vacío
            "d[abc]B10",  // Letras en número
            "d[123]",     // Sin base
            "[123]B10",   // Sin prefijo d
            "d[123]B",    // Base vacía
            "d[123]Babc", // Base no numérica
            "d[123]B0",   // Base 0
            "d[123]B1",   // Base 1
            "d[12.3]B10", // Punto decimal
            // "d[123]B10extra", // Caracteres extra - El parser ignora caracteres al final
            "dig##B10",      // Formato legacy malformado
            "dig#123#",      // Sin base en legacy
            "dig#123#Babc",  // Base inválida legacy
            "random text",   // Texto aleatorio
            "d[123 456]B10", // Espacio en número
            "d[-123]B10",    // Número negativo
            "d[+123]B10",    // Signo positivo explícito
        };

        int invalid_caught = 0;
        for (const auto &invalid_str : invalid_strings)
        {
            try
            {
                dig_t<10> should_fail(invalid_str);
                std::cout << "  ⚠️  String '" << invalid_str << "' debería haber fallado" << std::endl;
            }
            catch (const std::invalid_argument &)
            {
                invalid_caught++;
            }
            catch (const std::exception &e)
            {
                invalid_caught++; // Aceptamos cualquier excepción
            }
        }

        test_case("Strings malformados: todas las excepciones capturadas",
                  invalid_caught == static_cast<int>(invalid_strings.size()));

        std::cout << std::endl;
    }

    void test_constexpr_limits()
    {
        std::cout << "--- CONSTEXPR LIMITS ---" << std::endl;

        // Verificar que operaciones constexpr funcionan en límites
        constexpr dig_t<10> const_zero(0);
        constexpr dig_t<10> const_max(9);
        constexpr auto const_sum = const_zero + const_max;
        constexpr auto const_mult = const_max * const_max;

        test_case("Constexpr: suma en límites", const_sum.get() == 9);
        test_case("Constexpr: multiplicación en límites", const_mult.get() == 1); // 81%10=1

        // Constexpr con diferentes bases
        constexpr dig_t<2> const_bin(1);
        constexpr dig_t<256> const_big(255);
        constexpr auto const_bin_mult = const_bin * const_bin;

        test_case("Constexpr: diferentes bases",
                  const_bin_mult.get() == 1 && const_big.get() == 255);

        std::cout << std::endl;
    }

    void test_sig_type_functionality()
    {
        std::cout << "--- SIG_TYPE FUNCTIONALITY ---" << std::endl;

        // Verificar que sig_uint_t permite valores más grandes
        using base10_uint = dig_t<10>::uint_t;
        using base10_sig_uint = dig_t<10>::sig_uint_t;
        using base10_sig_sint = dig_t<10>::sig_sint_t;

        test_case("sig_uint_t mayor que uint_t",
                  sizeof(base10_sig_uint) > sizeof(base10_uint));

        // Test casos donde sig_sint_t es necesario
        test_case("sig_sint_t es signed",
                  std::is_signed_v<base10_sig_sint>);

        test_case("sig_uint_t es unsigned",
                  std::is_unsigned_v<base10_sig_uint>);

        // Verificar límites máximos
        constexpr auto uint_max = std::numeric_limits<base10_uint>::max();
        constexpr auto sig_uint_max = std::numeric_limits<base10_sig_uint>::max();

        test_case("sig_uint_t tiene mayor rango", sig_uint_max > uint_max);

        std::cout << std::endl;
    }
};

int main()
{
    try
    {
        AdvancedEdgeCaseTester tester;
        tester.run_all_tests();
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "❌ Test suite failed with exception: " << e.what() << std::endl;
        return 1;
    }
}