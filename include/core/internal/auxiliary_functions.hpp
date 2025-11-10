#ifndef NUMREPR_CORE_INTERNAL_AUXILIARY_FUNCTIONS_HPP_INCLUDED
#define NUMREPR_CORE_INTERNAL_AUXILIARY_FUNCTIONS_HPP_INCLUDED

#include <concepts>
#include <cmath>
#include <type_traits>
#include <bit>
#include "auxiliary_types.hpp"

namespace NumRepr {

  namespace auxiliary_functions {

  template <typename T>
  constexpr T ceilsqrt(T n) noexcept {
      static_assert(std::is_unsigned_v<T>&&std::is_integral_v<T>, 
                    "ceilsqrt can only be used with unsigned integral types"
                   );
      if (n < 2) { return n; }
      // Use a robust iterative method (based on Newton's method)
      T x0 = n;
      T x1 = (x0 + n / x0) / 2;
      while (x1 < x0) {
          x0 = x1;
          x1 = (x0 + n / x0) / 2;
      }
      // At this point, x0 is floor(sqrt(n)).
      // We need ceil(sqrt(n)), so if x0*x0 is not n and the square is smaller, we add 1.
      return (x0 * x0 >= n) ? x0 : x0 + 1;
  }

  // --- Backward compatibility wrappers for std::size_t ---
  // This overload is kept for compatibility with code that might call it with 3 arguments.
  constexpr inline
  std::size_t ceilsqrt(std::size_t n, std::size_t, std::size_t) noexcept {
    return ceilsqrt<std::size_t>(n);
  }

  constexpr inline
  std::size_t ceilsqrt(std::size_t n) noexcept {
    return ceilsqrt<std::size_t>(n);
  }

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

  /// Máximo exponente para cada base que cabe en uint64_t
  /// Obtenida con Maxima CAS (cada lista es [base, max_exponent])
  /// Solo se imprimen las primeras bases que tienen exponente máximo
  /// diferente a la base anterior
  /// [2,63]
  /// [3,40]
  /// [4,31]
  /// [5,27]
  /// [6,24]
  /// [7,22]
  /// [8,21]
  /// [9,20]
  /// [10,19]
  /// [11,18]
  /// [12,17]
  /// [14,16]
  /// [16,15]
  /// [20,14]
  /// [24,13]
  /// [31,12]
  /// [41,11]
  /// [57,10]
  /// [85,9]
  /// [139,8]
  /// [256,7]
  /// [566,6]
  /// [1626,5]
  /// [7132,4]
  /// [65536,3]
  /// [2642246,2]

  template <std::uint64_t base>
  consteval std::size_t max_exponent_for_base_ct() noexcept {
      if constexpr (base < 2) return std::numeric_limits<std::uint64_t>::max();
      else if constexpr (base == 2) return 63;
      else if constexpr (base == 3) return 40;
      else if constexpr (base == 4) return 31;
      else if constexpr (base == 5) return 27;
      else if constexpr (base == 6) return 24;
      else if constexpr (base == 7) return 22;
      else if constexpr (base == 8) return 21;
      else if constexpr (base == 9) return 20;
      else if constexpr (base == 10) return 19;
      else if constexpr (base == 11) return 18;
      else if constexpr (base >= 12 && base < 14) return 17;
      else if constexpr (base >= 14 && base < 16) return 16;
      else if constexpr (base >= 16 && base < 20) return 15;
      else if constexpr (base >= 20 && base < 24) return 14;
      else if constexpr (base >= 24 && base < 31) return 13;
      else if constexpr (base >= 31 && base < 41) return 12;
      else if constexpr (base >= 41 && base < 57) return 11;
      else if constexpr (base >= 57 && base < 85) return 10;
      else if constexpr (base >= 85 && base < 139) return 9;
      else if constexpr (base >= 139 && base < 256) return 8;
      else if constexpr (base >= 256ull && base < 566ull) return 7;
      else if constexpr (base >= 566ull && base < 1626ull) return 6;
      else if constexpr (base >= 1626ull && base < 7132ull) return 5;
      else if constexpr (base >= 7132ull && base < 65536ull) return 4;
      else if constexpr (base >= 65536ull && base < 2642246ull) return 3;
      else if constexpr (base >= 2642246ull && base < 4294967296ull) return 2;
      else return 1;
  }

