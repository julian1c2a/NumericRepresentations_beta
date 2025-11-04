

#ifndef BASIC_TYPES_HPP_INCLUDED
#define BASIC_TYPES_HPP_INCLUDED

#include <cinttypes>

#include <compare>
#include <concepts>

#include <optional>

#include <type_traits>

#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>

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
 *
 * @details
 * Este archivo define el sistema de tipos fundamental del proyecto, incluyendo:
 *
 * **1. Aliases de tipos estándar:** Nombres simplificados para tipos enteros estándar
 *
 * **2. Sistema de meta-funciones para escalamiento de tipos:**
 * - `sig_UInt_for_UInt_t<T>`: Obtiene el siguiente tipo entero **sin signo** de mayor capacidad
 * - `sig_SInt_for_UInt_t<T>`: Obtiene el siguiente tipo entero **con signo** de mayor capacidad
 *
 * **3. Convención de nombres IMPORTANTE:**
 * - El prefijo "sig_" significa "**siguiente**" (español: next/higher capacity)
 * - NO significa "signed" (con signo)
 * - Ejemplo: `sig_uint_t` = "siguiente uint_t" = tipo uint con mayor capacidad
 *
 * **4. Conceptos y traits:** Validación de tipos en tiempo de compilación
 *
 * @note El uso del español en algunos nombres refleja el origen del proyecto
 * @note Las meta-funciones evitan overflow en operaciones aritméticas intermedias
 *
 * @example
 * ```cpp
 * // Escalamiento de tipos
 * using bigger = sig_UInt_for_UInt_t<uint32_t>; // = uint64_t
 * using signed_bigger = sig_SInt_for_UInt_t<uint32_t>; // = int64_t
 * ```
 */
namespace NumRepr
{
  /// NUEVOS NOMBRES PARA LOS ENTEROS O PARECIDOS
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

  // 128-bit types - compiler specific
#if defined(__GNUC__) && !defined(__clang__)
  // GCC specific 128-bit types
  using uint128_t = __uint128_t;
  using sint128_t = __int128_t;
#elif defined(__clang__)
// Clang specific 128-bit types (if available)
#if __has_extension(int128)
  using uint128_t = __uint128_t;
  using sint128_t = __int128_t;
#else
  // Fallback: use pair of 64-bit or disable 128-bit operations
  struct uint128_t
  {
    std::uint64_t low, high;
  };
  struct sint128_t
  {
    std::uint64_t low;
    std::int64_t high;
  };
#endif
#elif defined(_MSC_VER)
  // MSVC doesn't have native 128-bit types
  // We can use __m128i from SSE or create our own
  struct uint128_t
  {
    std::uint64_t low, high;
  };
  struct sint128_t
  {
    std::uint64_t low;
    std::int64_t high;
  };
#else
  // Generic fallback for other compilers
  struct uint128_t
  {
    std::uint64_t low, high;
  };
  struct sint128_t
  {
    std::uint64_t low;
    std::int64_t high;
  };
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

  // using ssize_t 		= std::ssize_t;

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

  namespace type_traits
  {

    /// TYPE_TRAITS AND CONCEPTS

    /// CONCEPT
    template <typename IntT>
    concept arith_integral_c =
        std::is_arithmetic_v<IntT> && std::is_integral_v<IntT>;

    /// CONCEPT
    template <typename NatIntT>
    concept arith_natural_c =
        std::is_arithmetic_v<NatIntT> && std::is_unsigned_v<NatIntT> &&
        std::is_integral_v<NatIntT>;

    /// CONCEPT
    template <typename CharT>
    concept char_type_c =
        std::is_same_v<CharT, char> || std::is_same_v<CharT, signed char> ||
        std::is_same_v<CharT, unsigned char> || std::is_same_v<CharT, wchar_t>;

    /// CONSTANT
    template <char_type_c CharT>
    constexpr inline CharT nullchar{CharT('\0')};

    /// BORRAR C_STR
    char *clear_ccad(char *, usint_t);

    template <template <uchint_t B> class T, uchint_t B>
    inline const char *devCadenaC(
        T<B> arg,
        size_t long_ccad = 64) noexcept
    {
      char *c_cad = new char[long_ccad];
      c_cad = clear_ccad(c_cad, long_ccad);
      std::stringstream pre_cad;
      pre_cad << arg;
      std::string cad(pre_cad.str());
      const size_t longitud = cad.length();
      for (size_t i = 0; i < longitud; ++i)
      {
        c_cad[i] = cad[i];
      }
      for (size_t i = longitud; i < long_ccad; ++i)
      {
        c_cad[i] = nullchar<char>;
      }
      return c_cad;
    }

