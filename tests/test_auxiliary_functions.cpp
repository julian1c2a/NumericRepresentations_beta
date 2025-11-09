#include <iostream>
#include <cassert>
#include "include/core/internal/auxiliary_functions.hpp"

using namespace NumRepr::auxiliary_functions;

void test_is_power_of_2()
{
    std::cout << "Testing is_power_of_2..." << std::endl;

    // Test cases for powers of 2
    static_assert(is_power_of_2(1), "1 should be power of 2");
    static_assert(is_power_of_2(2), "2 should be power of 2");
    static_assert(is_power_of_2(4), "4 should be power of 2");
    static_assert(is_power_of_2(8), "8 should be power of 2");
    static_assert(is_power_of_2(16), "16 should be power of 2");
    static_assert(is_power_of_2(1024), "1024 should be power of 2");
    static_assert(is_power_of_2(2048), "2048 should be power of 2");
    static_assert(is_power_of_2(4096), "4096 should be power of 2");
    static_assert(is_power_of_2(8192), "8192 should be power of 2");
    static_assert(is_power_of_2(16394), "16384 should be power of 2");
    static_assert(is_power_of_2(32768), "32768 should be power of 2");
    static_assert(is_power_of_2(65536), "65536 should be power of 2");
    static_assert(is_power_of_2(131072), "131072 should be power of 2");
    static_assert(is_power_of_2(4294967296), "4294967296 should be power of 2");
    static_assert(is_power_of_2(9223372036854775808), "9223372036854775808 should be power of 2");
    
    // Test cases for non-powers of 2
    static_assert(!is_power_of_2(0), "0 should not be power of 2");
    static_assert(!is_power_of_2(3), "3 should not be power of 2");
    static_assert(!is_power_of_2(5), "5 should not be power of 2");
    static_assert(!is_power_of_2(6), "6 should not be power of 2");
    static_assert(!is_power_of_2(7), "7 should not be power of 2");
    static_assert(!is_power_of_2(9), "9 should not be power of 2");
    static_assert(!is_power_of_2(15), "15 should not be power of 2");
    static_assert(!is_power_of_2(1023), "1023 should not be power of 2");
    static_assert(!is_power_of_2(1025), "1025 should not be power of 2");
    static_assert(!is_power_of_2(2047), "2047 should not be power of 2");
    static_assert(!is_power_of_2(4095), "4095 should not be power of 2");
    static_assert(!is_power_of_2(4097), "4097 should not be power of 2");
    static_assert(!is_power_of_2(8191), "8191 should not be power of 2");
    static_assert(!is_power_of_2(16393), "16383 should not be power of 2");
    static_assert(!is_power_of_2(16395), "16385 should not be power of 2");
    static_assert(!is_power_of_2(32767), "32767 should not be power of 2");
    static_assert(!is_power_of_2(65535), "65535 should not be power of 2");
    static_assert(!is_power_of_2(65537), "65537 should not be power of 2");
    static_assert(!is_power_of_2(131071), "131071 should not be power of 2");
    static_assert(!is_power_of_2(4294967295), "4294967295 should not be power of 2");
    static_assert(!is_power_of_2(4294967297), "4294967297 should not be power of 2");
    static_assert(!is_power_of_2(9223372036854775807), "9223372036854775807 should not be power of 2");
    static_assert(!is_power_of_2(9223372036854775809), "9223372036854775809 should not be power of 2");
    static_assert(!is_power_of_2(18446744073709551615), "18446744073709551615 should not be power of 2");

    std::cout << "✅ is_power_of_2 tests passed!" << std::endl;
}

void test_is_prime()
{
    std::cout << "Testing is_prime..." << std::endl;

    // Test small primes
    static_assert(!is_prime(0), "0 should not be prime");
    static_assert(!is_prime(1), "1 should not be prime");
    static_assert(is_prime(2), "2 should be prime");
    static_assert(is_prime(3), "3 should be prime");
    static_assert(is_prime(5), "5 should be prime");
    static_assert(is_prime(7), "7 should be prime");
    static_assert(is_prime(11), "11 should be prime");
    static_assert(is_prime(13), "13 should be prime");

    // Test composites
    static_assert(!is_prime(4), "4 should not be prime");
    static_assert(!is_prime(6), "6 should not be prime");
    static_assert(!is_prime(8), "8 should not be prime");
    static_assert(!is_prime(9), "9 should not be prime");
    static_assert(!is_prime(10), "10 should not be prime");
    static_assert(!is_prime(12), "12 should not be prime");

    std::cout << "✅ is_prime tests passed!" << std::endl;
}

