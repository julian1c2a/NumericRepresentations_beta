#ifndef TESTUNIT_HPP_INCLUDED
#define TESTUNIT_HPP_INCLUDED

#include "int_reg_digs_t.hpp"
#include "utilities.hpp"

namespace NumRepr { /// BEGIN OF NAMESPACE NUMREPR
namespace testing { /// BEGIN OF NAMESPACE TESTING

void show_test_convert_to_int_driver();

template <std::size_t B, std::size_t L>
constexpr inline uint64_t
conversion_to_int(const reg_digs_t<B, L> &arg) noexcept {
  namespace us = utilities::special;
  return us::conversion_to_int<B, L, reg_digs_t<B, L>>(arg);
}

template <std::size_t B, std::size_t L>
constexpr inline std::uint64_t
convert_to_int(const reg_digs_t<B, L> &arg) noexcept {
  std::uint64_t cB = B;
  std::uint64_t accum{arg[L - 1]()};
  for (std::int64_t ix = L - 1; ix > 0; --ix) {
    accum *= cB;
    accum += std::uint64_t(arg[ix - 1]());
  }
  return accum;
}

template <std::size_t B, std::size_t L>
constexpr inline uint64_t Base_pow_to_Size() noexcept {
  namespace us = utilities::special;
  return us::Base_pow_to_Size<B, L>();
}

///                              todo, num_pruebas , num_pruebas
///                              bien, #correctos  , #errores
using test_result_t = std::tuple<bool, std::size_t, std::size_t>;

namespace nat_reg { /// BEGIN OF NAMESPACE NAT_REG
/// PURAS PRUEBAS
/// MUESTRA DE RESULTADOS
} /// END OF NAMESPACE NAT_REG

namespace reg_digs { /// BEGIN OF NAMESPACE REG_DIGS

template <std::uint64_t Base, std::size_t Long>
test_result_t test_div_fediv_entre_dos_objetos_tipo_reg_digs() {
  namespace us = utilities::special;
  using reg_digs_t = reg_digs_t<Base, Long>;

  size_t correctos = 0;
  size_t errores = 0;

  bool first_bad_result = true;
  bool todo_ha_ido_bien = true;

  reg_digs_t dndo{};
  reg_digs_t dsor{};
  dndo = 0;
  for (size_t dndo_idx{0}; dndo_idx < us::Pow_B2L_v<Base, Long>; ++dndo_idx) {
    dsor = 1;
    for (size_t dsor_idx{1}; dsor_idx < us::Pow_B2L_v<Base, Long>; ++dsor_idx) {
      const auto dndo_int{convert_to_int<Base, Long>(dndo)};
      const auto dsor_int{convert_to_int<Base, Long>(dsor)};

      const auto result(fediv(dndo, dsor));
      const auto cociente = std::get<0>(result);
      const auto resto = std::get<1>(result);

      const auto cociente_calc = dndo_int / dsor_int;
      const auto resto_calc = dndo_int % dsor_int;

      const auto cociente_sync = dndo_idx / dsor_idx;
      const auto resto_sync = dndo_idx % dsor_idx;

      const auto cociente_int{convert_to_int<Base, Long>(cociente)};
      const auto resto_int{convert_to_int<Base, Long>(resto)};

      const bool cociente_bien_1 = (cociente_int == cociente_sync);
      const bool cociente_bien_2 = (cociente_int == cociente_calc);
      const bool resto_bien_1 = (resto_int == resto_sync);
      const bool resto_bien_2 = (resto_int == resto_calc);
      const bool bien =
          cociente_bien_1 && cociente_bien_2 && resto_bien_1 && resto_bien_2;

      if (bien) {
        ++correctos;
      } else {
        ++errores;
        if (first_bad_result) {
          first_bad_result = false;
        }
      }

      todo_ha_ido_bien = todo_ha_ido_bien && bien;
      m_incr(dsor);
    }

    m_incr(dndo);
  }
  return test_result_t{todo_ha_ido_bien, correctos, errores};
}

template <std::uint64_t Base, std::size_t Long>
test_result_t test_comparacion_igual_que_entre_dos_objetos_tipo_reg_digs() {
  using reg_digs_t = reg_digs_t<Base, Long>;
  namespace us = utilities::special;
  bool todo_correcto = true;

  constexpr uint64_t B2L{us::Base_pow_to_Size<Base, Long>()};

  std::size_t correctos{0};
  std::size_t errores{0};

  reg_digs_t rd_x{0};
  for (std::uint64_t ix{0}; ix < B2L; ++ix) {
    reg_digs_t rd_y{0};
    for (std::uint64_t iy{0}; iy < B2L; ++iy) {
      const bool comp = rd_x == rd_y;
      const bool comp_ref = (conversion_to_int<Base, Long>(rd_x) ==
                             conversion_to_int<Base, Long>(rd_y));
      const bool bien{comp == comp_ref};
      if (!bien) {
        ++errores;
      } else {
        ++correctos;
      }
      todo_correcto = todo_correcto && bien;
      m_incr(rd_y);
    }
    m_incr(rd_x);
  }
  return test_result_t{todo_correcto, correctos, errores};
}

template <std::uint64_t Base, std::size_t Long>
test_result_t test_comparacion_distinto_que_entre_dos_objetos_tipo_reg_digs() {
  using reg_digs_t = reg_digs_t<Base, Long>;
  namespace us = utilities::special;
  bool todo_correcto = true;

  constexpr uint64_t B2L{us::Base_pow_to_Size<Base, Long>()};

  std::size_t correctos{0};
  std::size_t errores{0};

  reg_digs_t rd_x{0};
  for (std::uint64_t ix{0}; ix < B2L; ++ix) {
    reg_digs_t rd_y{0};
    for (std::uint64_t iy{0}; iy < B2L; ++iy) {
      const bool comp = rd_x != rd_y;
      const bool comp_ref = (conversion_to_int<Base, Long>(rd_x) !=
                             conversion_to_int<Base, Long>(rd_y));
      const bool bien{comp == comp_ref};
      if (!bien) {
        ++errores;
      } else {
        ++correctos;
      }
      todo_correcto = todo_correcto && bien;
      m_incr(rd_y);
    }
    m_incr(rd_x);
  }
  return test_result_t{todo_correcto, correctos, errores};
}

template <std::uint64_t Base, std::size_t Long>
test_result_t test_comparacion_menor_que_entre_dos_objetos_tipo_reg_digs() {
  using reg_digs_t = reg_digs_t<Base, Long>;
  namespace us = utilities::special;

  bool todo_correcto = true;

  constexpr uint64_t B2L{us::Base_pow_to_Size<Base, Long>()};

  std::size_t correctos{0};
  std::size_t errores{0};

  reg_digs_t rd_x{0};
  for (std::uint64_t ix{0}; ix < B2L; ++ix) {
    reg_digs_t rd_y{0};
    for (std::uint64_t iy{0}; iy < B2L; ++iy) {
      const bool comp = rd_x < rd_y;
      const bool comp_ref = (conversion_to_int<Base, Long>(rd_x) <
                             conversion_to_int<Base, Long>(rd_y));
      const bool bien{comp == comp_ref};
      if (!bien) {
        ++errores;
      } else {
        ++correctos;
      }
      todo_correcto = todo_correcto && bien;
      m_incr(rd_y);
    }
    m_incr(rd_x);
  }
  return test_result_t{todo_correcto, correctos, errores};
}

template <std::uint64_t Base, std::size_t Long>
test_result_t
test_comparacion_menor_o_igual_que_entre_dos_objetos_tipo_reg_digs() {
  using reg_digs_t = reg_digs_t<Base, Long>;
  namespace us = utilities::special;

  bool todo_correcto = true;

  constexpr uint64_t B2L{us::Base_pow_to_Size<Base, Long>()};

  std::size_t correctos{0};
  std::size_t errores{0};

  reg_digs_t rd_x{0};
  for (std::uint64_t ix{0}; ix < B2L; ++ix) {
    reg_digs_t rd_y{0};
    for (std::uint64_t iy{0}; iy < B2L; ++iy) {
      const bool comp = rd_x <= rd_y;
      const bool comp_ref = (conversion_to_int<Base, Long>(rd_x) <=
                             conversion_to_int<Base, Long>(rd_y));
      const bool bien{comp == comp_ref};
      if (!bien) {
        ++errores;
      } else {
        ++correctos;
      }
      todo_correcto = todo_correcto && bien;
      m_incr(rd_y);
    }
    m_incr(rd_x);
  }
  return test_result_t{todo_correcto, correctos, errores};
}

template <std::uint64_t Base, std::size_t Long>
test_result_t test_comparacion_mayor_que_entre_dos_objetos_tipo_reg_digs() {
  using reg_digs_t = reg_digs_t<Base, Long>;
  namespace us = utilities::special;

  bool todo_correcto = true;

  constexpr uint64_t B2L{us::Base_pow_to_Size<Base, Long>()};

  std::size_t correctos{0};
  std::size_t errores{0};

  reg_digs_t rd_x{0};
  for (std::uint64_t ix{0}; ix < B2L; ++ix) {
    reg_digs_t rd_y{0};
    for (std::uint64_t iy{0}; iy < B2L; ++iy) {
      const bool comp = rd_x > rd_y;
      const bool comp_ref = (conversion_to_int<Base, Long>(rd_x) >
                             conversion_to_int<Base, Long>(rd_y));
      const bool bien{comp == comp_ref};
      if (!bien) {
        ++errores;
      } else {
        ++correctos;
      }
      todo_correcto = todo_correcto && bien;
      m_incr(rd_y);
    }
    m_incr(rd_x);
  }
  return test_result_t{todo_correcto, correctos, errores};
}

template <std::uint64_t Base, std::size_t Long>
test_result_t
test_comparacion_mayor_o_igual_que_entre_dos_objetos_tipo_reg_digs() {
  using reg_digs_t = reg_digs_t<Base, Long>;
  namespace us = utilities::special;

  bool todo_correcto = true;

  constexpr uint64_t B2L{us::Base_pow_to_Size<Base, Long>()};

  std::size_t correctos{0};
  std::size_t errores{0};

  reg_digs_t rd_x{0};
  for (std::uint64_t ix{0}; ix < B2L; ++ix) {
    reg_digs_t rd_y{0};
    for (std::uint64_t iy{0}; iy < B2L; ++iy) {
      const bool comp = rd_x >= rd_y;
      const bool comp_ref = (conversion_to_int<Base, Long>(rd_x) >=
                             conversion_to_int<Base, Long>(rd_y));
      const bool bien{comp == comp_ref};
      if (!bien) {
        ++errores;
      } else {
        ++correctos;
      }
      todo_correcto = todo_correcto && bien;
      m_incr(rd_y);
    }
    m_incr(rd_x);
  }
  return test_result_t{todo_correcto, correctos, errores};
}

template <std::uint64_t Base> test_result_t test_dig_suma_dig_con_asignacion() {
  using d_t = dig_t<Base>;
  namespace us = utilities::special;

  bool todo_correcto = true;

  constexpr uint64_t B2L{us::Base_pow_to_Size<Base, 1>()};

  std::size_t correctos{0};
  std::size_t errores{0};

  d_t rd_x{0};
  for (std::uint64_t ix{0}; ix < B2L; ++ix) {
    d_t rd_y{0};
    for (std::uint64_t iy{0}; iy < B2L; ++iy) {
      d_t rd_z{rd_x};
      m_sum_digs_carryin_0(rd_z, rd_y);
      const std::uint64_t iz = rd_z();
      const std::uint64_t iw = (ix + iy) % B2L;
      const bool bien{iz == iw};
      if (!bien) {
        ++errores;
      } else {
        ++correctos;
      }
      todo_correcto = todo_correcto && bien;
      ++rd_y;
    }
    ++rd_x;
  }
  return test_result_t{todo_correcto, correctos, errores};
}

template <std::uint64_t Base> test_result_t test_dig_mult_dig_con_asignacion() {
  using d_t = dig_t<Base>;
  namespace us = utilities::special;

  bool todo_correcto = true;

  [[maybe_unused]] constexpr uint64_t B2L{us::Base_pow_to_Size<Base, 1>()};

  std::size_t correctos{0};
  std::size_t errores{0};

  d_t rd_x{0};
  for (std::uint64_t ix{0}; ix < Base; ++ix) {
    d_t rd_y{0};
    for (std::uint64_t iy{0}; iy < Base; ++iy) {
      d_t rd_z{rd_x};
      d_t rd_p{m_mult(rd_z, rd_y)};
      const std::uint64_t iz = rd_z();
      const std::uint64_t iw = (ix * iy) % Base;
      const std::uint64_t iq = rd_p();
      const std::uint64_t ip = (ix * iy) / Base;
      const bool bien{(iz == iw) and (ip == iq)};
      if (!bien) {
        ++errores;
      } else {
        ++correctos;
      }
      todo_correcto = todo_correcto && bien;
      ++rd_y;
    }
    ++rd_x;
  }
  return test_result_t{todo_correcto, correctos, errores};
}

template <std::uint64_t Base, std::size_t Long>
std::tuple<bool, uint32_t, uint32_t> test_dig_mult_reg_n_dig_con_asignacion() {
  using rd_t = reg_digs_t<Base, Long>;
  using d_t = dig_t<Base>;
  namespace us = utilities::special;

  constexpr uint64_t B2L{us::Base_pow_to_Size<Base, Long>()};
  bool todo_correcto = true;
  std::size_t correctos{0};
  std::size_t errores{0};

  rd_t rd_x{0};
  for (std::uint64_t ix{0}; ix < B2L; ++ix) {
    d_t rd_y{0};
    for (std::uint64_t iy{0}; iy < Base; ++iy) {
      rd_t rd_z{rd_x};
      d_t rd_p{m_mult(rd_z, rd_y)};
      const std::uint64_t iz = conversion_to_int<Base, Long>(rd_z);
      const std::uint64_t iw = (ix * iy) % B2L;
      const std::uint64_t iq = rd_p();
      const std::uint64_t ip = (ix * iy) / B2L;
      const bool bien{(iz == iw) && (ip == iq)};
      if (!bien) {
        ++errores;
      } else {
        ++correctos;
      }
      todo_correcto = todo_correcto && bien;
      ++rd_y;
    }
    m_incr(rd_x);
  }
  return std::make_tuple(todo_correcto, correctos, errores);
}

template <std::uint64_t Base, std::size_t Long>
test_result_t test_reg_mult_reg_con_asignacion() {
  using rd_t = reg_digs_t<Base, Long>;
  namespace us = utilities::special;

  bool todo_correcto = true;

  constexpr uint64_t B2L{us::Base_pow_to_Size<Base, Long>()};
  std::fstream fichero("test_mult_reg_reg_w_assign.txt",
                       fichero.out | fichero.app);

  std::size_t correctos{0};
  std::size_t errores{0};

  rd_t rd_x{0};
  for (std::uint64_t ix{0}; ix < B2L; ++ix) {
    rd_t rd_y{0};
    for (std::uint64_t iy{0}; iy < B2L; ++iy) {
      rd_t rd_z{rd_x};
      rd_t rd_p{m_mult(rd_z, rd_y)};
      const std::uint64_t iz = conversion_to_int<Base, Long>(rd_z);
      const std::uint64_t iw =
          (ix * iy) % B2L; // parte baja de la salida que sale por el primer
                           // parametro de entrada
      const std::uint64_t iq = conversion_to_int<Base, Long>(rd_p);
      const std::uint64_t ip =
          (ix * iy) /
          B2L; // parte alta de la salida que sale por el parametro de salida
      const bool bien{(iz == iw) && (ip == iq)};

      if (!bien) {
        ++errores;
      } else {
        ++correctos;
      }
      todo_correcto = todo_correcto && bien;
      m_incr(rd_y);
    }
    m_incr(rd_x);
  }
  fichero.close();
  return std::make_tuple(todo_correcto, correctos, errores);
}

template <std::uint64_t Base>
test_result_t test_dig_resta_dig_con_asignacion() {
  using d_t = dig_t<Base>;
  namespace us = utilities::special;

  bool todo_correcto = true;

  constexpr uint64_t B2L{us::Base_pow_to_Size<Base, 1>()};

  std::size_t correctos{0};
  std::size_t errores{0};

  d_t rd_x{Base - 1};
  for (std::int64_t ix{B2L - 1}; ix > -1; --ix) {
    d_t rd_y{ix};
    for (std::int64_t iy{ix}; iy > -1; --iy) {
      d_t rd_z{rd_x};
      m_subtract_digs_borrowin_0(rd_z, rd_y);
      const std::uint64_t iz = rd_z();
      const std::uint64_t iw = ix - iy;
      const bool bien{iz == iw};

      if (!bien) {
        ++errores;
      } else {
        ++correctos;
      }
      todo_correcto = todo_correcto && bien;
      --rd_y;
    }
    --rd_x;
  }
  return std::make_tuple(todo_correcto, correctos, errores);
}

template <std::uint64_t Base>
std::tuple<bool, std::size_t, std::size_t>
test_dig_resta_con_borrow_dig_con_asignacion() {
  using d_t = dig_t<Base>;
  namespace us = utilities::special;

  bool todo_correcto = true;

  [[maybe_unused]] constexpr uint64_t B2L{us::Base_pow_to_Size<Base, 1>()};

  std::size_t correctos{0};
  std::size_t errores{0};

  d_t rd_x{Base - 1};
  for (std::int64_t ix{Base - 1}; ix > -1; --ix) {
    d_t rd_y{Base - 1};
    for (std::int64_t iy{Base - 1}; iy > -1; --iy) {
      d_t rd_z{rd_x};
      m_subtract_digs_borrowin_1(rd_z, rd_y);
      const std::int64_t iz = rd_z();
      const std::int64_t iw =
          ((ix - iy - 1) < 0) ? (ix - iy - 1 + Base) : (ix - iy - 1);
      const bool bien{iz == iw};
      if (!bien) {
        ++errores;
      } else {
        ++correctos;
      }
      todo_correcto = todo_correcto && bien;
      --rd_y;
    }
    --rd_x;
  }
  return std::make_tuple(todo_correcto, correctos, errores);
}

template <std::uint64_t Base> void lista_dig_resta_dig_con_asignacion() {
  using d_t = dig_t<Base>;
  namespace us = utilities::special;

  constexpr uint64_t B2L{us::Base_pow_to_Size<Base, 1>()};

  std::string filename{"resta_de_digitos_lista.txt"};
  std::fstream fichero{filename, fichero.out | fichero.app};

  bool todo_correcto = true;
  d_t rd_x{Base - 1};
  for (std::int64_t ix{B2L - 1}; ix > -1; --ix) {
    d_t rd_y{Base - 1};
    for (std::int64_t iy{B2L - 1}; iy > -1; --iy) {
      d_t rd_z{rd_x};
      d_t borrow = m_subtract_digs_borrowin_0(rd_z, rd_y);
      const std::int64_t iz = rd_z();
      const std::int64_t iw = ((ix - iy) < 0) ? (ix - iy + Base) : (ix - iy);
      const bool bien{iz == iw};

      todo_correcto = todo_correcto && bien;
      fichero << std::boolalpha;
      fichero << "Integers : \t" << ix << "\t - " << iy << "\t = \t" << iw
              << std::endl;
      fichero << "Digits<\t" << Base << "\t> : " << rd_x << "\t - " << rd_y
              << "\t = \t" << rd_z << std::endl;
      fichero << "       \t" << Base << "\t    "
              << "   "
              << "\t   "
              << "\t   "
              << "\t            " << borrow << std::endl;
      fichero << "Correcto : \t" << todo_correcto << std::endl;
      fichero << "--------------------------------------------------"
              << std::endl;
      --rd_y;
    }
    --rd_x;
  }
  fichero.close();
}

template <std::uint64_t Base>
test_result_t test_dig_suma_dig_con_carry_con_asignacion() {
  using d_t = dig_t<Base>;
  namespace us = utilities::special;

  bool todo_correcto = true;

  constexpr uint64_t B2L{us::Base_pow_to_Size<Base, 1>()};

  std::size_t correctos{0};
  std::size_t errores{0};

  d_t rd_x{0};
  for (std::uint64_t ix{0}; ix < B2L; ++ix) {
    d_t rd_y{0};
    for (std::uint64_t iy{0}; iy < B2L; ++iy) {
      d_t rd_z{rd_x};
      m_sum_digs_carryin_1(rd_z, rd_y);
      const std::uint64_t iz = rd_z();
      const std::uint64_t iw = (ix + iy + 1) % B2L;
      const bool bien{iz == iw};

      if (!bien) {
        ++errores;
      } else {
        ++correctos;
      }
      todo_correcto = todo_correcto && bien;
      ++rd_y;
    }
    ++rd_x;
  }
  return test_result_t{todo_correcto, correctos, errores};
}

template <std::uint64_t Base, std::uint64_t Longitud>
test_result_t test_incremento_con_asignacion() {
  using rd_t = reg_digs_t<Base, Longitud>;
  using d_t = dig_t<Base>;
  namespace us = utilities::special;

  bool todo_correcto = true;

  constexpr uint64_t B2L{us::Base_pow_to_Size<Base, Longitud>()};

  std::size_t correctos{0};
  std::size_t errores{0};

  rd_t rd_x{};
  rd_x.fill(d_t{0});
  for (std::uint64_t ix{0}; ix < B2L; ++ix) {
    rd_t rd_z{rd_x};
    m_incr(rd_z);
    const std::uint64_t iz = conversion_to_int<Base, Longitud>(rd_z);
    const std::uint64_t iw = (ix + 1) % B2L;
    const bool bien{iz == iw};

    if (!bien) {
      ++errores;
    } else {
      ++correctos;
    }
    todo_correcto = todo_correcto && bien;
    m_incr(rd_x);
  }
  return test_result_t{todo_correcto, correctos, errores};
}

template <std::uint64_t Base, std::uint64_t Longitud>
test_result_t test_decremento_con_asignacion() {
  namespace us = utilities::special;

  using rd_t = reg_digs_t<Base, Longitud>;
  using d_t = dig_t<Base>;

  bool todo_correcto = true;

  constexpr uint64_t B2L{us::Base_pow_to_Size<Base, Longitud>()};

  std::size_t correctos{0};
  std::size_t errores{0};

  rd_t rd_x{};
  rd_x.fill(d_t{Base - 1});
  for (std::int64_t ix{B2L - 1}; ix > 0; --ix) {
    rd_t rd_z{rd_x};
    m_decr(rd_z);
    const std::int64_t iz = conversion_to_int<Base, Longitud>(rd_z);
    const std::int64_t iw = ((ix - 1) < 0) ? (ix - 1 + Base) : (ix - 1);
    const bool bien{iz == iw};
    if (!bien) {
      ++errores;
    } else {
      ++correctos;
    }
    todo_correcto = todo_correcto && bien;
    m_decr(rd_x);
  }
  return test_result_t{todo_correcto, correctos, errores};
}

template <std::uint64_t Base, std::uint64_t Longitud>
test_result_t test_suma_con_asignacion() {
  using rd_t = reg_digs_t<Base, Longitud>;
  using d_t = dig_t<Base>;
  namespace us = utilities::special;

  bool todo_correcto = true;

  constexpr uint64_t B2L{us::Base_pow_to_Size<Base, Longitud>()};

  std::size_t correctos{0};
  std::size_t errores{0};

  rd_t rd_x{};
  rd_x.fill(d_t{0});
  rd_t rd_y{};
  rd_y.fill(d_t{0});
  for (std::uint64_t ix{0}; ix < B2L; ++ix) {
    for (std::uint64_t iy{0}; iy < B2L; ++iy) {
      rd_t rd_z{rd_x};
      m_sum(rd_z, rd_y);
      const std::uint64_t iz = conversion_to_int<Base, Longitud>(rd_z);
      const std::uint64_t iw = (ix + iy) % B2L;
      const bool bien{iz == iw};

      if (!bien) {
        ++errores;
      } else {
        ++correctos;
      }
      todo_correcto = todo_correcto && bien;
      m_incr(rd_y);
    }
    m_incr(rd_x);
  }
  return test_result_t{todo_correcto, correctos, errores};
}

template <std::uint64_t Base, std::uint64_t Longitud>
test_result_t test_resta_con_asignacion() {
  using rd_t = reg_digs_t<Base, Longitud>;
  using d_t = dig_t<Base>;
  namespace us = utilities::special;

  bool todo_correcto = true;
  constexpr uint64_t B2L{us::Base_pow_to_Size<Base, Longitud>()};

  std::size_t correctos{0};
  std::size_t errores{0};

  rd_t rd_x;
  rd_x.fill(d_t::dig_Bm1());
  for (std::int64_t ix{B2L - 1}; ix > -1; --ix) {
    rd_t rd_y;
    rd_y.fill(d_t::dig_0());
    for (std::int64_t iy{0}; iy <= ix; ++iy) {
      rd_t rd_z{rd_x};
      d_t borrow = m_subtract(rd_z, rd_y);
      const std::uint64_t iz = convert_to_int<Base, Longitud>(rd_z);
      const std::uint64_t iw = ix - iy;
      const std::uint64_t ib = std::uint64_t(borrow());
      const std::uint64_t ic = (ix >= iy) ? 0 : 1;
      const bool correcto_ix = (ix == convert_to_int<Base, Longitud>(rd_x));
      const bool correcto_iy = (iy == convert_to_int<Base, Longitud>(rd_y));
      const bool bien{(iz == iw) && (ib == ic) && correcto_ix && correcto_iy};

      if (!bien) {
        ++errores;
      } else {
        ++correctos;
      }
      todo_correcto = todo_correcto && bien;

      m_incr(rd_y);
    }
    m_decr(rd_x);
  }
  return test_result_t{todo_correcto, correctos, errores};
}

template <std::size_t B, std::size_t L>
test_result_t test_calc_coc_dig_rem_div_dsor() {

  using rd_t = reg_digs_t<B, L>;

  rd_t dndo{};
  rd_t dsor{};

  constexpr auto B2L{Base_pow_to_Size<B, L>()};
  bool todo_ha_ido_bien = true;
  uint64_t correctos{0};
  uint64_t errores{0};
  dndo = 3;
  for (uint64_t ix = 3; ix < B2L; ++ix) {
    const uint64_t inicio_iy =
        std::max(uint64_t(((ix - 1) / (B - 1)) + 1), uint64_t(2));
    dsor = inicio_iy;

    // iy ha de comenzar con un numero que n tal que ix/Bm1 == iy
    //                                         y que ix%Bm1 == Bm1-1
    // iy == std::max(((ix+1)/Bm1)-1,2)
    for (uint64_t iy = inicio_iy; iy <= ix; ++iy) {
      const auto [cociente, resto] = calc_coc_dig_rem_div_dsor(dndo, dsor);

      const uint64_t dndo_int{convert_to_int<B, L>(dndo)};
      const uint64_t dsor_int{convert_to_int<B, L>(dsor)};
      const uint64_t cociente_int = dndo_int / dsor_int;
      const uint64_t resto_int = dndo_int % dsor_int;

      const uint64_t cociente_ret_int{uint64_t(cociente())};
      const auto resto_ret_int{convert_to_int<B, L>(resto)};

      const bool coc_correcto = (cociente_ret_int == cociente_int);
      const bool rem_correcto = (resto_ret_int == resto_int);

      const bool bien = coc_correcto && rem_correcto;

      if (bien) {
        ++correctos;
      } else {
        ++errores;
      }
      todo_ha_ido_bien = todo_ha_ido_bien && bien;
      m_incr(dsor);
    }
    m_incr(dndo);
  }
  test_result_t ret{todo_ha_ido_bien, correctos, errores};
  return ret;
}

template <std::uint64_t Base, std::size_t Long>
void show_test_incr_with_assign() {
  std::cout << std::boolalpha;
  auto resultado{test_incremento_con_asignacion<Base, Long>()};
  auto todo_correcto{std::get<0>(resultado)};
  auto correctos{std::get<1>(resultado)};
  auto errores{std::get<2>(resultado)};
  std::cout << "TEST para el incremento y asignación sobre el tipo "
               "reg_digs_t<"
            << int(Base) << "," << int(Long) << ">" << std::endl;
  std::cout << "El vector \"correctos\" tiene " << correctos << " elementos "
            << std::endl;
  std::cout << "El vector \"errores  \" tiene " << errores << " elementos "
            << std::endl;
  std::cout << "Todo ha ido bien : " << todo_correcto << std::endl;
}

template <std::uint64_t Base, std::size_t Long>
void show_test_decr_with_assign() {
  std::cout << std::boolalpha;
  auto resultado{test_decremento_con_asignacion<Base, Long>()};
  auto todo_correcto{std::get<0>(resultado)};
  auto correctos{std::get<1>(resultado)};
  auto errores{std::get<2>(resultado)};
  std::cout << "TEST para el decremento y asignación sobre el tipo "
               "reg_digs_t<"
            << int(Base) << "," << int(Long) << ">" << std::endl;
  std::cout << "El vector \"correctos\" tiene " << correctos << " elementos "
            << std::endl;
  std::cout << "El vector \"errores  \" tiene " << errores << " elementos "
            << std::endl;
  std::cout << "Todo ha ido bien : " << todo_correcto << std::endl;
}

template <std::uint64_t Base, std::size_t Long>
void show_test_comp_equal_than_reg_reg() {
  std::cout << std::boolalpha;
  auto resultado{
      test_comparacion_igual_que_entre_dos_objetos_tipo_reg_digs<Base, Long>()};
  auto todo_correcto{std::get<0>(resultado)};
  auto correctos{std::get<1>(resultado)};
  auto errores{std::get<2>(resultado)};
  std::cout << "TEST para la comparación entre objetos \" == \" del tipo "
               "reg_digs_t<"
            << int(Base) << "," << int(Long) << ">" << std::endl;
  std::cout << "El vector \"correctos\" tiene " << correctos << " elementos "
            << std::endl;
  std::cout << "El vector \"errores  \" tiene " << errores << " elementos "
            << std::endl;
  std::cout << "Todo ha ido bien : " << todo_correcto << std::endl;
}

template <std::uint64_t Base, std::size_t Long>
void show_test_comp_notequal_than_reg_reg() {
  std::cout << std::boolalpha;
  auto resultado{
    test_comparacion_distinto_que_entre_dos_objetos_tipo_reg_digs<Base,Long>()
  };
  auto todo_correcto{std::get<0>(resultado)};
  auto correctos{std::get<1>(resultado)};
  auto errores{std::get<2>(resultado)};
  std::cout << "TEST para la comparación entre objetos \" != \" del tipo "
               "reg_digs_t<"
            << int(Base) << "," << int(Long) << ">" << std::endl;
  std::cout << "El vector \"correctos\" tiene " << correctos << " elementos "
            << std::endl;
  std::cout << "El vector \"errores  \" tiene " << errores << " elementos "
            << std::endl;
  std::cout << "Todo ha ido bien : " << todo_correcto << std::endl;
}

template <std::uint64_t Base, std::size_t Long>
void show_test_comp_less_than_reg_reg() {
  std::cout << std::boolalpha;
  auto resultado{
      test_comparacion_menor_que_entre_dos_objetos_tipo_reg_digs<Base, Long>()};
  auto todo_correcto{std::get<0>(resultado)};
  auto correctos{std::get<1>(resultado)};
  auto errores{std::get<2>(resultado)};
  std::cout << "TEST para la comparación entre objetos \" menor que \" del "
               "tipo reg_digs_t<"
            << int(Base) << "," << int(Long) << ">" << std::endl;
  std::cout << "El vector \"correctos\" tiene " << correctos << " elementos "
            << std::endl;
  std::cout << "El vector \"errores  \" tiene " << errores << " elementos "
            << std::endl;
  std::cout << "Todo ha ido bien : " << todo_correcto << std::endl;
}

template <std::uint64_t Base, std::size_t Long>
void show_test_comp_less_or_equal_than_reg_reg() {
  std::cout << std::boolalpha;
  auto resultado{
    test_comparacion_menor_o_igual_que_entre_dos_objetos_tipo_reg_digs
    <
    	Base,Long
	>()
  };
  auto todo_correcto{std::get<0>(resultado)};
  auto correctos{std::get<1>(resultado)};
  auto errores{std::get<2>(resultado)};
  std::cout << "TEST para la comparación entre objetos \" menor o igual que \" "
               "del tipo reg_digs_t<"
            << int(Base) << "," << int(Long) << ">" << std::endl;
  std::cout << "El vector \"correctos\" tiene " << correctos << " elementos "
            << std::endl;
  std::cout << "El vector \"errores  \" tiene " << errores << " elementos "
            << std::endl;
  std::cout << "Todo ha ido bien : " << todo_correcto << std::endl;
}

template <std::uint64_t Base, std::size_t Long>
void show_test_comp_greater_than_reg_reg() {
  std::cout << std::boolalpha;
  auto resultado{
      test_comparacion_mayor_que_entre_dos_objetos_tipo_reg_digs<Base, Long>()
  };
  auto todo_correcto{std::get<0>(resultado)};
  auto correctos{std::get<1>(resultado)};
  auto errores{std::get<2>(resultado)};
  std::cout << "TEST para la comparación \" mayor que \" entre objetos del "
               "tipo reg_digs_t<"
            << int(Base) << "," << int(Long) << ">" << std::endl;
  std::cout << "El vector \"correctos\" tiene " << correctos << " elementos "
            << std::endl;
  std::cout << "El vector \"errores  \" tiene " << errores << " elementos "
            << std::endl;
  std::cout << "Todo ha ido bien : " << todo_correcto << std::endl;
}

template <std::uint64_t Base, std::size_t Long>
void show_test_comp_greater_or_equal_than_reg_reg() {
  std::cout << std::boolalpha;
  auto resultado{
	test_comparacion_mayor_o_igual_que_entre_dos_objetos_tipo_reg_digs
	<
          Base, Long
  	>()
  };
  auto todo_correcto{std::get<0>(resultado)};
  auto correctos{std::get<1>(resultado)};
  auto errores{std::get<2>(resultado)};
  std::cout << "TEST para la comparación \" mayor o igual que \" entre objetos "
               "del tipo reg_digs_t<"
            << int(Base) << "," << int(Long) << ">" << std::endl;
  std::cout << "El vector \"correctos\" tiene " << correctos << " elementos "
            << std::endl;
  std::cout << "El vector \"errores  \" tiene " << errores << " elementos "
            << std::endl;
  std::cout << "Todo ha ido bien : " << todo_correcto << std::endl;
}

template <std::uint64_t Base, std::size_t Long>
void show_test_sum_with_assign() {
  std::cout << std::boolalpha;
  auto resultado{test_suma_con_asignacion<Base, Long>()};
  auto todo_correcto{std::get<0>(resultado)};
  auto correctos{std::get<1>(resultado)};
  auto errores{std::get<2>(resultado)};
  std::cout
      << "TEST para la suma y asignación sobre el tipo reg_digs_t<"
      << int(Base) << "," << int(Long) << ">" << std::endl;
  std::cout << "El vector \"correctos\" tiene " << correctos << " elementos "
            << std::endl;
  std::cout << "El vector \"errores  \" tiene " << errores << " elementos "
            << std::endl;
  std::cout << "Todo ha ido bien : " << todo_correcto << std::endl;
}

template <std::uint64_t Base> void show_test_mult_2_digits_with_assign() {
  std::cout << std::boolalpha;
  auto resultado{test_dig_mult_dig_con_asignacion<Base>()};
  auto todo_correcto{std::get<0>(resultado)};
  auto correctos{std::get<1>(resultado)};
  auto errores{std::get<2>(resultado)};
  std::cout << "TEST para la multiplicacion y asignación sobre 2 objetos tipo "
               "dig_t<"
            << int(Base) << ">" << std::endl;
  std::cout << "El vector \"correctos\" tiene " << correctos << " elementos "
            << std::endl;
  std::cout << "El vector \"errores  \" tiene " << errores << " elementos "
            << std::endl;
  std::cout << "Todo ha ido bien : " << todo_correcto << std::endl;
}

template <std::uint64_t Base, std::size_t Long>
void show_test_subtract_with_assign() {
  std::cout << std::boolalpha;
  auto resultado{test_resta_con_asignacion<Base, Long>()};
  auto todo_correcto{std::get<0>(resultado)};
  auto correctos{std::get<1>(resultado)};
  auto errores{std::get<2>(resultado)};
  std::cout
      << "TEST para la resta y asignación sobre el tipo reg_digs_t<"
      << int(Base) << "," << int(Long) << ">" << std::endl;
  std::cout << "El vector \"correctos\" tiene " << correctos << " elementos "
            << std::endl;
  std::cout << "El vector \"errores  \" tiene " << errores << " elementos "
            << std::endl;
  std::cout << "Todo ha ido bien : " << todo_correcto << std::endl;
}

template <std::uint64_t Base> void show_test_sum_with_assign_two_digits() {
  std::cout << std::boolalpha;
  auto resultado{test_dig_suma_dig_con_asignacion<Base>()};
  auto todo_correcto{std::get<0>(resultado)};
  auto correctos{std::get<1>(resultado)};
  auto errores{std::get<2>(resultado)};
  std::cout << "TEST para la suma y asignación sobre 2 objetos tipo dig_t<"
            << int(Base) << ">" << std::endl;
  std::cout << "El vector \"correctos\" tiene " << correctos << " elementos "
            << std::endl;
  std::cout << "El vector \"errores  \" tiene " << errores << " elementos "
            << std::endl;
  std::cout << "Todo ha ido bien : " << todo_correcto << std::endl;
}

template <std::uint64_t Base, std::size_t Long>
void show_test_mult_reg_n_dig_with_assign() {
  std::cout << std::boolalpha;
  auto resultado{test_dig_mult_reg_n_dig_con_asignacion<Base, Long>()};
  auto todo_correcto{std::get<0>(resultado)};
  auto correctos{std::get<1>(resultado)};
  auto errores{std::get<2>(resultado)};
  std::cout << "TEST para la multiplicacion y asignación sobre objeto "
               "izquierdo tipo reg_dig_t<"
            << int(Base) << " , " << int(Long)
            << "> y objeto derecho tipo dig_t<" << int(Base) << ">"
            << std::endl;
  std::cout << "El vector \"correctos\" tiene " << correctos << " elementos "
            << std::endl;
  std::cout << "El vector \"errores  \" tiene " << errores << " elementos "
            << std::endl;
  std::cout << "Todo ha ido bien : " << todo_correcto << std::endl;
}

template <std::uint64_t Base, std::size_t Long>
void show_test_calc_coc_dig_rem_div_dsor_for_fediv() {
  std::cout << std::boolalpha;
  test_result_t resultado{test_calc_coc_dig_rem_div_dsor<Base, Long>()};
  auto todo_correcto{std::get<0>(resultado)};
  auto correctos{std::get<1>(resultado)};
  auto errores{std::get<2>(resultado)};
  std::cout << "TEST para la aproximacion del cociente por digito para la "
            << "implementacion de  la division euclidea "
            << "entre objetos de tipo reg_dig_t<" << int(Base) << " , "
            << int(Long) << "> y objeto derecho tipo dig_t<" << int(Base) << ">"
            << std::endl;
  std::cout << "El vector \"correctos\" tiene " << correctos << " elementos "
            << std::endl;
  std::cout << "El vector \"errores  \" tiene " << errores << " elementos "
            << std::endl;
  std::cout << "Todo ha ido bien : " << todo_correcto << std::endl;
}

template <std::uint64_t Base, std::size_t Long>
void show_test_mult_reg_n_reg_with_assign() {
  std::cout << std::boolalpha;
  auto resultado{test_reg_mult_reg_con_asignacion<Base, Long>()};
  auto todo_correcto{std::get<0>(resultado)};
  auto correctos{std::get<1>(resultado)};
  auto errores{std::get<2>(resultado)};
  std::cout << "TEST para la multiplicacion y asignación sobre 2 objetos tipo "
               "reg_dig_t<"
            << int(Base) << " , " << int(Long) << ">" << std::endl;
  std::cout << "El vector \"correctos\" tiene " << correctos << " elementos "
            << std::endl;
  std::cout << "El vector \"errores  \" tiene " << errores << " elementos "
            << std::endl;
  std::cout << "Todo ha ido bien : " << todo_correcto << std::endl;
}

template <std::uint64_t Base> void show_test_subtract_with_assign_two_digits() {
  std::cout << std::boolalpha;
  auto resultado{test_dig_resta_dig_con_asignacion<Base>()};
  auto todo_correcto{std::get<0>(resultado)};
  auto correctos{std::get<1>(resultado)};
  auto errores{std::get<2>(resultado)};
  std::cout << "TEST para la resta y asignación sobre 2 objetos tipo dig_t<"
            << int(Base) << ">" << std::endl;
  std::cout << "El vector \"correctos\" tiene " << correctos << " elementos "
            << std::endl;
  std::cout << "El vector \"errores  \" tiene " << errores << " elementos "
            << std::endl;
  std::cout << "Todo ha ido bien : " << todo_correcto << std::endl;
}

template <std::uint64_t Base>
void show_test_subtract_with_borrow_with_assign_two_digits() {
  std::cout << std::boolalpha;
  auto resultado{test_dig_resta_con_borrow_dig_con_asignacion<Base>()};
  auto todo_correcto{std::get<0>(resultado)};
  auto correctos{std::get<1>(resultado)};
  auto errores{std::get<2>(resultado)};
  std::cout << "TEST para la resta con borrow y asignación sobre 2 objetos "
               "tipo dig_t<"
            << int(Base) << ">" << std::endl;
  std::cout << "El vector \"correctos\" tiene " << correctos << " elementos "
            << std::endl;
  std::cout << "El vector \"errores  \" tiene " << errores << " elementos "
            << std::endl;
  std::cout << "Todo ha ido bien : " << todo_correcto << std::endl;
}

template <std::uint64_t Base>
void show_test_sum_n_carry_with_assign_two_digits() {
  std::cout << std::boolalpha;
//  auto t_start = std::chrono::high_resolution_clock::now();
  auto resultado{test_dig_suma_dig_con_carry_con_asignacion<Base>()};
//  auto t_end = std::chrono::high_resolution_clock::now();
//  std::cout
//      << "Tiempo transcurrido: "
//      << std::chrono::duration<double, std::milli>(t_end - t_start).count()
//      << " ms\n";
  auto todo_correcto{std::get<0>(resultado)};
  auto correctos{std::get<1>(resultado)};
  auto errores{std::get<2>(resultado)};
  std::cout << "TEST para la suma con carry y asignación sobre 2 objetos tipo "
               "dig_t<"
            << int(Base) << ">" << std::endl;
  std::cout << "El vector \"correctos\" tiene " << correctos << " elementos "
            << std::endl;
  std::cout << "El vector \"errores  \" tiene " << errores << " elementos "
            << std::endl;
  std::cout << "Todo ha ido bien : " << todo_correcto << std::endl;
}

template <std::uint64_t Base, std::size_t Long>
void show_test_div_fediv_two_reg_digs() {
  std::cout << std::boolalpha;
//  auto t_start = std::chrono::high_resolution_clock::now();
  auto resultado{test_div_fediv_entre_dos_objetos_tipo_reg_digs<Base, Long>()};
//  auto t_end = std::chrono::high_resolution_clock::now();

  auto todo_correcto{std::get<0>(resultado)};
  auto correctos{std::get<1>(resultado)};
  auto errores{std::get<2>(resultado)};
  std::cout
      << "TEST para la division (con resto) sobre 2 objetos tipo reg_digs_t<"
      << int(Base) << "," << int(Long) << ">" << std::endl;
//  std::cout
//      << "Tiempo transcurrido: "
//      << std::chrono::duration<double, std::milli>(t_end - t_start).count()
//      << " ms\n";
  std::cout << "El numero de pruebas \"correctas\" son " << correctos
            << " pruebas exitosas " << std::endl;
  std::cout << "El numero de pruebas \"erroneas\"  son " << errores
            << " pruebas fallidas " << std::endl;
  std::cout << "Todo ha ido bien : " << todo_correcto << std::endl;
}

template <std::size_t B, std::size_t L> void show_test_convert_to_int() {
  using rd_t = reg_digs_t<B, L>;
  constexpr uint64_t B2L{Base_pow_to_Size<B, L>()};
  uint64_t correctos{0};
  uint64_t errores{0};
  bool todo_ha_ido_bien{true};
  rd_t operando{0};
  for (uint64_t ix{0}; ix < B2L; ++ix) {
    const uint64_t operando_uint{convert_to_int<B, L>(operando)};
    const bool bien{ix == operando_uint};
    if (bien)
      ++correctos;
    else {
      ++errores;
    }
    todo_ha_ido_bien = todo_ha_ido_bien && bien;
    m_incr(operando);
  }
  std::cout << std::boolalpha;
  std::cout << "Resultados del TEST para la función CONVERT_TO_INT<" << B << ","
            << L << ">(CONST REG_DIGS_T &)" << std::endl;
  std::cout << "Correctos == " << correctos << std::endl;
  std::cout << "Errores   == " << errores << std::endl;
  std::cout << "Todo bien == " << todo_ha_ido_bien << std::endl;
}

template <std::size_t B, std::size_t L> void show_test_conversion_to_int() {
  using rd_t = reg_digs_t<B, L>;
  constexpr uint64_t B2L{Base_pow_to_Size<B, L>()};
  uint64_t correctos{0};
  uint64_t errores{0};
  bool todo_ha_ido_bien{true};
  rd_t operando{0};
  for (uint64_t ix{0}; ix < B2L; ++ix) {
    const uint64_t operando_uint(conversion_to_int<B, L>(operando));
    const bool bien{ix == operando_uint};
    if (bien)
      ++correctos;
    else {
      ++errores;
    }
    todo_ha_ido_bien = todo_ha_ido_bien && bien;
    m_incr(operando);
  }
  std::cout << std::boolalpha;
  std::cout << "Resultados del TEST para la función CONVERSION_TO_INT<" << B
            << "," << L << ">(CONST REG_DIGS_T &)" << std::endl;
  std::cout << "Correctos == " << correctos << std::endl;
  std::cout << "Errores   == " << errores << std::endl;
  std::cout << "Todo bien == " << todo_ha_ido_bien << std::endl;
}
} // namespace reg_digs

namespace dig { /// BEGIN OF NAMESPACE DIG
template <std::uint64_t B> void display_constr_UINT_dig_t() {
  using base_B_dig_t = dig_t<B>;

  std::uint64_t k{0};
  for (std::uint64_t i{0}; i < 1030; ++i) {
    base_B_dig_t unidades(i);
    if ((k % static_cast<ullint_t>(B)) != static_cast<ullint_t>(B - 1)) {
      std::cout << k << "->" << unidades << ";";
    } else {
      std::cout << k << "->" << unidades << "|" << std::endl;
    }
    ++k;
  }
  std::cout << std::endl;
}

template <std::uint64_t B> void display_constr_SINT_dig_t() {
  using base_B_dig_t = dig_t<B>;

  std::int64_t k{-1000};
  std::int64_t kold{0};
  for (std::int64_t i{-1030}; i < 1030; ++i) {
    base_B_dig_t unidades(i);
    if ((k % static_cast<std::int64_t>(B)) !=
        static_cast<std::int64_t>(B - 1)) {
      if ((k % static_cast<std::int64_t>(B)) == 0) {
        std::cout << k << "->" << unidades << ";";
      } else {
        std::cout << k << "->" << unidades << ";";
      }
    } else {
      std::cout << kold << "->" << unidades << "|" << std::endl;
    }
    ++k;
  }
  std::cout << std::endl;
}

template <std::uint64_t B> void display_constr_defecto_dig_t() {
  using base_B_dig_t = dig_t<B>;
  base_B_dig_t unidades_parentesis = base_B_dig_t();
  std::cout << "unidades llamadas con parentesis vacios : "
            << unidades_parentesis << std::endl;
  base_B_dig_t unidades_llaves{};
  std::cout << "unidades llamadas con llaves vacias : " << unidades_llaves
            << std::endl;
  base_B_dig_t unidades;
  std::cout << "unidades llamadas sin inicializacion aparente : " << unidades
            << std::endl;
}

template <std::uint64_t B> void display_constr_copia_dig_t() {
  using base_B_dig_t = dig_t<B>;
  {
    base_B_dig_t unidades(static_cast<ullint_t>((B / 2) + 1));
    base_B_dig_t unidades_copiadas(unidades);
    std::cout << unidades << " =?= " << unidades_copiadas << std::endl;
  }
  {
    base_B_dig_t unidades{static_cast<ullint_t>((B / 2) + 1)};
    base_B_dig_t unidades_copiadas(unidades);
    std::cout << unidades << " =?= " << unidades_copiadas << std::endl;
  }
  {
    base_B_dig_t unidades = static_cast<ullint_t>((B / 2) + 1);
    base_B_dig_t unidades_copiadas(unidades);
    std::cout << unidades << " =?= " << unidades_copiadas << std::endl;
  }
}

template <std::uint64_t B> void display_constr_movimiento_dig_t() {
  using base_B_dig_t = dig_t<B>;
  {
    base_B_dig_t A((B / 2) + 1);
    std::cout << A << std::endl;
    base_B_dig_t unidades(std::move(A));
    std::cout << unidades << std::endl;
    std::cout << A << std::endl;
  }
  {
    base_B_dig_t A{(B / 2) + 1};
    std::cout << A << std::endl;
    base_B_dig_t unidades(std::move(A));
    std::cout << unidades << std::endl;
    std::cout << A << std::endl;
  }
  {
    base_B_dig_t A = (B / 2) + 1;
    base_B_dig_t unidades(std::move(A));
    std::cout << unidades << std::endl;
    std::cout << A << std::endl;
  }
}

template <std::uint64_t B> void display_operator_assign_UINT_dig_t() {
  using base_B_dig_t = dig_t<B>;
  std::uint64_t k{0};
  std::uint64_t kold{0};
  for (std::uint64_t i{0}; i < 1024 + 6; ++i) {
    base_B_dig_t unidades;
    unidades = i;
    if ((k % static_cast<ullint_t>(B)) != static_cast<ullint_t>(B - 1)) {
      if ((k % static_cast<ullint_t>(B)) == 0)
        std::cout << kold << "->" << unidades << ";";
      else
        std::cout << kold << "->" << unidades << ";";
      ++k;
    } else {
      std::cout << kold << "->" << unidades << "|" << std::endl;
      ++k;
      kold = k;
    }
  }
  std::cout << std::endl;
}

template <std::uint64_t B> void display_operator_assign_SINT_dig_t() {
  using base_B_dig_t = dig_t<B>;

  std::int64_t k{0};
  for (std::int64_t i{-1000}; i < 1001; ++i) {
    base_B_dig_t unidades;
    unidades = i;
    if ((k % static_cast<std::int64_t>(B)) !=
        static_cast<std::int64_t>(B - 1)) {
      std::cout << i << "->" << unidades << ";";
    } else
      std::cout << i << "->" << unidades << "|" << std::endl;
    ++k;
  }
  std::cout << std::endl;
}

template <std::uint64_t B>
void display_operator_assign_copia_dig_t() {
  using base_B_dig_t = dig_t<B>;
  std::int64_t k{0};
  for (std::int64_t i{-1000}; i < 1001; ++i) {
    base_B_dig_t A{i};
    base_B_dig_t unidades;
    unidades = A;
    if ((k % static_cast<std::int64_t>(B)) !=
        static_cast<std::int64_t>(B - 1)) {
      if ((k % static_cast<std::int64_t>(B)) == 0)
        std::cout << i << "->" << unidades << ";";
      else {
        std::cout << i << "->" << unidades << ";";
      }
    } else {
      std::cout << i << "->" << unidades << "|" << std::endl;
    }
    ++k;
  }
  std::cout << std::endl;
}

template <std::uint64_t B>
void display_operator_assign_movimiento_dig_t() {
  using base_B_dig_t = dig_t<B>;
  std::int64_t k{0};

  for (std::int64_t i{-1000}; i < 1001; ++i) {
    base_B_dig_t A{i};
    base_B_dig_t C{A};
    base_B_dig_t unidades{};
    unidades = A;
    if ((k % static_cast<std::int64_t>(B)) !=
        static_cast<std::int64_t>(B - 1)) {
      if ((k % static_cast<std::int64_t>(B)) == 0)
        std::cout << i << "|1->" << unidades << ";" << C << "-;-";
      else {
        std::cout << i << "|2->" << unidades << ";" << C << "-;-";
      }
    } else {
      std::cout << i << "|3->" << unidades << C << "-|" << std::endl;
    }
    ++k;
  }
  std::cout << std::endl;
}

template <std::uint64_t B>
void display_operator_preincrement() {
  using base_B_dig_t = dig_t<B>;
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::int64_t md{};
  base_B_dig_t uds{};
  for (std::int64_t idx{0}; idx < 2 * B + 1; ++idx) {
    if ((++uds).get() == ((++md) % B))
      ++contador_buenos;
    else
      ++contador_malos;
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "___BEGIN__TESTS__PRE_INCREMENTOS___BEGIN___" << std::endl;
  std::cout << " Numero de incrementos correctos	= " << contador_buenos
            << std::endl;
  std::cout << " Numero de incrementos fallidos		= " << contador_malos
            << std::endl;
  std::cout << " Numero total de pruebas			= "
            << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"	= "
            << static_cast<std::uint64_t>(2 * B + 1) << std::endl;
  std::cout << "___END____TESTS__PRE_INCREMENTOS_____END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_postincrement() {
  using base_B_dig_t = dig_t<B>;
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::int64_t md{};
  base_B_dig_t uds{};
  for (std::int64_t idx{0}; idx < 2 * B + 1; ++idx) {
    if ((uds++).get() == ((md++) % B))
      ++contador_buenos;
    else
      ++contador_malos;
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "___BEGIN__TESTS__POSTINCREMENTOS___BEGIN___" << std::endl;
  std::cout << " Numero de incrementos correctos	= " << contador_buenos
            << std::endl;
  std::cout << " Numero de incrementos fallidos		= " << contador_malos
            << std::endl;
  std::cout << " Numero total de pruebas			= "
            << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"	= "
            << static_cast<std::uint64_t>(2 * B + 1) << std::endl;
  std::cout << "___END____TESTS__POSTINCREMENTOS_____END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_predecrement() {
  using base_B_dig_t = dig_t<B>;
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::int64_t md{2 * B + 1};
  base_B_dig_t uds{B + 1};
  for (std::int64_t idx{0}; idx < 2 * B + 1; ++idx) {
    if ((--uds).get() == ((--md) % B))
      ++contador_buenos;
    else
      ++contador_malos;
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "___BEGIN__TESTS__PRE_DECREMENTOS___BEGIN___" << std::endl;
  std::cout << " Numero de decrementos correctos	= " << contador_buenos
            << std::endl;
  std::cout << " Numero de decrementos fallidos		= " << contador_malos
            << std::endl;
  std::cout << " Numero total de pruebas			= "
            << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"	= "
            << static_cast<std::uint64_t>(2 * B + 1) << std::endl;
  std::cout << "___END____TESTS__PRE_DECREMENTOS_____END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_postdecrement() {
  using base_B_dig_t = dig_t<B>;
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::int64_t md{2 * B + 1};
  base_B_dig_t uds{B + 1};
  for (std::int64_t idx{0}; idx < 2 * B + 1; ++idx) {
    if ((uds--).get() == ((md--) % B))
      ++contador_buenos;
    else
      ++contador_malos;
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "___BEGIN__TESTS__POSTDECREMENTOS___BEGIN___" << std::endl;
  std::cout << " Numero de decrementos correctos	= " << contador_buenos
            << std::endl;
  std::cout << " Numero de decrementos fallidos		= " << contador_malos
            << std::endl;
  std::cout << " Numero total de pruebas			= "
            << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"	= "
            << static_cast<std::uint64_t>(2 * B + 1) << std::endl;
  std::cout << "___END____TESTS__POSTDECREMENTOS_____END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_add_assign() {
  using base_B_dig_t = dig_t<B>;
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::int64_t md{0};
  std::int64_t nd{0};
  base_B_dig_t nos{0};
  base_B_dig_t uds{0};
  for (std::int64_t idx_nos{0}; idx_nos < 2 * B + 1; ++idx_nos) {
    for (std::int64_t idx_uds{0}; idx_uds < 2 * B + 1; ++idx_uds) {
      uds = md;
      uds += nos;
      if (uds.get() == (md + nd) % B)
        ++contador_buenos;
      else
        ++contador_malos;
      ++md;
    }
    ++nd;
    nos = nd;
  }
  constexpr std::uint64_t ciclos{static_cast<std::uint64_t>(2 * B + 1) *
                                 static_cast<std::uint64_t>(2 * B + 1)};
  std::cout << "___________________________________________" << std::endl;
  std::cout << "___BEGIN__TESTS____ADD_&_ASSIGN____BEGIN___" << std::endl;
  std::cout << " Numero de sumasignaciones correctas= " << contador_buenos
            << std::endl;
  std::cout << " Numero de sumasignaciones fallidas	= " << contador_malos
            << std::endl;
  std::cout << " Numero total de pruebas			= "
            << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"	= " << ciclos
            << std::endl;
  std::cout << "___END_____TESTS____ADD_&_ASSIGN_____END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_add_assign_uint() {
  using base_B_dig_t = dig_t<B>;
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  for (std::int64_t nd{0}; nd < 2 * B + 1; ++nd) {
    for (std::int64_t md{0}; md < 2 * B + 1; ++md) {
      base_B_dig_t uds{md};
      uds += nd;
      if (uds.get() == ((md + nd) % B))
        ++contador_buenos;
      else
        ++contador_malos;
    }
  }
  constexpr std::uint64_t ciclos{static_cast<std::uint64_t>(2 * B + 1) *
                                 static_cast<std::uint64_t>(2 * B + 1)};
  std::cout << "___________________________________________" << std::endl;
  std::cout << "___BEGIN__TESTS_ADD_&_ASSIGN_UINT__BEGIN___" << std::endl;
  std::cout << " Numero de sumasignaciones correctas= " << contador_buenos
            << std::endl;
  std::cout << " Numero de sumasignaciones fallidas	= " << contador_malos
            << std::endl;
  std::cout << " Numero total de pruebas			= "
            << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"	= " << ciclos
            << std::endl;
  std::cout << "___END____TESTS_ADD_&_ASSIGN_UINT____END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_substract_assign() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int64_t int64_B{B};
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::uint64_t contador{};
  for (std::int64_t nd{1 - int64_B}; nd < int64_B; ++nd) {
    for (std::int64_t md{1 - int64_B}; md < int64_B; ++md) {
      std::int64_t mmd{md};
      base_B_dig_t nos{nd};
      base_B_dig_t uds{mmd};
      uds -= nos;
      mmd -= nd;

      while (mmd < 0)
        mmd += int64_B;
      while (mmd >= int64_B)
        mmd -= int64_B;

      if (uds.get() == mmd)
        ++contador_buenos;
      else
        ++contador_malos;

      ++contador;
    }
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "__BEGIN__TESTS_SUBSTRACT_&_ASSIGN__BEGIN___" << std::endl;
  std::cout << " Numero de sumasignaciones correctas= " << contador_buenos
            << std::endl;
  std::cout << " Numero de sumasignaciones fallidas	= " << contador_malos
            << std::endl;
  std::cout << " Numero total de pruebas			= "
            << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"	= " << contador
            << std::endl;
  std::cout << "__END____TESTS_SUBSTRACT_&_ASSIGN____END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_substract_assign_uint() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int64_t int64_B{B};
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::uint64_t contador{};
  for (std::int64_t nd{1 - int64_B}; nd < int64_B; ++nd) {
    for (std::int64_t md{1 - int64_B}; md < int64_B; ++md) {
      std::int64_t mmd{md};
      base_B_dig_t uds{mmd};
      uds -= nd;
      mmd -= nd;
      while (mmd < 0) {
        mmd += B;
      }
      while (mmd >= B) {
        mmd -= B;
      }
      if (uds.get() == mmd) {
        ++contador_buenos;
      } else {
        ++contador_malos;
      }
      ++contador;
    }
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "_BEGIN_TESTS_SUBSTRACT_&_ASSIGN_INT_BEGIN__" << std::endl;
  std::cout << " Numero de sumasignaciones correctas= " << contador_buenos
            << std::endl;
  std::cout << " Numero de sumasignaciones fallidas	= " << contador_malos
            << std::endl;
  std::cout << " Numero total de pruebas			= "
            << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"	= " << contador
            << std::endl;
  std::cout << "_END___TESTS_SUBSTRACT_&_ASSIGN_INT__END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_mult_assign() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int64_t int64_B{B};
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::uint64_t contador{};
  for (std::int64_t nd{1 - int64_B}; nd < int64_B; ++nd) {
    for (std::int64_t md{1 - int64_B}; md < int64_B; ++md) {
      std::int64_t mmd{md};
      base_B_dig_t nos{nd};
      base_B_dig_t uds{mmd};
      uds *= nos;
      mmd *= nd;

      while (mmd < 0)
        mmd += int64_B;
      while (mmd >= int64_B)
        mmd -= int64_B;

      if (uds.get() == mmd)
        ++contador_buenos;
      else
        ++contador_malos;

      ++contador;
    }
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "__BEGIN__TESTS____MULT_&_ASSIGN____BEGIN___" << std::endl;
  std::cout << " Numero de sumasignaciones correctas= " << contador_buenos
            << std::endl;
  std::cout << " Numero de sumasignaciones fallidas	= " << contador_malos
            << std::endl;
  std::cout << " Numero total de pruebas			= "
            << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"	= " << contador
            << std::endl;
  std::cout << "__END____TESTS____MULT_&_ASSIGN______END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_mult_assign_uint() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int32_t int32_B{B};
  std::uint32_t contador_buenos{};
  std::uint32_t contador_malos{};
  std::uint32_t contador{};
  for (std::int32_t nd{1 - int32_B}; nd < int32_B; ++nd) {
    for (std::int32_t md{1 - int32_B}; md < int32_B; ++md) {
      std::int32_t mmd{md};
      base_B_dig_t uds{mmd};
      uds *= nd;
      mmd *= nd;
      while (mmd < 0) {
        mmd += B;
      }
      while (mmd >= int32_B) {
        mmd -= B;
      }
      if (uds.get() == mmd) {
        ++contador_buenos;
      } else {
        ++contador_malos;
      }
      ++contador;
    }
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "_BEGIN_TESTS___MULT_&_ASSIGN_INT____BEGIN__" << std::endl;
  std::cout << " Numero de sumasignaciones correctas= " << contador_buenos
            << std::endl;
  std::cout << " Numero de sumasignaciones fallidas	= " << contador_malos
            << std::endl;
  std::cout << " Numero total de pruebas			= "
            << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"	= " << contador
            << std::endl;
  std::cout << "_END___TESTS___MULT_&_ASSIGN_INT_____END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_ediv_assign() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int64_t int64_B{B};
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::uint64_t contador{};
  for (std::int64_t nd{1 - int64_B}; nd < int64_B; ++nd) {
    if ((nd % int64_B) != 0) {
      for (std::int64_t md{1 - int64_B}; md < int64_B; ++md) {
        base_B_dig_t uds{md};
        std::int64_t mmd{md};
        while (mmd < 0)
          mmd += int64_B;
        base_B_dig_t nos{nd};
        std::int64_t nnd{nd};
        while (nnd < 0)
          nnd += int64_B;

        uds /= nos;
        mmd /= nnd;

        while (mmd < 0)
          mmd += int64_B;
        while (mmd >= int64_B)
          mmd -= int64_B;

        if (uds.get() == mmd)
          ++contador_buenos;
        else
          ++contador_malos;

        ++contador;
      }
    }
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "__BEGIN__TESTS____EDIV_&_ASSIGN____BEGIN___" << std::endl;
  std::cout << " Numero de sumasignaciones correctas= " << contador_buenos
            << std::endl;
  std::cout << " Numero de sumasignaciones fallidas	= " << contador_malos
            << std::endl;
  std::cout << " Numero total de pruebas			= "
            << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"	= " << contador
            << std::endl;
  std::cout << "__END____TESTS____EDIV_&_ASSIGN______END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_ediv_assign_uint() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int32_t int32_B{B};
  std::uint32_t contador_buenos{};
  std::uint32_t contador_malos{};
  std::uint32_t contador{};
  for (std::int32_t nd{1 - int32_B}; nd < int32_B; ++nd) {
    if (nd != 0) {
      for (std::int32_t md{1 - int32_B}; md < int32_B; ++md) {
        std::int32_t mmd{md};
        std::int32_t nnd{nd};
        base_B_dig_t uds{mmd};

        while (mmd < 0) {
          mmd += int32_B;
        }
        while (nnd < 0) {
          nnd += int32_B;
        }

        uds /= nnd;
        mmd /= nnd;

        while (mmd < 0) {
          mmd += B;
        }
        while (mmd >= int32_B) {
          mmd -= B;
        }

        if (uds.get() == mmd) {
          ++contador_buenos;
        } else {
          ++contador_malos;
        }

        ++contador;
      }
    }
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "_BEGIN_TESTS___EDIV_&_ASSIGN_INT____BEGIN__" << std::endl;
  std::cout << " Numero de sumasignaciones correctas= " << contador_buenos
            << std::endl;
  std::cout << " Numero de sumasignaciones fallidas	= " << contador_malos
            << std::endl;
  std::cout << " Numero total de pruebas			= "
            << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"	= " << contador
            << std::endl;
  std::cout << "_END___TESTS___EDIV_&_ASSIGN_INT_____END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_erem_assign() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int64_t int64_B{B};
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::uint64_t contador{};
  for (std::int64_t nd{1 - int64_B}; nd < int64_B; ++nd) {
    if (nd != 0) {
      for (std::int64_t md{1 - int64_B}; md < int64_B; ++md) {
        std::int64_t mmd{md};
        std::int64_t nnd{nd};
        base_B_dig_t nos{nd};
        base_B_dig_t uds{mmd};

        while (mmd < 0)
          mmd += int64_B;
        while (nnd < 0)
          nnd += int64_B;

        uds %= nos;
        mmd %= nnd;

        while (mmd < 0)
          mmd += int64_B;
        while (mmd >= int64_B)
          mmd -= int64_B;

        if (uds.get() == mmd)
          ++contador_buenos;
        else
          ++contador_malos;

        ++contador;
      }
    }
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "__BEGIN__TESTS____EREM_&_ASSIGN____BEGIN___" << std::endl;
  std::cout << " Numero de sumasignaciones correctas= " << contador_buenos
            << std::endl;
  std::cout << " Numero de sumasignaciones fallidas	= " << contador_malos
            << std::endl;
  std::cout << " Numero total de pruebas			= "
            << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"	= " << contador
            << std::endl;
  std::cout << "__END____TESTS____EREM_&_ASSIGN______END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_erem_assign_uint() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int32_t int32_B{B};
  std::uint32_t contador_buenos{};
  std::uint32_t contador_malos{};
  std::uint32_t contador{};
  for (std::int32_t nd{1 - int32_B}; nd < int32_B; ++nd) {
    if (nd != 0) {
      for (std::int32_t md{1 - int32_B}; md < int32_B; ++md) {
        std::int32_t mmd{md};
        std::int32_t nnd{nd};
        base_B_dig_t uds{mmd};

        while (mmd < 0) {
          mmd += int32_B;
        }
        while (nnd < 0) {
          nnd += int32_B;
        }

        uds %= nnd;
        mmd %= nnd;

        while (mmd < 0) {
          mmd += B;
        }
        while (mmd >= int32_B) {
          mmd -= B;
        }

        if (uds.get() == mmd) {
          ++contador_buenos;
        } else {
          ++contador_malos;
        }

        ++contador;
      }
    }
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "_BEGIN_TESTS___EREM_&_ASSIGN_INT____BEGIN__" << std::endl;
  std::cout << " Numero de sumasignaciones correctas= " << contador_buenos
            << std::endl;
  std::cout << " Numero de sumasignaciones fallidas	= " << contador_malos
            << std::endl;
  std::cout << " Numero total de pruebas			= "
            << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"	= " << contador
            << std::endl;
  std::cout << "_END___TESTS___EREM_&_ASSIGN_INT_____END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_add() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int64_t int64_B{B};
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::uint64_t contador{};
  for (std::int64_t nd{1 - int64_B}; nd < int64_B; ++nd) {
    for (std::int64_t md{1 - int64_B}; md < int64_B; ++md) {
      std::int64_t suma_int{md + nd};
      base_B_dig_t nos{nd};
      base_B_dig_t uds{md};
      base_B_dig_t suma_dig{nos + uds};

      while (suma_int < 0)
        suma_int += int64_B;
      while (suma_int >= int64_B)
        suma_int -= int64_B;

      if (suma_dig.get() == suma_int)
        ++contador_buenos;
      else
        ++contador_malos;

      ++contador;
    }
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "___BEGIN_______TESTS____SUMA_______BEGIN___" << std::endl;
  std::cout << " Numero de sumasignaciones correctas= " << contador_buenos
            << std::endl;
  std::cout << " Numero de sumasignaciones fallidas	= " << contador_malos
            << std::endl;
  std::cout << " Numero total de pruebas			= "
            << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"	= " << contador
            << std::endl;
  std::cout << "___END_________TESTS____SUMA_________END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_add_int() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int32_t int32_B{B};
  std::uint32_t contador_buenos{};
  std::uint32_t contador_malos{};
  std::uint32_t contador{};
  for (std::int32_t nd{1 - int32_B}; nd < int32_B; ++nd) {
    for (std::int32_t md{1 - int32_B}; md < int32_B; ++md) {
      std::int32_t suma_int{md + nd};
      base_B_dig_t uds{md};
      base_B_dig_t suma_dig{uds + nd};

      while (suma_int < 0)
        suma_int += int32_B;
      while (suma_int >= int32_B)
        suma_int -= int32_B;

      if (suma_dig.get() == suma_int)
        ++contador_buenos;
      else
        ++contador_malos;

      ++contador;
    }
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "___BEGIN______TESTS_SUMA_INT_______BEGIN___" << std::endl;
  std::cout << " Numero de sumasignaciones correctas= " << contador_buenos
            << std::endl;
  std::cout << " Numero de sumasignaciones fallidas	= " << contador_malos
            << std::endl;
  std::cout << " Numero total de pruebas			= "
            << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"	= " << contador
            << std::endl;
  std::cout << "___END________TESTS_SUMA_INT_________END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_substract() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int64_t int64_B{B};
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::uint64_t contador{};
  for (std::int64_t nd{1 - int64_B}; nd < int64_B; ++nd) {
    for (std::int64_t md{1 - int64_B}; md < int64_B; ++md) {
      std::int64_t suma_int{md - nd};
      base_B_dig_t nos{nd};
      base_B_dig_t uds{md};
      base_B_dig_t suma_dig{uds - nos};

      while (suma_int < 0)
        suma_int += int64_B;
      while (suma_int >= int64_B)
        suma_int -= int64_B;

      if (suma_dig.get() == suma_int)
        ++contador_buenos;
      else
        ++contador_malos;

      ++contador;
    }
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "___BEGIN_____TESTS__SUBSTRACT______BEGIN___" << std::endl;
  std::cout << " Numero de restas correctas			= "
            << contador_buenos << std::endl;
  std::cout << " Numero de restas fallidas			= "
            << contador_malos << std::endl;
  std::cout << " Numero total de pruebas			= "
            << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"	= " << contador
            << std::endl;
  std::cout << "___END_______TESTS__SUBSTRACT________END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_substract_int() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int32_t int32_B{B};
  std::uint32_t contador_buenos{};
  std::uint32_t contador_malos{};
  std::uint32_t contador{};
  for (std::int32_t nd{1 - int32_B}; nd < int32_B; ++nd) {
    for (std::int32_t md{1 - int32_B}; md < int32_B; ++md) {
      std::int32_t suma_int{md - nd};
      base_B_dig_t uds{md};
      base_B_dig_t suma_dig{uds - nd};

      while (suma_int < 0)
        suma_int += int32_B;
      while (suma_int >= int32_B)
        suma_int -= int32_B;

      if (suma_dig.get() == suma_int)
        ++contador_buenos;
      else
        ++contador_malos;

      ++contador;
    }
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "___BEGIN______TESTS_RESTA_INT______BEGIN___" << std::endl;
  std::cout << " Numero de restas correctas			= "
            << contador_buenos << std::endl;
  std::cout << " Numero de restas fallidas			= "
            << contador_malos << std::endl;
  std::cout << " Numero total de pruebas			= "
            << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"	= " << contador
            << std::endl;
  std::cout << "___END________TESTS_RESTA_INT________END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_multiply() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int64_t int64_B{B};
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::uint64_t contador{};
  for (std::int64_t nd{1 - int64_B}; nd < int64_B; ++nd) {
    for (std::int64_t md{1 - int64_B}; md < int64_B; ++md) {
      std::int64_t result_int{md * nd};
      base_B_dig_t nos{nd};
      base_B_dig_t uds{md};
      base_B_dig_t result_dig{uds * nos};

      while (result_int < 0)
        result_int += int64_B;
      while (result_int >= int64_B)
        result_int -= int64_B;

      if (result_dig.get() == result_int)
        ++contador_buenos;
      else
        ++contador_malos;

      ++contador;
    }
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "___BEGIN___TESTS_MULTIPLICACIONES__BEGIN___" << std::endl;
  std::cout << " Numero de multiplicaciones correctas	= " << contador_buenos
            << std::endl;
  std::cout << " Numero de multiplicaciones fallidas	= " << contador_malos
            << std::endl;
  std::cout << " Numero total de pruebas				= "
            << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"		= " << contador
            << std::endl;
  std::cout << "___END_____TESTS_MULTIPLICACIONES____END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_multiply_int() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int32_t int32_B{B};
  std::uint32_t contador_buenos{};
  std::uint32_t contador_malos{};
  std::uint32_t contador{};
  for (std::int32_t nd{1 - int32_B}; nd < int32_B; ++nd) {
    for (std::int32_t md{1 - int32_B}; md < int32_B; ++md) {
      std::int32_t result_int{md * nd};
      base_B_dig_t uds{md};
      base_B_dig_t result_dig{uds * nd};

      while (result_int < 0)
        result_int += int32_B;
      while (result_int >= int32_B)
        result_int -= int32_B;

      if (result_dig.get() == result_int)
        ++contador_buenos;
      else
        ++contador_malos;

      ++contador;
    }
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "__BEGIN_TESTS_MULTIPLICACIONES_INT_BEGIN___" << std::endl;
  std::cout << " Numero de multiplicaciones correctas	= " << contador_buenos
            << std::endl;
  std::cout << " Numero de multiplicaciones fallidas	= " << contador_malos
            << std::endl;
  std::cout << " Numero total de pruebas				= "
            << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"		= " << contador
            << std::endl;
  std::cout << "___END__TESTS_MULTIPLICACIONES_INT___END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_edivision() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int64_t int64_B{B};
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::uint64_t contador{};
  for (std::int64_t nd{-1}; nd < int64_B; ++nd) {
    if (nd % B != 0) {
      for (std::int64_t md{-1}; md < int64_B; ++md) {

        base_B_dig_t nos{nd};
        base_B_dig_t uds{md};
        base_B_dig_t result_dig{uds / nos};
        base_B_dig_t prueba_ediv_dig{uds - (result_dig * nos)};

        std::int64_t mmd{md};
        while (mmd < 0)
          mmd += int64_B;
        while (mmd >= int64_B)
          mmd -= int64_B;
        std::int64_t nnd{nd};
        while (nnd < 0)
          nnd += int64_B;
        while (nnd >= int64_B)
          nnd -= int64_B;
        std::int64_t result_int{mmd / nnd};
        while (result_int < 0)
          result_int += int64_B;
        while (result_int >= int64_B)
          result_int -= int64_B;
        std::int64_t prueba_ediv_int{mmd - (result_int * nnd)};
        while (prueba_ediv_int < 0)
          prueba_ediv_int += int64_B;
        while (prueba_ediv_int >= int64_B)
          prueba_ediv_int -= int64_B;
        if (prueba_ediv_dig.get() == prueba_ediv_int) {
          ++contador_buenos;
        } else {
          ++contador_malos;
        }
        ++contador;
      }
    }
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "___BEGIN_____TESTS_EDIVISIONES_____BEGIN___" << std::endl;
  std::cout << " Numero de divisiones euclideas correctas	= "
            << contador_buenos << std::endl;
  std::cout << " Numero de divisiones euclideas fallidas	= "
            << contador_malos << std::endl;
  std::cout
      << " Numero total de pruebas					= "
      << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"			= "
            << contador << std::endl;
  std::cout << "___END_______TESTS_EDIVISIONES_______END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_edivision_int() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int64_t int64_B{B};
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::uint64_t contador{};
  for (std::int64_t nd{1 - int64_B}; nd < int64_B; ++nd) {
    if (nd % B != 0) {
      for (std::int64_t md{1 - int64_B}; md < int64_B; ++md) {
        std::int64_t mmd{md};
        while (mmd < 0)
          mmd += int64_B;
        while (mmd >= int64_B)
          mmd -= int64_B;
        std::int64_t nnd{nd};
        while (nnd < 0)
          nnd += int64_B;
        while (nnd >= int64_B)
          nnd -= int64_B;
        std::int64_t result_int{mmd / nnd};
        while (result_int < 0)
          result_int += int64_B;
        while (result_int >= int64_B)
          result_int -= int64_B;

        base_B_dig_t uds{mmd};
        base_B_dig_t result_dig{uds / nnd};

        if (result_dig.get() == result_int)
          ++contador_buenos;
        else
          ++contador_malos;

        ++contador;
      }
    }
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "__BEGIN___TESTS_EDIVISIONES_INT____BEGIN___" << std::endl;
  std::cout << " Numero de divisiones euclideas correctas	= "
            << contador_buenos << std::endl;
  std::cout << " Numero de divisiones euclideas fallidas	= "
            << contador_malos << std::endl;
  std::cout
      << " Numero total de pruebas					= "
      << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"			= "
            << contador << std::endl;
  std::cout << "___END____TESTS_EDIVISIONES_INT______END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_C_B() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int64_t int64_B{B};
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::uint64_t contador{};
  for (std::int64_t nd{-2 * int64_B}; nd < 2 * int64_B; ++nd) {
    std::int64_t nnd{nd};
    while (nnd < 0)
      nnd += int64_B;
    while (nnd >= int64_B)
      nnd -= int64_B;

    std::int64_t result_int{int64_B - nnd};
    while (result_int < 0)
      result_int += int64_B;
    while (result_int >= int64_B)
      result_int -= int64_B;

    base_B_dig_t uds{nnd};
    base_B_dig_t result_dig{uds.C_B()};

    if (result_dig.get() == result_int)
      ++contador_buenos;
    else
      ++contador_malos;

    ++contador;
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "__BEGIN___TESTS_COMPLEMENTO_BASE___BEGIN___" << std::endl;
  std::cout << " Numero de complementos a la base correctas	= "
            << contador_buenos << std::endl;
  std::cout << " Numero de complementos a la base fallidos	= "
            << contador_malos << std::endl;
  std::cout
      << " Numero total de pruebas					= "
      << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"			= "
            << contador << std::endl;
  std::cout << "__END_____TESTS_COMPLEMENTO_BASE_____END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_operator_C_Bm1() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int64_t int64_B{B};
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::uint64_t contador{};
  for (std::int64_t nd{-2 * int64_B}; nd < 2 * int64_B; ++nd) {
    std::int64_t nnd{nd};
    while (nnd < 0)
      nnd += int64_B;
    while (nnd >= int64_B)
      nnd -= int64_B;

    std::int64_t result_int{int64_B - nnd - 1};
    while (result_int < 0)
      result_int += int64_B;
    while (result_int >= int64_B)
      result_int -= int64_B;

    base_B_dig_t uds{nnd};
    base_B_dig_t result_dig{uds.C_Bm1()};

    if (result_dig.get() == result_int)
      ++contador_buenos;
    else
      ++contador_malos;

    ++contador;
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "__BEGIN__TESTS_COMPLEMENTO_BASEm1__BEGIN___" << std::endl;
  std::cout << " Numero de complementos a la Bm1 correctas	= "
            << contador_buenos << std::endl;
  std::cout << " Numero de complementos a la Bm1 fallidos	= "
            << contador_malos << std::endl;
  std::cout
      << " Numero total de pruebas					= "
      << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"			= "
            << contador << std::endl;
  std::cout << "__END_____TESTS_COMPLEMENTO_BASEm1___END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_prop_C_B_eq_inv_C_B() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int64_t int64_B{B};
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::uint64_t contador{};
  for (std::int64_t nd{-2 * int64_B}; nd < 2 * int64_B; ++nd) {
    base_B_dig_t uds{nd};
    base_B_dig_t result_interm_dig{uds.C_B()};
    base_B_dig_t result_dig{result_interm_dig.C_B()};

    if (result_dig == uds)
      ++contador_buenos;
    else
      ++contador_malos;

    ++contador;
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "__BEGIN__TESTS_dig.C_B().C_B()=dig__BEGIN__" << std::endl;
  std::cout << " Numero de C_B(C_B())=Id() correctas	= " << contador_buenos
            << std::endl;
  std::cout << " Numero de C_B(C_B())=Id() fallidos	= " << contador_malos
            << std::endl;
  std::cout
      << " Numero total de pruebas					= "
      << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"			= "
            << contador << std::endl;
  std::cout << "__END____TESTS_dig.C_B().C_B()=dig____END__" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_prop_C_Bm1_eq_inv_C_Bm1() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int64_t int64_B{B};
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::uint64_t contador{};
  for (std::int64_t nd{-2 * int64_B}; nd < 2 * int64_B; ++nd) {
    base_B_dig_t uds{nd};
    base_B_dig_t result_interm_dig{uds.C_Bm1()};
    base_B_dig_t result_dig{result_interm_dig.C_Bm1()};

    if (result_dig == uds)
      ++contador_buenos;
    else
      ++contador_malos;

    ++contador;
  }
  std::cout << "_______________________________________________" << std::endl;
  std::cout << "__BEGIN__TESTS_dig.C_Bm1().C_Bm1()=dig__BEGIN__" << std::endl;
  std::cout << " Numero de C_Bm1(C_Bm1())=Id() correctas	= "
            << contador_buenos << std::endl;
  std::cout << " Numero de C_B(C_B())=Id() fallidos	= " << contador_malos
            << std::endl;
  std::cout
      << " Numero total de pruebas					= "
      << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"			= "
            << contador << std::endl;
  std::cout << "__END____TESTS_dig.C_Bm1().C_Bm1()=dig____END__" << std::endl;
  std::cout << "_______________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_prop_C_B_minus_1_eq_C_Bm1() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int64_t int64_B{B};
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::uint64_t contador{};
  for (std::int64_t nd{-2 * int64_B}; nd < 2 * int64_B; ++nd) {
    base_B_dig_t uds{nd};
    base_B_dig_t uds_C_Bm1_p1{uds.C_Bm1()};
    ++uds_C_Bm1_p1;
    base_B_dig_t uds_C_B{uds.C_B()};

    if (uds_C_Bm1_p1 == uds_C_B)
      ++contador_buenos;
    else
      ++contador_malos;

    ++contador;
  }
  std::cout << "_______________________________________________" << std::endl;
  std::cout << "__BEGIN__TESTS_dig.C_Bm1()+1=dig.C_B()__BEGIN__" << std::endl;
  std::cout << " Numero de C_Bm1(C_Bm1())=Id() correctas	= "
            << contador_buenos << std::endl;
  std::cout << " Numero de C_B(C_B())=Id() fallidos	= " << contador_malos
            << std::endl;
  std::cout
      << " Numero total de pruebas					= "
      << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"			= "
            << contador << std::endl;
  std::cout << "__END____TESTS_dig.C_Bm1()+1=dig.C_B()____END__" << std::endl;
  std::cout << "_______________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_unary_operator_minus() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int64_t int64_B{B};
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::uint64_t contador{};
  for (std::int64_t nd{-2 * int64_B}; nd < 2 * int64_B; ++nd) {
    std::int64_t nnd{nd};
    while (nnd < 0)
      nnd += int64_B;
    while (nnd >= int64_B)
      nnd -= int64_B;

    std::int64_t result_int{int64_B - nnd};
    while (result_int < 0)
      result_int += int64_B;
    while (result_int >= int64_B)
      result_int -= int64_B;

    base_B_dig_t uds{nnd};
    base_B_dig_t result_dig{-uds};

    if (result_dig.get() == result_int)
      ++contador_buenos;
    else
      ++contador_malos;

    ++contador;
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "__BEGIN___TESTS_OPERATOR_-_UNARIO__BEGIN___" << std::endl;
  std::cout << " Numero de cambios de signo correctas	= " << contador_buenos
            << std::endl;
  std::cout << " Numero de cambios de signo fallidos	= " << contador_malos
            << std::endl;
  std::cout
      << " Numero total de pruebas					= "
      << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"			= "
            << contador << std::endl;
  std::cout << "__END_____TESTS_OPERATOR_-_UNARIO____END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}

template <std::uint64_t B>
void display_unary_operator_neg() {
  using base_B_dig_t = dig_t<B>;
  constexpr std::int64_t int64_B{B};
  std::uint64_t contador_buenos{};
  std::uint64_t contador_malos{};
  std::uint64_t contador{};
  for (std::int64_t nd{-2 * int64_B}; nd < 2 * int64_B; ++nd) {
    std::int64_t nnd{nd};
    while (nnd < 0)
      nnd += int64_B;
    while (nnd >= int64_B)
      nnd -= int64_B;

    std::int64_t result_int{int64_B - nnd - 1};
    while (result_int < 0)
      result_int += int64_B;
    while (result_int >= int64_B)
      result_int -= int64_B;

    base_B_dig_t uds{nnd};
    base_B_dig_t result_dig{!uds};

    if (result_dig.get() == result_int)
      ++contador_buenos;
    else
      ++contador_malos;

    ++contador;
  }
  std::cout << "___________________________________________" << std::endl;
  std::cout << "__BEGIN___TESTS_OPERATOR_!_UNARIO__BEGIN___" << std::endl;
  std::cout << " Numero de negaciones correctas	= " << contador_buenos
            << std::endl;
  std::cout << " Numero de negaciones fallidas	= " << contador_malos
            << std::endl;
  std::cout
      << " Numero total de pruebas					= "
      << contador_buenos + contador_malos << std::endl;
  std::cout << " Numero limite del ciclo \"for\"			= "
            << contador << std::endl;
  std::cout << "__END_____TESTS_OPERATOR_!_UNARIO____END___" << std::endl;
  std::cout << "___________________________________________" << std::endl;
}
} // namespace dig
} // namespace testing
} // namespace NumRepr

#endif // TESTUNIT_HPP_INCLUDED