    inline constexpr char *clear_ccad(
        char *cad_c,
        size_t long_de_cad_c) noexcept
    {
      for (size_t I = 0; I < long_de_cad_c; ++I)
        cad_c[I] = nullchar<char>;
      return cad_c;
    }

    inline constexpr ullint_t atoull(char *text) noexcept
    {
      int i = 0;
      while (*text)
      {
        i = (i << 3) + (i << 1) + (*text - '0');
        ++text;
      }
      return (i);
    }

    /// METAOPERADOR QUE NOS DA LA ADECUACION DE UN TIPO PARA SER BASE DE UN SISTEMA
    /// DE NUMERACION. VALE CUALQUIER TIPO UNSIGNED INTEGRAL QUE NO SEA EL MAYOR
    /// CONSIDERADO AQUI. EL MAYOR CONSIDERADO ES Uint64_t

    /// CONSTANT BOOL TEMPLATE
    template <typename UINT_T>
    constexpr bool is_uint_type_for_radix_v =
        std::is_unsigned_v<UINT_T> && (!std::is_same_v<UINT_T, uint64_t>);

    /// CONCEPT FOR UNSIGNED INTEGRAL TYPES VALID FOR THE RADIX
    template <typename UINT_T>
    concept uint_type_for_radix_c = is_uint_type_for_radix_v<UINT_T>;

    /// METAOPERADOR QUE NOS DA SI UN TIPO INTEGRAL ES UNSIGNED
    /// VALEN LOS QUE VALEN PARA RADIX MAS LOS TIPO MAS GRANDES
    /// POR LO TANTO Uint64_t SE CONSIDERA UN UNSIGNED INTEGRAL TYPE

    /// CONSTANT BOOL VARIABLE ON COMPILE TIME FOR CONCEPT ON UINT_T
    template <typename UINT_T>
    constexpr bool is_unsigned_type_v =
        is_uint_type_for_radix_v<UINT_T> || std::is_same_v<UINT_T, std::uint64_t>;

    /// CONCEPT FOR UNSIGNED INTEGRAL TYPES
    template <typename UINT_T>
    concept unsigned_integral_c = is_unsigned_type_v<UINT_T>;

    /// METAOPERADOR QUE NOS DA SI UN TIPO INTEGRAL ES SIGNED

    /// CONSTANT BOOL FOR CONCEPT ON SINT_T
    template <typename SINT_T>
    constexpr bool is_signed_type_v =
        std::is_signed_v<SINT_T> || std::is_same_v<SINT_T, sint64_t>;

    /// CONCEPT FOR SIGNED INTEGRAL TYPES
    template <typename SINT_T>
    concept signed_integral_c = is_signed_type_v<SINT_T>;

    /// KEYWORD TYPENAME
    /// TEMPLATE<TYPENAME T> CLASS NOMBRE_T; /// CLASS : NOMBRE_T<STRING>
    /// Si T es un tipo, entonces se puede sustituir en la plantilla de clase
    /// ------------------------------------------------------------------------------------
    /// CONCEPT STD::UNSIGNED_INTEGRAL
    /// TEMPLATE<STD::UNSIGNED_INTEGRAL T> CLASS NOMBRE_T; /// CLASS : NOMBRE_T<UNSINGED INT>
    /// Si T es un tipo que cumple los requerrimientos de UNSIGNED_INTEGRAL_T, esto es,
    /// T es un tipo integer y unsigned entonces se puede admitir para la plantilla de
    /// clases
    /// -------------------------------------------------------------------------------------
    ///       TEMPLATE CLASS           TYPE     NON-TYPE       TRUE CLASS > TYPE DEFINITION
    /// template<typename              int_type,int_type base> class digito<int_type,base>;
    /// TEMPLATE CLASS CONCEPT         TYPE     NON-TYPE       TYPE DEFINITION
    /// template<allowable_base_type_c int_type,int_type base> class digito<int_type,base>;

