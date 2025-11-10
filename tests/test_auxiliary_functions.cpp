#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "include/core/internal/auxiliary_functions.hpp"

using namespace NumRepr::auxiliary_functions;

TEST_CASE("is_power_of_2 tests", "[auxiliary_functions]")
{
    // Test cases for powers of 2
    STATIC_REQUIRE(is_power_of_2(1));
    STATIC_REQUIRE(is_power_of_2(2));
    STATIC_REQUIRE(is_power_of_2(4));
    STATIC_REQUIRE(is_power_of_2(8));
    STATIC_REQUIRE(is_power_of_2(16));
    STATIC_REQUIRE(is_power_of_2(1024));
    STATIC_REQUIRE(is_power_of_2(2048));
    STATIC_REQUIRE(is_power_of_2(4096));
    STATIC_REQUIRE(is_power_of_2(8192));
    STATIC_REQUIRE(is_power_of_2(16384));
    STATIC_REQUIRE(is_power_of_2(32768));
    STATIC_REQUIRE(is_power_of_2(65536));
    STATIC_REQUIRE(is_power_of_2(131072));
    STATIC_REQUIRE(is_power_of_2(4294967296));
    STATIC_REQUIRE(is_power_of_2(9223372036854775808ULL));

    // Test cases for non-powers of 2
    STATIC_REQUIRE_FALSE(is_power_of_2(0));
    STATIC_REQUIRE_FALSE(is_power_of_2(3));
    STATIC_REQUIRE_FALSE(is_power_of_2(5));
    STATIC_REQUIRE_FALSE(is_power_of_2(6));
    STATIC_REQUIRE_FALSE(is_power_of_2(7));
    STATIC_REQUIRE_FALSE(is_power_of_2(9));
    STATIC_REQUIRE_FALSE(is_power_of_2(15));
    STATIC_REQUIRE_FALSE(is_power_of_2(1023));
    STATIC_REQUIRE_FALSE(is_power_of_2(1025));
    STATIC_REQUIRE_FALSE(is_power_of_2(2047));
    STATIC_REQUIRE_FALSE(is_power_of_2(4095));
    STATIC_REQUIRE_FALSE(is_power_of_2(4097));
    STATIC_REQUIRE_FALSE(is_power_of_2(8191));
    STATIC_REQUIRE_FALSE(is_power_of_2(16393));
    STATIC_REQUIRE_FALSE(is_power_of_2(16395));
    STATIC_REQUIRE_FALSE(is_power_of_2(32767));
    STATIC_REQUIRE_FALSE(is_power_of_2(65535));
    STATIC_REQUIRE_FALSE(is_power_of_2(65537));
    STATIC_REQUIRE_FALSE(is_power_of_2(131071));
    STATIC_REQUIRE_FALSE(is_power_of_2(4294967295));
    STATIC_REQUIRE_FALSE(is_power_of_2(4294967297));
    STATIC_REQUIRE_FALSE(is_power_of_2(9223372036854775807ULL));
    STATIC_REQUIRE_FALSE(is_power_of_2(9223372036854775809ULL));
    STATIC_REQUIRE_FALSE(is_power_of_2(18446744073709551615ULL));
}

TEST_CASE("is_prime tests", "[auxiliary_functions]")
{
    // Test small primes
    STATIC_REQUIRE_FALSE(is_prime(0));
    STATIC_REQUIRE_FALSE(is_prime(1));
    STATIC_REQUIRE(is_prime(2));
    STATIC_REQUIRE(is_prime(3));
    STATIC_REQUIRE(is_prime(5));
    STATIC_REQUIRE(is_prime(7));
    STATIC_REQUIRE(is_prime(11));
    STATIC_REQUIRE(is_prime(13));

    // Test composites
    STATIC_REQUIRE_FALSE(is_prime(4));
    STATIC_REQUIRE_FALSE(is_prime(6));
    STATIC_REQUIRE_FALSE(is_prime(8));
    STATIC_REQUIRE_FALSE(is_prime(9));
    STATIC_REQUIRE_FALSE(is_prime(10));
    STATIC_REQUIRE_FALSE(is_prime(12));

    // Runtime tests
    REQUIRE(is_prime(97));
    REQUIRE_FALSE(is_prime(100));
}

TEST_CASE("gcd and lcm tests", "[auxiliary_functions]")
{
    // Test GCD
    STATIC_REQUIRE(gcd(12, 8) == 4);
    STATIC_REQUIRE(gcd(15, 25) == 5);
    STATIC_REQUIRE(gcd(17, 13) == 1);
    STATIC_REQUIRE(gcd(0, 5) == 5);
    STATIC_REQUIRE(gcd(5, 0) == 5);

    // Test LCM
    STATIC_REQUIRE(lcm(4, 6) == 12);
    STATIC_REQUIRE(lcm(15, 25) == 75);
    STATIC_REQUIRE(lcm(7, 13) == 91);
    STATIC_REQUIRE(lcm(0, 5) == 0);

    // Runtime tests
    REQUIRE(gcd(48, 18) == 6);
    REQUIRE(lcm(12, 15) == 60);
}

TEST_CASE("int_pow tests", "[auxiliary_functions]")
{
    STATIC_REQUIRE(int_pow(2, 0) == 1);
    STATIC_REQUIRE(int_pow(2, 1) == 2);
    STATIC_REQUIRE(int_pow(2, 3) == 8);
    STATIC_REQUIRE(int_pow(3, 4) == 81);
    STATIC_REQUIRE(int_pow(5, 3) == 125);
    STATIC_REQUIRE(int_pow(0, 5) == 0);
    STATIC_REQUIRE(int_pow(1, 100) == 1);

    // Runtime test
    REQUIRE(int_pow(2, 10) == 1024);
}

TEST_CASE("int_pow2ct tests", "[auxiliary_functions]")
{
    STATIC_REQUIRE(int_pow2ct<0>() == 1);
    STATIC_REQUIRE(int_pow2ct<1>() == 2);
    STATIC_REQUIRE(int_pow2ct<3>() == 8);
    STATIC_REQUIRE(int_pow2ct<5>() == 32);
    STATIC_REQUIRE(int_pow2ct<32>() == 4294967296);
}

TEST_CASE("digit_counting tests", "[auxiliary_functions]")
{
    // Base 10
    STATIC_REQUIRE(count_digits_base10(0) == 1);
    STATIC_REQUIRE(count_digits_base10(5) == 1);
    STATIC_REQUIRE(count_digits_base10(42) == 2);
    STATIC_REQUIRE(count_digits_base10(123) == 3);
    STATIC_REQUIRE(count_digits_base10(1000) == 4);

    // Different bases
    STATIC_REQUIRE(count_digits_base(8, 2) == 4);     // 1000
    STATIC_REQUIRE(count_digits_base(15, 16) == 1);  // F
    STATIC_REQUIRE(count_digits_base(16, 16) == 2); // 10

    // Runtime test
    REQUIRE(count_digits_base10(987654321) == 9);
}