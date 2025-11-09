#ifndef UTILITIES_HPP_INCLUDED
#define UTILITIES_HPP_INCLUDED

#include "core/internal/basic_types.hpp"

#include <array>
#include <tuple>

namespace utilities
{
  template <NumRepr::type_traits::unsigned_integral_c UINT_T>
  using uintspair = typename std::array<UINT_T, 2>;
  template <NumRepr::type_traits::unsigned_integral_c UINT_T, UINT_T B>
  using uintspairlist = typename std::array<uintspair<UINT_T>, B>;
  template <NumRepr::type_traits::unsigned_integral_c UINT_T, UINT_T B>
  using uintspairtbl = typename std::array<uintspairlist<UINT_T, B>, B>;

  namespace ugly_pack2tuple_details { /* simplified in new location */ }

  namespace ugly_details { struct local_void_t {}; template <class Head_t, class... Tail_t> struct for_each_same_type { using second_t = typename std::tuple_element<0, std::tuple<Tail_t...>>::type; constexpr static bool are_same_type_v = ((std::is_same_v<Head_t, second_t>) && (for_each_same_type<Tail_t...>::are_same_type_v)); }; template <class Head_t> struct for_each_same_type<Head_t> { constexpr static bool are_same_type_v = true; }; }

  template <typename... Ts>
  concept all_are_the_same_type_c = requires(Ts...) { ugly_details::for_each_same_type<Ts...>::are_same_type_v; };

  template <typename... Ts>
  concept there_is_one_or_more_c = requires(Ts...) { ((sizeof...(Ts)) > 0); };

  namespace ugly_pack_details { template <typename... Ts> requires(all_are_the_same_type_c<Ts...> && there_is_one_or_more_c<Ts...>) struct pack2array { static constexpr std::size_t size = sizeof...(Ts); using inner_type = std::common_type_t<Ts...>; using array_type = std::array<inner_type, size>; using elem_type = inner_type; constexpr array_type operator()(Ts... args) const noexcept { return array_type{static_cast<inner_type>(args)...}; } template <std::size_t J> static constexpr elem_type get(Ts... args) noexcept { array_type content{static_cast<inner_type>(args)...}; return content[J]; } template <std::size_t... I> static constexpr void for_each_impl(array_type &iarray, const Ts... args, std::index_sequence<I...>) noexcept { ((iarray[I] = static_cast<inner_type>(args)), ...); } static constexpr void for_each(array_type &iarray, const Ts... args) noexcept { for_each_impl(iarray, args..., std::make_index_sequence<sizeof...(args)>{}); } }; }

  template <class... Ts>
    requires(all_are_the_same_type_c<Ts...> && there_is_one_or_more_c<Ts...>)
  void assign_with_order(auto &dest, const Ts &...args) noexcept
  {
    using type = typename ugly_pack_details::pack2array<Ts...>;
    type::for_each(dest, args...);
    return;
  }

  namespace special
  {
    template <NumRepr::usint_t B, NumRepr::usint_t L>
    consteval inline NumRepr::uint64_t Base_pow_to_Size() noexcept
    {
      constexpr NumRepr::uint64_t Bc{B};
      if constexpr (L == 0) return static_cast<NumRepr::uint64_t>(1);
      else if constexpr (L == 1) return static_cast<NumRepr::uint64_t>(Bc);
      else if constexpr (L == 2) return static_cast<NumRepr::uint64_t>(Bc * Bc);
      else return static_cast<NumRepr::uint64_t>(Bc * Base_pow_to_Size<B, L - 1>());
    }

    template <NumRepr::usint_t Base, NumRepr::usint_t Exp>
    struct pow_B_to_E_t { static constexpr NumRepr::uint64_t base = static_cast<NumRepr::uint64_t>(Base); static constexpr NumRepr::uint64_t exponent = static_cast<NumRepr::uint64_t>(Exp); static constexpr NumRepr::uint64_t value = base * (pow_B_to_E_t<base, exponent - 1>::value); };

    template <NumRepr::usint_t Base>
    struct pow_B_to_E_t<Base, 2> { static constexpr NumRepr::uint64_t base = static_cast<NumRepr::uint64_t>(Base); static constexpr NumRepr::uint64_t exponent = static_cast<NumRepr::uint64_t>(2); static constexpr NumRepr::uint64_t value = base * base; };

    template <NumRepr::usint_t Base>
    struct pow_B_to_E_t<Base, 1> { static constexpr NumRepr::uint64_t base = static_cast<NumRepr::uint64_t>(Base); static constexpr NumRepr::uint64_t exponent = static_cast<NumRepr::uint64_t>(1); static constexpr NumRepr::uint64_t value = base; };

