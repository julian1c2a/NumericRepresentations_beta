#ifndef BASIC_TYPES_HPP_INCLUDED
#define BASIC_TYPES_HPP_INCLUDED

#include <cstdint>

#include <compare>

#include <type_traits>

#include <concepts>

#include <optional>
#include <expected>
#if __has_include(<expected>)
#  include <expected>
#else
#  include <variant>
#  include <utility>
namespace std {
  template <typename E>
  struct unexpected {
    E value_;
    explicit unexpected(E v) : value_(v) {}
    E error() const noexcept { return value_; }
  };

  template <typename T, typename E>
  class expected {
    std::variant<T, E> v_;
  public:
    expected(const T &t) : v_(t) {}
    expected(T &&t) : v_(std::move(t)) {}
    expected(std::unexpected<E> ue) : v_(ue.value_) {}
    bool has_value() const noexcept { return std::holds_alternative<T>(v_); }
    explicit operator bool() const noexcept { return has_value(); }
    T &value() { return std::get<T>(v_); }
    const T &value() const { return std::get<T>(v_); }
    E error() const { return std::get<E>(v_); }
  };

  template <typename E>
  std::unexpected<E> unexpected(E e) { return std::unexpected<E>(e); }
}
#endif

#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

#include <array>
#include <list>
#include <map>
#include <vector>

#include <climits>
#include <cmath>
#include <limits>
#include <numeric>

#include <functional>
#include <iterator>

/**
 * @file basic_types.hpp
 * @brief Tipos básicos y meta-funciones para el sistema de representaciones numéricas
 */
namespace NumRepr {
  using chint_t = char;
  using schint_t = signed char;
  using ssint_t = signed short int;
  using sint_t = signed int;
  using slint_t = signed long int;
  using sllint_t = signed long long int;
  using uchint_t = unsigned char;
  using usint_t = unsigned short int;
  using uint_t = unsigned int;
  using ulint_t = unsigned long int;
  using ullint_t = unsigned long long int;

  /* Compatibility aliases (old names without _t) */
  using schint = schint_t;
  using ssint = ssint_t;
  using sint = sint_t;
  using slint = slint_t;
  using sllint = sllint_t;
  using uchint = uchint_t;
  using usint = usint_t;
  using uint = uint_t;
  using ulint = ulint_t;
  using ullint = ullint_t;

#if defined(__GNUC__) && !defined(__clang__)
  using uint128_t = __uint128_t;
  using sint128_t = __int128_t;
#elif defined(__clang__)
#if __has_extension(int128)
  using uint128_t = __uint128_t;
  using sint128_t = __int128_t;
#else
  struct uint128_t { std::uint64_t low, high; };
  struct sint128_t { std::uint64_t low; std::int64_t high; };
#endif
#elif defined(_MSC_VER)
  struct uint128_t { std::uint64_t low, high; };
  struct sint128_t { std::uint64_t low; std::int64_t high; };
#else
  struct uint128_t { std::uint64_t low, high; };
  struct sint128_t { std::uint64_t low; std::int64_t high; };
#endif

  using size_t = std::size_t;
  using sint8_t = std::int8_t;
  using sint16_t = std::int16_t;
  using sint32_t = std::int32_t;
  using sint64_t = std::int64_t;
  using int8_t = std::int8_t;
  using int16_t = std::int16_t;
  using int32_t = std::int32_t;
  using int64_t = std::int64_t;
  using fast8_t = std::int_fast8_t;
  using fast16_t = std::int_fast16_t;
  using fast32_t = std::int_fast32_t;
  using fast64_t = std::int_fast64_t;
  using least8_t = std::int_least8_t;
  using least16_t = std::int_least16_t;
  using least32_t = std::int_least32_t;
  using least64_t = std::int_least64_t;
  using uint8_t = std::uint8_t;
  using uint16_t = std::uint16_t;
  using uint32_t = std::uint32_t;
  using uint64_t = std::uint64_t;
  using ufast8_t = std::uint_fast8_t;
  using ufast16_t = std::uint_fast16_t;
  using ufast32_t = std::uint_fast32_t;
  using ufast64_t = std::uint_fast64_t;
  using uleast8_t = std::uint_least8_t;
  using uleast16_t = std::uint_least16_t;
  using uleast32_t = std::uint_least32_t;
  using uleast64_t = std::uint_least64_t;
  using intmax_t = std::intmax_t;
  using uintmax_t = std::uintmax_t;

