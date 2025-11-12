#include <catch2/catch_test_macros.hpp>
#include "core/internal/auxiliary_functions.hpp"
#include <limits>
#include <vector>

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

TEST_CASE("is_power_of_2 properties", "[auxiliary_functions][is_power_of_2]")
{
    SECTION("Division by 2 property") {
        for (int i = 1; i < 64; ++i) {
            std::uint64_t p = 1ULL << i;
            REQUIRE(is_power_of_2(p));
            REQUIRE(is_power_of_2(p / 2));
        }
        REQUIRE(is_power_of_2(1));
        // is_power_of_2(1/2) is is_power_of_2(0) which is false. The property is for x > 1.
    }

    SECTION("Multiplication by 2 property") {
        for (int i = 0; i < 63; ++i) {
            std::uint64_t p = 1ULL << i;
            REQUIRE(is_power_of_2(p));
            REQUIRE(is_power_of_2(p * 2));
        }
    }

    SECTION("Only odd power of 2 is 1") {
        REQUIRE(is_power_of_2(1));
        REQUIRE(1 % 2 != 0);
        for (int i = 1; i < 64; ++i) {
            std::uint64_t p = 1ULL << i;
            REQUIRE(p % 2 == 0);
        }
    }

    SECTION("Sum of two different powers of 2 is not a power of 2") {
        for (int i = 0; i < 63; ++i) {
            for (int j = i + 1; j < 63; ++j) {
                std::uint64_t p1 = 1ULL << i;
                std::uint64_t p2 = 1ULL << j;
                REQUIRE_FALSE(is_power_of_2(p1 + p2));
            }
        }
    }

    SECTION("Compile-time version properties") {
        STATIC_REQUIRE(is_power_of_2_ct<1>());
        STATIC_REQUIRE(is_power_of_2_ct<2>());
        STATIC_REQUIRE(is_power_of_2_ct<4>());
        STATIC_REQUIRE_FALSE(is_power_of_2_ct<0>());
        STATIC_REQUIRE_FALSE(is_power_of_2_ct<3>());
        STATIC_REQUIRE_FALSE(is_power_of_2_ct<6>());
    }
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


TEST_CASE("is_prime tests", "[auxiliary_functions][is_prime]")
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

    // Runtime tests with different types
    REQUIRE(is_prime<int>(97));
    REQUIRE_FALSE(is_prime<int>(100));
    REQUIRE(is_prime<unsigned int>(7919));
    REQUIRE_FALSE(is_prime<unsigned long>(7921));
}

