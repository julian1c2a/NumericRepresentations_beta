#ifndef AUXILIARY_FUNCTIONS_HPP_INCLUDED
#define AUXILIARY_FUNCTIONS_HPP_INCLUDED

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <numeric>

#include "auxiliary_types.hpp"

namespace NumRepr
{

  namespace detail
  {

    /// @brief Compute ceiling of square root using binary search
    /// @param n Number to compute ceiling square root of
    /// @param low Lower bound for search (precondition: low*low <= n)
    /// @param high Upper bound for search (precondition: high*high > n)
    /// @return The ceiling of the square root of n
    /// @pre low*low <= n && high*high > n
    constexpr inline std::size_t ceilsqrt(std::size_t n, std::size_t low, std::size_t high) noexcept
    {
      const auto mid{std::midpoint(low, high)};
      const auto sqmid{mid * mid};
      return ((low + 1 >= high) ? high
              : (sqmid == n)    ? mid
              : (sqmid < n)     ? ceilsqrt(n, mid, high)
                                : ceilsqrt(n, low, mid));
    }

    /// @brief Compute ceiling of square root
    /// @param n Number to compute ceiling square root of
    /// @return The ceiling of the square root of n
    constexpr inline std::size_t ceilsqrt(std::size_t n) noexcept
    {
      const auto num_max_dig{std::numeric_limits<std::size_t>::digits};
      return ((n < 3) ? n : ceilsqrt(n, 1, std::size_t(1) << (num_max_dig / 2)));
    }

    /// @brief Check if n is divisible by an odd integer in range [2*low+1, 2*high+1)
    /// @param n Number to check for factors
    /// @param low Lower bound of the range (will test 2*low+1)
    /// @param high Upper bound of the range (exclusive)
    /// @return true if n has an odd factor in the specified range
    constexpr inline bool find_factor(std::size_t n, std::size_t low, std::size_t high) noexcept
    {
      const auto mid{std::midpoint(low, high)};
      return ((low + 1 >= high) ? (n % (2 * low + 1)) == 0 : (find_factor(n, low, mid) || find_factor(n, mid, high)));
    }

  } // namespace detail

  namespace auxiliary_functions
  {

    /// @brief Check if a number is a power of 2
    /// @param num Number to check
    /// @return true if num is a power of 2, false otherwise
    /// @note Returns false for num = 0
    constexpr inline bool is_power_of_2(std::uint64_t num) noexcept
    {
      // Efficient bit manipulation: n & (n-1) == 0 for powers of 2
      // Also handles 0 case correctly (0 is not a power of 2)
      return num > 0 && (num & (num - 1)) == 0;
    }

    /// @brief Check if a number is prime
    /// @param n Number to check for primality
    /// @return true if n is prime, false otherwise
    constexpr inline bool is_prime(std::size_t n) noexcept
    {
      if (n < 2)
        return false;
      else if (n == 2 || n == 3)
        return true;
      else if (n % 2 == 0 || n % 3 == 0)
        return false;
      else
        return (!detail::find_factor(n, 1, (detail::ceilsqrt(n) + 1) / 2));
    }

    /// @brief Compute the greatest common divisor using Euclidean algorithm
    /// @param a First number
    /// @param b Second number
    /// @return The greatest common divisor of a and b
    constexpr inline std::uint64_t gcd(std::uint64_t a, std::uint64_t b) noexcept
    {
      while (b != 0)
      {
        const auto temp = b;
        b = a % b;
        a = temp;
      }
      return a;
    }

    /// @brief Compute the least common multiple
    /// @param a First number
    /// @param b Second number
    /// @return The least common multiple of a and b
    constexpr inline std::uint64_t lcm(std::uint64_t a, std::uint64_t b) noexcept
    {
      return (a == 0 || b == 0) ? 0 : (a / gcd(a, b)) * b;
    }

    /// @brief Compute integer power efficiently using exponentiation by squaring
    /// @param base The base number
    /// @param exponent The exponent (non-negative)
    /// @return base raised to the power of exponent
    constexpr inline std::uint64_t integer_power(std::uint64_t base, std::uint32_t exponent) noexcept
    {
      if (exponent == 0)
        return 1;
      if (exponent == 1)
        return base;
      if (base == 0)
        return 0;
      if (base == 1)
        return 1;

      std::uint64_t result = 1;
      std::uint64_t current_base = base;

      while (exponent > 0)
      {
        if (exponent & 1)
        {
          result *= current_base;
        }
        current_base *= current_base;
        exponent >>= 1;
      }

      return result;
    }

    /// @brief Check if a number is a perfect square
    /// @param n Number to check
    /// @return true if n is a perfect square, false otherwise
    constexpr inline bool is_perfect_square(std::uint64_t n) noexcept
    {
      if (n == 0)
        return true;
      const auto root = detail::ceilsqrt(n);
      return root * root == n;
    }

    /// @brief Count the number of digits in base 10
    /// @param n Number to count digits for
    /// @return Number of digits in base 10 representation
    constexpr inline std::size_t count_digits_base10(std::uint64_t n) noexcept
    {
      if (n == 0)
        return 1;

      std::size_t count = 0;
      while (n > 0)
      {
        n /= 10;
        ++count;
      }
      return count;
    }

    /// @brief Count the number of digits in any base
    /// @param n Number to count digits for
    /// @param base The base to use (must be >= 2)
    /// @return Number of digits in the given base
    constexpr inline std::size_t count_digits_base(std::uint64_t n, std::uint64_t base) noexcept
    {
      if (base < 2)
        return 0; // Invalid base
      if (n == 0)
        return 1;

      std::size_t count = 0;
      while (n > 0)
      {
        n /= base;
        ++count;
      }
      return count;
    }

  } // namespace auxiliary_functions
} // namespace NumRepr

#endif // AUXILIARY_FUNCTIONS_HPP_INCLUDED
