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