    /// METAOPERADOR QUE NOS DA SI UN TIPO ES INTEGRAL
    /// TEMPLATE CONSTANT BOOL (FUNCIÓN QUE ENTRA UN TIPO Y DEVUELVE TRUE/FALSE)
    template <typename INT_TYPE>
    inline constexpr bool is_integral_type_v = std::is_integral_v<INT_TYPE>;
    /// CONCEPT DEFINCITION
    template <typename INT_T>
    concept integral_c = is_integral_type_v<INT_T>;

    /// METAOPERADORES DE COMPARACION DE CAPACIDAD DE INTEGERS
    /// DADOS DOS TIPOS ME DEVULVE UN TRUE/FALSE
    /// COMO OPERADORES < <= == != >= > PARA TIPOS
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

    ///<  METAFUNCION : DA EL SIGUIENTE TIPO NATURAL PARA EL ACTUAL TIPO NATURAL
    ///<  POR ESPECIALIZACION EXPLICITA
    namespace ugly_details_UInt_for_UInt
    {
      template <unsigned_integral_c UInt_t>
      struct __sig_UInt_for_UInt_t
      {
        using type = void;
      };

      template <>
      struct __sig_UInt_for_UInt_t<ullint_t>
      {
        using type = uint64_t;
      };

      template <>
      struct __sig_UInt_for_UInt_t<ulint_t>
      {
        template <unsigned_integral_c uint_type>
        static inline constexpr bool uint_type_gt_this_type_v =
            gt_sz_v<uint_type, ulint_t>;

        using type = typename std::conditional_t<
            uint_type_gt_this_type_v<ullint_t>, ullint_t,
            typename __sig_UInt_for_UInt_t<ullint_t>::type>;
      };

      template <>
      struct __sig_UInt_for_UInt_t<uint_t>
      {
        template <unsigned_integral_c uint_type>
        static inline constexpr bool uint_type_gt_this_type_v =
            gt_sz_v<uint_type, uint_t>;

        using type =
            std::conditional_t<uint_type_gt_this_type_v<ulint_t>, ulint_t,
                               typename __sig_UInt_for_UInt_t<ulint_t>::type>;
      };

      template <>
      struct __sig_UInt_for_UInt_t<usint_t>
      {
        template <unsigned_integral_c uint_type>
        static inline constexpr bool uint_type_gt_this_type_v =
            gt_sz_v<uint_type, usint_t>;

        using type = std::conditional_t<uint_type_gt_this_type_v<uint_t>, uint_t,
                                        typename __sig_UInt_for_UInt_t<uint_t>::type>;
      };

      template <>
      struct __sig_UInt_for_UInt_t<uchint_t>
      {
        template <unsigned_integral_c uint_type>
        static inline constexpr bool uint_type_gt_this_type_v =
            gt_sz_v<uint_type, uchint_t>;

        using type =
            std::conditional_t<uint_type_gt_this_type_v<usint_t>, usint_t,
                               typename __sig_UInt_for_UInt_t<usint_t>::type>;
      };

    } // namespace ugly_details_UInt_for_UInt

    /**
     * @brief Meta-función que obtiene el siguiente tipo entero sin signo de mayor capacidad
     *
     * @tparam UInt_t Tipo entero sin signo de entrada
     *
     * @details
     * Esta meta-función implementa una escalera de tipos, devolviendo el siguiente
     * tipo entero sin signo con mayor capacidad que el tipo de entrada.
     * El prefijo "sig_" significa "**siguiente**" (next/higher), NO "signed".
     *
     * **Mapeo de tipos:**
     * - `uint8_t`  → `uint16_t`
     * - `uint16_t` → `uint32_t`
     * - `uint32_t` → `uint64_t`
     * - `uint64_t` → `uint128_t` (si está disponible)
     * - `uint128_t`→ `void` (no hay siguiente tipo)
     *
     * @note El prefijo "sig_" deriva del español "**siguiente**", no de "signed"
     * @note Útil para evitar overflow en operaciones aritméticas intermedias
     * @note Se usa en dig_t para parsing de números grandes
     *
     * @example
     * ```cpp
     * using next_type = sig_UInt_for_UInt_t<uint32_t>; // next_type = uint64_t
     * using bigger = sig_UInt_for_UInt_t<uint16_t>;    // bigger = uint32_t
     * ```
     */
    template <typename UInt_t>
    using sig_UInt_for_UInt_t =
        typename ugly_details_UInt_for_UInt::__sig_UInt_for_UInt_t<UInt_t>::type;