  namespace type_traits {

    template <typename IntT>
    concept arith_integral_c =
        std::is_arithmetic_v<IntT> && std::is_integral_v<IntT>;

    template <typename NatIntT>
    concept arith_natural_c =
        std::is_arithmetic_v<NatIntT> && std::is_unsigned_v<NatIntT> &&
        std::is_integral_v<NatIntT>;

    template <typename CharT>
    concept char_type_c =
        std::is_same_v<CharT, char> || std::is_same_v<CharT, signed char> ||
        std::is_same_v<CharT, unsigned char> || std::is_same_v<CharT, wchar_t>;

    template <char_type_c CharT>
    constexpr inline CharT nullchar{CharT('\0')};

    inline constexpr ullint_t atoull(const char *text) noexcept {
      ullint_t i = 0;
      while (*text) {
        i = (i << 3) + (i << 1) + static_cast<ullint_t>(*text - '0');
        ++text;
      }
      return i;
    }

    inline constexpr ullint_t atoull(std::string_view sv) noexcept {
      ullint_t i = 0;
      for (char c : sv) {
        i = (i << 3) + (i << 1) + static_cast<ullint_t>(c - '0');
      }
      return i;
    }

    enum class atoull_err_t : int { empty_str, no_digit, overflow, unknown };

    inline std::expected<ullint_t, atoull_err_t> atoull_checked(const char *text) noexcept {
      if (text == nullptr) return std::unexpected(atoull_err_t::empty_str);
      ullint_t i = 0;
      bool any = false;
      constexpr ullint_t maxv = std::numeric_limits<ullint_t>::max();
      while (*text) {
        char c = *text;
        if (c < '0' || c > '9') return std::unexpected(atoull_err_t::no_digit);
        unsigned digit = static_cast<unsigned>(c - '0');
        if (i > (maxv - digit) / 10) return std::unexpected(atoull_err_t::overflow);
        i = i * 10 + digit;
        any = true;
        ++text;
      }
      if (!any) return std::unexpected(atoull_err_t::empty_str);
      return std::expected<ullint_t, atoull_err_t>(i);
    }

    inline std::expected<ullint_t, atoull_err_t> atoull_checked(std::string_view sv) noexcept {
      if (sv.data() == nullptr || sv.size() == 0) return std::unexpected(atoull_err_t::empty_str);
      ullint_t i = 0;
      bool any = false;
      constexpr ullint_t maxv = std::numeric_limits<ullint_t>::max();
      for (char c : sv) {
        if (c < '0' || c > '9') return std::unexpected(atoull_err_t::no_digit);
        unsigned digit = static_cast<unsigned>(c - '0');
        if (i > (maxv - digit) / 10) return std::unexpected(atoull_err_t::overflow);
        i = i * 10 + digit;
        any = true;
      }
      if (!any) return std::unexpected(atoull_err_t::empty_str);
      return std::expected<ullint_t, atoull_err_t>(i);
    }

    inline std::expected<std::pair<ullint_t, size_t>, atoull_err_t> atoull_consume(const char *text) noexcept {
      if (text == nullptr) return std::unexpected(atoull_err_t::empty_str);
      ullint_t i = 0;
      size_t idx = 0;
      constexpr ullint_t maxv = std::numeric_limits<ullint_t>::max();
      while (text[idx]) {
        char c = text[idx];
        if (c < '0' || c > '9') break;
        unsigned digit = static_cast<unsigned>(c - '0');
        if (i > (maxv - digit) / 10) return std::unexpected(atoull_err_t::overflow);
        i = i * 10 + digit;
        ++idx;
      }
      if (idx == 0) return std::unexpected(atoull_err_t::no_digit);
      return std::expected<std::pair<ullint_t, size_t>, atoull_err_t>(std::pair<ullint_t, size_t>{i, idx});
    }

