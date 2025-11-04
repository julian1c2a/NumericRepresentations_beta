#ifndef BASE_NUM_T_HPP_INCLUDED
#define BASE_NUM_T_HPP_INCLUDED

#include "basic_types.hpp"
#include "dig_t.hpp"
#include "int_reg_digs_t.hpp"

namespace NumRepr {

template <std::uint64_t B>
  requires(B > 1)
struct BaseNum : public std::basic_string<dig_t<B>> {
public:

  using dig_t = dig_t<B>;
  using uint_type = typename dig_t::UINT_T;
  using base_type = std::basic_string<dig_t>;
  using iterator = typename base_type::iterator;
  using const_iterator = typename base_type::const_iterator;
  using reverse_iterator = typename base_type::reverse_iterator;
  using const_reverse_iterator = typename base_type::const_reverse_iterator;

public:
  inline constexpr std::size_t size() const noexcept {
    return (static_cast<const base_type *const>(this)->size());
  }

  inline constexpr void resize(std::size_t arg) noexcept {
    (static_cast<base_type *const>(this)->resize(arg));
  }

  inline constexpr dig_t operator[](std::size_t index) const noexcept {
    return (static_cast<const base_type *const>(this)->operator[](index));
  }

  inline constexpr dig_t &operator[](std::size_t index) noexcept {
    return (static_cast<base_type *const>(this)->operator[](index));
  }

  inline constexpr void clear() noexcept {
    static_cast<base_type *const>(this)->clear();
  }

  inline constexpr void push_back(dig_t arg) noexcept {
    static_cast<base_type *const>(this)->push_back(arg);
  }

  inline constexpr void insert(std::size_t pos, std::size_t count, dig_t parg) noexcept {
    static_cast<base_type *const>(this)->insert(pos, count, parg);
  }

  inline constexpr BaseNum substr(std::size_t pos, std::size_t count) const noexcept {
    static_cast<const base_type *const>(this)->substr(pos, count);
    return (*this);
  }

  inline constexpr void push_front(dig_t parg) noexcept {
    static_cast<base_type *const>(this)->insert(0, 1, parg);
  }

  inline constexpr iterator begin() noexcept {
    return static_cast<base_type *const>(this)->begin();
  }

  inline constexpr const_iterator end() const noexcept {
    return static_cast<const base_type *const>(this)->end();
  }

  inline constexpr reverse_iterator rbegin() noexcept {
    return static_cast<base_type *const>(this)->rbegin();
  }

  inline constexpr const_reverse_iterator rend() const noexcept {
    return static_cast<const base_type *const>(this)->rend();
  }

  inline constexpr void erase(std::size_t pos, std::size_t count) noexcept {
    static_cast<base_type *const>(this)->erase(pos, count);
  }

  // OPERADOR DE CONCATENACION
  inline constexpr const BaseNum &
  operator&=(const BaseNum &arg) noexcept {
    (*(static_cast<base_type *const>(this))) += arg;
    return (*this);
  }
};

template <std::uint64_t B>
inline constexpr ullint_t get_max_power_of_base_in_int_type() noexcept {
  using int_type = typename dig_t<B>::UINT_T;
  constexpr long double max =
      static_cast<long double>(type_traits::maxbase<int_type>());
  constexpr long double max_unit =
      static_cast<long double>(std::numeric_limits<char>::max());
  constexpr long double nb_unit =
      static_cast<long double>(1 + (log(max_unit) / log(2)));
  constexpr long double n_units_Int_T = static_cast<long double>(sizeof(int_type));
  constexpr long double nb_Int_T = nb_unit * n_units_Int_T;
  constexpr long double log_2_b_B = std::log(static_cast<long double>(2)) /
                                    std::log(static_cast<long double>(B));
  constexpr long double ld_expB = (std::floor(nb_Int_T * log_2_b_B));
  // long double ld_potB = (floor(pow(static_cast<long double>(B),ld_expB)));
  constexpr ullint_t ret = static_cast<ullint_t>(ld_expB);
  return ret;
}

template <std::uint64_t B>
inline constexpr ullint_t get_num_digits_for_max_base_in_int_type() noexcept {
  using int_type = typename dig_t<B>::UINT_T;
  constexpr long double max =
      static_cast<long double>(std::numeric_limits<int_type>::max() + 1);
  constexpr long double max_unit =
      2 * static_cast<long double>(std::numeric_limits<char>::max() + 1);
  constexpr long double nb_unit =
      static_cast<long double>((log(max_unit) / log(2)));
  constexpr long double n_units_Int_T = static_cast<long double>(sizeof(int_type));
  constexpr long double nb_Int_T = nb_unit * n_units_Int_T;
  constexpr long double log_2_b_B =
      log(static_cast<long double>(2)) / log(static_cast<long double>(B));
  long double ld_expB = (floor(nb_Int_T * log_2_b_B));
  long double ld_potB = (floor(pow(static_cast<long double>(B), ld_expB)));
  // bool B_es_pot_de_2 = false;
  ullint pot_2 = 2;
  for (ullint b = 1; b < max_unit; b++) {
    if (B == pot_2) {
      ld_expB += static_cast<long double>(1);
      // B_es_pot_de_2 = true;
      break;
    }
    pot_2 *= 2;
  }
  constexpr long double max_pot_B_Int_T =
      static_cast<long double>(pot_max_base_b_in_uint_t<B>());
  long double multiplo = 1;
  ullint ind = 0;
  while ((multiplo < max) and (ind < B)) {
    multiplo = floor(multiplo + max_pot_B_Int_T);
    if (multiplo > max) {
      multiplo = floor(multiplo - max_pot_B_Int_T);
      ullint ret = static_cast<ullint>(multiplo - 1.0);
      return ret;
    }
    ++ind;
  }
  constexpr ullint ret = ullint(ld_expB);
  return ret;
}

template <std::uint64_t B>
inline constexpr ullint_t get_max_base_in_int_type() noexcept {
  using int_type = typename dig_t<B>::UINT_T;
  constexpr long double max =
      static_cast<long double>(std::numeric_limits<int_type>::max());
  constexpr long double n_digs_base_B =
      static_cast<long double>(get_num_digits_for_max_base_in_int_type<B>());
  constexpr long double dos = static_cast<long double>(2);
  constexpr long double base = static_cast<long double>(B);
  constexpr ullint ret =
      static_cast<ullint>(ceil((n_digs_base_B * log(dos)) / log(base)));
  return ret;
}
} // namespace NumRepr
#endif //  BASE_NUM_T__HPP__INCLUDED