    ///<  METAFUNCION : DA EL SIGUIENTE TIPO ENTERO PARA EL ACTUAL TIPO NATURAL
    ///<  POR ESPECIALIZACION EXPLICITA
    namespace ugly_details_sig_SInt_for_UInt
    {
      template <typename UInt>
      struct __sig_SInt_for_UInt_t
      {
        using type = void;
      };

      template <>
      struct __sig_SInt_for_UInt_t<ullint_t>
      {
        using type = sint64_t;
      };
      /* is_unsigned_sz_gt_v */
      template <>
      struct __sig_SInt_for_UInt_t<ulint_t>
      {
        template <typename int_type>
        static inline constexpr bool int_type_gt_this_type_v =
            gt_sz_v<int_type, ulint_t>;

        using type =
            std::conditional_t<int_type_gt_this_type_v<sllint_t>, sllint_t,
                               typename __sig_SInt_for_UInt_t<ullint_t>::type>;
      };

      template <>
      struct __sig_SInt_for_UInt_t<uint_t>
      {
        template <typename int_type>
        static inline constexpr bool int_type_gt_this_type_v =
            gt_sz_v<int_type, uint_t>;

        using type =
            std::conditional_t<int_type_gt_this_type_v<slint_t>, slint_t,
                               typename __sig_SInt_for_UInt_t<ulint_t>::type>;
      };

      template <>
      struct __sig_SInt_for_UInt_t<usint_t>
      {
        template <typename int_type>
        static inline constexpr bool int_type_gt_this_type_v =
            gt_sz_v<int_type, usint_t>;

        using type = std::conditional_t<int_type_gt_this_type_v<sint_t>, sint_t,
                                        typename __sig_SInt_for_UInt_t<uint_t>::type>;
      };

      template <>
      struct __sig_SInt_for_UInt_t<uchint_t>
      {
        template <typename int_type>
        static inline constexpr bool int_type_gt_this_type_v =
            gt_sz_v<int_type, uchint_t>;

        using type =
            std::conditional_t<int_type_gt_this_type_v<ssint_t>, ssint_t,
                               typename __sig_SInt_for_UInt_t<usint_t>::type>;
      };

    } // namespace ugly_details_sig_SInt_for_UInt

    /**
     * @brief Meta-función que obtiene el siguiente tipo entero CON SIGNO de mayor capacidad
     *
     * @tparam UInt_t Tipo entero sin signo de entrada
     *
     * @details
     * Esta meta-función toma un tipo entero **sin signo** y devuelve el siguiente
     * tipo entero **CON SIGNO** de mayor capacidad. Es complementaria a sig_UInt_for_UInt_t.
     * El prefijo "sig_" significa "**siguiente**" (next/higher), NO "signed".
     *
     * **Mapeo de tipos:**
     * - `uint8_t`  → `int16_t`
     * - `uint16_t` → `int32_t`
     * - `uint32_t` → `int64_t`
     * - `uint64_t` → `int128_t` (si está disponible)
     * - `uint128_t`→ `void` (no hay siguiente tipo)
     *
     * @note El prefijo "sig_" deriva del español "**siguiente**", no de "signed"
     * @note Útil cuando se necesita manejar valores negativos temporalmente
     * @note El tipo resultante SÍ tiene signo, pero el "sig_" se refiere a "siguiente"
     * @note Se usa para operaciones que pueden generar resultados negativos intermedios
     *
     * @example
     * ```cpp
     * using signed_next = sig_SInt_for_UInt_t<uint32_t>; // signed_next = int64_t
     * using bigger_signed = sig_SInt_for_UInt_t<uint16_t>; // bigger_signed = int32_t
     * ```
     */
    template <typename UInt_t>
    using sig_SInt_for_UInt_t =
        typename ugly_details_sig_SInt_for_UInt::__sig_SInt_for_UInt_t<UInt_t>::type;

    ///<  METAFUNCION : DA EL SIGUIENTE TIPO NATURAL PARA EL ACTUAL TIPO ENTERO
    ///<  POR ESPECIALIZACION EXPLICITA
    namespace ugly_details_UInt_for_SInt
    {
      template <typename SInt>
      struct __sig_UInt_for_SInt_t
      {
        using type = void;
      };

      template <>
      struct __sig_UInt_for_SInt_t<sint64_t>
      {
        using type = uint64_t;
      };