    inline std::expected<std::pair<ullint_t, size_t>, atoull_err_t> atoull_consume(std::string_view sv) noexcept {
      if (sv.data() == nullptr || sv.size() == 0) return std::unexpected(atoull_err_t::empty_str);
      ullint_t i = 0;
      size_t idx = 0;
      constexpr ullint_t maxv = std::numeric_limits<ullint_t>::max();
      while (idx < sv.size()) {
        char c = sv[idx];
        if (c < '0' || c > '9') break;
        unsigned digit = static_cast<unsigned>(c - '0');
        if (i > (maxv - digit) / 10) return std::unexpected(atoull_err_t::overflow);
        i = i * 10 + digit;
        ++idx;
      }
      if (idx == 0) return std::unexpected(atoull_err_t::no_digit);
      return std::expected<std::pair<ullint_t, size_t>, atoull_err_t>(std::pair<ullint_t, size_t>{i, idx});
    }

    template <typename UINT_T>
    constexpr bool is_uint_type_for_radix_v =
        std::is_unsigned_v<UINT_T> && (!std::is_same_v<UINT_T, uint64_t>);

    template <typename UINT_T>
    concept uint_type_for_radix_c = is_uint_type_for_radix_v<UINT_T>;

    template <typename UINT_T>
    constexpr bool is_unsigned_type_v =
        is_uint_type_for_radix_v<UINT_T> || std::is_same_v<UINT_T, std::uint64_t>;

    template <typename UINT_T>
    concept unsigned_integral_c = is_unsigned_type_v<UINT_T>;

    template <typename SINT_T>
    constexpr bool is_signed_type_v =
        std::is_signed_v<SINT_T> || std::is_same_v<SINT_T, sint64_t>;

    template <typename SINT_T>
    concept signed_integral_c = is_signed_type_v<SINT_T>;

    template <typename INT_TYPE>
    inline constexpr bool is_integral_type_v = std::is_integral_v<INT_TYPE>;
    template <typename INT_T>
    concept integral_c = is_integral_type_v<INT_T>;

    template <typename T, typename S>
    constexpr bool eq_sz_v = (sizeof(T) == sizeof(S));
    template <typename T, typename S>
    constexpr bool gt_sz_v = (sizeof(T) > sizeof(S));
    template <typename T, typename S>
    constexpr bool lt_sz_v = (sizeof(T) < sizeof(S));
    template <typename T, typename S>
    constexpr bool ge_sz_v = gt_sz_v<T, S> || eq_sz_v<T, S>;
    template <typename T, typename S>
    constexpr bool le_sz_v = lt_sz_v<T, S> || eq_sz_v<T, S>;

    namespace ugly_details_UInt_for_UInt {

      template <unsigned_integral_c UInt_t>
      struct __sig_UInt_for_UInt_t { using type = void; };

      template <>
      struct __sig_UInt_for_UInt_t<ullint_t> { using type = uint64_t; };

      template <>
      struct __sig_UInt_for_UInt_t<ulint_t> {
        template <unsigned_integral_c uint_type>
        static inline constexpr bool uint_type_gt_this_type_v =
            gt_sz_v<uint_type, ulint_t>;

        using type = typename std::conditional_t<
            uint_type_gt_this_type_v<ullint_t>, 
                ullint_t,
                typename __sig_UInt_for_UInt_t<ullint_t>::type
            >;
      };

      template <>
      struct __sig_UInt_for_UInt_t<uint_t> {
        template <unsigned_integral_c uint_type>
        static inline constexpr bool uint_type_gt_this_type_v =
            gt_sz_v<uint_type, uint_t>;