TEST_CASE("is_prime_ct tests", "[auxiliary_functions][is_prime]")
{
    STATIC_REQUIRE(is_prime_ct<2>());
    STATIC_REQUIRE(is_prime_ct<3>());
    STATIC_REQUIRE(is_prime_ct<5>());
    STATIC_REQUIRE(is_prime_ct<7>());
    STATIC_REQUIRE(is_prime_ct<11>());
    STATIC_REQUIRE(is_prime_ct<13>());
    STATIC_REQUIRE(is_prime_ct<97>());

    STATIC_REQUIRE_FALSE(is_prime_ct<4>());
    STATIC_REQUIRE_FALSE(is_prime_ct<9>());
    STATIC_REQUIRE_FALSE(is_prime_ct<100>());
    STATIC_REQUIRE_FALSE(is_prime_ct<7921>()); // 89*89
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

TEST_CASE("int_pow2_ct tests", "[auxiliary_functions]")
{
    STATIC_REQUIRE(int_pow2_ct<0>() == 1);
    STATIC_REQUIRE(int_pow2_ct<1>() == 2);
    STATIC_REQUIRE(int_pow2_ct<3>() == 8);
    STATIC_REQUIRE(int_pow2_ct<5>() == 32);
    STATIC_REQUIRE(int_pow2_ct<32>() == 4294967296);
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

TEST_CASE("int_log2 and int_log2_ct tests", "[auxiliary_functions]")
{
    STATIC_REQUIRE(int_log2(1) == 0);
    STATIC_REQUIRE(int_log2(2) == 1);
    STATIC_REQUIRE(int_log2(3) == 1);
    STATIC_REQUIRE(int_log2(4) == 2);
    STATIC_REQUIRE(int_log2(1023) == 9);
    STATIC_REQUIRE(int_log2(1024) == 10);
    STATIC_REQUIRE(int_log2(1025) == 10);

    STATIC_REQUIRE(int_log2_ct<1>() == 0);
    STATIC_REQUIRE(int_log2_ct<2>() == 1);
    STATIC_REQUIRE(int_log2_ct<3>() == 1);
    STATIC_REQUIRE(int_log2_ct<4>() == 2);
    STATIC_REQUIRE(int_log2_ct<1023>() == 9);
    STATIC_REQUIRE(int_log2_ct<1024>() == 10);
    STATIC_REQUIRE(int_log2_ct<1025>() == 10);

    // Test aliases
    STATIC_REQUIRE(NumRepr::auxiliary_functions::log2(1024) == 10);
    STATIC_REQUIRE(log2ct<1024>() == 10);
}

TEST_CASE("int_pow2 and int_pow2_ct tests", "[auxiliary_functions]")
{
    STATIC_REQUIRE(int_pow2(0) == 1);
    STATIC_REQUIRE(int_pow2(1) == 2);
    STATIC_REQUIRE(int_pow2(10) == 1024);
    STATIC_REQUIRE(int_pow2(16) == 65536);

    STATIC_REQUIRE(int_pow2_ct<0>() == 1);
    STATIC_REQUIRE(int_pow2_ct<1>() == 2);
    STATIC_REQUIRE(int_pow2_ct<10>() == 1024);
    STATIC_REQUIRE(int_pow2_ct<16>() == 65536);

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

TEST_CASE("In-depth floorsqrt tests", "[auxiliary_functions][floorsqrt]") {
    SECTION("Basic and edge cases") {
        STATIC_REQUIRE(floorsqrt(0u) == 0u);
        STATIC_REQUIRE(floorsqrt(1u) == 1u);
        STATIC_REQUIRE(floorsqrt(2u) == 1u);
        STATIC_REQUIRE(floorsqrt(3u) == 1u);
    }

    SECTION("Perfect squares") {
        for (unsigned long long i = 0; i <= 1000; ++i) {
            REQUIRE(floorsqrt(i * i) == i);
        }
        // Larger perfect squares
        REQUIRE(floorsqrt(1000000ULL * 1000000ULL) == 1000000ULL);
        unsigned long long large_square_base = 3037000499ULL; // floor(sqrt(ULLONG_MAX/2))
        unsigned long long large_square = large_square_base * large_square_base;
        REQUIRE(floorsqrt(large_square) == large_square_base);
    }

    SECTION("Numbers around perfect squares") {
        for (unsigned long long i = 1; i <= 10000; ++i) {
            unsigned long long sq = i * i;
            REQUIRE(floorsqrt(sq) == i);
            if (sq > 0) {
                REQUIRE(floorsqrt(sq - 1) == i - 1);
            }
        }
    }

    SECTION("Maximum values of integer types") {
        REQUIRE(floorsqrt(std::numeric_limits<unsigned char>::max()) == 15); // 255
        REQUIRE(floorsqrt(std::numeric_limits<unsigned short>::max()) == 255); // 65535
        REQUIRE(floorsqrt(std::numeric_limits<unsigned int>::max()) == 65535);
        REQUIRE(floorsqrt(std::numeric_limits<unsigned long>::max()) == (sizeof(unsigned long) == 8 ? 4294967295UL : 65535UL));
        REQUIRE(floorsqrt(std::numeric_limits<unsigned long long>::max()) == 4294967295ULL);
    }

    SECTION("Property checking r*r <= n < (r+1)*(r+1)") {
        // Test a range of numbers
        for (unsigned int n = 0; n < 200000; ++n) {
            unsigned int r = floorsqrt(n);
            unsigned long long r_ll = r;
            unsigned long long n_ll = n;
            REQUIRE(r_ll * r_ll <= n_ll);
            if (r_ll < std::numeric_limits<unsigned int>::max()) { // Avoid overflow on r_ll+1
                 REQUIRE((r_ll + 1) * (r_ll + 1) > n_ll);
            }
        }
    }

    SECTION("Large values") {
        unsigned long long large_val1 = 1234567890123456789ULL;
        unsigned long long root1 = floorsqrt(large_val1);
        REQUIRE(root1 == 1111111106ULL);
        REQUIRE(root1 <= large_val1 / root1);
        REQUIRE((root1 + 1) > large_val1 / (root1 + 1)); // check (root1+1)^2 > large_val1 to avoid overflow

        unsigned long long large_val2 = std::numeric_limits<unsigned long long>::max();
        unsigned long long root2 = floorsqrt(large_val2);
        REQUIRE(root2 == 4294967295ULL);
        REQUIRE(root2 <= large_val2 / root2); // check root2*root2 <= large_val2
        unsigned long long root2_plus_1 = root2 + 1;
        REQUIRE(root2_plus_1 > large_val2 / root2_plus_1); // check (root2+1)^2 > large_val2
    }
}

TEST_CASE("In-depth ceilsqrt tests", "[auxiliary_functions][ceilsqrt]") {
    SECTION("Basic and edge cases") {
        STATIC_REQUIRE(ceilsqrt(0u) == 0u);
        STATIC_REQUIRE(ceilsqrt(1u) == 1u);
        STATIC_REQUIRE(ceilsqrt(2u) == 2u);
        STATIC_REQUIRE(ceilsqrt(3u) == 2u);
        STATIC_REQUIRE(ceilsqrt(4u) == 2u);
    }

    SECTION("Perfect squares") {
        for (unsigned long long i = 0; i <= 1000; ++i) {
            REQUIRE(ceilsqrt(i * i) == i);
        }
        unsigned long long large_square_base = 3037000499ULL;
        unsigned long long large_square = large_square_base * large_square_base;
        REQUIRE(ceilsqrt(large_square) == large_square_base);
    }

    SECTION("Numbers around perfect squares") {
        for (unsigned long long i = 1; i <= 10000; ++i) {
            unsigned long long sq = i * i;
            REQUIRE(ceilsqrt(sq) == i);
            if (sq > 1) {
                REQUIRE(ceilsqrt(sq - 1) == i);
            }
            if (i < std::numeric_limits<unsigned long long>::max()) {
                REQUIRE(ceilsqrt(sq + 1) == i + 1);
            }
        }
    }

    SECTION("Maximum values of integer types") {
        REQUIRE(ceilsqrt(std::numeric_limits<unsigned char>::max()) == 16); // 255 -> 15.96 -> 16
        REQUIRE(ceilsqrt(std::numeric_limits<unsigned short>::max()) == 256); // 65535 -> 255.99 -> 256
        REQUIRE(ceilsqrt(std::numeric_limits<unsigned int>::max()) == 65536);
        REQUIRE(ceilsqrt(std::numeric_limits<unsigned long>::max()) == (sizeof(unsigned long) == 8 ? 4294967296UL : 65536UL));
        REQUIRE(ceilsqrt(std::numeric_limits<unsigned long long>::max()) == 4294967296ULL);
    }

    SECTION("Property checking (r-1)^2 < n <= r*r") {
        // Test a range of numbers
        for (unsigned int n = 1; n < 200000; ++n) {
            unsigned int r = ceilsqrt(n);
            unsigned long long r_ll = r;
            unsigned long long n_ll = n;
            REQUIRE(r_ll * r_ll >= n_ll);
            if (r_ll > 0) {
                REQUIRE((r_ll - 1) * (r_ll - 1) < n_ll);
            }
        }
    }

    SECTION("Large values") {
        unsigned long long large_val1 = 1234567890123456789ULL;
        unsigned long long root1 = ceilsqrt(large_val1);
        REQUIRE(root1 == 1111111107ULL);
        REQUIRE(root1 >= large_val1 / root1); // check root1*root1 >= large_val1
        if (root1 > 0) {
            unsigned long long root1_minus_1 = root1 - 1;
            // check (root1-1)^2 < large_val1, equivalent to (root1-1)^2 <= large_val1 - 1
            REQUIRE(root1_minus_1 <= (large_val1 - 1) / root1_minus_1);
        }

        unsigned long long large_val2 = std::numeric_limits<unsigned long long>::max();
        unsigned long long root2 = ceilsqrt(large_val2);
        REQUIRE(root2 == 4294967296ULL);
        REQUIRE(root2 >= large_val2 / root2);
        if (root2 > 0) {
            unsigned long long root2_minus_1 = root2 - 1;
            // check (root2-1)^2 < large_val2, equivalent to (root2-1)^2 <= large_val2 - 1
            REQUIRE(root2_minus_1 <= (large_val2 - 1) / root2_minus_1);
        }
    }
}

TEST_CASE("In-depth is_perfect_square tests", "[auxiliary_functions][is_perfect_square]")
{
    SECTION("Test with unsigned int (uses template version with floorsqrt)") {
        // Largest perfect square for unsigned int
        unsigned int max_root = 65535;
        unsigned int max_square = 4294836225u; // 65535^2
        REQUIRE(is_perfect_square(max_square));
        REQUIRE_FALSE(is_perfect_square(max_square + 1));
        REQUIRE_FALSE(is_perfect_square(max_square - 1));
        REQUIRE_FALSE(is_perfect_square(std::numeric_limits<unsigned int>::max()));
    }

    SECTION("Test with uint64_t (uses overload with ceilsqrt)") {
        // Largest perfect square for uint64_t
        unsigned long long max_root_64 = 4294967295ULL;
        unsigned long long max_square_64 = max_root_64 * max_root_64;
        REQUIRE(is_perfect_square(max_square_64));
        REQUIRE_FALSE(is_perfect_square(max_square_64 - 1));

        // A large non-perfect square
        REQUIRE_FALSE(is_perfect_square(max_square_64 + 1));

        // Test near max value
        REQUIRE_FALSE(is_perfect_square(std::numeric_limits<unsigned long long>::max()));
        REQUIRE_FALSE(is_perfect_square(std::numeric_limits<unsigned long long>::max() - 1));
        
        unsigned long long large_base = 3037000499ULL;
        unsigned long long large_square = large_base * large_base;
        REQUIRE(is_perfect_square(large_square));
        REQUIRE_FALSE(is_perfect_square(large_square + 1));
    }

    SECTION("Loop test for perfect squares") {
        for (unsigned int i = 0; i <= 65535; ++i) {
            unsigned int sq = i * i;
            REQUIRE(is_perfect_square(sq));
            if (i > 0 && sq < std::numeric_limits<unsigned int>::max()) {
                REQUIRE_FALSE(is_perfect_square(sq + 1));
            }
        }
    }
}

TEST_CASE("find_factor with std::expected", "[auxiliary_functions][find_factor]")
{
    SECTION("Error conditions") {
        // low <= 1
        auto res1 = find_factor(15, 1, 5);
        REQUIRE(!res1.has_value());
        REQUIRE(res1.error() == factor_error::domain_error);
        
        // n <= high
        auto res2 = find_factor(15, 2, 15);
        REQUIRE(!res2.has_value());
        REQUIRE(res2.error() == factor_error::domain_error);

        // high <= low, but not an error, should be false
        auto res3 = find_factor(15, 5, 5);
        REQUIRE(res3.has_value());
        REQUIRE(*res3 == false);

        auto res4 = find_factor(15, 6, 5);
        REQUIRE(res4.has_value());
        REQUIRE(*res4 == false);
    }

    SECTION("Finding factors") {
        // n = 33 = 3 * 11. Factors are 3 (k=1, not allowed), 11 (k=5).
        // We can't check for factor 3 with this function.
        auto res1 = find_factor(33, 2, 6);
        REQUIRE(res1.has_value());
        REQUIRE(*res1 == true); // k=5 in [2,6) -> factor 11

        // n = 15 = 3 * 5. Factors 3 (k=1), 5 (k=2).
        auto res2 = find_factor(15, 2, 3);
        REQUIRE(res2.has_value());
        REQUIRE(*res2 == true); // k=2 in [2,3) -> factor 5
    }

    SECTION("Not finding factors") {
        // Prime number
        auto res1 = find_factor(13, 2, 4);
        REQUIRE(res1.has_value());
        REQUIRE(*res1 == false);

        // Composite with factors outside range
        auto res2 = find_factor(33, 2, 5);
        REQUIRE(res2.has_value());
        REQUIRE(*res2 == false); // k=5 (factor 11) is not in [2,5)
    }
}

TEST_CASE("In-depth is_prime tests", "[auxiliary_functions][is_prime]")
{
    SECTION("Test against a list of known primes") {
        const std::vector<std::size_t> primes = {
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
            73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151,
            157, 163, 167, 173, 179, 181, 191, 193, 197, 199
        };
        for (auto p : primes) {
            REQUIRE(is_prime(p));
        }
    }

    SECTION("Test composites and numbers around primes") {
        // Composites
        REQUIRE_FALSE(is_prime(4));
        REQUIRE_FALSE(is_prime(6));
        REQUIRE_FALSE(is_prime(9));
        REQUIRE_FALSE(is_prime(15));
        REQUIRE_FALSE(is_prime(25));
        REQUIRE_FALSE(is_prime(27));
        REQUIRE_FALSE(is_prime(33));
        REQUIRE_FALSE(is_prime(35));
        REQUIRE_FALSE(is_prime(121)); // 11*11
        REQUIRE_FALSE(is_prime(169)); // 13*13

        // Around primes
        REQUIRE_FALSE(is_prime(18));
        REQUIRE(is_prime(19));
        REQUIRE_FALSE(is_prime(20));

        REQUIRE_FALSE(is_prime(198));
        REQUIRE(is_prime(199));
        REQUIRE_FALSE(is_prime(200));
    }

    SECTION("Test larger numbers") {
        REQUIRE(is_prime(7919)); // 1000th prime
        REQUIRE_FALSE(is_prime(7921)); // 89*89

        REQUIRE(is_prime(99989)); // A larger prime
        REQUIRE_FALSE(is_prime(100000));
        
        REQUIRE(is_prime(15485863)); // A large prime
        REQUIRE_FALSE(is_prime(15485864));
        REQUIRE_FALSE(is_prime(15485865));
    }
}

TEST_CASE("floorsqrt_ct_newton tests (helper function)", "[auxiliary_functions][floorsqrt_ct_newton][helper]")
{
    // La función floorsqrt_ct_newton implementa Newton-Raphson de forma recursiva
    // Dado un valor inicial x0, debería converger a floor(sqrt(n))
    
    SECTION("Testing convergence with good initial guesses") {
        // Para n=100, sqrt(100)=10, con x0=16 (sobreestimación)
        STATIC_REQUIRE(floorsqrt_ct_newton<100, 16>() == 10);
        
        // Para n=100, x0=10 (exacto) debería retornar 10
        STATIC_REQUIRE(floorsqrt_ct_newton<100, 10>() == 10);
        
        // Para n=64, sqrt(64)=8, con x0=16 (sobreestimación)
        STATIC_REQUIRE(floorsqrt_ct_newton<64, 16>() == 8);
        
        // Para n=81, sqrt(81)=9, con x0=16 (sobreestimación)
        STATIC_REQUIRE(floorsqrt_ct_newton<81, 16>() == 9);
        
        // Para n=144, sqrt(144)=12, con x0=16 (sobreestimación)
        STATIC_REQUIRE(floorsqrt_ct_newton<144, 16>() == 12);
    }
    
    SECTION("Testing with non-perfect squares") {
        // Para n=10, sqrt(10)≈3.16, floor=3, con x0=8
        STATIC_REQUIRE(floorsqrt_ct_newton<10, 8>() == 3);
        
        // Para n=50, sqrt(50)≈7.07, floor=7, con x0=16
        STATIC_REQUIRE(floorsqrt_ct_newton<50, 16>() == 7);
        
        // Para n=99, sqrt(99)≈9.95, floor=9, con x0=16
        STATIC_REQUIRE(floorsqrt_ct_newton<99, 16>() == 9);
        
        // Para n=1000, sqrt(1000)≈31.62, floor=31, con x0=64
        STATIC_REQUIRE(floorsqrt_ct_newton<1000, 64>() == 31);
    }
    
    SECTION("Testing with various initial guesses") {
        // n=25, sqrt(25)=5
        STATIC_REQUIRE(floorsqrt_ct_newton<25, 8>() == 5);   // x0=8 (sobreestimación)
        STATIC_REQUIRE(floorsqrt_ct_newton<25, 16>() == 5);  // x0=16 (mayor sobreestimación)
        STATIC_REQUIRE(floorsqrt_ct_newton<25, 32>() == 5);  // x0=32 (sobreestimación grande)
        
        // n=36, sqrt(36)=6
        STATIC_REQUIRE(floorsqrt_ct_newton<36, 8>() == 6);
        STATIC_REQUIRE(floorsqrt_ct_newton<36, 16>() == 6);
        
        // n=49, sqrt(49)=7
        STATIC_REQUIRE(floorsqrt_ct_newton<49, 8>() == 7);
        STATIC_REQUIRE(floorsqrt_ct_newton<49, 16>() == 7);
    }
    
    SECTION("Testing convergence properties") {
        // La función Newton-Raphson converge cuando x1 >= x0
        // donde x1 = (x0 + n/x0) / 2
        
        // Para n=100, x0=10: x1 = (10 + 100/10)/2 = 10, convergió
        STATIC_REQUIRE(floorsqrt_ct_newton<100, 10>() == 10);
        
        // Para n=100, x0=11: x1 = (11 + 100/11)/2 ≈ 10.04, sigue iterando
        STATIC_REQUIRE(floorsqrt_ct_newton<100, 11>() == 10);
        
        // Para n=169, x0=13: x1 = (13 + 169/13)/2 = 13, convergió
        STATIC_REQUIRE(floorsqrt_ct_newton<169, 13>() == 13);
    }
    
    SECTION("Testing with large numbers") {
        // n=10000, sqrt(10000)=100, con x0=128
        STATIC_REQUIRE(floorsqrt_ct_newton<10000, 128>() == 100);
        
        // n=1000000, sqrt(1000000)=1000, con x0=1024
        STATIC_REQUIRE(floorsqrt_ct_newton<1000000, 1024>() == 1000);
    }
}

TEST_CASE("floorsqrt_ct tests", "[auxiliary_functions][floorsqrt_ct]")
{
    // Basic cases
    STATIC_REQUIRE(floorsqrt_ct<0>() == 0);
    STATIC_REQUIRE(floorsqrt_ct<1>() == 1);
    STATIC_REQUIRE(floorsqrt_ct<2>() == 1);
    STATIC_REQUIRE(floorsqrt_ct<3>() == 1);
    STATIC_REQUIRE(floorsqrt_ct<4>() == 2);
    STATIC_REQUIRE(floorsqrt_ct<15>() == 3);
    STATIC_REQUIRE(floorsqrt_ct<16>() == 4);
    STATIC_REQUIRE(floorsqrt_ct<17>() == 4);
    STATIC_REQUIRE(floorsqrt_ct<24>() == 4);
    STATIC_REQUIRE(floorsqrt_ct<25>() == 5);
    STATIC_REQUIRE(floorsqrt_ct<26>() == 5);

    // Perfect squares
    STATIC_REQUIRE(floorsqrt_ct<100>() == 10);
    STATIC_REQUIRE(floorsqrt_ct<121>() == 11);
    STATIC_REQUIRE(floorsqrt_ct<144>() == 12);
    STATIC_REQUIRE(floorsqrt_ct<169>() == 13);
    STATIC_REQUIRE(floorsqrt_ct<196>() == 14);
    STATIC_REQUIRE(floorsqrt_ct<225>() == 15);
    STATIC_REQUIRE(floorsqrt_ct<256>() == 16);
    STATIC_REQUIRE(floorsqrt_ct<289>() == 17);
    STATIC_REQUIRE(floorsqrt_ct<324>() == 18);
    STATIC_REQUIRE(floorsqrt_ct<361>() == 19);
    STATIC_REQUIRE(floorsqrt_ct<400>() == 20);

    // Large values
    STATIC_REQUIRE(floorsqrt_ct<1000>() == 31);
    STATIC_REQUIRE(floorsqrt_ct<10000>() == 100);
    STATIC_REQUIRE(floorsqrt_ct<100000>() == 316);
    STATIC_REQUIRE(floorsqrt_ct<1000000>() == 1000);
}

TEST_CASE("ceilsqrt_ct tests", "[auxiliary_functions][ceilsqrt_ct]")
{
    // Basic cases
    STATIC_REQUIRE(ceilsqrt_ct<0>() == 0);
    STATIC_REQUIRE(ceilsqrt_ct<1>() == 1);
    STATIC_REQUIRE(ceilsqrt_ct<2>() == 2);
    STATIC_REQUIRE(ceilsqrt_ct<3>() == 2);
    STATIC_REQUIRE(ceilsqrt_ct<4>() == 2);
    STATIC_REQUIRE(ceilsqrt_ct<15>() == 4);
    STATIC_REQUIRE(ceilsqrt_ct<16>() == 4);
    STATIC_REQUIRE(ceilsqrt_ct<17>() == 5);
    STATIC_REQUIRE(ceilsqrt_ct<24>() == 5);
    STATIC_REQUIRE(ceilsqrt_ct<25>() == 5);
    STATIC_REQUIRE(ceilsqrt_ct<26>() == 6);

    // Perfect squares
    STATIC_REQUIRE(ceilsqrt_ct<100>() == 10);
    STATIC_REQUIRE(ceilsqrt_ct<121>() == 11);
    STATIC_REQUIRE(ceilsqrt_ct<144>() == 12);
    STATIC_REQUIRE(ceilsqrt_ct<169>() == 13);
    STATIC_REQUIRE(ceilsqrt_ct<196>() == 14);
    STATIC_REQUIRE(ceilsqrt_ct<225>() == 15);
    STATIC_REQUIRE(ceilsqrt_ct<256>() == 16);

    // Non-perfect squares
    STATIC_REQUIRE(ceilsqrt_ct<99>() == 10);
    STATIC_REQUIRE(ceilsqrt_ct<101>() == 11);
    STATIC_REQUIRE(ceilsqrt_ct<120>() == 11);
    STATIC_REQUIRE(ceilsqrt_ct<122>() == 12);

    // Large values
    STATIC_REQUIRE(ceilsqrt_ct<1000>() == 32);
    STATIC_REQUIRE(ceilsqrt_ct<10000>() == 100);
    STATIC_REQUIRE(ceilsqrt_ct<10001>() == 101);
}

TEST_CASE("is_perfect_square_ct tests", "[auxiliary_functions][is_perfect_square_ct]")
{
    // Perfect squares
    STATIC_REQUIRE(is_perfect_square_ct<0>());
    STATIC_REQUIRE(is_perfect_square_ct<1>());
    STATIC_REQUIRE(is_perfect_square_ct<4>());
    STATIC_REQUIRE(is_perfect_square_ct<9>());
    STATIC_REQUIRE(is_perfect_square_ct<16>());
    STATIC_REQUIRE(is_perfect_square_ct<25>());
    STATIC_REQUIRE(is_perfect_square_ct<36>());
    STATIC_REQUIRE(is_perfect_square_ct<49>());
    STATIC_REQUIRE(is_perfect_square_ct<64>());
    STATIC_REQUIRE(is_perfect_square_ct<81>());
    STATIC_REQUIRE(is_perfect_square_ct<100>());
    STATIC_REQUIRE(is_perfect_square_ct<121>());
    STATIC_REQUIRE(is_perfect_square_ct<144>());
    STATIC_REQUIRE(is_perfect_square_ct<169>());
    STATIC_REQUIRE(is_perfect_square_ct<196>());
    STATIC_REQUIRE(is_perfect_square_ct<225>());
    STATIC_REQUIRE(is_perfect_square_ct<256>());
    STATIC_REQUIRE(is_perfect_square_ct<289>());
    STATIC_REQUIRE(is_perfect_square_ct<324>());
    STATIC_REQUIRE(is_perfect_square_ct<361>());
    STATIC_REQUIRE(is_perfect_square_ct<400>());

    // Non-perfect squares
    STATIC_REQUIRE_FALSE(is_perfect_square_ct<2>());
    STATIC_REQUIRE_FALSE(is_perfect_square_ct<3>());
    STATIC_REQUIRE_FALSE(is_perfect_square_ct<5>());
    STATIC_REQUIRE_FALSE(is_perfect_square_ct<6>());
    STATIC_REQUIRE_FALSE(is_perfect_square_ct<7>());
    STATIC_REQUIRE_FALSE(is_perfect_square_ct<8>());
    STATIC_REQUIRE_FALSE(is_perfect_square_ct<10>());
    STATIC_REQUIRE_FALSE(is_perfect_square_ct<15>());
    STATIC_REQUIRE_FALSE(is_perfect_square_ct<24>());
    STATIC_REQUIRE_FALSE(is_perfect_square_ct<99>());
    STATIC_REQUIRE_FALSE(is_perfect_square_ct<101>());
    STATIC_REQUIRE_FALSE(is_perfect_square_ct<1000>());
}

TEST_CASE("gcd_ct tests", "[auxiliary_functions][gcd_ct]")
{
    // Basic GCD tests
    STATIC_REQUIRE(gcd_ct<12, 8>() == 4);
    STATIC_REQUIRE(gcd_ct<15, 25>() == 5);
    STATIC_REQUIRE(gcd_ct<17, 13>() == 1);
    STATIC_REQUIRE(gcd_ct<0, 5>() == 5);
    STATIC_REQUIRE(gcd_ct<5, 0>() == 5);
    STATIC_REQUIRE(gcd_ct<1, 5>() == 1);
    STATIC_REQUIRE(gcd_ct<5, 1>() == 1);
    STATIC_REQUIRE(gcd_ct<7, 7>() == 7);

    // More complex cases
    STATIC_REQUIRE(gcd_ct<48, 18>() == 6);
    STATIC_REQUIRE(gcd_ct<100, 35>() == 5);
    STATIC_REQUIRE(gcd_ct<270, 192>() == 6);
    STATIC_REQUIRE(gcd_ct<1071, 462>() == 21);

    // Commutative property
    STATIC_REQUIRE(gcd_ct<12, 8>() == gcd_ct<8, 12>());
    STATIC_REQUIRE(gcd_ct<48, 18>() == gcd_ct<18, 48>());

    // Coprime numbers
    STATIC_REQUIRE(gcd_ct<13, 17>() == 1);
    STATIC_REQUIRE(gcd_ct<25, 49>() == 1);
}

TEST_CASE("lcm_ct tests", "[auxiliary_functions][lcm_ct]")
{
    // Basic LCM tests
    STATIC_REQUIRE(lcm_ct<4, 6>() == 12);
    STATIC_REQUIRE(lcm_ct<15, 25>() == 75);
    STATIC_REQUIRE(lcm_ct<7, 13>() == 91);
    STATIC_REQUIRE(lcm_ct<0, 5>() == 0);
    STATIC_REQUIRE(lcm_ct<5, 0>() == 0);

    // More complex cases
    STATIC_REQUIRE(lcm_ct<12, 15>() == 60);
    STATIC_REQUIRE(lcm_ct<21, 6>() == 42);
    STATIC_REQUIRE(lcm_ct<8, 12>() == 24);

    // Commutative property
    STATIC_REQUIRE(lcm_ct<4, 6>() == lcm_ct<6, 4>());
    STATIC_REQUIRE(lcm_ct<12, 15>() == lcm_ct<15, 12>());

    // Relationship with GCD: lcm(a,b) * gcd(a,b) = a * b
    STATIC_REQUIRE(lcm_ct<12, 8>() * gcd_ct<12, 8>() == 12 * 8);
    STATIC_REQUIRE(lcm_ct<15, 25>() * gcd_ct<15, 25>() == 15 * 25);
}

TEST_CASE("find_factor_ct tests (helper function)", "[auxiliary_functions][find_factor_ct][helper]")
{
    // La función find_factor_ct busca recursivamente un factor impar en un rango
    // Busca k tal que (2*k + 1) divide a n
    
    SECTION("Finding factors in composite numbers") {
        // n = 15 = 3 * 5
        // Factor 3: k=1 (2*1+1=3), fuera del rango permitido (low > 1)
        // Factor 5: k=2 (2*2+1=5)
        STATIC_REQUIRE(find_factor_ct<std::uint64_t, 15, 2, 3>() == true);  // k=2 en [2,3) -> factor 5
        STATIC_REQUIRE(find_factor_ct<std::uint64_t, 15, 3, 5>() == false); // k=3,4 no son factores
        
        // n = 21 = 3 * 7
        // Factor 3: k=1 (2*1+1=3), fuera del rango
        // Factor 7: k=3 (2*3+1=7)
        STATIC_REQUIRE(find_factor_ct<std::uint64_t, 21, 2, 4>() == true);  // k=3 en [2,4) -> factor 7
        STATIC_REQUIRE(find_factor_ct<std::uint64_t, 21, 2, 3>() == false); // k=2 no es factor
        
        // n = 35 = 5 * 7
        // Factor 5: k=2 (2*2+1=5)
        // Factor 7: k=3 (2*3+1=7)
        STATIC_REQUIRE(find_factor_ct<std::uint64_t, 35, 2, 3>() == true);  // k=2 -> factor 5
        STATIC_REQUIRE(find_factor_ct<std::uint64_t, 35, 3, 4>() == true);  // k=3 -> factor 7
        
        // n = 33 = 3 * 11
        // Factor 3: k=1, fuera del rango
        // Factor 11: k=5 (2*5+1=11)
        STATIC_REQUIRE(find_factor_ct<std::uint64_t, 33, 2, 6>() == true);  // k=5 en [2,6) -> factor 11
        STATIC_REQUIRE(find_factor_ct<std::uint64_t, 33, 2, 5>() == false); // k=5 no está en [2,5)
    }
    
    SECTION("Not finding factors in primes or wrong ranges") {
        // n = 13 (primo)
        STATIC_REQUIRE(find_factor_ct<std::uint64_t, 13, 2, 4>() == false); // No factors
        
        // n = 17 (primo)
        STATIC_REQUIRE(find_factor_ct<std::uint64_t, 17, 2, 5>() == false); // No factors
        
        // n = 23 (primo)
        STATIC_REQUIRE(find_factor_ct<std::uint64_t, 23, 2, 8>() == false); // No factors
    }
    
    SECTION("Binary search behavior") {
        // n = 77 = 7 * 11
        // Factor 7: k=3 (2*3+1=7)
        // Factor 11: k=5 (2*5+1=11)
        STATIC_REQUIRE(find_factor_ct<std::uint64_t, 77, 2, 6>() == true);  // Encuentra k=3 o k=5
        STATIC_REQUIRE(find_factor_ct<std::uint64_t, 77, 2, 4>() == true);  // Encuentra k=3
        STATIC_REQUIRE(find_factor_ct<std::uint64_t, 77, 5, 6>() == true);  // Encuentra k=5
        
        // n = 143 = 11 * 13
        // Factor 11: k=5 (2*5+1=11)
        // Factor 13: k=6 (2*6+1=13)
        STATIC_REQUIRE(find_factor_ct<std::uint64_t, 143, 2, 7>() == true);  // Encuentra k=5 o k=6
        STATIC_REQUIRE(find_factor_ct<std::uint64_t, 143, 5, 6>() == true);  // Encuentra k=5
        STATIC_REQUIRE(find_factor_ct<std::uint64_t, 143, 6, 7>() == true);  // Encuentra k=6
    }
    
    SECTION("Edge cases with single element range") {
        // Rango de un solo elemento: low + 1 >= high
        // n = 25 = 5 * 5
        // Factor 5: k=2 (2*2+1=5)
        STATIC_REQUIRE(find_factor_ct<std::uint64_t, 25, 2, 3>() == true);  // Solo k=2
        
        // n = 49 = 7 * 7
        // Factor 7: k=3 (2*3+1=7)
        STATIC_REQUIRE(find_factor_ct<std::uint64_t, 49, 3, 4>() == true);  // Solo k=3
    }
}

TEST_CASE("pow_leq_limit_ct_helper tests (helper function)", "[auxiliary_functions][pow_leq_limit_ct_helper][helper]")
{
    // La función pow_leq_limit_ct_helper implementa exponenciación por cuadrados
    // con verificación de límite y detección de overflow
    // Parámetros: <result, cur, e, limit>
    
    SECTION("Base cases with e=0") {
        // Cuando e=0, retorna result <= limit
        STATIC_REQUIRE(pow_leq_limit_ct_helper<1, 2, 0, 10>() == true);   // 1 <= 10
        STATIC_REQUIRE(pow_leq_limit_ct_helper<5, 2, 0, 10>() == true);   // 5 <= 10
        STATIC_REQUIRE(pow_leq_limit_ct_helper<10, 2, 0, 10>() == true);  // 10 <= 10
        STATIC_REQUIRE(pow_leq_limit_ct_helper<11, 2, 0, 10>() == false); // 11 > 10
        STATIC_REQUIRE(pow_leq_limit_ct_helper<100, 2, 0, 50>() == false); // 100 > 50
    }
    
    SECTION("Simple exponentiations that fit in limit") {
        // result=1, cur=2, e=3, limit=8: Calculando 2^3 = 8
        STATIC_REQUIRE(pow_leq_limit_ct_helper<1, 2, 3, 8>() == true);   // 2^3 = 8 <= 8
        STATIC_REQUIRE(pow_leq_limit_ct_helper<1, 2, 3, 7>() == false);  // 2^3 = 8 > 7
        STATIC_REQUIRE(pow_leq_limit_ct_helper<1, 2, 3, 10>() == true);  // 2^3 = 8 <= 10
        
        // result=1, cur=3, e=2, limit=9: Calculando 3^2 = 9
        STATIC_REQUIRE(pow_leq_limit_ct_helper<1, 3, 2, 9>() == true);   // 3^2 = 9 <= 9
        STATIC_REQUIRE(pow_leq_limit_ct_helper<1, 3, 2, 8>() == false);  // 3^2 = 9 > 8
        
        // result=1, cur=5, e=2, limit=25: Calculando 5^2 = 25
        STATIC_REQUIRE(pow_leq_limit_ct_helper<1, 5, 2, 25>() == true);  // 5^2 = 25 <= 25
        STATIC_REQUIRE(pow_leq_limit_ct_helper<1, 5, 2, 24>() == false); // 5^2 = 25 > 24
    }
    
    SECTION("Testing bit manipulation (odd/even exponents)") {
        // e=1 (impar, bit 0 es 1): multiplica result por cur
        STATIC_REQUIRE(pow_leq_limit_ct_helper<1, 2, 1, 2>() == true);   // 1*2 = 2 <= 2
        STATIC_REQUIRE(pow_leq_limit_ct_helper<1, 2, 1, 1>() == false);  // 1*2 = 2 > 1
        
        // e=2 (par, bit 0 es 0): no multiplica result, solo eleva cur al cuadrado
        STATIC_REQUIRE(pow_leq_limit_ct_helper<1, 2, 2, 4>() == true);   // 2^2 = 4 <= 4
        STATIC_REQUIRE(pow_leq_limit_ct_helper<1, 2, 2, 3>() == false);  // 2^2 = 4 > 3
    }
    
    SECTION("Accumulated result cases") {
        // result ya tiene un valor acumulado
        // result=2, cur=3, e=2, limit=18: 2 * 3^2 = 2 * 9 = 18
        STATIC_REQUIRE(pow_leq_limit_ct_helper<2, 3, 2, 18>() == true);  // 18 <= 18
        STATIC_REQUIRE(pow_leq_limit_ct_helper<2, 3, 2, 17>() == false); // 18 > 17
        
        // result=4, cur=2, e=2, limit=16: 4 * 2^2 = 4 * 4 = 16
        STATIC_REQUIRE(pow_leq_limit_ct_helper<4, 2, 2, 16>() == true);  // 16 <= 16
        STATIC_REQUIRE(pow_leq_limit_ct_helper<4, 2, 2, 15>() == false); // 16 > 15
    }
    
    SECTION("Overflow detection") {
        // Casos donde cur * cur causaría overflow
        constexpr std::uint64_t max_val = std::numeric_limits<std::uint64_t>::max();
        constexpr std::uint64_t large_base = 4294967296ULL; // 2^32
        
        // large_base * large_base overflow
        STATIC_REQUIRE(pow_leq_limit_ct_helper<1, large_base, 2, max_val>() == false);
        
        // result * cur excedería el límite
        STATIC_REQUIRE(pow_leq_limit_ct_helper<100, 100, 1, 1000>() == false); // 100*100 > 1000
    }
    
    SECTION("Powers of 2 calculations") {
        // 2^4 = 16
        STATIC_REQUIRE(pow_leq_limit_ct_helper<1, 2, 4, 16>() == true);
        STATIC_REQUIRE(pow_leq_limit_ct_helper<1, 2, 4, 15>() == false);
        
        // 2^5 = 32
        STATIC_REQUIRE(pow_leq_limit_ct_helper<1, 2, 5, 32>() == true);
        STATIC_REQUIRE(pow_leq_limit_ct_helper<1, 2, 5, 31>() == false);
        
        // 2^10 = 1024
        STATIC_REQUIRE(pow_leq_limit_ct_helper<1, 2, 10, 1024>() == true);
        STATIC_REQUIRE(pow_leq_limit_ct_helper<1, 2, 10, 1023>() == false);
    }
}

TEST_CASE("pow_leq_limit_ct tests", "[auxiliary_functions][pow_leq_limit_ct]")
{
    // Base cases
    STATIC_REQUIRE(pow_leq_limit_ct<0, 5, 10>() == true);  // 0^5 = 0 <= 10
    STATIC_REQUIRE(pow_leq_limit_ct<1, 100, 10>() == true); // 1^100 = 1 <= 10
    STATIC_REQUIRE(pow_leq_limit_ct<2, 0, 5>() == true);   // 2^0 = 1 <= 5

    // Powers of 2
    STATIC_REQUIRE(pow_leq_limit_ct<2, 3, 8>() == true);   // 2^3 = 8 <= 8
    STATIC_REQUIRE(pow_leq_limit_ct<2, 3, 7>() == false);  // 2^3 = 8 > 7
    STATIC_REQUIRE(pow_leq_limit_ct<2, 10, 1024>() == true); // 2^10 = 1024 <= 1024
    STATIC_REQUIRE(pow_leq_limit_ct<2, 10, 1023>() == false); // 2^10 = 1024 > 1023

    // Other bases
    STATIC_REQUIRE(pow_leq_limit_ct<3, 4, 81>() == true);  // 3^4 = 81 <= 81
    STATIC_REQUIRE(pow_leq_limit_ct<3, 4, 80>() == false); // 3^4 = 81 > 80
    STATIC_REQUIRE(pow_leq_limit_ct<5, 3, 125>() == true); // 5^3 = 125 <= 125
    STATIC_REQUIRE(pow_leq_limit_ct<5, 3, 124>() == false); // 5^3 = 125 > 124

    // Large values (overflow detection)
    STATIC_REQUIRE(pow_leq_limit_ct<10, 19, 10000000000000000000ULL>() == true); // 10^19 <= 10^19
    // Note: 2^63 = 9223372036854775808, which is larger than max signed long long (9223372036854775807)
    // so this test is checking if the overflow detection works correctly
}

TEST_CASE("pow_leq_limit tests", "[auxiliary_functions][pow_leq_limit]")
{
    // Base cases
    REQUIRE(pow_leq_limit(0, 5, 10) == true);  // 0^5 = 0 <= 10
    REQUIRE(pow_leq_limit(1, 100, 10) == true); // 1^100 = 1 <= 10
    REQUIRE(pow_leq_limit(2, 0, 5) == true);   // 2^0 = 1 <= 5

    // Powers of 2
    REQUIRE(pow_leq_limit(2, 3, 8) == true);   // 2^3 = 8 <= 8
    REQUIRE(pow_leq_limit(2, 3, 7) == false);  // 2^3 = 8 > 7
    REQUIRE(pow_leq_limit(2, 10, 1024) == true); // 2^10 = 1024 <= 1024
    REQUIRE(pow_leq_limit(2, 10, 1023) == false); // 2^10 = 1024 > 1023

    // Other bases
    REQUIRE(pow_leq_limit(3, 4, 81) == true);  // 3^4 = 81 <= 81
    REQUIRE(pow_leq_limit(3, 4, 80) == false); // 3^4 = 81 > 80
    REQUIRE(pow_leq_limit(5, 3, 125) == true); // 5^3 = 125 <= 125
    REQUIRE(pow_leq_limit(5, 3, 124) == false); // 5^3 = 125 > 124
    REQUIRE(pow_leq_limit(10, 5, 100000) == true); // 10^5 = 100000 <= 100000
    REQUIRE(pow_leq_limit(10, 5, 99999) == false); // 10^5 = 100000 > 99999

    // Overflow detection
    REQUIRE(pow_leq_limit(2, 64, std::numeric_limits<std::uint64_t>::max()) == false); // Overflow
    REQUIRE(pow_leq_limit(1000, 10, std::numeric_limits<std::uint64_t>::max()) == false); // Overflow
}

// Definición de expresiones de iteración para Newton-Raphson genérico
namespace newton_test_helpers {
    // Expresión de iteración para raíz cuadrada: x1 = (x0 + n/x0) / 2
    template <std::uint64_t x0, std::uint64_t n>
    struct sqrt_iteration {
        static constexpr std::uint64_t value = (x0 + n / x0) / 2;
    };

    // Expresión de iteración para raíz cúbica: x1 = (2*x0 + n/(x0*x0)) / 3
    template <std::uint64_t x0, std::uint64_t n>
    struct cbrt_iteration {
        static constexpr std::uint64_t value = 
            (x0 == 0) ? (n > 0 ? 1 : 0) : (2 * x0 + n / (x0 * x0)) / 3;
    };
}

TEST_CASE("newton_raphson_ct generic method tests", "[auxiliary_functions][newton_raphson_ct]")
{
    using namespace newton_test_helpers;

    SECTION("Using generic Newton-Raphson for square root")
    {
        // Test con valores perfectos
        STATIC_REQUIRE(newton_raphson_ct<100, 16, sqrt_iteration>() == 10);
        STATIC_REQUIRE(newton_raphson_ct<64, 16, sqrt_iteration>() == 8);
        STATIC_REQUIRE(newton_raphson_ct<81, 16, sqrt_iteration>() == 9);
        STATIC_REQUIRE(newton_raphson_ct<144, 16, sqrt_iteration>() == 12);
        
        // Test con valores no perfectos
        STATIC_REQUIRE(newton_raphson_ct<10, 8, sqrt_iteration>() == 3);
        STATIC_REQUIRE(newton_raphson_ct<50, 16, sqrt_iteration>() == 7);
        STATIC_REQUIRE(newton_raphson_ct<99, 16, sqrt_iteration>() == 9);
        
        // Verificar que coincide con floorsqrt_ct_newton
        STATIC_REQUIRE(newton_raphson_ct<100, 16, sqrt_iteration>() == floorsqrt_ct_newton<100, 16>());
        STATIC_REQUIRE(newton_raphson_ct<1000, 64, sqrt_iteration>() == floorsqrt_ct_newton<1000, 64>());
    }

    SECTION("Potential for other uses - cube root approximation")
    {
        // Test básico (no será tan preciso como el de raíz cuadrada)
        // 27 = 3^3, comenzando con x0 = 4
        constexpr auto result_27 = newton_raphson_ct<27, 4, cbrt_iteration>();
        STATIC_REQUIRE(result_27 >= 3 && result_27 <= 4); // Debería estar cerca de 3
        
        // 64 = 4^3, comenzando con x0 = 5
        constexpr auto result_64 = newton_raphson_ct<64, 5, cbrt_iteration>();
        STATIC_REQUIRE(result_64 >= 4 && result_64 <= 5); // Debería estar cerca de 4
    }

    SECTION("Demonstrate reusability with different initial guesses")
    {
        // Mismo valor, diferentes estimaciones iniciales, mismo resultado
        // Nota: comenzar con x0 < sqrt(n) puede dar convergencia prematura
        STATIC_REQUIRE(newton_raphson_ct<100, 10, sqrt_iteration>() == 10);
        STATIC_REQUIRE(newton_raphson_ct<100, 16, sqrt_iteration>() == 10);
        STATIC_REQUIRE(newton_raphson_ct<100, 20, sqrt_iteration>() == 10);
        STATIC_REQUIRE(newton_raphson_ct<100, 32, sqrt_iteration>() == 10);
    }
}

// Helper para crear objetos de prueba con dígitos específicos
template<uint64_t Base, size_t Length>
struct MockDigitContainer {
    uint64_t digits[Length];
    
    struct Digit {
        uint64_t val;
        constexpr uint64_t operator()() const noexcept { return val; }
    };
    
    constexpr MockDigitContainer(std::initializer_list<uint64_t> init) noexcept {
        size_t i = 0;
        for (auto val : init) {
            if (i < Length) digits[i++] = val;
        }
        while (i < Length) digits[i++] = 0;
    }
    
    constexpr Digit operator[](size_t idx) const noexcept {
        return Digit{digits[idx]};
    }
};

TEST_CASE("conversion_to_int family", "[auxiliary_functions][conversion]")
{
    using namespace NumRepr::auxiliary_functions;
    
    SECTION("conversion_to_int basic - base 10")
    {
        constexpr MockDigitContainer<10, 3> container{6, 5, 4}; // 456 en base 10
        constexpr auto result = conversion_to_int<10, 3>(container);
        STATIC_REQUIRE(result == 456);
    }
    
    SECTION("conversion_to_int basic - base 2")
    {
        // digits[0]=LSB...digits[7]=MSB → valor = Σ(digit[i] * 2^i)
        // {0,1,0,1,0,1,0,1} = 0 + 2 + 0 + 8 + 0 + 32 + 0 + 128 = 170 = 0b10101010
        constexpr MockDigitContainer<2, 8> container{0, 1, 0, 1, 0, 1, 0, 1};
        constexpr auto result = conversion_to_int<2, 8>(container);
        STATIC_REQUIRE(result == 170);
    }
    
    SECTION("conversion_to_int basic - base 16")
    {
        // digits[0]=LSN...digits[3]=MSN → valor = Σ(digit[i] * 16^i)
        // {15,14,10,13} = 0xF + 0xE*16 + 0xA*256 + 0xD*4096 = 15 + 224 + 2560 + 53248 = 56047 = 0xDAEF
        constexpr MockDigitContainer<16, 4> container{15, 14, 10, 13};
        constexpr auto result = conversion_to_int<16, 4>(container);
        STATIC_REQUIRE(result == 0xDAEF);
    }
    
    SECTION("conversion_to_int_safe - éxito con valores válidos")
    {
        constexpr MockDigitContainer<10, 3> container{6, 5, 4}; // 456
        constexpr auto result = conversion_to_int_safe<10, 3>(container);
        STATIC_REQUIRE(result.has_value());
        STATIC_REQUIRE(*result == 456);
    }
    
    SECTION("conversion_to_int_safe - detecta dígito inválido")
    {
        constexpr MockDigitContainer<10, 3> container{6, 15, 4}; // 15 >= 10 (inválido)
        constexpr auto result = conversion_to_int_safe<10, 3>(container);
        STATIC_REQUIRE(!result.has_value());
        STATIC_REQUIRE(result.error() == ConversionError::InvalidDigit);
    }
    
    SECTION("conversion_to_int_safe - detecta base inválida")
    {
        constexpr MockDigitContainer<1, 3> container{0, 0, 0}; // Base 1 es inválida
        constexpr auto result = conversion_to_int_safe<1, 3>(container);
        STATIC_REQUIRE(!result.has_value());
        STATIC_REQUIRE(result.error() == ConversionError::InvalidBase);
    }
    
    SECTION("conversion_to_int_ct - compile time forzado")
    {
        constexpr MockDigitContainer<10, 3> container{9, 8, 7}; // 789
        constexpr auto result = conversion_to_int_ct<10, 3>(container);
        STATIC_REQUIRE(result == 789);
    }
    
    SECTION("conversion_to_int_ct - base 2")
    {
        constexpr MockDigitContainer<2, 4> container{1, 1, 1, 1}; // 1111 = 15
        constexpr auto result = conversion_to_int_ct<2, 4>(container);
        STATIC_REQUIRE(result == 15);
    }
    
    SECTION("conversion_to_int_safe_ct - éxito compile-time")
    {
        // digits[0]=unidades...digits[4]=decenas_de_millar
        // {3,2,1,2,3} = 3 + 2*10 + 1*100 + 2*1000 + 3*10000 = 32123
        constexpr MockDigitContainer<10, 5> container{3, 2, 1, 2, 3};
        constexpr auto result = conversion_to_int_safe_ct<10, 5>(container);
        STATIC_REQUIRE(result.has_value());
        STATIC_REQUIRE(*result == 32123);
    }
    
    SECTION("conversion_to_int_safe_ct - detecta error en compile-time")
    {
        constexpr MockDigitContainer<8, 3> container{7, 9, 6}; // 9 >= 8 (inválido en octal)
        constexpr auto result = conversion_to_int_safe_ct<8, 3>(container);
        STATIC_REQUIRE(!result.has_value());
        STATIC_REQUIRE(result.error() == ConversionError::InvalidDigit);
    }
    
    SECTION("conversion_to_int_safe - casos límite")
    {
        // Máximo valor en 1 dígito base 256
        constexpr MockDigitContainer<256, 1> max_single{255};
        constexpr auto result1 = conversion_to_int_safe<256, 1>(max_single);
        STATIC_REQUIRE(result1.has_value());
        STATIC_REQUIRE(*result1 == 255);
        
        // Caso con ceros
        constexpr MockDigitContainer<10, 4> zeros{0, 0, 0, 0};
        constexpr auto result2 = conversion_to_int_safe<10, 4>(zeros);
        STATIC_REQUIRE(result2.has_value());
        STATIC_REQUIRE(*result2 == 0);
        
        // Un solo dígito no-cero
        constexpr MockDigitContainer<10, 4> single{5, 0, 0, 0};
        constexpr auto result3 = conversion_to_int_safe<10, 4>(single);
        STATIC_REQUIRE(result3.has_value());
        STATIC_REQUIRE(*result3 == 5);
    }
    
    SECTION("Comparación: todas las versiones dan mismo resultado válido")
    {
        constexpr MockDigitContainer<10, 3> container{1, 2, 3}; // 321
        
        constexpr auto normal = conversion_to_int<10, 3>(container);
        constexpr auto safe = conversion_to_int_safe<10, 3>(container);
        constexpr auto ct = conversion_to_int_ct<10, 3>(container);
        constexpr auto safe_ct = conversion_to_int_safe_ct<10, 3>(container);
        
        STATIC_REQUIRE(normal == 321);
        STATIC_REQUIRE(safe.has_value());
        STATIC_REQUIRE(*safe == 321);
        STATIC_REQUIRE(ct == 321);
        STATIC_REQUIRE(safe_ct.has_value());
        STATIC_REQUIRE(*safe_ct == 321);
        
        // Todas coinciden
        STATIC_REQUIRE(normal == *safe);
        STATIC_REQUIRE(normal == ct);
        STATIC_REQUIRE(normal == *safe_ct);
    }
}

