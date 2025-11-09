#ifndef NUMREPR_CORE_INTERNAL_AUXILIARY_FUNCTIONS_HPP_INCLUDED
#define NUMREPR_CORE_INTERNAL_AUXILIARY_FUNCTIONS_HPP_INCLUDED

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <numeric>

#include "core/internal/auxiliary_types.hpp"

namespace NumRepr {

  namespace auxiliary_functions {

  constexpr inline
  std::size_t ceilsqrt(std::size_t n, std::size_t low, std::size_t high) noexcept {
    const auto mid{std::midpoint(low, high)};
    const auto sqmid{mid * mid};
    return ((low + 1 >= high) ? high
            : (sqmid == n)    ? mid
            : (sqmid < n)     ? ceilsqrt(n, mid, high)
                              : ceilsqrt(n, low, mid));
  } // END FUNCTION CEILSQRT

  constexpr inline
  std::size_t ceilsqrt(std::size_t n) noexcept {
    const auto num_max_dig{std::numeric_limits<std::size_t>::digits};
    return (
        (n < 3)     ? 
            n       :   // n <  3
            ceilsqrt(   // n >= 3
                n, 
                1, 
                std::size_t(1) << (num_max_dig / 2)
            )
    );
  }  // END FUNCTION CEILSQRT

  constexpr inline
  bool find_factor(std::size_t n, std::size_t low, std::size_t high) noexcept {
    const auto mid{std::midpoint(low, high)};
    return ((low + 1 >= high) ? 
              (n % (2 * low + 1)) == 0 : 
              (find_factor(n, low, mid) || find_factor(n, mid, high))
           );
  } // END FUNCTION FIND_FACTOR

  constexpr inline
  bool is_power_of_2(std::uint64_t num) noexcept { 
    return num > 0 && (num & (num - 1)) == 0; 
  } // END FUNCTION IS_POWER_OF_2

  constexpr inline
  bool is_prime(std::size_t n) noexcept {
    if (n < 2) return false;
    else if (n == 2 || n == 3) return true;
    else if (n % 2 == 0 || n % 3 == 0) return false;
    else 
      return (!find_factor(n, 1, (ceilsqrt(n) + 1) / 2));
  } // END FUNCTION IS_PRIME

  constexpr inline
  std::uint64_t gcd(std::uint64_t a, std::uint64_t b) noexcept {
    while (b != 0) { 
      const auto temp = b; 
      b = a % b; 
      a = temp; 
    }
    return a;
  } // END FUNCTION GCD

  constexpr inline
  std::uint64_t lcm(std::uint64_t a, std::uint64_t b) noexcept { 
    return (a == 0 || b == 0) ? 0 : (a / gcd(a, b)) * b; 
  } // END FUNCTION LCM

  constexpr inline
  std::uint64_t int_pow(std::uint64_t base, std::uint32_t exponent) noexcept {
    if (exponent == 0) return 1;
    if (exponent == 1) return base;
    if (base == 0) return 0;
    if (base == 1) return 1;
    std::uint64_t result = 1;
    std::uint64_t current_base = base;
    while (exponent > 0) {
      if (exponent & 1) { result *= current_base; }
      current_base *= current_base;
      exponent >>= 1;
    }
    return result;
  } // END FUNCTION INT_POW

  constexpr inline
  bool is_perfect_square(std::uint64_t n) noexcept {
    if (n == 0 || n == 1) { return true; }
    const auto root = ceilsqrt(n);
    return root * root == n;
  } // END FUNCTION IS_PERFECT_SQUARE

  // forward declaration for integer log2 (definition appears below)
  constexpr std::uint64_t int_log2(std::uint64_t n) noexcept;
  // forward declaration for count_digits_base (defined below)
  constexpr std::size_t count_digits_base(std::uint64_t n, std::uint64_t base) noexcept;

  constexpr inline
  std::size_t count_digits_base10(std::uint64_t n) noexcept { 
    // (forward declarations for functions defined later are placed at
    // namespace scope; here we can call the generic implementation.)
    // implement via generic count_digits_base to keep a single implementation
    return count_digits_base(n, 10);
  }  // END FUNCTION COUNT_DIGITS_BASE10

  constexpr inline
  std::size_t count_digits_base(std::uint64_t n, std::uint64_t base) noexcept { 
    if (base < 2) return 0;
    if (n == 0) return 1;

    // Fast path for base 2 using int_log2
    if (base == 2) {
      return static_cast<std::size_t>(int_log2(n)) + 1u;
    }

    // Helper: test whether base^exp <= limit without overflow
    auto pow_leq = 
      [](std::uint64_t b, std::uint32_t exp, std::uint64_t limit) noexcept {
        std::uint64_t result = 1;
        std::uint64_t cur = b;
        std::uint32_t e = exp;
        while (e > 0) {
          if (e & 1u) {
            if (cur == 0) return result <= limit;
            if (result > limit / cur) return false; // would overflow
            result *= cur;
          }
          e >>= 1u;
          if (e > 0) {
            if (cur > 0 && cur > limit / cur) 
                cur = limit + 1; // make cur > limit to short-circuit
            else cur *= cur;
          }
        }
        return result <= limit;
    };

    // Exponential search for an upper bound for the exponent
    std::uint32_t lo = 0u;
    std::uint32_t hi = 1u;
    while (pow_leq(base, hi, n)) {
      lo = hi;
      hi = hi * 2u;
      if (hi == 0u) break; // overflow guard
    }

    // binary search for the largest e such that base^e <= n
    while (lo + 1u < hi) {
      std::uint32_t mid = lo + (hi - lo) / 2u;
      if (pow_leq(base, mid, n)) lo = mid;
      else hi = mid;
    }

    // number of digits = exponent + 1
    return static_cast<std::size_t>(lo) + 1u;
  } // END FUNCTION COUNT_DIGITS_BASE

