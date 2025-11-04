/**
 * @file test_dual_format_comprehensive.cpp
 * @brief Comprehensive test suite for dual format I/O system
 *
 * Tests all aspects of the dual format parsing system:
 * - Strict format: d[n]Bbase
 * - Legacy format: dig#n#Bbase
 * - Edge cases and error handling
 * - Constexpr capabilities
 * - Multi-base compatibility
 * - Stream I/O operations
 */

#include <iostream>
#include <sstream>
#include <cassert>
#include <stdexcept>
#include <vector>
#include "dig_t.hpp"

using namespace NumRepr;

class DualFormatTester
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
        std::cout << "=== COMPREHENSIVE DUAL FORMAT I/O TEST SUITE ===" << std::endl;
        std::cout << "Testing both strict d[n]B and legacy dig#n#B formats\n"
                  << std::endl;

        test_basic_parsing();
        test_constexpr_capabilities();
        test_modulo_behavior();
        test_multi_base_compatibility();
        test_stream_operations();
        test_edge_cases();
        test_error_handling();
        test_output_consistency();

        print_summary();
    }

private:
    void test_basic_parsing()
    {
        std::cout << "--- BASIC PARSING TESTS ---" << std::endl;

        // Test strict format
        dig_t<10> strict_d1("d[7]B10");
        test_case("Strict format d[7]B10", strict_d1.get() == 7);

        // Test legacy format
        dig_t<10> legacy_d1("dig#7#B10");
        test_case("Legacy format dig#7#B10", legacy_d1.get() == 7);

        // Test both formats produce same result
        test_case("Strict and legacy produce same result",
                  strict_d1.get() == legacy_d1.get());

        // Test different values
        dig_t<16> strict_hex("d[15]B16");
        dig_t<16> legacy_hex("dig#15#B16");
        test_case("Hex values: d[15]B16 vs dig#15#B16",
                  strict_hex.get() == legacy_hex.get() && strict_hex.get() == 15);

        std::cout << std::endl;
    }

    void test_constexpr_capabilities()
    {
        std::cout << "--- CONSTEXPR CAPABILITIES ---" << std::endl;

        // Test compile-time parsing with strict format
        constexpr dig_t<10> ct_digit("d[5]B10");
        test_case("Constexpr parsing d[5]B10", ct_digit.get() == 5);

        // Test constexpr with different bases
        constexpr dig_t<2> binary("d[1]B2");
        constexpr dig_t<16> hex("d[10]B16");
        test_case("Constexpr binary d[1]B2", binary.get() == 1);
        test_case("Constexpr hex d[10]B16", hex.get() == 10);

        // Test constexpr constructor chain
        constexpr dig_t<8> octal = dig_t<8>("d[7]B8");
        test_case("Constexpr constructor chain", octal.get() == 7);

        std::cout << std::endl;
    }

    void test_modulo_behavior()
    {
        std::cout << "--- MODULO BEHAVIOR TESTS ---" << std::endl;

        // Test automatic modulo in strict format
        dig_t<10> mod_strict("d[127]B10");
        test_case("Modulo in strict: d[127]B10 -> 7", mod_strict.get() == 7);

        // Test automatic modulo in legacy format
        dig_t<10> mod_legacy("dig#127#B10");
        test_case("Modulo in legacy: dig#127#B10 -> 7", mod_legacy.get() == 7);

        // Test consistency
        test_case("Modulo consistency between formats",
                  mod_strict.get() == mod_legacy.get());

        // Test with different bases
        dig_t<5> base5_strict("d[23]B5");
        dig_t<5> base5_legacy("dig#23#B5");
        test_case("Base 5 modulo: 23 % 5 = 3",
                  base5_strict.get() == 3 && base5_legacy.get() == 3);

        std::cout << std::endl;
    }

    void test_multi_base_compatibility()
    {
        std::cout << "--- MULTI-BASE COMPATIBILITY ---" << std::endl;

        struct TestCase
        {
            std::string strict, legacy;
            int expected;
            int base;
        };

        std::vector<TestCase> test_cases = {
            {"d[1]B2", "dig#1#B2", 1, 2},
            {"d[5]B8", "dig#5#B8", 5, 8},
            {"d[9]B10", "dig#9#B10", 9, 10},
            {"d[15]B16", "dig#15#B16", 15, 16},
            {"d[63]B64", "dig#63#B64", 63, 64},
            {"d[99]B100", "dig#99#B100", 99, 100}};

        for (const auto &tc : test_cases)
        {
            switch (tc.base)
            {
            case 2:
            {
                dig_t<2> strict(tc.strict), legacy(tc.legacy);
                test_case("Base " + std::to_string(tc.base) + " compatibility",
                          strict.get() == tc.expected && legacy.get() == tc.expected);
                break;
            }
            case 8:
            {
                dig_t<8> strict(tc.strict), legacy(tc.legacy);
                test_case("Base " + std::to_string(tc.base) + " compatibility",
                          strict.get() == tc.expected && legacy.get() == tc.expected);
                break;
            }
            case 10:
            {
                dig_t<10> strict(tc.strict), legacy(tc.legacy);
                test_case("Base " + std::to_string(tc.base) + " compatibility",
                          strict.get() == tc.expected && legacy.get() == tc.expected);
                break;
            }
            case 16:
            {
                dig_t<16> strict(tc.strict), legacy(tc.legacy);
                test_case("Base " + std::to_string(tc.base) + " compatibility",
                          strict.get() == tc.expected && legacy.get() == tc.expected);
                break;
            }
            case 64:
            {
                dig_t<64> strict(tc.strict), legacy(tc.legacy);
                test_case("Base " + std::to_string(tc.base) + " compatibility",
                          strict.get() == tc.expected && legacy.get() == tc.expected);
                break;
            }
            case 100:
            {
                dig_t<100> strict(tc.strict), legacy(tc.legacy);
                test_case("Base " + std::to_string(tc.base) + " compatibility",
                          strict.get() == tc.expected && legacy.get() == tc.expected);
                break;
            }
            }
        }

        std::cout << std::endl;
    }

    void test_stream_operations()
    {
        std::cout << "--- STREAM I/O OPERATIONS ---" << std::endl;

        // Test input with strict format
        std::istringstream iss_strict("d[8]B10");
        dig_t<10> from_stream_strict;
        iss_strict >> from_stream_strict;
        test_case("Stream input strict d[8]B10", from_stream_strict.get() == 8);

        // Test input with legacy format
        std::istringstream iss_legacy("dig#8#B10");
        dig_t<10> from_stream_legacy;
        iss_legacy >> from_stream_legacy;
        test_case("Stream input legacy dig#8#B10", from_stream_legacy.get() == 8);

        // Test multiple inputs in same stream
        std::istringstream iss_multiple("d[3]B10 dig#7#B10 d[1]B10");
        dig_t<10> d1, d2, d3;
        iss_multiple >> d1 >> d2 >> d3;
        test_case("Multiple mixed format inputs",
                  d1.get() == 3 && d2.get() == 7 && d3.get() == 1);

        // Test output format consistency
        std::ostringstream oss;
        dig_t<10> test_digit(6);
        oss << test_digit;
        test_case("Output format is strict d[6]B10", oss.str() == "d[6]B10");

        std::cout << std::endl;
    }

    void test_edge_cases()
    {
        std::cout << "--- EDGE CASES ---" << std::endl;

        // Test zero values
        dig_t<10> zero_strict("d[0]B10");
        dig_t<10> zero_legacy("dig#0#B10");
        test_case("Zero values: both formats",
                  zero_strict.get() == 0 && zero_legacy.get() == 0);

        // Test maximum values
        dig_t<10> max_strict("d[9]B10");
        dig_t<10> max_legacy("dig#9#B10");
        test_case("Maximum values: both formats",
                  max_strict.get() == 9 && max_legacy.get() == 9);

        // Test with large numbers (should modulo)
        dig_t<10> large_strict("d[999999]B10");
        dig_t<10> large_legacy("dig#999999#B10");
        test_case("Large numbers modulo correctly",
                  large_strict.get() == 9 && large_legacy.get() == 9);

        // Test minimal base (base 2)
        dig_t<2> binary_strict("d[1]B2");
        dig_t<2> binary_legacy("dig#1#B2");
        test_case("Minimal base 2: both formats",
                  binary_strict.get() == 1 && binary_legacy.get() == 1);

        std::cout << std::endl;
    }

    void test_error_handling()
    {
        std::cout << "--- ERROR HANDLING ---" << std::endl;

        // Test invalid format detection
        bool caught_invalid_format = false;
        try
        {
            dig_t<10> invalid("invalid_format");
        }
        catch (const std::invalid_argument &)
        {
            caught_invalid_format = true;
        }
        test_case("Invalid format throws exception", caught_invalid_format);

        // Test base mismatch
        bool caught_base_mismatch = false;
        try
        {
            dig_t<10> wrong_base("d[5]B16"); // Claims base 16 but expecting 10
        }
        catch (const std::invalid_argument &)
        {
            caught_base_mismatch = true;
        }
        test_case("Base mismatch throws exception", caught_base_mismatch);

        // Test empty string
        bool caught_empty = false;
        try
        {
            dig_t<10> empty("");
        }
        catch (const std::invalid_argument &)
        {
            caught_empty = true;
        }
        test_case("Empty string throws exception", caught_empty);

        std::cout << std::endl;
    }

    void test_output_consistency()
    {
        std::cout << "--- OUTPUT CONSISTENCY ---" << std::endl;

        // Verify all digits output in strict format regardless of input format
        struct TestPair
        {
            std::string input;
            std::string expected_output;
        };

        std::vector<TestPair> test_pairs = {
            {"d[5]B10", "d[5]B10"},
            {"dig#5#B10", "d[5]B10"},  // Legacy input, strict output
            {"d[127]B10", "d[7]B10"},  // With modulo
            {"dig#127#B10", "d[7]B10"} // Legacy input with modulo
        };

        for (const auto &pair : test_pairs)
        {
            dig_t<10> digit(pair.input);
            std::ostringstream oss;
            oss << digit;
            test_case("Output consistency: " + pair.input + " -> " + pair.expected_output,
                      oss.str() == pair.expected_output);
        }

        std::cout << std::endl;
    }

    void print_summary()
    {
        std::cout << "=== DUAL FORMAT TEST SUMMARY ===" << std::endl;
        std::cout << "Tests passed: " << passed_tests << "/" << test_count << std::endl;

        if (passed_tests == test_count)
        {
            std::cout << "🎉 ALL TESTS PASSED! Dual format system is fully functional." << std::endl;
            std::cout << "\n✅ Key Features Validated:" << std::endl;
            std::cout << "   • Strict format d[n]B parsing" << std::endl;
            std::cout << "   • Legacy format dig#n#B parsing" << std::endl;
            std::cout << "   • Constexpr compile-time parsing" << std::endl;
            std::cout << "   • Multi-base compatibility (2-100)" << std::endl;
            std::cout << "   • Stream I/O operations" << std::endl;
            std::cout << "   • Automatic modulo arithmetic" << std::endl;
            std::cout << "   • Consistent strict format output" << std::endl;
            std::cout << "   • Robust error handling" << std::endl;
        }
        else
        {
            std::cout << "❌ Some tests failed. Review implementation." << std::endl;
        }
    }
};

int main()
{
    try
    {
        DualFormatTester tester;
        tester.run_all_tests();
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cout << "❌ Test suite error: " << e.what() << std::endl;
        return 1;
    }
}