#include "../include/dig_t.hpp"
#include "../include/digit_variant_t.hpp"
#include <concepts>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>
#include <variant>

namespace NumRepr
{

  digit_variant make_digit_variant(std::uint64_t Radix, std::int64_t value)
  {
    if ((Radix > 1) && (Radix < 66))
    {
      switch (Radix)
      {
      case 2:
        return digit_variant{dig_t<2>{value}};
      case 3:
        return digit_variant{dig_t<3>{value}};
      case 4:
        return digit_variant{dig_t<4>{value}};
      case 5:
        return digit_variant{dig_t<5>{value}};
      case 6:
        return digit_variant{dig_t<6>{value}};
      case 7:
        return digit_variant{dig_t<7>{value}};
      case 8:
        return digit_variant{dig_t<8>{value}};
      case 9:
        return digit_variant{dig_t<9>{value}};
      case 10:
        return digit_variant{dig_t<10>{value}};
      case 11:
        return digit_variant{dig_t<11>{value}};
      case 12:
        return digit_variant{dig_t<12>{value}};
      case 13:
        return digit_variant{dig_t<13>{value}};
      case 14:
        return digit_variant{dig_t<14>{value}};
      case 15:
        return digit_variant{dig_t<15>{value}};
      case 16:
        return digit_variant{dig_t<16>{value}};
      case 17:
        return digit_variant{dig_t<17>{value}};
      case 18:
        return digit_variant{dig_t<18>{value}};
      case 19:
        return digit_variant{dig_t<19>{value}};
      case 20:
        return digit_variant{dig_t<20>{value}};
      case 21:
        return digit_variant{dig_t<21>{value}};
      case 22:
        return digit_variant{dig_t<22>{value}};
      case 23:
        return digit_variant{dig_t<23>{value}};
      case 24:
        return digit_variant{dig_t<24>{value}};
      case 25:
        return digit_variant{dig_t<25>{value}};
      case 26:
        return digit_variant{dig_t<26>{value}};
      case 27:
        return digit_variant{dig_t<27>{value}};
      case 28:
        return digit_variant{dig_t<28>{value}};
      case 29:
        return digit_variant{dig_t<29>{value}};
      case 30:
        return digit_variant{dig_t<30>{value}};
      case 31:
        return digit_variant{dig_t<31>{value}};
      case 32:
        return digit_variant{dig_t<32>{value}};
      case 33:
        return digit_variant{dig_t<33>{value}};
      case 34:
        return digit_variant{dig_t<34>{value}};
      case 35:
        return digit_variant{dig_t<35>{value}};
      case 36:
        return digit_variant{dig_t<36>{value}};
      case 37:
        return digit_variant{dig_t<37>{value}};
      case 38:
        return digit_variant{dig_t<38>{value}};
      case 39:
        return digit_variant{dig_t<39>{value}};
      case 40:
        return digit_variant{dig_t<40>{value}};
      case 41:
        return digit_variant{dig_t<41>{value}};
      case 42:
        return digit_variant{dig_t<42>{value}};
      case 43:
        return digit_variant{dig_t<43>{value}};
      case 44:
        return digit_variant{dig_t<44>{value}};
      case 45:
        return digit_variant{dig_t<45>{value}};
      case 46:
        return digit_variant{dig_t<46>{value}};
      case 47:
        return digit_variant{dig_t<47>{value}};
      case 48:
        return digit_variant{dig_t<48>{value}};
      case 49:
        return digit_variant{dig_t<49>{value}};
      case 50:
        return digit_variant{dig_t<50>{value}};
      case 51:
        return digit_variant{dig_t<51>{value}};
      case 52:
        return digit_variant{dig_t<52>{value}};
      case 53:
        return digit_variant{dig_t<53>{value}};
      case 54:
        return digit_variant{dig_t<54>{value}};
      case 55:
        return digit_variant{dig_t<55>{value}};
      case 56:
        return digit_variant{dig_t<56>{value}};
      case 57:
        return digit_variant{dig_t<57>{value}};
      case 58:
        return digit_variant{dig_t<58>{value}};
      case 59:
        return digit_variant{dig_t<59>{value}};
      case 60:
        return digit_variant{dig_t<60>{value}};
      case 61:
        return digit_variant{dig_t<61>{value}};
      case 62:
        return digit_variant{dig_t<62>{value}};
      case 63:
        return digit_variant{dig_t<63>{value}};
      case 64:
        return digit_variant{dig_t<64>{value}};
      case 65:
        return digit_variant{dig_t<65>{value}};
      default:
        return digit_variant{dig_t<2>{0}};
      };
    }
    else
    {
      return digit_variant{dig_t<2>{0}};
    }
  }

