#include <catch2/catch_test_macros.hpp>
#include "core/internal/auxiliary_functions.hpp"
#include <limits>

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

TEST_CASE( "max_exponent_for_base_ct", "[auxiliary_functions]")
{
    STATIC_REQUIRE(max_exponent_for_base_ct<2>() == 63);
    STATIC_REQUIRE(max_exponent_for_base_ct<3>() == 40);
    STATIC_REQUIRE(max_exponent_for_base_ct<4>() == 31);
    STATIC_REQUIRE(max_exponent_for_base_ct<5>() == 27);
    STATIC_REQUIRE(max_exponent_for_base_ct<10>() == 19);
    STATIC_REQUIRE(max_exponent_for_base_ct<16>() == 15);
    STATIC_REQUIRE(max_exponent_for_base_ct<256>() == 7);
    STATIC_REQUIRE(max_exponent_for_base_ct<65536>() == 3);
    STATIC_REQUIRE(max_exponent_for_base_ct<4294967296>() == 1);
}

TEST_CASE( "max_exponent_for_base", "[auxiliary_functions]")
{
    STATIC_REQUIRE(max_exponent_for_base(2) == 63);
    STATIC_REQUIRE(max_exponent_for_base(3) == 40);
    STATIC_REQUIRE(max_exponent_for_base(4) == 31);
    STATIC_REQUIRE(max_exponent_for_base(5) == 27);
    STATIC_REQUIRE(max_exponent_for_base(10) == 19);
    STATIC_REQUIRE(max_exponent_for_base(16) == 15);
    STATIC_REQUIRE(max_exponent_for_base(256) == 7);
    STATIC_REQUIRE(max_exponent_for_base(65536) == 3);
    STATIC_REQUIRE(max_exponent_for_base(4294967296) == 1);
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

TEST_CASE("int_pow_ct tests", "[auxiliary_functions]")
{
    STATIC_REQUIRE(int_pow_ct<2, 0>() == 1);
    STATIC_REQUIRE(int_pow_ct<2, 1>() == 2);
    STATIC_REQUIRE(int_pow_ct<2, 3>() == 8);
    STATIC_REQUIRE(int_pow_ct<3, 4>() == 81);
    STATIC_REQUIRE(int_pow_ct<5, 3>() == 125);
    STATIC_REQUIRE(int_pow_ct<0, 5>() == 0);
    STATIC_REQUIRE(int_pow_ct<1, 100>() == 1);
}

TEST_CASE("is_perfect_square tests", "[auxiliary_functions]")
{
    STATIC_REQUIRE(is_perfect_square(0));
    STATIC_REQUIRE(is_perfect_square(1));
    STATIC_REQUIRE(is_perfect_square(4));
    STATIC_REQUIRE(is_perfect_square(9));
    STATIC_REQUIRE(is_perfect_square(16));
    STATIC_REQUIRE(is_perfect_square(25));
    STATIC_REQUIRE(is_perfect_square(36));
    STATIC_REQUIRE(is_perfect_square(49));
    STATIC_REQUIRE(is_perfect_square(64));
    STATIC_REQUIRE(is_perfect_square(81));
    STATIC_REQUIRE(is_perfect_square(100));
    STATIC_REQUIRE(is_perfect_square(144));
    STATIC_REQUIRE(is_perfect_square(169));
    STATIC_REQUIRE(is_perfect_square(196));
    STATIC_REQUIRE(is_perfect_square(225));
    STATIC_REQUIRE(is_perfect_square(256));
    STATIC_REQUIRE(is_perfect_square(289));
    STATIC_REQUIRE(is_perfect_square(324));
    STATIC_REQUIRE(is_perfect_square(361));
    STATIC_REQUIRE(is_perfect_square(400));

    STATIC_REQUIRE_FALSE(is_perfect_square(2));
    STATIC_REQUIRE_FALSE(is_perfect_square(3));
    STATIC_REQUIRE_FALSE(is_perfect_square(5));
    STATIC_REQUIRE_FALSE(is_perfect_square(6));
    STATIC_REQUIRE_FALSE(is_perfect_square(7));
    STATIC_REQUIRE_FALSE(is_perfect_square(8));
    STATIC_REQUIRE_FALSE(is_perfect_square(10));

    // Runtime test
    REQUIRE(is_perfect_square(625));
    REQUIRE_FALSE(is_perfect_square(626));
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

TEST_CASE("floorsqrt and ceilsqrt tests", "[auxiliary_functions]")
{
    // floorsqrt
    STATIC_REQUIRE(floorsqrt(std::size_t{0}) == 0);
    STATIC_REQUIRE(floorsqrt(std::size_t{1}) == 1);
    STATIC_REQUIRE(floorsqrt(std::size_t{2}) == 1);
    STATIC_REQUIRE(floorsqrt(std::size_t{3}) == 1);
    STATIC_REQUIRE(floorsqrt(std::size_t{4}) == 2);
    STATIC_REQUIRE(floorsqrt(std::size_t{15}) == 3);
    STATIC_REQUIRE(floorsqrt(std::size_t{16}) == 4);
    STATIC_REQUIRE(floorsqrt(std::size_t{17}) == 4);

    // ceilsqrt
    STATIC_REQUIRE(ceilsqrt(std::size_t{0}) == 0);
    STATIC_REQUIRE(ceilsqrt(std::size_t{1}) == 1);
    STATIC_REQUIRE(ceilsqrt(std::size_t{2}) == 2);
    STATIC_REQUIRE(ceilsqrt(std::size_t{3}) == 2);
    STATIC_REQUIRE(ceilsqrt(std::size_t{4}) == 2);
    STATIC_REQUIRE(ceilsqrt(std::size_t{15}) == 4);
    STATIC_REQUIRE(ceilsqrt(std::size_t{16}) == 4);
    STATIC_REQUIRE(ceilsqrt(std::size_t{17}) == 5);
    STATIC_REQUIRE(ceilsqrt(std::size_t{24}) == 5);
    STATIC_REQUIRE(ceilsqrt(std::size_t{25}) == 5);
    STATIC_REQUIRE(ceilsqrt(std::size_t{26}) == 6);
    REQUIRE(ceilsqrt(std::size_t{100}) == 10);
    REQUIRE(ceilsqrt(std::size_t{101}) == 11);
    REQUIRE(ceilsqrt(std::numeric_limits<std::size_t>::max()) > 0);

    // std::uint32_t
    REQUIRE(floorsqrt(std::numeric_limits<std::uint32_t>::max()) == 65535);
    REQUIRE(ceilsqrt(std::numeric_limits<std::uint32_t>::max()) == 65536);

    // std::uint16_t
    REQUIRE(floorsqrt(std::numeric_limits<std::uint16_t>::max()) == 255);
    REQUIRE(ceilsqrt(std::numeric_limits<std::uint16_t>::max()) == 256);
}

TEST_CASE("int_log2 and int_log2ct tests", "[auxiliary_functions]")
{
    STATIC_REQUIRE(int_log2(1) == 0);
    STATIC_REQUIRE(int_log2(2) == 1);
    STATIC_REQUIRE(int_log2(3) == 1);
    STATIC_REQUIRE(int_log2(4) == 2);
    STATIC_REQUIRE(int_log2(1023) == 9);
    STATIC_REQUIRE(int_log2(1024) == 10);
    STATIC_REQUIRE(int_log2(1025) == 10);

    STATIC_REQUIRE(int_log2ct<1>() == 0);
    STATIC_REQUIRE(int_log2ct<2>() == 1);
    STATIC_REQUIRE(int_log2ct<3>() == 1);
    STATIC_REQUIRE(int_log2ct<4>() == 2);
    STATIC_REQUIRE(int_log2ct<1023>() == 9);
    STATIC_REQUIRE(int_log2ct<1024>() == 10);
    STATIC_REQUIRE(int_log2ct<1025>() == 10);

    // Test aliases
    STATIC_REQUIRE(NumRepr::auxiliary_functions::log2(1024) == 10);
    STATIC_REQUIRE(log2ct<1024>() == 10);
}

TEST_CASE("int_pow2 and int_pow2ct tests", "[auxiliary_functions]")
{
    STATIC_REQUIRE(int_pow2(0) == 1);
    STATIC_REQUIRE(int_pow2(1) == 2);
    STATIC_REQUIRE(int_pow2(10) == 1024);
    STATIC_REQUIRE(int_pow2(16) == 65536);

    STATIC_REQUIRE(int_pow2ct<0>() == 1);
    STATIC_REQUIRE(int_pow2ct<1>() == 2);
    STATIC_REQUIRE(int_pow2ct<10>() == 1024);
    STATIC_REQUIRE(int_pow2ct<16>() == 65536);

    // Test aliases
    STATIC_REQUIRE(pow2(10) == 1024);
    STATIC_REQUIRE(pow2ct<10>() == 1024);
}

TEST_CASE("int_log and int_log_ct tests", "[auxiliary_functions]")
{
    // Test int_log_ct
    STATIC_REQUIRE(int_log_ct<10, 100>() == 2);
    STATIC_REQUIRE(int_log_ct<2, 8>() == 3);
    STATIC_REQUIRE(int_log_ct<3, 80>() == 3); // 3^3=27, 3^4=81
    STATIC_REQUIRE(int_log_ct<10, 99>() == 1);
    STATIC_REQUIRE(int_log_ct<10, 101>() == 2);
    STATIC_REQUIRE(int_log_ct<10, 9>() == 0);
    STATIC_REQUIRE(int_log_ct<10, 1>() == 0);
    STATIC_REQUIRE(int_log_ct<10, 0>() == -1);
    STATIC_REQUIRE(int_log_ct<10, -5>() == -1);

    // Test int_log
    REQUIRE(int_log(10, 100) == 2);
    REQUIRE(int_log(2, 8) == 3);
    REQUIRE(int_log(3, 80) == 3);
    REQUIRE(int_log(10, 99) == 1);
    REQUIRE(int_log(10, 101) == 2);
    REQUIRE(int_log(10, 9) == 0);
    REQUIRE(int_log(10, 1) == 0);
    REQUIRE(int_log(10, 0) == -1);
    REQUIRE(int_log(10, -5) == -1);
}