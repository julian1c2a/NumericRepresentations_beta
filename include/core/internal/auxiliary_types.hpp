#ifndef AUXILIARY_TYPES_HPP_INCLUDED
#define AUXILIARY_TYPES_HPP_INCLUDED


#include <core/internal/basic_types.hpp>

// ===============================
// AVISO: ARCHIVO DEPRECATED
// Este archivo se mantiene solo por compatibilidad histórica.
// Todos los tipos y utilidades han sido migrados a basic_types.hpp.
// Usar únicamente para referencia legacy.
// ===============================

namespace NumRepr
{

  // Todas las declaraciones aquí están DEPRECATED.

  enum class [[deprecated("Usar NumRepr::sign_funct_e de basic_types.hpp")]] sign_funct_e : char
  {
    vzero = 0,
    vminus = -1,
    vplus = +1
  };

  enum class [[deprecated("Usar NumRepr::dig_format_e de basic_types.hpp")]] dig_format_e : unsigned char
  {
    BINnat = 0,
    BCDnat = 1,
    BCDexc3 = 2,
    BCDaitk = 3,
    johnson_n = 4,
    biquinario = 5
  };

  enum class [[deprecated("Usar NumRepr::num_type_e de basic_types.hpp")]] num_type_e : unsigned char
  {
    natural = 0,
    entero = 1,
    racional = 2,
    real = 3
  };

  enum class [[deprecated("Usar NumRepr::nat_num_format_e de basic_types.hpp")]] nat_num_format_e : bool
  {
    natural = false,
    exc_n = true
  };

  enum class [[deprecated("Usar NumRepr::int_num_format_e de basic_types.hpp")]] int_num_format_e : unsigned char
  {
    int_CB = 0,
    int_CBm1 = 1,
    int_MS = 2,
    int_EXC_n = 3
  };

  enum class [[deprecated("Usar NumRepr::rat_num_format_e de basic_types.hpp")]] rat_num_format_e : unsigned char
  {
    pair_num_den = 0,
    fxd_pt = 1,
    flt_pt = 2
  };

  enum class [[deprecated("Usar NumRepr::binop_e de basic_types.hpp")]] binop_e : unsigned char
  {
    add = 0,
    sub = 1,
    mult = 2,
    div = 3,
    rem = 4,
    fediv = 5,
    other = 6
  };

  // Funciones utilitarias DEPRECATED
  [[deprecated("Usar NumRepr::to_int de basic_types.hpp")]]
  constexpr inline int to_int(sign_funct_e sign) noexcept
  {
    return static_cast<int>(sign);
  }

  [[deprecated("Usar NumRepr::is_positive de basic_types.hpp")]]
  constexpr inline bool is_positive(sign_funct_e sign) noexcept
  {
    return sign == sign_funct_e::vplus;
  }

  [[deprecated("Usar NumRepr::is_negative de basic_types.hpp")]]
  constexpr inline bool is_negative(sign_funct_e sign) noexcept
  {
    return sign == sign_funct_e::vminus;
  }

  [[deprecated("Usar NumRepr::is_zero de basic_types.hpp")]]
  constexpr inline bool is_zero(sign_funct_e sign) noexcept
  {
    return sign == sign_funct_e::vzero;
  }

  [[deprecated("Usar NumRepr::opposite_sign de basic_types.hpp")]]
  constexpr inline sign_funct_e opposite_sign(sign_funct_e sign) noexcept
  {
    return (sign == sign_funct_e::vplus) ? sign_funct_e::vminus : (sign == sign_funct_e::vminus) ? sign_funct_e::vplus : sign_funct_e::vzero;
  }

} // namespace NumRepr

#endif // AUXILIARY_TYPES_HPP_INCLUDED