    using type = std::conditional_t<uint_type_gt_this_type_v<ulint_t>,
                    ulint_t,
                    typename __sig_UInt_for_UInt_t<ulint_t>::type>;
      };

      template <>
      struct __sig_UInt_for_UInt_t<usint_t> {
        template <unsigned_integral_c uint_type>
        static inline constexpr bool uint_type_gt_this_type_v =
            gt_sz_v<uint_type, usint_t>;

        using type = std::conditional_t<
            uint_type_gt_this_type_v<uint_t>, 
                uint_t,
                typename __sig_UInt_for_UInt_t<uint_t>::type
        >;
      };

      template <>
      struct __sig_UInt_for_UInt_t<uchint_t> {
        template <unsigned_integral_c uint_type>
        static inline constexpr bool uint_type_gt_this_type_v =
            gt_sz_v<uint_type, uchint_t>;

        using type =
            std::conditional_t<
                uint_type_gt_this_type_v<usint_t>, 
                    usint_t,
                    typename __sig_UInt_for_UInt_t<usint_t>::type>;
      };

    } // namespace ugly_details_UInt_for_UInt

    template <typename UInt_t>
    using sig_UInt_for_UInt_t =
        typename ugly_details_UInt_for_UInt::__sig_UInt_for_UInt_t<UInt_t>::type;

    namespace ugly_details_sig_SInt_for_UInt {
      template <typename UInt>
      struct __sig_SInt_for_UInt_t { using type = void; };

      template <>
      struct __sig_SInt_for_UInt_t<ullint_t> { using type = sint64_t; };

      template <>
      struct __sig_SInt_for_UInt_t<ulint_t> {
        template <typename int_type>
        static inline constexpr bool int_type_gt_this_type_v =
            gt_sz_v<int_type, ulint_t>;

        using type =
            std::conditional_t<int_type_gt_this_type_v<sllint_t>, sllint_t,
                               typename __sig_SInt_for_UInt_t<ullint_t>::type>;
      };

      template <>
      struct __sig_SInt_for_UInt_t<uint_t> {
        template <typename int_type>
        static inline constexpr bool int_type_gt_this_type_v =
            gt_sz_v<int_type, uint_t>;

        using type =
            std::conditional_t<int_type_gt_this_type_v<slint_t>, slint_t,
                               typename __sig_SInt_for_UInt_t<ulint_t>::type>;
      };

      template <>
      struct __sig_SInt_for_UInt_t<usint_t> {
        template <typename int_type>
        static inline constexpr bool int_type_gt_this_type_v =
            gt_sz_v<int_type, usint_t>;

        using type = std::conditional_t<int_type_gt_this_type_v<sint_t>, sint_t,
                                        typename __sig_SInt_for_UInt_t<uint_t>::type>;
      };

      template <>
      struct __sig_SInt_for_UInt_t<uchint_t> {
        template <typename int_type>
        static inline constexpr bool int_type_gt_this_type_v =
            gt_sz_v<int_type, uchint_t>;

        using type =
            std::conditional_t<int_type_gt_this_type_v<ssint_t>, ssint_t,
                               typename __sig_SInt_for_UInt_t<usint_t>::type>;
      };

    } // namespace ugly_details_sig_SInt_for_UInt

    template <typename UInt_t>
    using sig_SInt_for_UInt_t =
        typename ugly_details_sig_SInt_for_UInt::__sig_SInt_for_UInt_t<UInt_t>::type;

    namespace ugly_details_UInt_for_SInt {
      template <typename SInt>
      struct __sig_UInt_for_SInt_t { using type = void; };

      template <>
      struct __sig_UInt_for_SInt_t<sint64_t> { using type = uint64_t; };

      template <>
      struct __sig_UInt_for_SInt_t<schint_t> { using type = uchint_t; };

      template <>
      struct __sig_UInt_for_SInt_t<ssint_t> { using type = usint_t; };

      template <>
      struct __sig_UInt_for_SInt_t<sint_t> { using type = uint_t; };

