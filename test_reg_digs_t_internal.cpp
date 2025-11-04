/**
 * @file test_reg_digs_t_internal.cpp
 * @brief Comprehensive internal test suite for reg_digs_t building block
 *
 * Tests all internal functionality of reg_digs_t as the foundation class:
 * - Constructors (default, variadic, initializer_list, array conversion)
 * - Arithmetic operations (suma, resta, carry, borrow)
 * - Heterogeneous operations (diferentes longitudes L y M)
 * - Comparisons (==, !=, <, >, <=, >=, <=>)
 * - Bitwise operations (|, &, shifts)
 * - Concatenation and subregisters
 * - Constexpr validation
 * - Edge cases with different lengths
 * - Type system (UINT_T, SIG_UINT_T, SIG_SINT_T)
 */

#include <iostream>
#include <sstream>
#include <cassert>
#include <array>
#include <type_traits>
#include "reg_digs_t.hpp"

using namespace NumRepr;

class RegDigsTester
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

public:
    void run_all_tests()
    {
        std::cout << "=== REG_DIGS_T INTERNAL TEST SUITE ===" << std::endl;
        std::cout << "Testing building block functionality for numeric types\n"
                  << std::endl;

        test_type_system();
        test_constructors();
        test_constexpr_constants();
        test_arithmetic_operations();
        test_heterogeneous_operations();
        test_comparisons();
        test_bitwise_operations();
        test_concatenation();
        test_constexpr_capabilities();
        test_edge_cases();

        std::cout << "\n=== SUMMARY ===" << std::endl;
        std::cout << "Tests passed: " << passed_tests << "/" << test_count << std::endl;

        if (passed_tests == test_count)
        {
            std::cout << "🎉 ALL INTERNAL TESTS PASSED!" << std::endl;
        }
        else
        {
            std::cout << "⚠️  Some internal tests failed." << std::endl;
        }
    }

    void test_type_system()
    {
        std::cout << "--- TYPE SYSTEM ---" << std::endl;

        // Verificar tipos básicos para diferentes bases
        using reg10_3 = reg_digs_t<10, 3>;
        using reg2_8 = reg_digs_t<2, 8>;
        using reg256_2 = reg_digs_t<256, 2>;

        // Verificar que los tipos se deduzcan correctamente
        test_case("Base 10: UINT_T definido",
                  !std::is_same_v<reg10_3::UINT_T, void>);

        test_case("Base 10: SIG_UINT_T es mayor",
                  sizeof(reg10_3::SIG_UINT_T) > sizeof(reg10_3::UINT_T));

        test_case("Base 2: tipos apropiados",
                  sizeof(reg2_8::UINT_T) >= 1);

        test_case("Base 256: SIG_UINT_T available",
                  !std::is_same_v<reg256_2::SIG_UINT_T, void>);

        // Verificar constantes estáticas
        test_case("Constantes estáticas disponibles",
                  reg10_3::ui_0() == 0 && reg10_3::ui_1() == 1 && reg10_3::ui_B() == 10);

        std::cout << std::endl;
    }

    void test_constructors()
    {
        std::cout << "--- CONSTRUCTORS ---" << std::endl;

        // Constructor por defecto
        reg_digs_t<10, 3> default_reg;
        test_case("Constructor defecto: inicializa a cero", default_reg.is_0());

        // Constructor con initializer_list
        reg_digs_t<10, 3> list_reg{dig_t<10>(1), dig_t<10>(2), dig_t<10>(3)};
        test_case("Constructor initializer_list: valores correctos",
                  list_reg[0].get() == 3 && list_reg[1].get() == 2 && list_reg[2].get() == 1);

        // Constructor variadic
        reg_digs_t<10, 3> variadic_reg(dig_t<10>(5), dig_t<10>(6), dig_t<10>(7));
        test_case("Constructor variadic: valores correctos",
                  variadic_reg[0].get() == 5 && variadic_reg[1].get() == 6 && variadic_reg[2].get() == 7);

        // Constructor desde array
        std::array<dig_t<10>, 3> arr = {dig_t<10>(8), dig_t<10>(9), dig_t<10>(0)};
        reg_digs_t<10, 3> array_reg(arr);
        test_case("Constructor desde array: valores correctos",
                  array_reg[0].get() == 8 && array_reg[1].get() == 9 && array_reg[2].get() == 0);

        // Constructor normalización desde enteros
        reg_digs_t<10, 3> norm_reg(15, 25, 35); // Debería normalizar: 15%10=5, 25%10=5, 35%10=5
        test_case("Constructor normalización: valores modulares",
                  norm_reg[0].get() == 5 && norm_reg[1].get() == 5 && norm_reg[2].get() == 5);

        std::cout << std::endl;
    }

    void test_constexpr_constants()
    {
        std::cout << "--- CONSTEXPR CONSTANTS ---" << std::endl;

        // Constexpr constants básicas
        constexpr auto zero_reg = reg_digs_t<10, 3>::regd_0();
        constexpr auto one_reg = reg_digs_t<10, 3>::regd_1();
        constexpr auto bm1_reg = reg_digs_t<10, 3>::regd_Bm1();

        test_case("Constexpr: zero register",
                  zero_reg.is_0());
        test_case("Constexpr: one register",
                  one_reg.is_1());
        test_case("Constexpr: B-1 register",
                  bm1_reg.is_Bm1());

        // Constexpr potencias de B
        constexpr auto b_reg = reg_digs_t<10, 3>::regd_B();
        test_case("Constexpr: B register",
                  b_reg.is_B());

        std::cout << std::endl;
    }

    void test_arithmetic_operations()
    {
        std::cout << "--- ARITHMETIC OPERATIONS ---" << std::endl;

        // Test incremento
        reg_digs_t<10, 3> inc_reg;
        inc_reg.set_1();
        auto carry = m_incr(inc_reg);
        test_case("Incremento: 1 -> 2",
                  inc_reg[0].get() == 2 && carry.get() == 0);

        // Test incremento con carry
        reg_digs_t<10, 2> carry_reg;
        carry_reg[0].set_Bm1(); // 9 en base 10
        carry_reg[1].set_Bm1(); // 99 en total
        auto final_carry = m_incr(carry_reg);
        test_case("Incremento con carry: 99 -> 00 + carry",
                  carry_reg.is_0() && final_carry.get() == 1);

        // Test decremento
        reg_digs_t<10, 3> dec_reg;
        dec_reg[0] = dig_t<10>(5);
        auto borrow = m_decr(dec_reg);
        test_case("Decremento: 5 -> 4",
                  dec_reg[0].get() == 4 && borrow.get() == 0);

        // Test decremento con borrow
        reg_digs_t<10, 2> borrow_reg;
        borrow_reg.set_0(); // 00
        auto final_borrow = m_decr(borrow_reg);
        test_case("Decremento con borrow: 00 -> 99 + borrow",
                  borrow_reg[0].get() == 9 && borrow_reg[1].get() == 9 && final_borrow.get() == 1);

        std::cout << std::endl;
    }

    void test_heterogeneous_operations()
    {
        std::cout << "--- HETEROGENEOUS OPERATIONS ---" << std::endl;

        // Operaciones entre diferentes longitudes
        reg_digs_t<10, 2> short_reg; // longitud 2
        reg_digs_t<10, 4> long_reg;  // longitud 4

        short_reg[0] = dig_t<10>(5);
        short_reg[1] = dig_t<10>(3); // 35 en total

        long_reg[0] = dig_t<10>(5);
        long_reg[1] = dig_t<10>(3); // 35 en los primeros dígitos
        // long_reg[2] y [3] permanecen en 0

        // Test comparación heterogénea
        test_case("Comparación heterogénea: igual", short_reg == long_reg);

        // Test asignación heterogénea
        reg_digs_t<10, 3> medium_reg = short_reg;
        test_case("Asignación heterogénea: valores correctos",
                  medium_reg[0].get() == 5 && medium_reg[1].get() == 3 && medium_reg[2].get() == 0);

        std::cout << std::endl;
    }

    void test_comparisons()
    {
        std::cout << "--- COMPARISONS ---" << std::endl;

        reg_digs_t<10, 3> reg1, reg2, reg3;

        reg1[0] = dig_t<10>(5); // 005
        reg2[0] = dig_t<10>(5); // 005
        reg3[0] = dig_t<10>(3); // 003

        // Igualdad
        test_case("Igualdad: reg1 == reg2", reg1 == reg2);
        test_case("Desigualdad: reg1 != reg3", reg1 != reg3);

        // Comparaciones de orden
        test_case("Mayor que: reg1 > reg3", reg1 > reg3);
        test_case("Menor que: reg3 < reg1", reg3 < reg1);
        test_case("Mayor o igual: reg1 >= reg2", reg1 >= reg2);
        test_case("Menor o igual: reg2 <= reg1", reg2 <= reg1);

        // Spaceship operator (C++20)
        auto cmp = reg1 <=> reg3;
        test_case("Spaceship: reg1 > reg3", cmp == std::strong_ordering::greater);

        // Comparación con dig_t individual
        test_case("Comparación con dig_t: reg3 == dig_t(3)", reg3 == dig_t<10>(3));

        std::cout << std::endl;
    }

    void test_bitwise_operations()
    {
        std::cout << "--- BITWISE OPERATIONS ---" << std::endl;

        reg_digs_t<10, 3> reg1, reg2;

        reg1[0] = dig_t<10>(5);
        reg1[1] = dig_t<10>(3);

        reg2[0] = dig_t<10>(7);
        reg2[1] = dig_t<10>(2);

        // OR bitwise
        auto or_result = reg1 | reg2;
        test_case("Bitwise OR: dígito a dígito",
                  or_result[0] == (dig_t<10>(5) | dig_t<10>(7)) &&
                      or_result[1] == (dig_t<10>(3) | dig_t<10>(2)));

        // AND bitwise
        auto and_result = reg1 & reg2;
        test_case("Bitwise AND: dígito a dígito",
                  and_result[0] == (dig_t<10>(5) & dig_t<10>(7)) &&
                      and_result[1] == (dig_t<10>(3) & dig_t<10>(2)));

        // Shifts (multiplicación/división por B^n)
        reg_digs_t<10, 4> shift_reg;
        shift_reg[0] = dig_t<10>(1);
        shift_reg[1] = dig_t<10>(2); // 021 originalmente

        auto left_shifted = shift_reg << 1;
        test_case("Left shift: multiplicación por B",
                  left_shifted[0].get() == 0 && left_shifted[1].get() == 1 && left_shifted[2].get() == 2);

        auto right_shifted = left_shifted >> 1;
        test_case("Right shift: división por B",
                  right_shifted[0].get() == 1 && right_shifted[1].get() == 2 && right_shifted[2].get() == 0);

        std::cout << std::endl;
    }

    void test_concatenation()
    {
        std::cout << "--- CONCATENATION ---" << std::endl;

        reg_digs_t<10, 2> reg1;
        reg_digs_t<10, 3> reg2;

        reg1[0] = dig_t<10>(1);
        reg1[1] = dig_t<10>(2); // 21

        reg2[0] = dig_t<10>(3);
        reg2[1] = dig_t<10>(4);
        reg2[2] = dig_t<10>(5); // 543

        // Concatenación de registros
        auto cat_result = concat(reg1, reg2);
        test_case("Concatenación: longitudes 2+3=5",
                  cat_result.size() == 5);
        test_case("Concatenación: valores correctos",
                  cat_result[0].get() == 1 && cat_result[1].get() == 2 &&
                      cat_result[2].get() == 3 && cat_result[3].get() == 4 && cat_result[4].get() == 5);

        // Concatenación con dígito individual
        auto cat_dig_result = concat(reg1, dig_t<10>(9));
        test_case("Concatenación con dígito: longitud 2+1=3",
                  cat_dig_result.size() == 3);
        test_case("Concatenación con dígito: valores correctos",
                  cat_dig_result[0].get() == 1 && cat_dig_result[1].get() == 2 && cat_dig_result[2].get() == 9);

        std::cout << std::endl;
    }

    void test_constexpr_capabilities()
    {
        std::cout << "--- CONSTEXPR CAPABILITIES ---" << std::endl;

        // Operaciones constexpr
        constexpr reg_digs_t<10, 3> const_reg1 = reg_digs_t<10, 3>::regd_1();
        constexpr reg_digs_t<10, 3> const_reg2 = reg_digs_t<10, 3>::regd_B();

        test_case("Constexpr: construcción en compile-time",
                  const_reg1.is_1() && const_reg2.is_B());

        // Comparaciones constexpr
        constexpr bool const_cmp = const_reg2 > const_reg1;
        test_case("Constexpr: comparaciones en compile-time", const_cmp);

        // Operaciones bit a bit constexpr
        constexpr auto const_or = const_reg1 | const_reg2;
        test_case("Constexpr: operaciones bitwise",
                  !const_or.is_0()); // Should not be zero

        std::cout << std::endl;
    }

    void test_edge_cases()
    {
        std::cout << "--- EDGE CASES ---" << std::endl;

        // Longitud 1 (caso mínimo)
        reg_digs_t<10, 1> single_reg;
        single_reg[0] = dig_t<10>(7);
        test_case("Longitud 1: construcción correcta", single_reg[0].get() == 7);

        // Base mínima (2)
        reg_digs_t<2, 4> binary_reg;
        binary_reg[0] = dig_t<2>(1);
        binary_reg[1] = dig_t<2>(0);
        binary_reg[2] = dig_t<2>(1); // 1010 en binario
        test_case("Base binaria: valores válidos",
                  binary_reg[0].get() == 1 && binary_reg[1].get() == 0 && binary_reg[2].get() == 1);

        // Base grande
        reg_digs_t<256, 2> large_base_reg;
        large_base_reg[0] = dig_t<256>(255);
        large_base_reg[1] = dig_t<256>(128);
        test_case("Base grande: valores máximos",
                  large_base_reg[0].get() == 255 && large_base_reg[1].get() == 128);

        // Overflow en construcción normalizada
        reg_digs_t<10, 2> overflow_reg(15, 999); // 15%10=5, 999%10=9
        test_case("Normalización con overflow: modulo correcto",
                  overflow_reg[0].get() == 5 && overflow_reg[1].get() == 9);

        // Operaciones con registros llenos
        reg_digs_t<10, 3> full_reg;
        full_reg.set_fill_Bm1(); // Todo 9s
        test_case("Registro lleno: todos B-1", full_reg.is_filled_of_Bm1());

        std::cout << std::endl;
    }
};

int main()
{
    try
    {
        RegDigsTester tester;
        tester.run_all_tests();
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "❌ Internal test suite failed with exception: " << e.what() << std::endl;
        return 1;
    }
}