      template <>
      struct __sig_UInt_for_SInt_t<schint_t>
      {
        using type = uchint_t;
      };

      template <>
      struct __sig_UInt_for_SInt_t<ssint_t>
      {
        using type = usint_t;
      };

      template <>
      struct __sig_UInt_for_SInt_t<sint_t>
      {
        using type = uint_t;
      };

      template <>
      struct __sig_UInt_for_SInt_t<slint_t>
      {
        using type = ulint_t;
      };

    } // namespace ugly_details_UInt_for_SInt

    /// FUNCIÓN DE DADO UN TIPO ENTERO CON SIGNO ME DA OTRO TIPO ENTERO SIN SIGNO
    ///      DADO      -> DEVUELVE
    ///      SINT8_T   -> UINT8_T
    ///      SINT16_T  -> UINT16_T
    ///      SINT32_T  -> UINT32_T
    ///      SINT64_T  -> UINT64_T
    template <typename Int_t>
    using sig_UInt_for_SInt_t =
        typename ugly_details_UInt_for_SInt::__sig_UInt_for_SInt_t<Int_t>::type;

    ///<  METAFUNCION : DA EL SIGUIENTE TIPO ENTERO PARA EL ACTUAL TIPO ENTERO
    ///<  POR ESPECIALIZACION EXPLICITA
    namespace ugly_details_SInt_for_SInt
    {

      template <typename SInt>
      struct __sig_SInt_for_SInt_t
      {
        using type = void;
      };

      template <>
      struct __sig_SInt_for_SInt_t<sllint_t>
      {
        using type = sint64_t;
      };

      template <>
      struct __sig_SInt_for_SInt_t<slint_t>
      {
        template <signed_integral_c SINT_T>
        static inline constexpr bool signed_gt_signed_v = gt_sz_v<SINT_T, slint_t>;

        using type =
            std::conditional_t<signed_gt_signed_v<sllint_t>, sllint_t,
                               typename __sig_SInt_for_SInt_t<sllint_t>::type>;
      };

      template <>
      struct __sig_SInt_for_SInt_t<sint_t>
      {
        template <typename SINT_T>
        static inline constexpr bool signed_gt_signed_v = gt_sz_v<SINT_T, sint_t>;

        using type =
            std::conditional_t<signed_gt_signed_v<slint_t>, slint_t,
                               typename __sig_SInt_for_SInt_t<slint_t>::type>;
      };

      template <>
      struct __sig_SInt_for_SInt_t<ssint_t>
      {
        template <typename SINT_T>
        static inline constexpr bool signed_gt_signed_v = gt_sz_v<SINT_T, ssint_t>;

        using type = std::conditional_t<signed_gt_signed_v<sint_t>, sint_t,
                                        typename __sig_SInt_for_SInt_t<sint_t>::type>;
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

    /// FUNCIÓN DE DADO UN TIPO ENTERO CON SIGNO ME DA OTRO TIPO ENTERO CON SIGNO
    ///      DADO      -> DEVUELVE
    ///      SINT8_T   -> SINT16_T
    ///      SINT16_T  -> SINT32_T
    ///      SINT32_T  -> SINT64_T
    ///      SINT64_T  -> SINT128_T
    ///      Sint64_t -> VOID
    template <typename SInt_t>
    using sig_SInt_for_SInt_t =
        typename ugly_details_SInt_for_SInt::__sig_SInt_for_SInt_t<SInt_t>::type;

    ///< METAFUNCIONES PARA DAR CON LOS MAXIMOS NUMEROS QUE CABEN EN UN TIPO
    ///< Y SIMILARES
    template <typename UINT_T>
    consteval UINT_T maxbase()
    {
      return (static_cast<UINT_T>(std::numeric_limits<UINT_T>::max()));
    }

    template <typename UINT_T>
    consteval UINT_T submaxbase()
    {
      return static_cast<UINT_T>(maxbase<UINT_T>() - 1);
    }

    template <typename UINT_T>
    consteval UINT_T minbase()
    {
      return static_cast<UINT_T>(2);
    }

    template <typename UINT_T>
    consteval UINT_T subminbase()
    {
      return static_cast<UINT_T>(3);
    }

    template <typename UINT_T>
    consteval UINT_T monobase()
    {
      return static_cast<UINT_T>(1);
    }

