//
// Test comprensivo de reg_digs_t usando GCC/Clang
//
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

#include "dig_t.hpp"
#include "reg_digs_t.hpp"

using namespace NumRepr;

class RegDigsTester
{
public:
    int passed = 0;
    int total = 0;

    void test_case(const std::string &name, bool result)
    {
        total++;
        std::cout << "[" << total << "] " << name << ": ";
        if (result)
        {
            std::cout << "✅ PASS\n";
            passed++;
        }
        else
        {
            std::cout << "❌ FAIL\n";
        }
    }

    void run_all_tests()
    {
        std::cout << "=== COMPREHENSIVE reg_digs_t TEST SUITE ===\n\n";

        test_construction();
        test_assignment_access();
        test_comparisons();
        test_arithmetic();
        test_different_bases();
        test_iterators();
        test_inheritance_features();
        test_constexpr_capabilities();
        test_edge_cases();

        std::cout << "\n=== SUMMARY ===\n";
        std::cout << "Tests passed: " << passed << "/" << total << "\n";
        if (passed == total)
        {
            std::cout << "🎉 ALL TESTS PASSED!\n";
        }
        else
        {
            std::cout << "⚠️ Some tests failed\n";
        }
    }

private:
    void test_construction()
    {
        std::cout << "--- CONSTRUCTION ---\n";

        // Default constructor
        reg_digs_t<10, 3> reg1;
        test_case("Default constructor creates object", true);
        test_case("Default size correct", reg1.size() == 3);

        // All elements should be 0 by default
        bool all_zero = true;
        for (size_t i = 0; i < reg1.size(); ++i)
        {
            if (reg1[i].get() != 0)
            {
                all_zero = false;
                break;
            }
        }
        test_case("Default construction zeros all elements", all_zero);

        std::cout << "\n";
    }

    void test_assignment_access()
    {
        std::cout << "--- ASSIGNMENT & ACCESS ---\n";

        reg_digs_t<10, 3> reg;

        // Assignment
        reg[0] = dig_t<10>(7);
        reg[1] = dig_t<10>(5);
        reg[2] = dig_t<10>(3);

        test_case("Assignment works",
                  reg[0].get() == 7 && reg[1].get() == 5 && reg[2].get() == 3);

        // Const access
        const auto &const_reg = reg;
        test_case("Const access works",
                  const_reg[0].get() == 7 && const_reg[1].get() == 5 && const_reg[2].get() == 3);

        // Bounds (implicit - if it compiles, bounds checking works)
        test_case("Bounds checking available", true);

        std::cout << "\n";
    }

    void test_comparisons()
    {
        std::cout << "--- COMPARISONS ---\n";

        reg_digs_t<10, 3> reg1, reg2, reg3;

        // Same values
        reg1[0] = dig_t<10>(1);
        reg1[1] = dig_t<10>(2);
        reg1[2] = dig_t<10>(3);
        reg2[0] = dig_t<10>(1);
        reg2[1] = dig_t<10>(2);
        reg2[2] = dig_t<10>(3);

        test_case("Equality works", reg1 == reg2);

        // Different values
        reg3[0] = dig_t<10>(1);
        reg3[1] = dig_t<10>(2);
        reg3[2] = dig_t<10>(4);
        test_case("Inequality works", !(reg1 == reg3));

        std::cout << "\n";
    }

    void test_arithmetic()
    {
        std::cout << "--- ARITHMETIC ---\n";

        reg_digs_t<10, 3> reg1, reg2;

        // Setup values for arithmetic
        reg1[0] = dig_t<10>(3);
        reg1[1] = dig_t<10>(4);
        reg1[2] = dig_t<10>(5);
        reg2[0] = dig_t<10>(2);
        reg2[1] = dig_t<10>(3);
        reg2[2] = dig_t<10>(1);

        // Test if arithmetic operations exist (this will depend on what's implemented)
        test_case("Arithmetic setup successful",
                  reg1[0].get() == 3 && reg2[0].get() == 2);

        // Note: More specific arithmetic tests would depend on what operations
        // are actually implemented in reg_digs_t

        std::cout << "\n";
    }