    template <NumRepr::usint_t Base>
    struct pow_B_to_E_t<Base, 0> { static constexpr NumRepr::uint64_t base = static_cast<NumRepr::uint64_t>(Base); static constexpr NumRepr::uint64_t exponent = static_cast<NumRepr::uint64_t>(0); static constexpr NumRepr::uint64_t value = static_cast<NumRepr::uint64_t>(1); };

    template <NumRepr::usint_t Base, NumRepr::usint_t Exp>
    constexpr NumRepr::uint64_t Pow_B2L_v = pow_B_to_E_t<Base, Exp>::value;

    template <std::int64_t IntObj_ct, std::int64_t BeginIntObj_ct,
              std::int64_t EndIntObj_ct, std::int64_t Base,
              template <std::int64_t, std::int64_t> class Funct_tt>
      requires((BeginIntObj_ct >= EndIntObj_ct) && (IntObj_ct >= BeginIntObj_ct))
    struct tuple_builder_t { using type = std::int64_t; static constexpr std::int64_t unit = static_cast<std::int64_t>(1); static constexpr std::int64_t value{IntObj_ct}; static constexpr std::int64_t begin_value{BeginIntObj_ct}; static constexpr std::int64_t end_value{EndIntObj_ct}; static consteval decltype(auto) build() noexcept { return std::tuple_cat(std::make_tuple(std::make_tuple(value, Funct_tt<Base, value>{}())), tuple_builder_t<value + unit, begin_value, end_value, Base, Funct_tt>::build()); } };

    template <std::int64_t BeginIntObj_ct, std::int64_t EndIntObj_ct,
              std::int64_t Base,
              template <std::int64_t, std::int64_t> class Funct_tt>
    struct tuple_builder_t<EndIntObj_ct - 1, BeginIntObj_ct, EndIntObj_ct, Base, Funct_tt> { using type = std::int64_t; static constexpr std::int64_t unit = static_cast<std::int64_t>(1); static constexpr std::int64_t value{EndIntObj_ct - unit}; static constexpr std::int64_t begin_value{BeginIntObj_ct}; static constexpr std::int64_t end_value{EndIntObj_ct}; static consteval decltype(auto) build() noexcept { return std::make_tuple(std::make_tuple(value, Funct_tt<Base, value>{}())); } };

    template <std::int64_t BeginIntObj_ct, std::int64_t EndIntObj_ct,
              std::int64_t Base,
              template <std::int64_t, std::int64_t> class Funct_tt>
      requires(BeginIntObj_ct <= EndIntObj_ct)
    struct tuple_builder_t<BeginIntObj_ct, BeginIntObj_ct, EndIntObj_ct, Base, Funct_tt> { using type = std::int64_t; static constexpr type unit = 1; static constexpr type value{BeginIntObj_ct}; static constexpr type begin_value{BeginIntObj_ct}; static constexpr type end_value{EndIntObj_ct}; static consteval decltype(auto) build() noexcept { return std::tuple_cat(std::make_tuple(std::make_tuple(value, Funct_tt<Base, value>{}())), tuple_builder_t<begin_value + unit, begin_value, end_value, Base, Funct_tt>::build()); } };

    template <std::int64_t BeginIntObj_ct, std::int64_t EndIntObj_ct,
              std::int64_t Base,
              template <std::int64_t, std::int64_t> class Funct_tt>
      requires(BeginIntObj_ct < EndIntObj_ct)
    struct tuple_user_constructor_t { static constexpr auto value = tuple_builder_t<BeginIntObj_ct, BeginIntObj_ct, EndIntObj_ct, Base, Funct_tt>::build(); };

    template <std::int64_t BeginIntObj_ct, std::int64_t EndIntObj_ct,
              std::int64_t Base,
              template <std::int64_t, std::int64_t> class Funct_tt>
      requires(BeginIntObj_ct < EndIntObj_ct)
    constexpr auto tuple_constr_v = tuple_user_constructor_t<BeginIntObj_ct, EndIntObj_ct, Base, Funct_tt>::build();

    template <auto B, auto L, typename A>
    constexpr inline NumRepr::uint64_t conversion_to_int(const A &arg) noexcept { using NumRepr::sint64_t; using NumRepr::uint64_t; constexpr uint64_t base{static_cast<uint64_t>(B)}; uint64_t acc{arg[L - 1]()}; for (sint64_t ix{L - 2}; ix > -1; --ix) { acc *= base; acc += static_cast<uint64_t>(arg[ix]()); }; return acc; }

  } /// END OF NAMESPACE SPECIAL

} /// END OF NAMESPACE UTILITIES

#endif // UTILITIES_HPP_INCLUDED