    template <typename UINT_T>
    consteval UINT_T nobase()
    {
      return static_cast<UINT_T>(0);
    }

    template <typename UINT_T>
    consteval UINT_T maxdigit()
    {
      return static_cast<UINT_T>(submaxbase<UINT_T>());
    }

    template <typename UINT_T>
    consteval UINT_T submaxdigit()
    {
      return static_cast<UINT_T>(submaxbase<UINT_T>() - 1);
    }

    template <typename UINT_T>
    consteval UINT_T digit_0()
    {
      return static_cast<UINT_T>(0u);
    }

    template <typename UINT_T>
    consteval UINT_T digit_1()
    {
      return static_cast<UINT_T>(1u);
    }

    template <typename UINT_T>
    consteval UINT_T base_2()
    {
      return static_cast<UINT_T>(2u);
    }

    template <typename UINT_T, UINT_T B>
    consteval bool base_geqt_2()
    {
      return (B >= base_2<UINT_T>());
    }

    template <typename UINT_T, UINT_T B>
    consteval bool base_leqt_max()
    {
      return (B <= maxbase<UINT_T>());
    }

    /// FUNCIÓN QUE DADO UN TIPO USIGNED INTEGRAL Y UN ENTERO DE ESE TIPO
    /// ES UNA BASE APROPIADA
    template <typename UINT_T, UINT_T B>
    consteval bool suitable_base()
    { // requires on B
      return (base_geqt_2<UINT_T, B>() && base_leqt_max<UINT_T, B>());
    }

    /// FUNCIÓN QUE DADO UN TIPO ENTERO SIN SIGNO ME DA EL ENTERO MEDIO
    /// UINT_A > MIDDLE_MAX => 2*UINT_A NO CABE EN UINT_T
    /// UINT_A < MIDDLE_MAX => 2*UINT_A SI CABE EN UINT_T
    template <typename UINT_T>
    consteval UINT_T middle_max()
    {
      using SIG_UINT_T = sig_UInt_for_UInt_t<UINT_T>;
      constexpr SIG_UINT_T maximo = maxbase<UINT_T>();
      constexpr SIG_UINT_T uno{1};
      constexpr SIG_UINT_T dos{2};
      return static_cast<UINT_T>((maximo + uno) / dos);
    }

    /// FUNCIÓN QUE DADO UN TIPO ENTERO SIN SIGNO ME DA EL ENTERO MEDIO
    /// UINT_A > SQRT_MAX => UINT_A^2 NO CABE EN UINT_T
    /// UINT_A < SQRT_MAX => UINT_A^2 SI CABE EN UINT_T

    /// @brief Compute integer square root (floor of square root)
    /// @param arg Number to compute square root of
    /// @return The floor of the square root of arg
    template <typename UINT_T>
    consteval UINT_T sqrt(UINT_T arg)
    {
      if (arg == 0)
      {
        return UINT_T(0);
      }
      else if (arg == 1)
      {
        return UINT_T(1);
      }
      else if (arg < 4) // arg is 2 or 3
      {
        return UINT_T(1);
      }
      else if (arg < 9) // arg is 4-8
      {
        return UINT_T(2);
      }
      else if (arg < 16) // arg is 9-15
      {
        return UINT_T(3);
      }
      else
      {
        // Use Newton's method for larger numbers
        UINT_T x = arg;
        UINT_T y = (x + 1) / 2;

        while (y < x)
        {
          x = y;
          y = (x + arg / x) / 2;
        }

        return x;
      }
    }

    template <typename UINT_T>
    consteval UINT_T sqrt_max()
    {
      using SIG_UINT_T = sig_UInt_for_UInt_t<UINT_T>;
      constexpr SIG_UINT_T maximo{maxbase<UINT_T>()};
      constexpr SIG_UINT_T uno{1};
      constexpr SIG_UINT_T base{maximo + uno};
      // constexpr SIG_UINT_T raiz_real{sqrt(base)};
      // return static_cast<UINT_T>(raiz_real);

      // Implementación simple de sqrt con Newton para compatibilidad constexpr en Clang
      constexpr auto x = static_cast<long double>(static_cast<SIG_UINT_T>(base));
      if (x == 0.0)
        return static_cast<UINT_T>(0);

      long double estimate = x * 0.5;
      for (int i = 0; i < 50; ++i)
      { // Máximo 50 iteraciones
        long double new_estimate = 0.5 * (estimate + x / estimate);
        if (estimate == new_estimate)
          break; // Convergencia
        estimate = new_estimate;
      }
      return static_cast<UINT_T>(estimate);
    }