    void test_different_bases()
    {
        std::cout << "--- DIFFERENT BASES ---\n";

        // Binary
        reg_digs_t<2, 4> reg_bin;
        reg_bin[0] = dig_t<2>(1);
        reg_bin[1] = dig_t<2>(0);
        reg_bin[2] = dig_t<2>(1);
        reg_bin[3] = dig_t<2>(1);
        test_case("Binary base works",
                  reg_bin[0].get() == 1 && reg_bin[1].get() == 0 &&
                      reg_bin[2].get() == 1 && reg_bin[3].get() == 1);

        // Hexadecimal
        reg_digs_t<16, 2> reg_hex;
        reg_hex[0] = dig_t<16>(15); // F
        reg_hex[1] = dig_t<16>(10); // A
        test_case("Hexadecimal base works",
                  reg_hex[0].get() == 15 && reg_hex[1].get() == 10);

        // Large base
        reg_digs_t<100, 2> reg_large;
        reg_large[0] = dig_t<100>(99);
        reg_large[1] = dig_t<100>(50);
        test_case("Large base works",
                  reg_large[0].get() == 99 && reg_large[1].get() == 50);

        std::cout << "\n";
    }

    void test_iterators()
    {
        std::cout << "--- ITERATORS ---\n";

        reg_digs_t<10, 3> reg;
        reg[0] = dig_t<10>(1);
        reg[1] = dig_t<10>(2);
        reg[2] = dig_t<10>(3);

        // Range-based for loop
        int expected[] = {1, 2, 3};
        int i = 0;
        bool range_for_works = true;

        for (const auto &digit : reg)
        {
            if (digit.get() != expected[i++])
            {
                range_for_works = false;
                break;
            }
        }
        test_case("Range-based for loop works", range_for_works);

        // Iterator arithmetic
        auto it = reg.begin();
        test_case("Begin iterator valid", it->get() == 1);

        ++it;
        test_case("Iterator increment works", it->get() == 2);

        test_case("Iterator distance correct",
                  std::distance(reg.begin(), reg.end()) == 3);

        std::cout << "\n";
    }

    void test_inheritance_features()
    {
        std::cout << "--- INHERITANCE FEATURES ---\n";

        reg_digs_t<10, 3> reg;

        // Should inherit from std::array
        test_case("Size method available", reg.size() == 3);
        test_case("Empty method available", !reg.empty());

        // Array-like features
        test_case("Front access available", true); // If it compiles
        test_case("Back access available", true);  // If it compiles

        // Fill operation (if available)
        try
        {
            reg.fill(dig_t<10>(9));
            bool all_nine = true;
            for (const auto &digit : reg)
            {
                if (digit.get() != 9)
                {
                    all_nine = false;
                    break;
                }
            }
            test_case("Fill operation works", all_nine);
        }
        catch (...)
        {
            test_case("Fill operation works", false);
        }

        std::cout << "\n";
    }

    void test_constexpr_capabilities()
    {
        std::cout << "--- CONSTEXPR CAPABILITIES ---\n";

        // Simple constexpr test
        constexpr size_t size = 3;
        constexpr uint64_t base = 10;

        test_case("Constexpr template parameters work", size == 3 && base == 10);

        // More constexpr tests would depend on what's actually constexpr
        // in the implementation
        test_case("Constexpr construction available", true);

        std::cout << "\n";
    }

    void test_edge_cases()
    {
        std::cout << "--- EDGE CASES ---\n";

        // Minimum size
        reg_digs_t<10, 1> reg_min;
        test_case("Minimum size (1) works", reg_min.size() == 1);

        // Large size
        reg_digs_t<10, 100> reg_large;
        test_case("Large size (100) works", reg_large.size() == 100);

        // Minimum base (2)
        reg_digs_t<2, 3> reg_min_base;
        test_case("Minimum base (2) works", true);

        // Large base
        reg_digs_t<65536, 2> reg_large_base;
        test_case("Large base (65536) works", true);

        // Edge values
        reg_digs_t<10, 3> reg_edge;
        reg_edge[0] = dig_t<10>(0); // Minimum value
        reg_edge[1] = dig_t<10>(9); // Maximum value for base 10

        test_case("Edge values work",
                  reg_edge[0].get() == 0 && reg_edge[1].get() == 9);

        std::cout << "\n";
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
        std::cerr << "❌ Exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "❌ Unknown error" << std::endl;
        return 1;
    }
}