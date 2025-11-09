#include <iostream>
#include <cassert>
#include <sstream>
#include "core/dig_t.hpp"

using namespace NumRepr;

void test_dig_t_construction()
{
    std::cout << "Testing dig_t construction...\n";

    // Test default construction
    dig_t<10> d1;
    assert(d1.get() == 0);

    // Test construction with value
    dig_t<10> d2(5);
    assert(d2.get() == 5);

    // Test construction with modular arithmetic
    dig_t<10> d3(15);
    assert(d3.get() == 5); // 15 % 10 = 5

    // Test different bases
    dig_t<2> d_bin(1);
    assert(d_bin.get() == 1);

    dig_t<16> d_hex(10);
    assert(d_hex.get() == 10);

    std::cout << "✓ dig_t construction tests passed\n";
}

void test_dig_t_operators()
{
    std::cout << "Testing dig_t arithmetic operators...\n";

    // Test addition
    dig_t<10> a(3);
    dig_t<10> b(4);
    dig_t<10> sum = a + b;
    assert(sum.get() == 7);

    // Test modular addition
    dig_t<10> c(8);
    dig_t<10> d(5);
    dig_t<10> mod_sum = c + d;
    assert(mod_sum.get() == 3); // (8 + 5) % 10 = 3

    // Test multiplication
    dig_t<10> e(3);
    dig_t<10> f(4);
    dig_t<10> product = e * f;
    assert(product.get() == 2); // (3 * 4) % 10 = 2 (wait, should be 12 % 10 = 2)

    // Test subtraction
    dig_t<10> g(7);
    dig_t<10> h(3);
    dig_t<10> diff = g - h;
    assert(diff.get() == 4);

    std::cout << "✓ dig_t arithmetic operator tests passed\n";
}

void test_dig_t_comparison()
{
    std::cout << "Testing dig_t comparison operators...\n";

    dig_t<10> a(5);
    dig_t<10> b(5);
    dig_t<10> c(3);
    dig_t<10> d(7);

    // Test equality
    assert(a == b);
    assert(!(a == c));

    // Test inequality
    assert(a != c);
    assert(!(a != b));

    // Test less than
    assert(c < a);
    assert(!(a < c));
    assert(!(a < b));

    // Test greater than
    assert(d > a);
    assert(!(a > d));
    assert(!(a > b));

    std::cout << "✓ dig_t comparison tests passed\n";
}

void test_dig_t_assignment()
{
    std::cout << "Testing dig_t assignment operators...\n";

    dig_t<10> a(3);

    // Test +=
    a += dig_t<10>(4);
    assert(a.get() == 7);

    // Test -=
    a -= dig_t<10>(2);
    assert(a.get() == 5);

    // Test *=
    a *= dig_t<10>(3);
    assert(a.get() == 5); // (5 * 3) % 10 = 5 (wait, should be 15 % 10 = 5)

    std::cout << "✓ dig_t assignment operator tests passed\n";
}

void test_dig_t_static_methods()
{
    std::cout << "Testing dig_t static methods...\n";

    // Test ui_max
    constexpr auto max_val = dig_t<10>::ui_max();
    static_assert(max_val == 9); // B - 1 = 10 - 1 = 9

    // Test ui_0 and ui_1
    constexpr auto zero = dig_t<10>::ui_0();
    constexpr auto one = dig_t<10>::ui_1();
    static_assert(zero == 0);
    static_assert(one == 1);

    // Test sui_B
    constexpr auto base_val = dig_t<10>::sui_B();
    static_assert(base_val == 10);

    std::cout << "✓ dig_t static method tests passed\n";
}

void test_dig_t_conversion()
{
    std::cout << "Testing dig_t type conversions...\n";

    dig_t<10> d(7);

    // Test conversion to uint_t
    auto uint_val = static_cast<dig_t<10>::uint_t>(d);
    assert(uint_val == 7);

    // Test get() method
    assert(d.get() == 7);

    // Test operator()
    assert(d() == 7);

    std::cout << "✓ dig_t conversion tests passed\n";
}

void test_dig_t_different_bases()
{
    std::cout << "Testing dig_t with different bases...\n";

    // Test binary base
    dig_t<2> bin(1);
    assert(bin.get() == 1);
    dig_t<2> bin_overflow(3);
    assert(bin_overflow.get() == 1); // 3 % 2 = 1

    // Test hex base
    dig_t<16> hex(15);
    assert(hex.get() == 15);
    dig_t<16> hex_overflow(17);
    assert(hex_overflow.get() == 1); // 17 % 16 = 1

    // Test large base
    dig_t<1000> large(999);
    assert(large.get() == 999);

    std::cout << "✓ dig_t different base tests passed\n";
}

void test_dig_t_io()
{
    std::cout << "Testing dig_t I/O operations...\n";

    // Test output stream
    dig_t<10> d(5);
    std::ostringstream oss;
    oss << d;
    std::string output = oss.str();

    // Should contain the digit value and base
    assert(output.find("5") != std::string::npos);
    assert(output.find("10") != std::string::npos);

    std::cout << "✓ dig_t I/O tests passed\n";
}

int main()
{
    std::cout << "=== Testing dig_t.hpp ===\n";

    try
    {
        test_dig_t_construction();
        test_dig_t_operators();
        test_dig_t_comparison();
        test_dig_t_assignment();
        test_dig_t_static_methods();
        test_dig_t_conversion();
        test_dig_t_different_bases();
        test_dig_t_io();

        std::cout << "\n✅ All dig_t.hpp tests PASSED!\n";
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cout << "\n❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cout << "\n❌ Test failed with unknown exception\n";
        return 1;
    }
}