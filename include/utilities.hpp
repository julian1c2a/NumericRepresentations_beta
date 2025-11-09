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

  /// template<class type_0, class type_1, ... , class type_Nm1>
  /// struct apilamiento_de_tipos_t {
  ///    type_0     obj_0;
  ///    type_1     obj_1;
  ///    ......     .....
  ///    type_Nm1   obj_Nm1;
  /// };
  /// example:
  /// apilamiento_de_tipos<int,std::string,double> objeto{1,"abc",2.98105};
  /// objeto.obj_0   == 1;
  /// objeto.obj_1   == "abc";
  /// objeto.obj_Nm1 == 2.98105;
  /// A partir del estandar de C++11
  /// template<class ...type_i>
  /// struct apilamiento_de_tipos_t {
  ///    type_0     obj_0; 	// sabemos type_i pero no type_0
  ///    type_1     obj_1; 	// sabemos type_i pero no type_1
  ///    ......     .....
  ///    type_Nm1   obj_Nm1;// sabemos type_i pero no type_Nm1
  /// };
  /// type_i es un PACK
  /// tipo std::tupla<class ... Ts>;
  namespace ugly_pack2tuple_details
  { // OPEN NAMESPACE UGLY_PACK2TUPLE_DETAILS
    template <typename... Ts>
    struct pack2tuple
    {
      using tuple_type = std::tuple<Ts...>;
      static constexpr unsigned pack_size() noexcept { return (sizeof...(Ts)); }
      constexpr tuple_type operator()(Ts &&...args) noexcept
      {
        tuple_type content = std::make_tuple(std::forward(args...));
        return std::move(content);
      }
      /// DEVUELVE EL TIPO INDICE K DE LA LISTA DE PARAMETROS TIPO EN EL TEMPLATE
      template <unsigned K>
      using elem_type = typename std::tuple_element<K, tuple_type>::type;
      /// DEVUELVE EL OBJETO ARGUMENTO INDICE J DE LA LISTA DE ARGUMENTOS PASADOS
      template <unsigned J>
      static constexpr elem_type<J>::type get(Ts &&...args) noexcept
      {
        tuple_type content = std::make_tuple(std::forward(args...));
        elem_type<J> ret{std::get<J>(std::forward(content))};
        return ret;
      }
    };
  } // CLOSE NAMESPACE UGLY_PACK2TUPLE_DETAILS

  /// EXAMPLE
  /// pack2tuple<int,std::string,double>; // tipo
  /// pack2tuple<int,std::string,double>::tuple_type ==
  /// std::tuple<int,std::string,double>; // tupla using mi_tupla =
  /// pack2tuple<int,std::string,double>::tuple_type; pack_size() devuelve 3
  /// mi_tupla(2,"xyz",3.14159) devuelve la tupla {2,"xyz",3.14159} // por copia o
  /// por movimiento elem_type<0> es int elem_type<1> es std::string elem_type<2>
  /// es double get<0>(2,"xyz",3.14159) == 2; get<1>(2,"xyz",3.14159) == "xyz";
  /// get<2>(2,"xyz",3.14159) == 3.14159;

  /// tuple_obj == mi_tupla(2,"xyz",3.14159) == {2,"xyz",3.14159}
  /// head of tuple_obj is {2}
  /// tail of tuple_obj is {"xyz",3.14159}

  namespace ugly_details
  { // OPEN NAMESPACE UGLY_DETAILS
    /// BEGIN: TEMPLATE GENERICO Y SUS ESPECIALIZACIONES
    struct local_void_t
    {
    };

    /// COMPRUEBA QUE TODOS LOS TIPOS PASADOS SON EL MISMO
    /// (PARA CONSTRUIR UN ARRAY POR EJEMPLO)
    template <class Head_t, class... Tail_t>
    struct for_each_same_type
    {
      using second_t = typename std::tuple_element<0, std::tuple<Tail_t...>>::type;
      constexpr static bool are_same_type_v =
          ((std::is_same_v<Head_t, second_t>) &&
           (for_each_same_type<Tail_t...>::are_same_type_v));
    };
    template <class Head_t>
    struct for_each_same_type<Head_t>
    {
      constexpr static bool are_same_type_v = true;
    };
  } // CLOSE NAMESPACE UGLY_DETAILS

  /// CONCEPT QUE ASEGURA QUE TODOS LOS TIPOS PASADOS POR PACK SON EL MISMO
  template <typename... Ts>
  concept all_are_the_same_type_c =
      requires(Ts...) { ugly_details::for_each_same_type<Ts...>::are_same_type_v; };

  /// CONCEPT QUE ASEGURA QUE HAY 1 O MÁS PARÁMETROS
  template <typename... Ts>
  concept there_is_one_or_more_c = requires(Ts...) { ((sizeof...(Ts)) > 0); };

  /// END: 	TEMPLATE GENERICO Y SUS ESPECIALIZACIONES
  namespace ugly_pack_details
  {
    template <typename... Ts>
      requires(all_are_the_same_type_c<Ts...> && there_is_one_or_more_c<Ts...>)
    struct pack2array
    {
      static constexpr std::size_t size = sizeof...(Ts);

      // Simplificado: usar std::common_type_t en lugar de template complejo
      using inner_type = std::common_type_t<Ts...>;
      using array_type = std::array<inner_type, size>;
      using elem_type = inner_type;

      // Operador simple compatible con MSVC
      constexpr array_type operator()(Ts... args) const noexcept
      {
        return array_type{static_cast<inner_type>(args)...};
      }

      // Versión simplificada de get
      template <std::size_t J>
      static constexpr elem_type get(Ts... args) noexcept
      {
        array_type content{static_cast<inner_type>(args)...};
        return content[J];
      }

      // for_each simplificado para MSVC
      template <std::size_t... I>
      static constexpr void for_each_impl(array_type &iarray, const Ts... args,
                                          std::index_sequence<I...>) noexcept
      {
        ((iarray[I] = static_cast<inner_type>(args)), ...);
      }

      static constexpr void for_each(array_type &iarray, const Ts... args) noexcept
      {
        for_each_impl(iarray, args..., std::make_index_sequence<sizeof...(args)>{});
      }
    };
  } /// close namespace ugly_pack_details

  /// FUNCIÓN QUE , DADO UN PACK DE ARGUMENTOS LOS COPIA (SI SON DEL MISMO TIPO)
  /// EN UN ARRAY CON UN ORDEN, EN TIEMPO DE COMPILACIÓN
  template <class... Ts>
    requires(all_are_the_same_type_c<Ts...> && there_is_one_or_more_c<Ts...>)
  void assign_with_order(auto &dest, const Ts &...args) noexcept
  {
    using type = typename ugly_pack_details::pack2array<Ts...>;
    type::for_each(dest, args...);
    return;
  }
  /// LA LLAMADA "REAL" ES
  ///
  ///			assign_with_order(dest,args...);
  ///
  /// donde los "args" son de tipo "Ts" (que es uno solo, todos iguales entre si)

  namespace special
  {

    /// FORMA SENCILLA DE CONSEGUIR POTENCIAS DE UNA BASE EN COMPILE TIME
    template <NumRepr::usint_t B, NumRepr::usint_t L>
    consteval inline NumRepr::uint64_t Base_pow_to_Size() noexcept
    {
      constexpr NumRepr::uint64_t Bc{B};
      if constexpr (L == 0)
        return static_cast<NumRepr::uint64_t>(1);
      else if constexpr (L == 1)
        return static_cast<NumRepr::uint64_t>(Bc);
      else if constexpr (L == 2)
        return static_cast<NumRepr::uint64_t>(Bc * Bc);
      else
        return static_cast<NumRepr::uint64_t>(Bc * Base_pow_to_Size<B, L - 1>());
    }

    /// FORMA ANTIGUA PERO SEGURA DE CONSEGUIR POTENCIAS DE UNA BASE EN COMPILE TIME
    template <NumRepr::usint_t Base, NumRepr::usint_t Exp>
    struct pow_B_to_E_t
    {
      static constexpr NumRepr::uint64_t base =
          static_cast<NumRepr::uint64_t>(Base);
      static constexpr NumRepr::uint64_t exponent =
          static_cast<NumRepr::uint64_t>(Exp);
      static constexpr NumRepr::uint64_t value =
          base * (pow_B_to_E_t<base, exponent - 1>::value);
    };

    template <NumRepr::usint_t Base>
    struct pow_B_to_E_t<Base, 2>
    {
      static constexpr NumRepr::uint64_t base =
          static_cast<NumRepr::uint64_t>(Base);
      static constexpr NumRepr::uint64_t exponent =
          static_cast<NumRepr::uint64_t>(2);
      static constexpr NumRepr::uint64_t value = base * base;
    };

    template <NumRepr::usint_t Base>
    struct pow_B_to_E_t<Base, 1>
    {
      static constexpr NumRepr::uint64_t base =
          static_cast<NumRepr::uint64_t>(Base);
      static constexpr NumRepr::uint64_t exponent =
          static_cast<NumRepr::uint64_t>(1);
      static constexpr NumRepr::uint64_t value = base;
    };

    template <NumRepr::usint_t Base>
    struct pow_B_to_E_t<Base, 0>
    {
      static constexpr NumRepr::uint64_t base =
          static_cast<NumRepr::uint64_t>(Base);
      static constexpr NumRepr::uint64_t exponent =
          static_cast<NumRepr::uint64_t>(0);
      static constexpr NumRepr::uint64_t value =
          static_cast<NumRepr::uint64_t>(1);
    };

    template <NumRepr::usint_t Base, NumRepr::usint_t Exp>
    constexpr NumRepr::uint64_t Pow_B2L_v = pow_B_to_E_t<Base, Exp>::value;

    /// OBTENER UNA TUPLA EN TIEMPO DE COMPILACION DONDE CADA POSICION ESTA
    /// INICIALIZADA PERO CON UNA LLAMADA DISTINTA A FUNCION POR CADA INDICE
    /// EN TIEMPO DE COMPILACION

    /// TEMPLATE GENERAL
    template <std::int64_t IntObj_ct, std::int64_t BeginIntObj_ct,
              std::int64_t EndIntObj_ct, std::int64_t Base,
              template <std::int64_t, std::int64_t> class Funct_tt>
      requires((BeginIntObj_ct >= EndIntObj_ct) && (IntObj_ct >= BeginIntObj_ct))
    struct tuple_builder_t
    {

      using type = std::int64_t;

      static constexpr std::int64_t unit = static_cast<std::int64_t>(1);

      static constexpr std::int64_t value{IntObj_ct};
      static constexpr std::int64_t begin_value{BeginIntObj_ct};
      static constexpr std::int64_t end_value{EndIntObj_ct};

      static consteval decltype(auto) build() noexcept
      {
        return std::tuple_cat(
            std::make_tuple(std::make_tuple(value, Funct_tt<Base, value>{}())),
            tuple_builder_t<value + unit, begin_value, end_value, Base,
                            Funct_tt>::build());
      }
    };

    /// ESPECIALIZACION DONDE INTOBJ_CT == ENDINTOBJ_CT-1
    template <std::int64_t BeginIntObj_ct, std::int64_t EndIntObj_ct,
              std::int64_t Base,
              template <std::int64_t, std::int64_t> class Funct_tt>
    struct tuple_builder_t<EndIntObj_ct - 1, BeginIntObj_ct, EndIntObj_ct, Base,
                           Funct_tt>
    {

      using type = std::int64_t;

      static constexpr std::int64_t unit = static_cast<std::int64_t>(1);

      static constexpr std::int64_t value{EndIntObj_ct - unit};
      static constexpr std::int64_t begin_value{BeginIntObj_ct};
      static constexpr std::int64_t end_value{EndIntObj_ct};

      static consteval decltype(auto) build() noexcept
      {
        return std::make_tuple(std::make_tuple(value, Funct_tt<Base, value>{}()));
      }
    };

    /// ESPECIALIZACION DONDE INTOBJ_CT == BEGININTOBJ_CT
    template <std::int64_t BeginIntObj_ct, std::int64_t EndIntObj_ct,
              std::int64_t Base,
              template <std::int64_t, std::int64_t> class Funct_tt>
      requires(BeginIntObj_ct <= EndIntObj_ct)
    struct tuple_builder_t<BeginIntObj_ct, BeginIntObj_ct, EndIntObj_ct, Base,
                           Funct_tt>
    {

      using type = std::int64_t;

      static constexpr type unit = 1;

      static constexpr type value{BeginIntObj_ct};
      static constexpr type begin_value{BeginIntObj_ct};
      static constexpr type end_value{EndIntObj_ct};

      static consteval decltype(auto) build() noexcept
      {
        return std::tuple_cat(
            std::make_tuple(std::make_tuple(value, Funct_tt<Base, value>{}())),
            tuple_builder_t<begin_value + unit, begin_value, end_value, Base,
                            Funct_tt>::build());
      }
    };

    template <std::int64_t BeginIntObj_ct, std::int64_t EndIntObj_ct,
              std::int64_t Base,
              template <std::int64_t, std::int64_t> class Funct_tt>
      requires(BeginIntObj_ct < EndIntObj_ct)
    struct tuple_user_constructor_t
    {
      static constexpr auto value =
          tuple_builder_t<BeginIntObj_ct, BeginIntObj_ct, EndIntObj_ct, Base,
                          Funct_tt>::build();
    };

    template <std::int64_t BeginIntObj_ct, std::int64_t EndIntObj_ct,
              std::int64_t Base,
              template <std::int64_t, std::int64_t> class Funct_tt>
      requires(BeginIntObj_ct < EndIntObj_ct)
    constexpr auto tuple_constr_v = tuple_user_constructor_t<
        BeginIntObj_ct, EndIntObj_ct, Base, Funct_tt>::build();

    // ========================================
    // REFACTORED TEMPLATE METAPROGRAMMING - MSVC COMPATIBLE
    // ========================================

    /**
     * @brief Compile-time for loop implementation compatible with all compilers
     * @details This refactored version eliminates template template parameters
     *          that cause issues with MSVC while maintaining full functionality
     *
     * The key insight is to use regular function objects instead of template
     * template parameters, which are more portable across compilers.
     */

    // Helper for recursive template expansion (MSVC-safe approach)
    template <std::size_t Index, std::size_t End>
    struct ct_for_impl
    {
      template <std::size_t Base, typename Functor, typename... Ts>
      static constexpr void apply(std::tuple<Ts...> const &t, Functor &&func) noexcept
      {
        if constexpr (Index < End)
        {
          func.template operator()<Base, Index>(std::get<Index>(t));
          ct_for_impl<Index + 1, End>::template apply<Base>(t, std::forward<Functor>(func));
        }
      }
    };

    // Specialization to end recursion
    template <std::size_t End>
    struct ct_for_impl<End, End>
    {
      template <std::size_t Base, typename Functor, typename... Ts>
      static constexpr void apply(std::tuple<Ts...> const &, Functor &&) noexcept
      {
        // Base case - do nothing
      }
    };

    /**
     * @brief Compile-time for loop - refactored for universal compiler compatibility
     * @tparam start Starting index
     * @tparam end Ending index (exclusive)
     * @tparam Base Base parameter for the operation
     * @tparam Functor Function object type (replaces template template parameter)
     * @tparam Ts Tuple element types
     * @param t The tuple to iterate over
     * @param func Function object to apply to each element
     *
     * @note This refactored version uses a function object approach instead of
     *       template template parameters, making it compatible with MSVC
     *
     * @example
     * ```cpp
     * // Function object that replaces template template parameter
     * struct MyFunctor {
     *     template<std::size_t Base, std::size_t Index>
     *     void operator()(auto&& element) const {
     *         // Process element at Index with Base
     *     }
     * };
     *
     * std::tuple<int, int, int> my_tuple{1, 2, 3};
     * ct_for<0, 3, 10>(my_tuple, MyFunctor{});
     * ```
     */
    template <std::size_t start, std::size_t end, std::size_t Base, typename Functor, typename... Ts>
    constexpr void ct_for(std::tuple<Ts...> const &t, Functor &&func) noexcept
    {
      ct_for_impl<start, end>::template apply<Base>(t, std::forward<Functor>(func));
    }

    // ========================================
    // BACKWARD COMPATIBILITY WRAPPER (DEPRECATED)
    // ========================================

    // Helper struct for legacy template template parameter adaptation (must be defined outside)
    template <template <typename, std::size_t, std::size_t> typename Funct_tt>
    struct legacy_wrapper_functor
    {
      template <std::size_t B, std::size_t Index>
      constexpr void operator()(auto &&element) const
      {
        using element_type = std::decay_t<decltype(element)>;
        Funct_tt<element_type, B, Index>{}(element);
      }
    };

    /**
     * @brief Legacy wrapper for old template template parameter interface
     * @deprecated Use the new function object interface instead
     * @note This provides limited compatibility for existing code
     */
    template <std::size_t start, std::size_t end, std::size_t Base,
              template <typename, std::size_t, std::size_t> typename Funct_tt,
              typename... Ts>
    constexpr void ct_for_legacy(std::tuple<Ts...> const &t) noexcept
    {
      ct_for<start, end, Base>(t, legacy_wrapper_functor<Funct_tt>{});
    }

    /// CONVERSION DE REGISTRO DE DIGITOS A ENTERO EN TIEMPO DE COMPILACION
    template <auto B, auto L, typename A>
    constexpr inline NumRepr::uint64_t conversion_to_int(const A &arg) noexcept
    {
      using NumRepr::sint64_t;
      using NumRepr::uint64_t;
      constexpr uint64_t base{static_cast<uint64_t>(B)};
      uint64_t acc{arg[L - 1]()};
      for (sint64_t ix{L - 2}; ix > -1; --ix)
      {
        acc *= base;
        acc += static_cast<uint64_t>(arg[ix]());
      };
      return acc;
    }

  } /// END OF NAMESPACE SPECIAL

} /// END OF NAMESPACE UTILITIES

#endif // UTILITIES_HPP_INCLUDED