      template <>
      struct __sig_UInt_for_SInt_t<slint_t> { using type = ulint_t; };

    } // namespace ugly_details_UInt_for_SInt

    template <typename Int_t>
    using sig_UInt_for_SInt_t =
        typename ugly_details_UInt_for_SInt::__sig_UInt_for_SInt_t<Int_t>::type;

    namespace ugly_details_SInt_for_SInt {

      template <typename SInt>
      struct __sig_SInt_for_SInt_t {  using type = void;  };

      template <>
      struct __sig_SInt_for_SInt_t<sllint_t> { using type = sint64_t; };

      template <>
      struct __sig_SInt_for_SInt_t<slint_t> {
        template <signed_integral_c SINT_T>
        static inline constexpr bool signed_gt_signed_v = gt_sz_v<SINT_T, slint_t>;

        using type = std::conditional_t<
                        signed_gt_signed_v<sllint_t>, 
                            sllint_t,
                            typename __sig_SInt_for_SInt_t<sllint_t>::type
                    >;
      };

      template <>
      struct __sig_SInt_for_SInt_t<sint_t> {
        template <typename SINT_T>
        static inline constexpr bool signed_gt_signed_v = gt_sz_v<SINT_T, sint_t>;

        using type = std::conditional_t<
            signed_gt_signed_v<slint_t>, 
                slint_t,
                typename __sig_SInt_for_SInt_t<slint_t>::type
        >;
      };

      template <>
      struct __sig_SInt_for_SInt_t<ssint_t> {
        template <typename SINT_T>
        static inline constexpr bool signed_gt_signed_v = gt_sz_v<SINT_T, ssint_t>;

        using type = std::conditional_t<
            signed_gt_signed_v<sint_t>, 
                sint_t,
                typename __sig_SInt_for_SInt_t<sint_t>::type
            >;
      };

      template <>
      struct __sig_SInt_for_SInt_t<schint_t>
      {
        template <typename SINT_T>
        static inline constexpr bool signed_gt_signed_v = gt_sz_v<SINT_T, schint_t>;

        using type =
            std::conditional_t<signed_gt_signed_v<ssint_t>, ssint_t,
                               typename __sig_SInt_for_SInt_t<ssint_t>::type>;
      };

    } // namespace ugly_details_SInt_for_SInt

    template <typename SInt_t>
    using sig_SInt_for_SInt_t =
        typename ugly_details_SInt_for_SInt::__sig_SInt_for_SInt_t<SInt_t>::type;

    template <typename UINT_T>
    consteval UINT_T maxbase() { return (static_cast<UINT_T>(std::numeric_limits<UINT_T>::max())); }
    template <typename UINT_T>
    consteval UINT_T submaxbase() { return static_cast<UINT_T>(maxbase<UINT_T>() - 1); }
    template <typename UINT_T>
    consteval UINT_T minbase() { return static_cast<UINT_T>(2); }
    template <typename UINT_T>
    consteval UINT_T subminbase() { return static_cast<UINT_T>(3); }
    template <typename UINT_T>
    consteval UINT_T monobase() { return static_cast<UINT_T>(1); }
    template <typename UINT_T>
    consteval UINT_T nobase() { return static_cast<UINT_T>(0); }
    template <typename UINT_T>
    consteval UINT_T maxdigit() { return static_cast<UINT_T>(submaxbase<UINT_T>()); }
    template <typename UINT_T>
    consteval UINT_T submaxdigit() { return static_cast<UINT_T>(submaxbase<UINT_T>() - 1); }
    template <typename UINT_T>
    consteval UINT_T digit_0() { return static_cast<UINT_T>(0u); }
    template <typename UINT_T>
    consteval UINT_T digit_1() { return static_cast<UINT_T>(1u); }
    template <typename UINT_T>
    consteval UINT_T base_2() { return static_cast<UINT_T>(2u); }

  template <typename UINT_T, UINT_T B>
  consteval bool base_geqt_2() { return (B >= base_2<UINT_T>()); }