  bool digit_variant::is_unit() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> bool
        {
          return (arg.is_unit());
        },
        *this);
  }

  bool digit_variant::is_0_divisor() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> bool
        {
          return (arg.is_0_divisor());
        },
        *this);
  }

  digit_variant digit_variant::mult_inv() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> digit_variant
        {
          return (arg.mult_inv());
        },
        *this);
  }

  digit_variant digit_variant::sum_carry(digit_variant arg_1, digit_variant arg_2) noexcept
  {
    return std::visit(
        []<std::uint64_t k, std::uint64_t l>(dig_t<k> left, const dig_t<l> right) -> digit_variant
        {
          if constexpr ((k == l) && (k > 1))
          {
            return sum_carry(left, right);
          }
          else
          {
            return dig_t<k>(0);
          }
        },
        arg_1, arg_2);
  }

  void digit_variant::set_0() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(dig_t<k> &arg) -> void
        {
          arg.set_0();
        },
        *this);
  }

  void digit_variant::set_1() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(dig_t<k> &arg) -> void
        {
          arg.set_1();
        },
        *this);
  }

  void digit_variant::set_Bm1() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(dig_t<k> &arg) -> void
        {
          arg.set_Bm1();
        },
        *this);
  }

  void digit_variant::set_Bm2() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(dig_t<k> &arg) -> void
        {
          arg.set_Bm2();
        },
        *this);
  }

  void digit_variant::set_dig(digit_variant left) noexcept
  {
    return std::visit(
        []<std::uint64_t k, std::uint64_t l>(dig_t<k> &argl, dig_t<l> argr) -> void
        {
          if constexpr (k == l)
            argl.set_dig(argr);
        },
        *this,
        left);
  }

  bool digit_variant::is_prime_base() const noexcept
  {
    return auxiliary_functions::is_prime(this->index());
  }

  digit_variant digit_variant::dig_max() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> digit_variant
        {
          return (arg.dig_Bm1());
        },
        *this);
  }

  digit_variant digit_variant::dig_submax() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> digit_variant
        {
          return (arg.dig_Bm2());
        },
        *this);
  }

  digit_variant digit_variant::dig_Bm1() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> digit_variant
        {
          return (arg.dig_Bm1());
        },
        *this);
  }

  digit_variant digit_variant::dig_Bm2() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> digit_variant
        {
          return (arg.dig_Bm2());
        },
        *this);
  }

  digit_variant digit_variant::dig_0() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> digit_variant
        {
          return (arg.dig_0());
        },
        *this);
  }

  digit_variant digit_variant::dig_1() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> digit_variant
        {
          return (arg.dig_1());
        },
        *this);
  }

  digit_variant::uint_t digit_variant::ui_max() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> auto
        {
          return (arg.ui_Bm1());
        },
        *this);
  }

  digit_variant::uint_t digit_variant::ui_submax() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> auto
        {
          return (arg.ui_Bm2());
        },
        *this);
  }

  digit_variant::uint_t digit_variant::ui_Bm1() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> auto
        {
          return (arg.ui_Bm1());
        },
        *this);
  }

  digit_variant::uint_t digit_variant::ui_Bm2() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> auto
        {
          return (arg.ui_Bm2());
        },
        *this);
  }

  digit_variant::uint_t digit_variant::ui_0() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> auto
        {
          return (arg.ui_0());
        },
        *this);
  }

  digit_variant::uint_t digit_variant::ui_1() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> auto
        {
          return (arg.ui_1());
        },
        *this);
  }

  bool digit_variant::is_0() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> bool
        {
          return (arg.is_0());
        },
        *this);
  }

  digit_variant::sig_uint_t digit_variant::sui_max() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> auto
        {
          return (arg.sui_max());
        },
        *this);
  }

  digit_variant::sig_uint_t digit_variant::sui_submax() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> auto
        {
          return (arg.sui_submax());
        },
        *this);
  }

  digit_variant::sig_uint_t digit_variant::sui_Bm1() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> auto
        {
          return (arg.sui_max());
        },
        *this);
  }

  digit_variant::sig_uint_t digit_variant::sui_Bm2() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> auto
        {
          return (arg.sui_submax());
        },
        *this);
  }

  digit_variant::sig_uint_t digit_variant::sui_0() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> auto
        {
          return (arg.sui_0());
        },
        *this);
  }

  digit_variant::sig_uint_t digit_variant::sui_1() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> auto
        {
          return (arg.sui_1());
        },
        *this);
  }

  digit_variant::sig_sint_t digit_variant::ssi_max() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> auto
        {
          return (arg.ssi_max());
        },
        *this);
  }

  digit_variant::sig_sint_t digit_variant::ssi_submax() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> auto
        {
          return (arg.ssi_submax());
        },
        *this);
  }

  digit_variant::sig_sint_t digit_variant::ssi_Bm1() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> auto
        {
          return (arg.ssi_max());
        },
        *this);
  }

  digit_variant::sig_sint_t digit_variant::ssi_Bm2() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> auto
        {
          return (arg.ssi_submax());
        },
        *this);
  }

  digit_variant::sig_sint_t digit_variant::ssi_0() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> auto
        {
          return (arg.ssi_0());
        },
        *this);
  }

  digit_variant::sig_sint_t digit_variant::ssi_1() noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> auto
        {
          return (arg.ssi_1());
        },
        *this);
  }

  bool digit_variant::is_not_0() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> bool
        {
          return (arg.is_not_0());
        },
        *this);
  }

  bool digit_variant::is_1() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> bool
        {
          return (arg.is_1());
        },
        *this);
  }

  bool digit_variant::is_not_1() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> bool
        {
          return (arg.is_not_1());
        },
        *this);
  }

  bool digit_variant::is_Bm1() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> bool
        {
          return (arg.is_Bm1());
        },
        *this);
  }

  bool digit_variant::is_not_Bm1() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> bool
        {
          return (arg.is_not_Bm1());
        },
        *this);
  }

  bool digit_variant::is_Bm1orBm2() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> bool
        {
          return (arg.is_Bm1orBm2());
        },
        *this);
  }

  bool digit_variant::is_not_Bm1orBm2() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> bool
        {
          return (arg.is_not_Bm1orBm2());
        },
        *this);
  }

  bool digit_variant::is_Bm2() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> bool
        {
          return (arg.is_Bm2());
        },
        *this);
  }

  bool digit_variant::is_not_Bm2() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> bool
        {
          return (arg.is_not_Bm2());
        },
        *this);
  }

  bool digit_variant::is_not_maxormin() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> bool
        {
          return (arg.is_not_maxormin());
        },
        *this);
  }

  bool digit_variant::is_maxormin() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> bool
        {
          return (arg.is_maxormin());
        },
        *this);
  }

  bool digit_variant::is_far_maxormin() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> bool
        {
          return (arg.is_far_maxormin());
        },
        *this);
  }

  bool digit_variant::is_near_maxormin() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> bool
        {
          return (arg.is_near_maxormin());
        },
        *this);
  }

  bool digit_variant::is_0or1() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> bool
        {
          return (arg.is_0or1());
        },
        *this);
  }

  bool digit_variant::is_not_0or1() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> bool
        {
          return (arg.is_not_0or1());
        },
        *this);
  }

  digit_variant digit_variant::C_Bm1() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> digit_variant
        {
          return (arg.C_Bm1());
        },
        *this);
  }

  const digit_variant &digit_variant::mC_Bm1() noexcept
  {
    auto fn =
        []<std::uint64_t k>(dig_t<k> &arg) -> void
    { arg.mC_Bm1(); };
    std::visit(fn, *this);
    return (*this);
  }

  digit_variant digit_variant::C_B() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> digit_variant
        {
          return (arg.C_B());
        },
        *this);
  }

  const digit_variant &digit_variant::mC_B() noexcept
  {
    auto fn =
        []<std::uint64_t k>(dig_t<k> &arg) -> void
    { arg.mC_B(); };
    std::visit(fn, *this);
    return (*this);
  }

  std::string digit_variant::to_string() const noexcept
  {
    return std::visit(
        []<std::uint64_t k>(const dig_t<k> &arg) -> std::string
        {
          if constexpr (k > 1)
            return arg.to_string();
          else
            return std::string("");
        },
        *this);
  }

  // bool digit_variant::from_string(const std::string& source)
  //{
  //   return
  //       std::visit(
  //           [source]<uint32_t k>(dig_t<k>& arg){
  //               if constexpr (k > 1)
  //                   return arg.from_string(source);
  //               else
  //                   return false;
  //           } ,
  //           *this
  //       );
  // }

  std::uint64_t digit_variant::radix() const noexcept
  {
    return (this->index() + 2);
  }

  std::strong_ordering digit_variant::operator<=>(digit_variant rhs) const noexcept
  {
    return std::visit(
        []<std::uint64_t k, std::uint64_t l>(
            const dig_t<k> &left, dig_t<l> right) -> std::strong_ordering
        {
          if constexpr ((k == l) && (k > 1))
          { // CASOS COMPARABLES
            return (left <=> right);
          }
          else
          { // CASOS INCOMPARABLES
            return std::strong_ordering::equivalent;
          }
        },     // FIN DE DEFINICION DE LA FUNCION LAMBDA
        *this, // ARGUMENTO 1
        rhs    // ARGUMENTO 2
        )      // FIN DEL VISIT
        ;      // FIN DEL RETURN
  } // FIN DE LA FUNCION OPERATOR==() -> STRONG_ORDERING

  bool digit_variant::operator==(digit_variant otro) const noexcept
  {
    return std::visit(
        []<std::uint64_t k, std::uint64_t l>(
            const dig_t<k> &left, dig_t<l> right) -> bool
        {
          if constexpr ((k == l) && (k > 1))
          { // CASOS COMPARABLES
            return (left == right);
          }
          else
          { // CASOS INCOMPARABLES
            return false;
          }
        },     // FIN DE DEFINICION DE LA FUNCION LAMBDA
        *this, // ARGUMENTO 1
        otro   // ARGUMENTO 2
        )      // FIN DEL VISIT
        ;      // FIN DEL RETURN
  } // FIN DE LA FUNCION OPERATOR==() -> BOOL

  template <type_traits::integral_c Int_t>

  bool digit_variant::operator==(Int_t rhs) const noexcept
  {
    return std::visit(
        []<std::uint64_t k, std::uint64_t l>(
            const dig_t<k> &left, Int_t right) -> bool
        {
          if constexpr ((k == l) && (k > 1))
          { // CASOS COMPARABLES
            return (left == right);
          }
          else
          { // CASOS INCOMPARABLES
            return false;
          }
        },     // FIN DE DEFINICION DE LA FUNCION LAMBDA
        *this, // ARGUMENTO 1
        rhs    // ARGUMENTO 2
        )      // FIN DEL VISIT
        ;      // FIN DEL RETURN
  } // FIN DE LA FUNCION OPERATOR==() -> BOOL

  template <type_traits::integral_c Int_t>

  bool digit_variant::operator!=(Int_t rhs) const noexcept
  {
    return std::visit(
        []<std::uint64_t k, std::uint64_t l>(
            const dig_t<k> &left, Int_t right) -> bool
        {
          if constexpr ((k == l) && (k > 1))
          { // CASOS COMPARABLES
            return (left != right);
          }
          else
          { // CASOS INCOMPARABLES
            return false;
          }
        },     // FIN DE DEFINICION DE LA FUNCION LAMBDA
        *this, // ARGUMENTO 1
        rhs    // ARGUMENTO 2
        )      // FIN DEL VISIT
        ;      // FIN DEL RETURN
  } // FIN DE LA FUNCION OPERATOR==() -> BOOL

  template <type_traits::integral_c Int_t>

  bool digit_variant::operator<(Int_t rhs) const noexcept
  {
    return std::visit(
        []<std::uint64_t k, std::uint64_t l>(
            const dig_t<k> &left, Int_t right) -> bool
        {
          if constexpr ((k == l) && (k > 1))
          { // CASOS COMPARABLES
            return (left < right);
          }
          else
          { // CASOS INCOMPARABLES
            return false;
          }
        },     // FIN DE DEFINICION DE LA FUNCION LAMBDA
        *this, // ARGUMENTO 1
        rhs    // ARGUMENTO 2
        )      // FIN DEL VISIT
        ;      // FIN DEL RETURN
  } // FIN DE LA FUNCION OPERATOR==() -> BOOL

  template <type_traits::integral_c Int_t>

  bool digit_variant::operator<=(Int_t rhs) const noexcept
  {
    return std::visit(
        []<std::uint64_t k, std::uint64_t l>(
            const dig_t<k> &left, Int_t right) -> bool
        {
          if constexpr ((k == l) && (k > 1))
          { // CASOS COMPARABLES
            return (left <= right);
          }
          else
          { // CASOS INCOMPARABLES
            return false;
          }
        },     // FIN DE DEFINICION DE LA FUNCION LAMBDA
        *this, // ARGUMENTO 1
        rhs    // ARGUMENTO 2
        )      // FIN DEL VISIT
        ;      // FIN DEL RETURN
  } // FIN DE LA FUNCION OPERATOR==() -> BOOL

  template <type_traits::integral_c Int_t>

  bool digit_variant::operator>(Int_t rhs) const noexcept
  {
    return std::visit(
        []<std::uint64_t k, std::uint64_t l>(
            const dig_t<k> &left, Int_t right) -> bool
        {
          if constexpr ((k == l) && (k > 1))
          { // CASOS COMPARABLES
            return (left > right);
          }
          else
          { // CASOS INCOMPARABLES
            return false;
          }
        },     // FIN DE DEFINICION DE LA FUNCION LAMBDA
        *this, // ARGUMENTO 1
        rhs    // ARGUMENTO 2
        )      // FIN DEL VISIT
        ;      // FIN DEL RETURN
  } // FIN DE LA FUNCION OPERATOR==() -> BOOL

  template <type_traits::integral_c Int_t>

  bool digit_variant::operator>=(Int_t rhs) const noexcept
  {
    return std::visit(
        []<std::uint64_t k, std::uint64_t l>(
            const dig_t<k> &left, Int_t right) -> bool
        {
          if constexpr ((k == l) && (k > 1))
          { // CASOS COMPARABLES
            return (left >= right);
          }
          else
          { // CASOS INCOMPARABLES
            return false;
          }
        },     // FIN DE DEFINICION DE LA FUNCION LAMBDA
        *this, // ARGUMENTO 1
        rhs    // ARGUMENTO 2
        )      // FIN DEL VISIT
        ;      // FIN DEL RETURN
  } // FIN DE LA FUNCION OPERATOR==() -> BOOL

  template <type_traits::integral_c Int_t>

  std::weak_ordering digit_variant::operator<=>(Int_t rhs) const noexcept
  {
    return std::visit(
        []<std::uint64_t k, std::uint64_t l>(
            const dig_t<k> &left, Int_t right) -> std::weak_ordering
        {
          if constexpr ((k == l) && (k > 1))
          { // CASOS COMPARABLES
            return (left <=> right);
          }
          else
          { // CASOS INCOMPARABLES
            return std::weak_ordering::equivalent;
          }
        },     // FIN DE DEFINICION DE LA FUNCION LAMBDA
        *this, // ARGUMENTO 1
        rhs    // ARGUMENTO 2
        )      // FIN DEL VISIT
        ;      // FIN DEL RETURN
  } // FIN DE LA FUNCION OPERATOR==() -> BOOL

  bool digit_variant::operator!=(digit_variant otro) const noexcept
  {
    return std::visit(
        []<std::uint64_t k, std::uint64_t l>(
            const dig_t<k> &left, const dig_t<l> &right) -> bool
        {
          if constexpr ((k == l) && (k > 1))
          { // CASOS COMPARABLES
            return (left != right);
          }
          else
          { // CASOS INCOMPARABLES
            return false;
          }
        },     // FIN DE DEFINICION DE LA FUNCION LAMBDA
        *this, // ARGUMENTO 1
        otro   // ARGUMENTO 2
        )      // FIN DEL VISIT
        ;      // FIN DEL RETURN
  } // FIN DE LA FUNCION OPERATOR!= -> BOOL

  bool digit_variant::operator<(digit_variant otro) const noexcept
  {
    return std::visit(
        []<std::uint64_t k, std::uint64_t l>(
            const dig_t<k> &left, const dig_t<l> &right) -> bool
        {
          if constexpr ((k == l) && (k > 1))
          { // CASOS COMPARABLES
            return (left < right);
          }
          else
          { // CASOS INCOMPARABLES
            return false;
          }
        },     // FIN DE DEFINICION DE LA FUNCION LAMBDA
        *this, // ARGUMENTO 1
        otro   // ARGUMENTO 2
        )      // FIN DEL VISIT
        ;      // FIN DEL RETURN
  } // FIN DE LA FUNCION OPERATOR== -> BOOL

  bool digit_variant::operator<=(digit_variant otro) const noexcept
  {
    return std::visit(
        []<std::uint64_t k, std::uint64_t l>(
            const dig_t<k> &left, const dig_t<l> &right) -> bool
        {
          if constexpr ((k == l) && (k > 1))
          { // CASOS COMPARABLES
            return (left <= right);
          }
          else
          { // CASOS INCOMPARABLES
            return false;
          }
        },     // FIN DE DEFINICION DE LA FUNCION LAMBDA
        *this, // ARGUMENTO 1
        otro   // ARGUMENTO 2
        )      // FIN DEL VISIT
        ;      // FIN DEL RETURN
  } // FIN DE LA FUNCION OPERATOR<= -> BOOL

  bool digit_variant::operator>(digit_variant otro) const noexcept
  {
    return std::visit(
        []<std::uint64_t k, std::uint64_t l>(
            const dig_t<k> &left, const dig_t<l> &right) -> bool
        {
          if constexpr ((k == l) && (k > 1))
          { // CASOS COMPARABLES
            return (left > right);
          }
          else
          { // CASOS INCOMPARABLES
            return false;
          }
        },     // FIN DE DEFINICION DE LA FUNCION LAMBDA
        *this, // ARGUMENTO 1
        otro   // ARGUMENTO 2
        )      // FIN DEL VISIT
        ;      // FIN DEL RETURN
  } // FIN DE LA FUNCION OPERATOR> -> BOOL

  bool digit_variant::operator>=(digit_variant otro) const noexcept
  {
    return std::visit(
        []<std::uint64_t k, std::uint64_t l>(
            const dig_t<k> &left, const dig_t<l> &right) -> bool
        {
          if constexpr ((k == l) && (k > 1))
          { // CASOS COMPARABLES
            return (left >= right);
          }
          else
          { // CASOS INCOMPARABLES
            return false;
          }
        },     // FIN DE DEFINICION DE LA FUNCION LAMBDA
        *this, // ARGUMENTO 1
        otro   // ARGUMENTO 2
        )      // FIN DEL VISIT
        ;      // FIN DEL RETURN
  } // FIN DE LA FUNCION OPERATOR>= -> BOOL

  //  const digit_variant& operator++() noexcept;
  const digit_variant &digit_variant::operator++() noexcept
  {
    auto fn =
        []<std::uint64_t k>(dig_t<k> &arg) -> void
    { ++arg; };
    std::visit(fn, *this);
    return (*this);
  } // FIN DE LA FUNCION OPERATOR++()

  // const digit_variant& operator--() noexcept;
  const digit_variant &digit_variant::operator--() noexcept
  {
    auto fn =
        []<std::uint64_t k>(dig_t<k> &arg) -> void
    {
      --arg;
    };
    std::visit(fn, *this);
    return (*this);
  } // FIN DE LA FUNCION OPERATOR--()

  // digit_variant operator++(int) noexcept;
  digit_variant digit_variant::operator++(int) noexcept
  {
    digit_variant result{};
    auto fn = [&result]<std::uint64_t K>(dig_t<K> &left) -> void
    {
      result = (left++);
    };
    std::visit(fn, *this);
    return result;
  }

  // digit_variant operator--(int) noexcept;
  digit_variant digit_variant::operator--(int) noexcept
  {
    digit_variant result{};
    auto fn = [&result]<std::uint64_t K>(dig_t<K> &left) -> void
    {
      result = (left--);
    };
    std::visit(fn, *this);
    return result;
  }

  const digit_variant &digit_variant::operator|=(
      digit_variant otro) noexcept
  {

    std::visit(
        []<std::uint64_t k, std::uint64_t l>(dig_t<k> &left, const dig_t<l> &right)
        {
          if constexpr ((k == l) && (k > 1))
          {
            left |= right;
          }
        },
        *this,
        otro);
    return (*this);
  }

  const digit_variant &digit_variant::operator&=(
      digit_variant otro) noexcept
  {
    std::visit(
        []<std::uint64_t k, std::uint64_t l>(dig_t<k> &left, const dig_t<l> &right)
        {
          if constexpr ((k == l) && (k > 1))
          {
            left &= right;
          }
        },
        *this,
        otro);
    return (*this);
  }

  //
  // const digit_variant& digit_variant::operator^=(
  //    digit_variant otro
  //  ) noexcept {
  //  std::visit(
  //    []<std::uint64_t k, std::uint64_t l>(dig_t<k>& left,const dig_t<l>& right) {
  //      if constexpr ((k == l) && (k > 1)) {
  //        left ^= right;
  //      }
  //    },
  //    *this,
  //    otro
  //  );
  //  return (*this);
  //}

  digit_variant digit_variant::operator|(const digit_variant &otro) const noexcept
  {
    digit_variant ret{};
    auto fn = [&ret]<std::uint64_t K, std::uint64_t L>(const dig_t<K> &left, const dig_t<L> &right) -> void
    {
      if constexpr ((K == L) && (K > 1))
        ret = (left | right);
    };
    std::visit(fn, *this, otro);
    return ret;
  }

  digit_variant digit_variant::operator&(const digit_variant &otro) const noexcept
  {
    digit_variant ret{};
    auto fn = [&ret]<std::uint64_t K, std::uint64_t L>(const dig_t<K> &left, const dig_t<L> &right) -> void
    {
      if constexpr ((K == L) && (K > 1))
        ret.emplace<dig_t<K>>(left & right);
    };
    std::visit(fn, *this, otro);
    return ret;
  }

  //
  // digit_variant digit_variant::operator^(digit_variant otro) const  noexcept
  //{
  //  digit_variant ret{};
  //  auto fn = [&ret]<std::uint64_t K,std::uint64_t L>(const dig_t<K>& left,dig_t<L> right) -> void {
  //       if constexpr ((K == L)&&(K > 1))
  //            ret.emplace<dig_t<K>>(left ^ right);
  //  };
  //  std::visit(fn,*this,otro);
  //  return ret;
  //}

  //
  // const digit_variant& digit_variant::operator>>=(std::size_t n)  noexcept  {
  //  std::visit(
  //    [n]<std::uint64_t k>(dig_t<k>& arg) -> void {
  //        arg >>= n;
  //    },
  //    *this
  //  );
  //  return (*this);
  //}

  //
  // const digit_variant& digit_variant::operator<<=(std::size_t n)  noexcept  {
  //  std::visit(
  //    [n]<std::uint64_t k>(dig_t<k>& arg) -> void {
  //        arg <<= n;
  //    },
  //    *this
  //  );
  //  return (*this);
  //}

  //
  // digit_variant digit_variant::operator<<(std::size_t n) const noexcept   {
  //    digit_variant result{};
  //    auto fn = [&result,n]<std::uint64_t K>(const dig_t<K>& left) {
  //        if   constexpr ( K > 1 )  {
  //                result = (left << n);
  //        }
  //    };
  //    std::visit(fn , *this);
  //    return result;
  //}

  //
  // digit_variant digit_variant::operator>>(std::size_t n) const  noexcept  {
  //    digit_variant result{};
  //    auto fn = [&result,n]<std::uint64_t K>(const dig_t<K>& left) {
  //        if   constexpr ( K > 1 )  {
  //                result = (left >> n);
  //        }
  //    };
  //    std::visit(fn , *this);
  //    return result;
  //}

  const digit_variant &digit_variant::operator+=(digit_variant otro) noexcept
  {
    auto fn =
        []<std::uint64_t k, std::uint64_t l>(dig_t<k> &left, dig_t<l> right) -> void
    {
      if constexpr (k == l)
        left += right;
    };
    std::visit(fn, *this, otro);
    return (*this);
  }

  const digit_variant &digit_variant::operator-=(digit_variant otro) noexcept
  {
    auto fn =
        []<std::uint64_t k, std::uint64_t l>(dig_t<k> &left, dig_t<l> right) -> void
    {
      if constexpr (k == l)
      {
        left -= right;
      }
    };
    std::visit(fn, *this, otro);
    return (*this);
  }

  const digit_variant &digit_variant::operator*=(digit_variant otro) noexcept
  {
    auto fn =
        []<std::uint64_t k, std::uint64_t l>(dig_t<k> &left, dig_t<l> right) -> void
    {
      if constexpr (k == l)
      {
        left *= right;
      }
    };
    std::visit(fn, *this, otro);
    return (*this);
  }

  const digit_variant &digit_variant::operator/=(digit_variant otro) noexcept
  {
    auto fn =
        []<std::uint64_t k, std::uint64_t l>(dig_t<k> &left, dig_t<l> right) -> void
    {
      if constexpr (k == l)
      {
        left /= right;
      }
    };
    std::visit(fn, *this, otro);
    return (*this);
  }

  const digit_variant &digit_variant::operator%=(digit_variant otro) noexcept
  {
    auto fn =
        []<std::uint64_t k, std::uint64_t l>(dig_t<k> &left, dig_t<l> right) -> void
    {
      if constexpr (k == l)
      {
        left %= right;
      }
    };
    std::visit(fn, *this, otro);
    return (*this);
  }

  digit_variant digit_variant::operator+(digit_variant other) const noexcept
  {
    digit_variant result{};
    auto fn = [&result]<std::uint64_t K, std::uint64_t L>(const dig_t<K> &left, dig_t<L> right)
    {
      if constexpr ((K == L) && (K > 1) && (L > 1))
      {
        result = left + right;
      }
    };
    std::visit(fn, *this, other);
    return result;
  }

  digit_variant digit_variant::operator-(digit_variant other) const noexcept
  {
    digit_variant result{};
    auto fn = [&result]<std::uint64_t K, std::uint64_t L>(const dig_t<K> &left, dig_t<L> right)
    {
      if constexpr ((K == L) && (K > 1) && (L > 1))
      {
        result = left - right;
      }
    };
    std::visit(fn, *this, other);
    return result;
  }

  digit_variant digit_variant::operator*(digit_variant other) const noexcept
  {
    digit_variant result{};
    auto fn = [&result]<std::uint64_t K, std::uint64_t L>(const dig_t<K> &left, dig_t<L> right)
    {
      if constexpr ((K == L) && (K > 1) && (L > 1))
      {
        result = left * right;
      }
    };
    std::visit(fn, *this, other);
    return result;
  }

  digit_variant digit_variant::operator/(digit_variant other) const noexcept
  {
    digit_variant result{};
    auto fn = [&result]<std::uint64_t K, std::uint64_t L>(const dig_t<K> &left, dig_t<L> right)
    {
      if constexpr ((K == L) && (K > 1) && (L > 1))
      {
        if (right.is_not_0())
          result = left / right;
      }
    };
    std::visit(fn, *this, other);
    return result;
  }

  digit_variant digit_variant::operator%(digit_variant other) const noexcept
  {
    digit_variant result{};
    auto fn = [&result]<std::uint64_t K, std::uint64_t L>(const dig_t<K> &left, dig_t<L> right)
    {
      if constexpr ((K == L) && (K > 1) && (L > 1))
      {
        if (right.is_not_0())
          result = left % right;
      }
    };
    std::visit(fn, *this, other);
    return result;
  }

  //
  // digit_variant digit_variant::operator+() const  noexcept {
  //  return digit_variant{*this};
  //}

  digit_variant digit_variant::operator~() const noexcept
  {
    digit_variant result{};
    std::visit(
        [&result]<std::uint64_t k>(const dig_t<k> &arg) -> void
        {
          result.emplace<dig_t<k>>(arg.C_Bm1());
        },
        *this);
    return result;
  }

  digit_variant digit_variant::operator-() const noexcept
  {
    digit_variant result{};
    std::visit(
        [&result]<std::uint64_t k>(const dig_t<k> &arg) -> void
        {
          result.emplace<dig_t<k>>(-arg);
        },
        *this);
    return result;
  }

  std::ostream &operator<<(std::ostream &os, const digit_variant &arg)
  {
    auto fn = [&os]<std::uint64_t K>(const dig_t<K> &to_out) -> void
    {
      os << to_out;
    };
    std::visit(fn, arg);
    return os;
  }

  std::istream &operator>>(std::istream &is, digit_variant &arg)
  {
    auto fn = [&is]<std::uint64_t K>(dig_t<K> &from_in) -> void
    {
      is >> from_in;
    };
    std::visit(fn, arg);
    return is;
  }

} // END OF NAMESPACE UINTVAR