    ///< QUEREMOS FABRICAR LA METAFUNCION TypeFromIntNumber_t<numero_sin_signo>
    ///< QUE DEVUELVA EL TIPO ENTERO SIN SIGNO MAS PEQUENO PARA EL NUMERO
    ///< numero_sin_signo
    namespace ugly_details_for_suitable_type_deduction
    {
      template <typename T, T Radix>
      struct UIntTypeForRadix;
      ///< DEFINICION PARA ESPECIALIZACION TYPE_TRAITS::UINT_TYPE_FOR_RADIX
      ///< FOR RADIX VALID
      template <integral_c T, T Radix>
        requires(Radix > 1)
      struct UIntTypeForRadix<T, Radix>
      {
        using UIntType = std::conditional_t<
            static_cast<uint64_t>(Radix) <= maxbase<uint8_t>(),
            uint8_t, std::conditional_t<static_cast<uint64_t>(Radix) <= maxbase<uint16_t>(), uint16_t, std::conditional_t<static_cast<uint64_t>(Radix) <= maxbase<uint32_t>(), uint32_t, uint64_t>>>;
      };
    } // namespace ugly_details_for_suitable_type_deduction
    using namespace ugly_details_for_suitable_type_deduction;

    ///< DEFINICION PARA LLAMAR A TYPE_TRAITS::UINT_TYPE_FOR_RADIX
    ///< CON SOLO RADIX
    ///< DEVUELVE EL TIPO MAS PEQUENO PARA EL NUMERO SIN SIGNO ENTERO QUE LE
    ///< PASAMOS EN TIEMPO DE COMPILACION SUME BIEN
    template <ullint_t Radix>
    using TypeFromIntNumber_t =
        typename UIntTypeForRadix<decltype(Radix), Radix>::UIntType;

    ///< QUEREMOS FABRICAR LA METAFUNCION TypeFromIntNumberLTSqrtMaxOfType_t<numero>
    ///< QUE DEVUELVA EL TIPO ENTERO SIN SIGNO MAS PEQUENO PARA EL NUMERO numero
    ///< TAL QUE SQRT(TYPE::MAX())>=B-1
    namespace ugly_details_for_greater_suitable_type_deduction
    {
      template <typename T, T Radix>
      struct UIntTypeForRadixContainsMultResult;
      ///< DEFINICION PARA ESPECIALIZACION
      ///< TYPE_TRAITS::UINT_TYPE_FOR_RADIX_WITH_CONTAINS_MULT_RESULT FOR RADIX VALID
      template <integral_c T, T Radix>
        requires(Radix > 1)
      struct UIntTypeForRadixContainsMultResult<T, Radix>
      {
        static constexpr ullint_t uint_value_0_max =
            static_cast<ullint_t>(sqrt_max<uchint_t>());
        static constexpr ullint_t uint_value_1_max =
            static_cast<ullint_t>(sqrt_max<usint_t>());
        static constexpr ullint_t uint_value_2_max =
            static_cast<ullint_t>(sqrt_max<uint_t>());
        static constexpr ullint_t uint_value_3_max =
            static_cast<ullint_t>(sqrt_max<ulint_t>());
        static constexpr ullint_t uint_value_4_max =
            static_cast<ullint_t>(sqrt_max<ullint_t>());
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
    } // namespace ugly_details_for_greater_suitable_type_deduction

    using namespace ugly_details_for_greater_suitable_type_deduction;

    ///< DEFINICION PARA LLAMAR A TYPE_TRAITS::UINT_TYPE_FOR_RADIX_WITH_HOLD_OPS_t
    ///< CON SOLO RADIX
    ///< DEVUELVE EL TIPO MAS PEQUENO PARA EL NUMERO SIN SIGNO ENTERO QUE LE
    ///< PASAMOS EN TIEMPO DE COMPILACION
    template <integral_c IntType, IntType Radix>
    using GreaterTypeFromIntNumber_t =
        typename UIntTypeForRadixContainsMultResult<decltype(Radix),
                                                    Radix>::UIntType;

  } // namespace type_traits
} // namespace NumRepr

#endif // BASIC_TYPES_HPP_INCLUDED
