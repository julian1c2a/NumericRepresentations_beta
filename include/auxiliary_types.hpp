#ifndef AUXILIARY_TYPES_HPP_INCLUDED
#define AUXILIARY_TYPES_HPP_INCLUDED

#include "basic_types.hpp"

namespace NumRepr
{

  /****************************/
  //
  //	SIGN AND FORMAT ENUMERATIONS
  //
  /****************************/

  /// @brief Sign function enumeration for representing mathematical signs
  /// @details Used for determining the sign of numbers in various representations
  enum class sign_funct_e : char
  {
    vzero = 0,   ///< Zero value (neutral)
    vminus = -1, ///< Negative value
    vplus = +1   ///< Positive value
  };

  /// @brief Digit format enumeration for different number representation formats
  /// @details Supports various binary and decimal encoding formats
  enum class dig_format_e : unsigned char
  {
    BINnat = 0,    ///< Binary natural format
    BCDnat = 1,    ///< Binary Coded Decimal natural format
    BCDexc3 = 2,   ///< BCD Excess-3 format
    BCDaitk = 3,   ///< BCD Aiken format (2421 code)
    johnson_n = 4, ///< Johnson counter format
    biquinario = 5 ///< Biquinary format (5-2 representation)
  };

  /// @brief Number type enumeration for mathematical number classifications
  /// @details Represents the fundamental types of numbers in mathematics
  enum class num_type_e : unsigned char
  {
    natural = 0,  ///< Natural numbers (ℕ): {0, 1, 2, 3, ...}
    entero = 1,   ///< Integer numbers (ℤ): {..., -2, -1, 0, 1, 2, ...}
    racional = 2, ///< Rational numbers (ℚ): fractions p/q where q≠0
    real = 3      ///< Real numbers (ℝ): all rational and irrational numbers
  };

  /// @brief Natural number format enumeration
  /// @details Specifies representation format for natural numbers
  enum class nat_num_format_e : bool
  {
    natural = false, ///< Standard natural number representation
    exc_n = true     ///< Excess-n representation format
  };

  /// @brief Integer number format enumeration
  /// @details Different representations for signed integers
  enum class int_num_format_e : unsigned char
  {
    int_CB = 0,   ///< Complement to Base (radix complement)
    int_CBm1 = 1, ///< Complement to Base-1 (diminished radix complement)
    int_MS = 2,   ///< Magnitude and Sign representation
    int_EXC_n = 3 ///< Excess-n representation (biased representation)
  };

  /// @brief Rational number format enumeration
  /// @details Different ways to represent rational numbers
  enum class rat_num_format_e : unsigned char
  {
    pair_num_den = 0, ///< Numerator/Denominator pair representation
    fxd_pt = 1,       ///< Fixed-point representation
    flt_pt = 2        ///< Floating-point representation
  };

  /// @brief Binary operation enumeration
  /// @details Fundamental arithmetic and logical operations
  enum class binop_e : unsigned char
  {
    add = 0,   ///< Addition operation
    sub = 1,   ///< Subtraction operation
    mult = 2,  ///< Multiplication operation
    div = 3,   ///< Division operation
    rem = 4,   ///< Remainder operation (modulo)
    fediv = 5, ///< Floor division operation
    other = 6  ///< Other/custom operations
  };

  /****************************/
  //
  //  UTILITY FUNCTIONS FOR ENUMS
  //
  /****************************/

  /// @brief Convert sign enumeration to integer value
  /// @param sign The sign enumeration value
  /// @return Integer representation (-1, 0, or 1)
  constexpr inline int to_int(sign_funct_e sign) noexcept
  {
    return static_cast<int>(sign);
  }

  /// @brief Check if a sign is positive
  /// @param sign The sign enumeration value
  /// @return true if positive, false otherwise
  constexpr inline bool is_positive(sign_funct_e sign) noexcept
  {
    return sign == sign_funct_e::vplus;
  }

  /// @brief Check if a sign is negative
  /// @param sign The sign enumeration value
  /// @return true if negative, false otherwise
  constexpr inline bool is_negative(sign_funct_e sign) noexcept
  {
    return sign == sign_funct_e::vminus;
  }

  /// @brief Check if a sign is zero
  /// @param sign The sign enumeration value
  /// @return true if zero, false otherwise
  constexpr inline bool is_zero(sign_funct_e sign) noexcept
  {
    return sign == sign_funct_e::vzero;
  }

  /// @brief Get the opposite sign
  /// @param sign The original sign
  /// @return The opposite sign (positive becomes negative, etc.)
  constexpr inline sign_funct_e opposite_sign(sign_funct_e sign) noexcept
  {
    return (sign == sign_funct_e::vplus) ? sign_funct_e::vminus : (sign == sign_funct_e::vminus) ? sign_funct_e::vplus
                                                                                                 : sign_funct_e::vzero;
  }

} // namespace NumRepr

#endif // AUXILIARY_TYPES_HPP_INCLUDED
