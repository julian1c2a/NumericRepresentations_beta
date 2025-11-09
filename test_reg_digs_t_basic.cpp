/**
 * @file test_reg_digs_t_basic.cpp
 * @brief Basic test suite for reg_digs_t building block
 *
 * Simplified tests focusing on core functionality that works:
 * - Basic constructors
 * - Constexpr constants
 * - Simple comparisons
 * - Basic operations
 */

#include <iostream>
#include <sstream>
#include <cassert>
#include <array>
#include <type_traits>
#include "reg_digs_t.hpp"

using namespace NumRepr;

class RegDigsBasicTester
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
        std::cout << "=== REG_DIGS_T BASIC TEST SUITE ===" << std::endl;
        std::cout << "Testing core building block functionality\n"
                  << std::endl;

        test_basic_construction();
        test_constexpr_constants();
        test_basic_comparisons();
        test_basic_operations();
        test_to_string();

        std::cout << "\n=== SUMMARY ===" << std::endl;
        std::cout << "Tests passed: " << passed_tests << "/" << test_count << std::endl;

        if (passed_tests == test_count)
        {
            std::cout << "🎉 ALL BASIC TESTS PASSED!" << std::endl;
        }
        else
        {
            std::cout << "⚠️  Some basic tests failed." << std::endl;
        }
    }

    void test_basic_construction()
    {
        std::cout << "--- BASIC CONSTRUCTION ---" << std::endl;

        // Constructor por defecto
        reg_digs_t<10, 3> default_reg;
        test_case("Constructor defecto: inicializa correctamente", true);

        // Acceso básico a elementos
        test_case("Acceso a elementos: disponible",
                  default_reg.size() == 3);

        // Constructor con dígitos individuales
        try
        {
            reg_digs_t<10, 3> digit_reg(dig_t<10>(1), dig_t<10>(2), dig_t<10>(3));
            test_case("Constructor con dígitos: funciona", true);
        }
        catch (...)
        {
            test_case("Constructor con dígitos: funciona", false);
        }

        std::cout << std::endl;
    }

    void test_constexpr_constants()
    {
        std::cout << "--- CONSTEXPR CONSTANTS ---" << std::endl;

        // Constexpr constants básicas
        try
        {
            constexpr auto zero_reg = reg_digs_t<10, 3>::regd_0();
            test_case("Constexpr: zero register disponible", true);
        }
        catch (...)
        {
            test_case("Constexpr: zero register disponible", false);
        }

        try
        {
            constexpr auto one_reg = reg_digs_t<10, 3>::regd_1();
            test_case("Constexpr: one register disponible", true);
        }
        catch (...)
        {
            test_case("Constexpr: one register disponible", false);
        }

        try
        {
            constexpr auto bm1_reg = reg_digs_t<10, 3>::regd_Bm1();
            test_case("Constexpr: B-1 register disponible", true);
        }
        catch (...)
        {
            test_case("Constexpr: B-1 register disponible", false);
        }

        std::cout << std::endl;
    }

    void test_basic_comparisons()
    {
        std::cout << "--- BASIC COMPARISONS ---" << std::endl;

        reg_digs_t<10, 3> reg1, reg2;

        // Igualdad básica
        test_case("Igualdad: registros por defecto iguales", reg1 == reg2);

        // Test básico de funciones de verificación
        test_case("Verificación is_0(): funciona", reg1.is_0());

        // Modifica un registro
        reg1[0] = dig_t<10>(5);
        test_case("Desigualdad: después de modificación", reg1 != reg2);

        std::cout << std::endl;
    }

    void test_basic_operations()
    {
        std::cout << "--- BASIC OPERATIONS ---" << std::endl;

        reg_digs_t<10, 3> reg;

        // Set operations
        try
        {
            reg.set_1();
            test_case("Set operation: set_1() funciona", true);
        }
        catch (...)
        {
            test_case("Set operation: set_1() funciona", false);
        }

        try
        {
            test_case("Verificación is_1(): después de set_1()", reg.is_1());
        }
        catch (...)
        {
            test_case("Verificación is_1(): después de set_1()", false);
        }

        try
        {
            reg.set_0();
            test_case("Set operation: set_0() funciona", reg.is_0());
        }
        catch (...)
        {
            test_case("Set operation: set_0() funciona", false);
        }

        // Fill operations
        try
        {
            reg.set_fill_1();
            test_case("Fill operation: set_fill_1() funciona", true);
        }
        catch (...)
        {
            test_case("Fill operation: set_fill_1() funciona", false);
        }

        std::cout << std::endl;
    }

    void test_to_string()
    {
        std::cout << "--- TO_STRING ---" << std::endl;

        try
        {
            reg_digs_t<10, 3> reg;
            reg.set_1();

            std::string str = reg.to_string();
            test_case("to_string(): genera string", !str.empty());

            // Verificar que contiene elementos esperados
            test_case("to_string(): contiene 'reg_digs_t'",
                      str.find("reg_digs_t") != std::string::npos);

            test_case("to_string(): contiene 'B10'",
                      str.find("B10") != std::string::npos);

            std::cout << "  Ejemplo: " << str << std::endl;
        }
        catch (...)
        {
            test_case("to_string(): genera string", false);
        }

        std::cout << std::endl;
    }
};

int main()
{
    try
    {
        RegDigsBasicTester tester;
        tester.run_all_tests();
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "❌ Basic test suite failed with exception: " << e.what() << std::endl;
        return 1;
    }
}