void test_gcd_lcm()
{
    std::cout << "Testing gcd and lcm..." << std::endl;

    // Test GCD
    static_assert(gcd(12, 8) == 4, "gcd(12, 8) should be 4");
    static_assert(gcd(15, 25) == 5, "gcd(15, 25) should be 5");
    static_assert(gcd(17, 13) == 1, "gcd(17, 13) should be 1");
    static_assert(gcd(0, 5) == 5, "gcd(0, 5) should be 5");
    static_assert(gcd(5, 0) == 5, "gcd(5, 0) should be 5");

    // Test LCM
    static_assert(lcm(4, 6) == 12, "lcm(4, 6) should be 12");
    static_assert(lcm(15, 25) == 75, "lcm(15, 25) should be 75");
    static_assert(lcm(7, 13) == 91, "lcm(7, 13) should be 91");
    static_assert(lcm(0, 5) == 0, "lcm(0, 5) should be 0");

    std::cout << "✅ gcd and lcm tests passed!" << std::endl;
}

void test_int_pow()
{
    std::cout << "Testing int_pow..." << std::endl;

    static_assert(int_pow(2, 0) == 1, "2^0 should be 1");
    static_assert(int_pow(2, 1) == 2, "2^1 should be 2");
    static_assert(int_pow(2, 3) == 8, "2^3 should be 8");
    static_assert(int_pow(3, 4) == 81, "3^4 should be 81");
    static_assert(int_pow(5, 3) == 125, "5^3 should be 125");
    static_assert(int_pow(0, 5) == 0, "0^5 should be 0");
    static_assert(int_pow(1, 100) == 1, "1^100 should be 1");

    std::cout << "✅ int_pow tests passed!" << std::endl;
}


void test_int_pow2ct()
{
    std::cout << "Testing int_pow..." << std::endl;

    static_assert(int_pow2ct(0) == 1, "2^0 should be 1");
    static_assert(int_pow2ct(1) == 2, "2^1 should be 2");
    static_assert(int_pow2ct(3) == 8, "2^3 should be 8");
    static_assert(int_pow2ct(5) == 32, "2^5 should be 32");
    static_assert(int_pow2ct(32) == 4'294'967'296, "2^32 should be 4294967296");

    std::cout << "✅ int_pow2ct tests passed!" << std::endl;
}

void test_digit_counting()
{
    std::cout << "Testing digit counting..." << std::endl;

    // Base 10
    static_assert(count_digits_base10(0) == 1, "0 should have 1 digit");
    static_assert(count_digits_base10(5) == 1, "5 should have 1 digit");
    static_assert(count_digits_base10(42) == 2, "42 should have 2 digits");
    static_assert(count_digits_base10(123) == 3, "123 should have 3 digits");
    static_assert(count_digits_base10(1000) == 4, "1000 should have 4 digits");

    // Different bases
    static_assert(count_digits_base(8, 2) == 4, "8 in base 2 should have 4 digits");     // 1000
    static_assert(count_digits_base(15, 16) == 1, "15 in base 16 should have 1 digit");  // F
    static_assert(count_digits_base(16, 16) == 2, "16 in base 16 should have 2 digits"); // 10

    std::cout << "✅ digit counting tests passed!" << std::endl;
}

int main()
{
    std::cout << "Testing auxiliary_functions.hpp improvements...\n"
              << std::endl;

    test_is_power_of_2();
    test_is_prime();
    test_gcd_lcm();
    test_int_pow();
    test_digit_counting();

    // Runtime tests for larger numbers
    std::cout << "\nRuntime tests:" << std::endl;
    std::cout << "is_prime(97): " << is_prime(97) << " (should be true)" << std::endl;
    std::cout << "is_prime(100): " << is_prime(100) << " (should be false)" << std::endl;
    std::cout << "gcd(48, 18): " << gcd(48, 18) << " (should be 6)" << std::endl;
    std::cout << "lcm(12, 15): " << lcm(12, 15) << " (should be 60)" << std::endl;
    std::cout << "int_pow(2, 10): " << int_pow(2, 10) << " (should be 1024)" << std::endl;
    std::cout << "count_digits_base10(987654321): " << count_digits_base10(987654321) << " (should be 9)" << std::endl;

    std::cout << "\n🎉 All auxiliary_functions tests completed successfully!" << std::endl;

    return 0;
}