  template <typename UINT_T, UINT_T B>
  consteval bool base_leqt_max() { return (B <= maxbase<UINT_T>()); }

  template <typename UINT_T, UINT_T B>
  consteval bool suitable_base() { return (base_geqt_2<UINT_T, B>() && base_leqt_max<UINT_T, B>()); }

    template <typename UINT_T>
    consteval UINT_T middle_max() {
      using SIG_UINT_T = sig_UInt_for_UInt_t<UINT_T>;
      constexpr SIG_UINT_T maximo = maxbase<UINT_T>();
      constexpr SIG_UINT_T uno{1};
      constexpr SIG_UINT_T dos{2};
      return static_cast<UINT_T>((maximo + uno) / dos);
    }

    template <typename UINT_T>
    consteval UINT_T sqrt_max() {
      using SIG_UINT_T = sig_UInt_for_UInt_t<UINT_T>;
      constexpr SIG_UINT_T maximo{maxbase<UINT_T>()};
      constexpr SIG_UINT_T uno{1};
      constexpr SIG_UINT_T base{maximo + uno};
      constexpr auto x{static_cast<long double>(static_cast<SIG_UINT_T>(base))};
      if (x == 0.0) return static_cast<UINT_T>(0);
      long double estimate = x * 0.5;
      for (int i = 0; i < 50; ++i) { long double new_estimate = 0.5 * (estimate + x / estimate); if (estimate == new_estimate) break; estimate = new_estimate; }
      return static_cast<UINT_T>(estimate);
    }

    namespace ugly_details_for_suitable_type_deduction {
      template <typename T, T Radix>
      struct UIntTypeForRadix;
      template <integral_c T, T Radix>
      struct UIntTypeForRadix<T, Radix> {
        using UIntType = std::conditional_t<
            static_cast<uint64_t>(Radix) <= maxbase<uint8_t>(),
            uint8_t,
            std::conditional_t<
                static_cast<uint64_t>(Radix) <= maxbase<uint16_t>(),
                uint16_t,
                std::conditional_t<
                    static_cast<uint64_t>(Radix) <= maxbase<uint32_t>(),
                    uint32_t,
                    uint64_t>>>;
      };
    }
    using namespace ugly_details_for_suitable_type_deduction;

    template <ullint_t Radix>
    using TypeFromIntNumber_t = typename UIntTypeForRadix<decltype(Radix), Radix>::UIntType;

    namespace ugly_details_for_greater_suitable_type_deduction {
      template <typename T, T Radix>
      struct UIntTypeForRadixContainsMultResult;
      template <integral_c T, T Radix>
      requires(Radix > 1)
      struct UIntTypeForRadixContainsMultResult<T, Radix> {
        static constexpr ullint_t uint_value_0_max = static_cast<ullint_t>(sqrt_max<uchint_t>());
        static constexpr ullint_t uint_value_1_max = static_cast<ullint_t>(sqrt_max<usint_t>());
        static constexpr ullint_t uint_value_2_max = static_cast<ullint_t>(sqrt_max<uint_t>());
        static constexpr ullint_t uint_value_3_max = static_cast<ullint_t>(sqrt_max<ulint_t>());
        static constexpr ullint_t uint_value_4_max = static_cast<ullint_t>(sqrt_max<ullint_t>());
        static constexpr ullint_t uint_value = static_cast<ullint_t>(Radix);
        using UIntType = std::conditional_t<
            uint_value <= uint_value_0_max, uchint_t,
            std::conditional_t<
                uint_value <= uint_value_1_max, usint_t,
                std::conditional_t<
                    uint_value <= uint_value_2_max, uint_t,
                    std::conditional_t<
                        uint_value <= uint_value_3_max, ulint_t,
                        std::conditional_t<uint_value <= uint_value_4_max, ullint_t,
                                           uint64_t>>>>>;
      };
    }
    using namespace ugly_details_for_greater_suitable_type_deduction;

  } // namespace type_traits
} // namespace NumRepr

#endif // BASIC_TYPES_HPP_INCLUDED
