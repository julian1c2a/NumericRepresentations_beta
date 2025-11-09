#include <iostream>
#include <cassert>
#include "include/auxiliary_types.hpp"

using namespace NumRepr;

int main()
{
    std::cout << "Testing auxiliary_types.hpp improvements...\n"
              << std::endl;

    // Test sign functions
    std::cout << "=== Testing sign_funct_e ===" << std::endl;

    constexpr auto positive = sign_funct_e::vplus;
    constexpr auto negative = sign_funct_e::vminus;
    constexpr auto zero = sign_funct_e::vzero;

    // Test utility functions
    static_assert(to_int(positive) == 1, "Positive should be 1");
    static_assert(to_int(negative) == -1, "Negative should be -1");
    static_assert(to_int(zero) == 0, "Zero should be 0");

    static_assert(is_positive(positive), "Should detect positive");
    static_assert(!is_positive(negative), "Should not detect negative as positive");
    static_assert(!is_positive(zero), "Should not detect zero as positive");

    static_assert(is_negative(negative), "Should detect negative");
    static_assert(!is_negative(positive), "Should not detect positive as negative");
    static_assert(!is_negative(zero), "Should not detect zero as negative");

    static_assert(is_zero(zero), "Should detect zero");
    static_assert(!is_zero(positive), "Should not detect positive as zero");
    static_assert(!is_zero(negative), "Should not detect negative as zero");

    // Test opposite signs
    static_assert(opposite_sign(positive) == negative, "Opposite of positive should be negative");
    static_assert(opposite_sign(negative) == positive, "Opposite of negative should be positive");
    static_assert(opposite_sign(zero) == zero, "Opposite of zero should be zero");

    std::cout << "✅ All sign function tests passed!" << std::endl;

    // Test enum values
    std::cout << "\n=== Testing enum values ===" << std::endl;

    std::cout << "Number types:" << std::endl;
    std::cout << "  - Natural: " << static_cast<int>(num_type_e::natural) << std::endl;
    std::cout << "  - Integer: " << static_cast<int>(num_type_e::entero) << std::endl;
    std::cout << "  - Rational: " << static_cast<int>(num_type_e::racional) << std::endl;
    std::cout << "  - Real: " << static_cast<int>(num_type_e::real) << std::endl;

    std::cout << "\nInteger formats:" << std::endl;
    std::cout << "  - Complement to Base: " << static_cast<int>(int_num_format_e::int_CB) << std::endl;
    std::cout << "  - Complement to Base-1: " << static_cast<int>(int_num_format_e::int_CBm1) << std::endl;
    std::cout << "  - Magnitude & Sign: " << static_cast<int>(int_num_format_e::int_MS) << std::endl;
    std::cout << "  - Excess-n: " << static_cast<int>(int_num_format_e::int_EXC_n) << std::endl;

    std::cout << "\nBinary operations:" << std::endl;
    std::cout << "  - Add: " << static_cast<int>(binop_e::add) << std::endl;
    std::cout << "  - Sub: " << static_cast<int>(binop_e::sub) << std::endl;
    std::cout << "  - Mult: " << static_cast<int>(binop_e::mult) << std::endl;
    std::cout << "  - Div: " << static_cast<int>(binop_e::div) << std::endl;
    std::cout << "  - Rem: " << static_cast<int>(binop_e::rem) << std::endl;

    std::cout << "\n✅ All tests completed successfully!" << std::endl;
    std::cout << "🎉 auxiliary_types.hpp is working correctly with improvements!" << std::endl;

    return 0;
}