#ifndef AUXILIARY_TYPES_HPP_INCLUDED
#define AUXILIARY_TYPES_HPP_INCLUDED

#include "core/internal/basic_types.hpp"

namespace NumRepr
{

  enum class sign_funct_e : char
  {
    vzero = 0,
    vminus = -1,
    vplus = +1
  };

  enum class dig_format_e : unsigned char
  {
    BINnat = 0,
    BCDnat = 1,
    BCDexc3 = 2,
    BCDaitk = 3,
    johnson_n = 4,
    biquinario = 5
  };

  enum class num_type_e : unsigned char
  {
    natural = 0,
    entero = 1,
    racional = 2,
    real = 3
  };

  enum class nat_num_format_e : bool
  {
    natural = false,
    exc_n = true
  };

  enum class int_num_format_e : unsigned char
  {
    int_CB = 0,
    int_CBm1 = 1,
    int_MS = 2,
    int_EXC_n = 3
  };

  enum class rat_num_format_e : unsigned char
  {
    pair_num_den = 0,
    fxd_pt = 1,
    flt_pt = 2
  };

  enum class binop_e : unsigned char
  {
    add = 0,
    sub = 1,
    mult = 2,
    div = 3,
    rem = 4,
    fediv = 5,
    other = 6
  };

  constexpr inline int to_int(sign_funct_e sign) noexcept { return static_cast<int>(sign); }
  constexpr inline bool is_positive(sign_funct_e sign) noexcept { return sign == sign_funct_e::vplus; }
  constexpr inline bool is_negative(sign_funct_e sign) noexcept { return sign == sign_funct_e::vminus; }
  constexpr inline bool is_zero(sign_funct_e sign) noexcept { return sign == sign_funct_e::vzero; }
  constexpr inline sign_funct_e opposite_sign(sign_funct_e sign) noexcept { return (sign == sign_funct_e::vplus) ? sign_funct_e::vminus : (sign == sign_funct_e::vminus) ? sign_funct_e::vplus : sign_funct_e::vzero; }

} // namespace NumRepr

#endif // AUXILIARY_TYPES_HPP_INCLUDED