  constexpr std::size_t max_exponent_for_base(std::uint64_t base) noexcept {
      if (base < 2) return std::numeric_limits<std::uint64_t>::max();
      else if (base == 2) return 63;
      else if (base == 3) return 40;
      else if (base == 4) return 31;
      else if (base == 5) return 27;
      else if (base == 6) return 24;
      else if (base == 7) return 22;
      else if (base == 8) return 21;
      else if (base == 9) return 20;
      else if (base == 10) return 19;
      else if (base == 11) return 18;
      else if (base >= 12 && base < 14) return 17;
      else if (base >= 14 && base < 16) return 16;
      else if (base >= 16 && base < 20) return 15;
      else if (base >= 20 && base < 24) return 14;
      else if (base >= 24 && base < 31) return 13;
      else if (base >= 31 && base < 41) return 12;
      else if (base >= 41 && base < 57) return 11;
      else if (base >= 57 && base < 85) return 10;
      else if (base >= 85 && base < 139) return 9;
      else if (base >= 139 && base < 256) return 8;
      else if (base >= 256 && base < 566) return 7;
      else if (base >= 566 && base < 1626) return 6;
      else if (base >= 1626 && base < 7132) return 5;
      else if (base >= 7132 && base < 65536) return 4;
      else if (base >= 65536 && base < 2642246) return 3;
      else if (base >= 2642246 && base < 4294967296) return 2;
      else return 1;
  }

  template <std::uint64_t base, std::size_t exponent>
    requires (exponent <= max_exponent_for_base_ct<base>())
  consteval
  std::uint64_t int_pow_ct() noexcept {
    if constexpr (exponent == 0) { return 1; }
    else if constexpr (exponent == 1) { return base; }
    else if constexpr (base == 0) { return 0; }
    else if constexpr (base == 1) { return 1; }
    else {
      std::uint64_t result = 1;
      std::uint64_t current_base = base;
      std::uint32_t exp = exponent;
      while (exp > 0) {
        if (exp & 1) { result *= current_base; }
        current_base *= current_base;
        exp >>= 1;
      }
      return result;
    }
  } // END FUNCTION INT_POW_CT

  constexpr inline std::uint64_t int_pow(std::uint64_t base,
                                         std::uint32_t exponent) noexcept {
    if (exponent <= max_exponent_for_base(base)) {
      // safe to compute
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
    } else {
      return 0; // overflow case
    }
    
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

  template <std::uint64_t base, std::int64_t n> consteval
  std::int64_t int_log_ct() noexcept {
    if constexpr (n <= 0) {
      return -1; // Not in domain of the function log_base(n)
                 // Domain(log_base) = ]0, +infinity[ = [1, +infinity[
    } else if constexpr (n < base) {
      return 0;
    } else {
      return 1 + int_log_ct<base, n / base>();
    }
  }  // END FUNCTION INT_LOG_CT

  std::int64_t int_log(std::uint64_t base, std::int64_t n) noexcept {
    if (n <= 0) {
      return -1; // Not in domain of the function log_base(n)
                 // Domain(log_base) = ]0, +infinity[ = [1, +infinity[
    } else if (n < base) {
      return 0;
    } else {
      return 1 + int_log(base, n / base);
    }
  }  // END FUNCTION INT_LOG_CT

  constexpr inline
  std::size_t count_digits_base10(std::uint64_t n) noexcept { 
    // (forward declarations for functions defined later are placed at
    // namespace scope; here we can call the generic implementation.)
    // implement via generic count_digits_base to keep a single implementation
    return count_digits_base(n, 10);
  }  // END FUNCTION COUNT_DIGITS_BASE10

  constexpr inline
  std::size_t count_digits_base(std::uint64_t n, std::uint64_t base) noexcept { 
    if (base < 2) return 0; // invalid base
    if (n == 0) return 1; // zero has one digit in any base

    // Fast path for base 2 using int_log2
    if (base == 2) {
      // 2^k has k+1 digits => k = floor(log2(n)) => digits = floor(log2(n)) + 1
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
    return std::bit_width(n) - 1;
  }  // END FUNCTION INT_LOG2CT

  constexpr
  std::uint64_t int_log2(std::uint64_t n) noexcept {
    if (n == 0) return 0; // Or handle as an error, though std::bit_width(0) is 0.
    return std::bit_width(n) - 1;
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