  // ---- util_functs moved here ----
  // potencia de 2 (consteval template)
  template<std::uint64_t>
  consteval std::uint64_t int_pow2ct() noexcept;
  template<std::uint64_t>
  consteval std::uint64_t int_log2ct() noexcept;

  constexpr
  std::uint64_t int_pow2(std::uint64_t) noexcept;
  constexpr
  std::uint64_t int_log2(std::uint64_t) noexcept;

  template<std::uint64_t n>
  consteval
  std::uint64_t int_pow2ct() noexcept {
    if constexpr (n == 0) { return 1ull; }
    else if constexpr (n == 1) { return 2ull; }
    else { return (2ull*int_pow2ct<n-1ull>()); }
  } // END FUNCTION INT_POW2CT

  constexpr
  std::uint64_t int_pow2(std::uint64_t n) noexcept {
    if (n == 0) { return 1ull; }
    else if (n == 1) { return 2ull; }
    else { return (2ull*int_pow2(n-1ull)); }
  } // END FUNCTION INT_POW2

  // Backwards-compatible aliases: keep the old names while the codebase
  // migrates to int_* names. These simply forward to the new functions.
  template<std::uint64_t N>
  consteval std::uint64_t pow2ct() noexcept { return int_pow2ct<N>(); }

  constexpr std::uint64_t pow2(std::uint64_t n) noexcept { return int_pow2(n); }

  template<std::uint64_t n>
    requires (n>0)
  consteval
  std::uint64_t int_log2ct() noexcept {
    if constexpr (n == 1) { return 0ull; }
    else if constexpr (n == 2) { return 1ull; }
    else if constexpr (n <= 4) { return 2ull; }
    else if constexpr (n <= 8) { return 3ull; }
    else if constexpr (n <= 16) { return 4ull; }
    else if constexpr (n <= 32) { return 5ull; }
    else if constexpr (n <= 64) { return 6ull; }
    else if constexpr (n <= 128) { return 7ull; }
    else if constexpr (n <= 256) { return 8ull; }
    else if constexpr (n <= 512) { return 9ull; }
    else if constexpr (n <= 1024) { return 10ull; }
    else if constexpr (n <= 2048) { return 11ull; }
    else if constexpr (n <= 4096) { return 12ull; }
    else if constexpr (n <= 8192) { return 13ull; }
    else if constexpr (n <= 16384) { return 14ull; }
    else if constexpr (n <= 32768) { return 15ull; }
    else if constexpr (n <= 65536) { return 16ull; }
    else { return (1+int_log2ct<n/2>()); }
  }  // END FUNCTION INT_LOG2CT

  constexpr
  std::uint64_t int_log2(std::uint64_t n) noexcept {
    if (n <= 1) { return 0ull; }
    else if (n <= 2) { return 1ull; }
    else if (n <= 4) { return 2ull; }
    else if (n <= 8) { return 3ull; }
    else if (n <= 16) { return 4ull; }
    else if (n <= 32) { return 5ull; }
    else if (n <= 64) { return 6ull; }
    else if (n <= 128) { return 7ull; }
    else if (n <= 256) { return 8ull; }
    else if (n <= 512) { return 9ull; }
    else if (n <= 1024) { return 10ull; }
    else if (n <= 2048) { return 11ull; }
    else if (n <= 4096) { return 12ull; }
    else if (n <= 8192) { return 13ull; }
    else if (n <= 16384) { return 14ull; }
    else if (n <= 32768) { return 15ull; }
    else if (n <= 65536) { return 16ull; }
    else { return (1+int_log2(n/2)); }
  } // END FUNCTION INT_LOG2

    // Backwards-compatible aliases for log2/log2ct that forward to the
    // new int_log2/int_log2ct implementations. This allows an incremental
    // migration of the codebase while keeping old names working.
    template<std::uint64_t N>
    consteval std::uint64_t log2ct() noexcept { return int_log2ct<N>(); }

    constexpr std::uint64_t log2(std::uint64_t n) noexcept { return int_log2(n); }

  } // CLOSE NAMESPACE auxiliary_functions
} // CLOSE NAMESPACE NumRepr

#endif // AUXILIARY_FUNCTIONS_HPP_INCLUDED
