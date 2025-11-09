// Wrapper compatibility header: re-export the canonical header in include/core/
#ifndef DIG_T_HPP_INCLUDED
#define DIG_T_HPP_INCLUDED

#include "core/dig_t.hpp"

#endif // DIG_T_HPP_INCLUDED
/**
 * @file dig_t.hpp
 * @brief Implementación de dígitos modulares para representaciones numéricas
 * @author NumericRepresentations Project
 * @date 2025
 * @version 1.0
 *
 * @details
 * Este archivo contiene la implementación completa de la clase dig_t, que proporciona
 * dígitos con aritmética modular automática. La clase ha sido validada con MSVC,
 * GCC y Clang, soportando C++20/C++23 con optimizaciones constexpr.
 */

#ifndef DIG_T_HPP_INCLUDED
#define DIG_T_HPP_INCLUDED

#include <array>
#include <string>
#include <stdexcept>

#include "core/internal/basic_types.hpp"
#include "core/internal/auxiliary_types.hpp"
#include "core/internal/auxiliary_functions.hpp"

namespace NumRepr
{

  using type_traits::maxbase;
  using type_traits::sig_SInt_for_UInt_t;
  using type_traits::sig_UInt_for_UInt_t;
  using type_traits::sqrt_max;
  using type_traits::suitable_base;
  using type_traits::uint_type_for_radix_c;

  /**
   * @brief Clase template para dígitos con aritmética modular
   *
   * Esta clase implementa un wrapper para tipos enteros sin signo que proporciona
   * aritmética modular automática. Todos los operadores están sobrecargados para
   * trabajar en módulo B, donde B es la base del sistema numérico.
   *
   * @tparam B Base del sistema numérico (debe ser > 1)
   *
   * @details
   * Características principales:
   * - Aritmética modular automática para todos los operadores
   * - Soporte para operadores especializados (&=min, |=max, ^=power, etc.)
   * - Compatibilidad con C++20/C++23 (three-way comparison, concepts)
   * - Serialización con formato autodocumentado d[valor]B<base>
   * - Optimizaciones constexpr para tiempo de compilación
   * - Validación de tipos mediante concepts
   *
   * @example
   * ```cpp
   * dig_t<10> decimal(7);        // Dígito en base 10
   * dig_t<10> otro(8);
   * auto suma = decimal + otro;   // = 5 (15 % 10)
   * auto producto = decimal * otro; // = 6 (56 % 10)
   * ```
   *
   * @note La clase utiliza template constraints para garantizar que B > 1
   * @warning Los operadores bitwise tienen semántica matemática, no bitwise tradicional
  // Wrapper compatibility header: reexport the canonical header in include/core/
  #ifndef DIG_T_HPP_INCLUDED
  #define DIG_T_HPP_INCLUDED

  // Se mantiene este archivo por compatibilidad con includes antiguos.
  // Su contenido se delega al archivo canonical en include/core/dig_t.hpp

  #include "core/dig_t.hpp"

  #endif // DIG_T_HPP_INCLUDED
     * @tparam Int_type Tipo entero (signed o unsigned)
     * @param arg Valor entero a restar
     * @return Nuevo dig_t con el resultado de la resta
     *
     * @details
     * Realiza la operación: resultado = *this - normaliza(arg)
     *
     * Implementación:
     * 1. Crea una copia de *this: ret(*this)
     * 2. Normaliza el argumento: tmp(normaliza<Int_type>(arg))
     * 3. Aplica resta: ret -= tmp
     * 4. Retorna la copia modificada
     *
     * @example
     * ```cpp
     * dig_t<10> a(7);
     * dig_t<10> b = a - 3;   // b = 4 (7-3 = 4)
     * dig_t<10> c = a - 15;  // c = 2 (7-5 = 2) si normaliza(15)=5
     * ```
     *
     * @note El argumento se normaliza automáticamente antes de la resta
     */
    template <type_traits::integral_c Int_type>
    constexpr dig_t operator-(Int_type arg) const noexcept
    {
      dig_t ret(*this);
      const dig_t tmp(normaliza<Int_type>(arg));
      ret -= tmp;
      return ret;
    }

    /**
     * @brief Operador de multiplicación binario para tipos enteros (template)
     *
     * @tparam Int_type Tipo entero (signed o unsigned)
     * @param arg Valor entero por el cual multiplicar
     * @return Nuevo dig_t con el resultado de la multiplicación
     *
     * @details
     * Realiza la operación: resultado = *this * normaliza(arg)
     *
     * Implementación:
     * 1. Crea una copia de *this: ret(*this)
     * 2. Normaliza el argumento: tmp(normaliza<Int_type>(arg))
     * 3. Aplica multiplicación: ret *= tmp
     * 4. Retorna la copia modificada
     *
     * @example
     * ```cpp
     * dig_t<10> a(7);
     * dig_t<10> b = a * 3;   // b = 1 (21 % 10 = 1)
     * dig_t<10> c = a * 15;  // c = 5 (7*5 = 35, 35%10 = 5) si normaliza(15)=5
     * ```
     *
     * @note El argumento se normaliza automáticamente antes de la multiplicación
     */
    template <type_traits::integral_c Int_type>
    constexpr dig_t operator*(Int_type arg) const noexcept
    {
      dig_t ret(*this);
      const dig_t tmp(normaliza<Int_type>(arg));
      ret *= tmp;
      return ret;
    }

    /**
     * @brief Operador de división binario para tipos enteros (template)
     *
     * @tparam Int_type Tipo entero (signed o unsigned)
     * @param arg Valor entero divisor
     * @return Nuevo dig_t con el resultado de la división
     *
     * @details
     * Realiza la operación: resultado = *this / normaliza(arg)
     *
     * Implementación:
     * 1. Crea una copia de *this: ret(*this)
     * 2. Normaliza el argumento: cparg(normaliza<Int_type>(arg))
     * 3. Si cparg != 0: aplica división ret /= cparg
     * 4. Si cparg == 0: no opera
     * 5. Retorna la copia (modificada o no)
     *
     * @example
     * ```cpp
     * dig_t<10> a(8);
     * dig_t<10> b = a / 3;   // b = 2 (8/3 = 2)
     * dig_t<10> c = a / 15;  // c = 1 (8/5 = 1) si normaliza(15)=5
     * ```
     *
     * @note El argumento se normaliza automáticamente antes de la división
     * @warning No arroja excepción en división por cero normalizado
     */
    template <type_traits::integral_c Int_type>
    constexpr dig_t operator/(Int_type arg) const noexcept
    {
      dig_t ret(*this);
      const dig_t cparg(normaliza<Int_type>(arg));
      if (cparg != dig_0())
        ret /= cparg;
      return ret;
    }

    /**
     * @brief Operador de módulo binario para tipos enteros (template)
     *
     * @tparam Int_type Tipo entero (signed o unsigned)
     * @param arg Valor entero divisor para el módulo
     * @return Nuevo dig_t con el resultado del módulo
     *
     * @details
     * Realiza la operación: resultado = *this % normaliza(arg)
     *
     * Implementación:
     * 1. Crea una copia de *this: ret(*this)
     * 2. Normaliza el argumento: cparg(normaliza<Int_type>(arg))
     * 3. Si cparg != 0: aplica módulo ret %= cparg
     * 4. Si cparg == 0: no opera
     * 5. Retorna la copia (modificada o no)
     *
     * @example
     * ```cpp
     * dig_t<10> a(8);
     * dig_t<10> b = a % 3;   // b = 2 (8 % 3 = 2)
     * dig_t<10> c = a % 15;  // c = 3 (8 % 5 = 3) si normaliza(15)=5
     * ```
     *
     * @note El argumento se normaliza automáticamente antes del módulo
     * @warning No arroja excepción en módulo por cero normalizado
     */
    template <type_traits::integral_c Int_type>
    constexpr dig_t operator%(Int_type arg) const noexcept
    {
      dig_t ret(*this);
      const dig_t cparg(normaliza<Int_type>(arg));
      if (cparg != dig_0())
        ret %= cparg;
      return ret;
    }

    /****************************************/
    /*									  */
    /*	     COMPLEMENTO BASE 			  */
    /*	      Y BASE MENOS 1			  */
    /*									  */
    /****************************************/

    /**
     * @brief Operador NOT bitwise (complemento a B-1)
     *
     * @return Nuevo dig_t con el complemento a B-1 del dígito
     *
     * @details
     * Implementación basada en analogía con aritmética de dígitos:
     * En base 2, ~bit invierte el bit (0↔1). En base B, ~dígito
     * calcula el complemento a (B-1): resultado = (B-1) - dígito
     *
     * Fórmula: ~m_d = ui_max() - m_d = (B-1) - m_d
     *
     * @example
     * ```cpp
     * dig_t<10> a(3);
     * dig_t<10> b = ~a;  // b = 6 (9-3=6, complemento a 9)
     *
     * dig_t<10> c(7);
     * dig_t<10> d = ~c;  // d = 2 (9-7=2)
     *
     * // Analogía: en base 2: ~0=1, ~1=0
     * //           en base B: ~x = (B-1)-x
     * ```
     *
     * @note Equivalente al método C_Bm1()
     * @note En base 10: ~3=6, ~7=2, ~0=9, ~9=0
     */
    constexpr dig_t operator~() const noexcept
    {
      return dig_t(ui_max() - m_d);
    }

    /**
     * @brief Operador menos unario (complemento a B)
     *
     * @return Nuevo dig_t con el complemento a B del dígito
     *
     * @details
     * Calcula el complemento a B (complemento aritmético):
     * - Si m_d == 0: resultado = 0
     * - Si m_d != 0: resultado = B - m_d
     *
     * Este operador implementa la negación aritmética modular.
     *
     * @example
     * ```cpp
     * dig_t<10> a(3);
     * dig_t<10> b = -a;  // b = 7 (10-3=7)
     *
     * dig_t<10> c(0);
     * dig_t<10> d = -c;  // d = 0 (caso especial)
     *
     * // Verificación: a + (-a) = 0 (mod B)
     * // 3 + 7 = 10 ≡ 0 (mod 10) ✓
     * ```
     *
     * @note Equivalente al método C_B()
     * @note Cumple la propiedad: x + (-x) ≡ 0 (mod B) para x ≠ 0
     */
    constexpr dig_t operator-() const noexcept
    {
      return dig_t((m_d == 0) ? 0 : (B - m_d));
    }

    /**
     * @brief Operador NOT lógico (complemento a B-1)
     *
     * @return Nuevo dig_t con el complemento a B-1 del dígito
     *
     * @details
     * Implementación basada en analogía con aritmética de dígitos:
     * En base 2, !bit invierte la lógica booleana. En base B, !dígito
     * calcula el complemento a (B-1), igual que ~.
     *
     * Comportamiento: !dígito = (B-1) - dígito
     *
     * @example
     * ```cpp
     * dig_t<10> a(3);
     * dig_t<10> b = !a;  // b = 6 (9-3=6, complemento a 9)
     *
     * // Analogía: en base 2: !0=1, !1=0
     * //           en base B: !x = (B-1)-x
     * ```
     *
     * @note Idéntico a operator~() - ambos implementan complemento a (B-1)
     * @note Equivalente al método C_Bm1()
     */
    constexpr dig_t operator!() const noexcept
    {
      return dig_t(ui_max() - m_d);
    }

    /**
     * @brief Operador AND lógico (implementado como mínimo de dígitos)
     *
     * @param arg Dígito con el cual comparar
     * @return El menor de los dos dígitos
     *
     * @details
     * Implementación basada en analogía con aritmética de dígitos:
     * En base 2, && opera con lógica booleana. En base B, && opera
     * como el mínimo, igual que &.
     *
     * Comportamiento: a && b = min(a, b)
     *
     * @example
     * ```cpp
     * dig_t<10> a(7);
     * dig_t<10> b(3);
     * dig_t<10> c = a && b;  // c = 3 (min(7,3))
     *
     * // Analogía: en base 2: 1&&0=0 (min), en base B: a&&b=min(a,b)
     * ```
     *
     * @note Idéntico a operator& - ambos implementan mínimo
     */
    constexpr dig_t operator&&(const dig_t &arg) const noexcept
    {
      return (((*this) <= arg) ? (*this) : arg);
    }

    /**
     * @brief Operador OR lógico (implementado como máximo de dígitos)
     *
     * @param arg Dígito con el cual comparar
     * @return El mayor de los dos dígitos
     *
     * @details
     * Implementación basada en analogía con aritmética de dígitos:
     * En base 2, || opera con lógica booleana. En base B, || opera
     * como el máximo, igual que |.
     *
     * Comportamiento: a || b = max(a, b)
     *
     * @example
     * ```cpp
     * dig_t<10> a(7);
     * dig_t<10> b(3);
     * dig_t<10> c = a || b;  // c = 7 (max(7,3))
     *
     * // Analogía: en base 2: 1||0=1 (max), en base B: a||b=max(a,b)
     * ```
     *
     * @note Idéntico a operator| - ambos implementan máximo
     */
    constexpr dig_t operator||(const dig_t &arg) const noexcept
    {
      return (((*this) >= arg) ? (*this) : arg);
    }

    constexpr /// "C_Bm1" es identico a "operator!()"
        dig_t C_Bm1() const noexcept
    {
      return dig_t(ui_max() - m_d);
    }

    constexpr /// "C_B" es identico a "operator-()"
        dig_t C_B() const noexcept
    {
      return dig_t((m_d == 0) ? 0 : (B - m_d));
    }

    /****************************************************/
    /*				    							  */
    /*    MODIFICADORES COMPLEMENTO	    			  */
    /*				    							  */
    /****************************************************/

    constexpr const dig_t &mC_Bm1() noexcept
    {
      m_d = (ui_max() - m_d);
      return (*this);
    }

    constexpr const dig_t &mC_B() noexcept
    {
      (m_d == 0) ? (m_d) : (m_d = (B - m_d));
      return (*this);
    }

    /// dig_t<uchint,7> a,b,c;
    /// a = 5;
    /// b = 2;
    /// c = 0;
    /// !a == 1 is TRUE  a.C_Bm1() == 1 is TRUE
    /// !b == 4 is TRUE  b.C_Bm1() == 4 is TRUE
    /// !c == 6 is TRUE  c.C_Bm1() == 6 is TRUE
    /// -a == 2 is TRUE  a.C_B() == 2 is TRUE
    /// -b == 5 is TRUE  b.C_B() == 5 is TRUE
    /// -c == 0 is TRUE  c.C_B() == 0 is TRUE
    ///  a.mC_Bm1() == 1 is TRUE  a == 1 is TRUE
    ///  b.mC_Bm1() == 4 is TRUE  b == 4 is TRUE
    ///  c.mC_Bm1() == 6 is TRUE  c == 6 is TRUE
    ///  a.mC_B() 	== 2 is TRUE  a	== 2 is TRUE
    ///  b.mC_B() 	== 5 is TRUE  b	== 5 is TRUE
    ///  c.mC_B() 	== 0 is TRUE  c	== 0 is TRUE

    /**********************************/
    /*                            	*/
    /*   	NULO Y MAXIMO         	  	*/
    /*                            	*/
    /**********************************/

    constexpr bool is_0() const noexcept { return (m_d == ui_0()); }

    constexpr bool is_1() const noexcept { return (m_d == ui_1()); }

    constexpr bool is_0or1() const noexcept
    {
      return ((m_d == ui_0()) || (m_d == ui_1()));
    }

    constexpr bool is_not_1() const noexcept { return (m_d != ui_1()); }

    constexpr bool is_not_0() const noexcept { return (m_d != ui_0()); }

    constexpr bool is_not_0or1() const noexcept { return (!is_0or1()); }

    constexpr bool is_Bm1() const noexcept { return (m_d == ui_Bm1()); }

    constexpr bool is_not_Bm1() const noexcept
    {
      return (m_d != ui_Bm1());
    }

    constexpr bool is_Bm1orBm2() const noexcept
    {
      return (is_Bm1() || is_Bm2());
    }

    constexpr bool is_not_Bm1orBm2() const noexcept
    {
      return (is_not_Bm1() && is_not_Bm2());
    }

    constexpr bool is_Bm2() const noexcept { return (m_d == ui_Bm2()); }

    constexpr bool is_not_Bm2() const noexcept
    {
      return (m_d != ui_Bm2());
    }

    constexpr bool is_not_maxormin() const noexcept
    {
      return (is_not_0() && is_not_Bm1());
    }

    constexpr bool is_maxormin() const noexcept
    {
      return (is_0() || is_Bm1());
    }

    constexpr bool is_far_maxormin() const noexcept
    {
      if constexpr (B == 2u)
      {
        return false;
      }
      else
      {
        return (is_not_0() && is_not_Bm1() && is_not_1() && is_not_Bm2());
      }
    }

    constexpr bool is_near_maxormin() const noexcept
    {
      if constexpr (B == 2u)
      {
        return true;
      }
      else
      {
        return (is_0() || is_Bm1() || is_1() || is_Bm2());
      }
    }

    /**********************************/
    /*		    	                */
    /* 	     VARIOS CASTS	        */
    /*						        */
    /**********************************/

    /// TIENE QUE DEVOLVER STD::STRING
  private:
    std::string num_to_string() const noexcept
    {
      const std::int64_t data_member = static_cast<std::int64_t>(this->m_d);
      std::ostringstream fmtr_obj;
      fmtr_obj << data_member;
      const std::string ret{fmtr_obj.str()};
      return ret;
    }

    std::string radix_str() const noexcept
    {
      constexpr std::int64_t radix = static_cast<std::int64_t>(B);
      std::ostringstream fmtr_obj;
      fmtr_obj << radix;
      const std::string ret{static_cast<std::string>("B") + static_cast<std::string>(fmtr_obj.str())};
      return ret;
    }

    /**
     * @brief Parser constexpr unificado para ambos formatos de entrada
     *
     * @param str String a parsear
     * @param size Longitud del string
     * @return Par con valor parseado y éxito del parsing
     *
     * @details
     * Parser constexpr que acepta ambos formatos:
     * - Formato estricto: "d[n]Bbase"
     * - Formato legacy: "dig#n#Bbase"
     *
     * Se utiliza internamente por from_string, from_cstr, constructores
     * y operator>> para garantizar consistencia total.
     */
    static constexpr std::pair<uint_t, bool> parse_impl(const char *str, std::size_t size, std::uint64_t base_template) noexcept
    {
      if (!str || size < 4)
        return {0, false};

      std::size_t pos = 0;

      // Determinar formato: 'd' o "dig"
      bool is_strict_format = false;

      if (size >= 4 && str[0] == 'd' && str[1] == '[')
      {
        // Formato estricto: d[n]B
        is_strict_format = true;
        pos = 2; // Saltar "d["
      }
      else if (size >= 6 && str[0] == 'd' && str[1] == 'i' && str[2] == 'g' && str[3] == '#')
      {
        // Formato legacy: dig#n#B
        is_strict_format = false;
        pos = 4; // Saltar "dig#"
      }
      else
      {
        return {0, false}; // Formato no reconocido
      }

      // Extraer el número usando aritmética modular incremental para evitar overflow
      uint_t numero = 0;
      std::size_t digit_count = 0;

      if (is_strict_format)
      {
        // Leer hasta ']'
        while (pos < size && str[pos] != ']')
        {
          if (str[pos] >= '0' && str[pos] <= '9')
          {
            // Aritmética modular incremental: (numero * 10 + digito) % B
            // Esto evita overflow manteniendo numero siempre < B
            sig_uint_t temp = static_cast<sig_uint_t>(numero) * 10 + (str[pos] - '0');
            numero = static_cast<uint_t>(temp % static_cast<sig_uint_t>(base_template));
            digit_count++;
          }
          else
          {
            return {0, false};
          }
          pos++;
        }

        if (pos >= size || str[pos] != ']')
          return {0, false};
        pos++; // Saltar ']'
      }
      else
      {
        // Leer hasta '#'
        while (pos < size && str[pos] != '#')
        {
          if (str[pos] >= '0' && str[pos] <= '9')
          {
            // Aritmética modular incremental: (numero * 10 + digito) % B
            sig_uint_t temp = static_cast<sig_uint_t>(numero) * 10 + (str[pos] - '0');
            numero = static_cast<uint_t>(temp % static_cast<sig_uint_t>(base_template));
            digit_count++;
          }
          else
          {
            return {0, false};
          }
          pos++;
        }

        if (pos >= size || str[pos] != '#')
          return {0, false};
        pos++; // Saltar '#'
      }

      if (digit_count == 0)
        return {0, false};

      // Verificar 'B'
      if (pos >= size || str[pos] != 'B')
        return {0, false};
      pos++;

      // Extraer y verificar base
      sig_uint_t base_leida = 0;
      std::size_t base_digits = 0;

      while (pos < size && str[pos] >= '0' && str[pos] <= '9')
      {
        base_leida = base_leida * 10 + (str[pos] - '0');
        base_digits++;
        pos++;
      }

      if (base_digits == 0 || base_leida != base_template)
        return {0, false};

      // Ya aplicamos módulo incrementalmente, no necesario aplicar otra vez
      return {numero, true};
    }

  public:
    constexpr std::uint64_t radix() const { return B; }

    /**
     * @brief Convierte el dígito a su representación en string
     *
     * @return std::string con formato "d[valor]Bbase"
     *
     * @details
     * Genera la representación textual del dígito usando el formato estricto:
     * - Formato: `d[n]B`
     * - `d`: Identificador de dígito
     * - `[n]`: Valor del dígito entre corchetes
     * - `B`: Indicador de base seguido del valor de la base
     *
     * Este formato es consistente con el operador<< y complementario
     * al parsing realizado por operator>>.
     *
     * @example
     * ```cpp
     * dig_t<10> a(7);
     * std::string s = a.to_string();  // s = "d[7]B10"
     *
     * dig_t<16> b(15);
     * auto str = b.to_string();       // str = "d[15]B16"
     * ```
     *
     * @note Formato estricto: usa [] como separadores (no #)
     * @note Consistente con operator<< para uniformidad de salida
     */
    constexpr std::string to_string() const noexcept
    {
      const std::string num{this->num_to_string()};
      const std::string ret{"d[" + num + "]" + radix_str()};
      return ret;
    }
  };

  /************************************/
  /*                                  */
  /*   IMPLEMENTACIONES DE PARSING    */
  /*                                  */
  /************************************/

  template <std::uint64_t Base>
    requires(Base > 1)
  dig_t<Base> dig_t<Base>::from_string(const std::string &str)
  {
    auto [value, success] = parse_impl(str.c_str(), str.size(), Base);

    if (!success)
    {
      throw std::invalid_argument("Invalid dig_t format: expected 'd[number]B" +
                                  std::to_string(Base) + "' or 'dig#number#B" +
                                  std::to_string(Base) + "'");
    }

    return dig_t<Base>(value);
  }

  template <std::uint64_t Base>
    requires(Base > 1)
  constexpr dig_t<Base> dig_t<Base>::from_cstr(const char *str)
  {
    if (str == nullptr)
    {
      throw std::invalid_argument("Null pointer passed to from_cstr");
    }

    // Calcular longitud manualmente para constexpr
    std::size_t len = 0;
    while (str[len] != '\0')
      len++;

    auto [value, success] = parse_impl(str, len, Base);

    if (!success)
    {
      throw std::invalid_argument("Invalid dig_t format: expected 'd[number]B" +
                                  std::to_string(Base) + "' or 'dig#number#B" +
                                  std::to_string(Base) + "'");
    }

    return dig_t<Base>(value);
  }

  // Implementaciones de constructores desde string
  template <std::uint64_t Base>
    requires(Base > 1)
  dig_t<Base>::dig_t(const std::string &str) : dig_t(from_string(str))
  {
  }

  template <std::uint64_t Base>
    requires(Base > 1)
  constexpr dig_t<Base>::dig_t(const char *str) : dig_t(from_cstr(str))
  {
  }

  /************************************/
  /*                                  */
  /*         ISTREAM Y OSTREAM        */
  /*                                  */
  /************************************/

  /**
   * @brief Operador de entrada desde istream (operator>>)
   *
   * @tparam Base Base del sistema numérico (debe ser > 1)
   * @param is Stream de entrada (std::istream)
   * @param arg Referencia al dig_t donde almacenar el resultado
   * @return Referencia al istream para encadenamiento
   *
   * @details
   * Parsea cualquiera de los formatos soportados desde un stream de entrada:
   * - Formato estricto: "d[número]Bbase"
   * - Formato alternativo: "dig#número#Bbase"
   *
   * Implementa una máquina de estados que detecta automáticamente el formato.
   * Valida que la base coincida con la plantilla y normaliza el número.
   *
   * @example
   * ```cpp
   * std::stringstream ss1("d[42]B10");
   * dig_t<10> d1;
   * ss1 >> d1;  // d1.m_d = 2 (formato estricto)
   *
   * std::stringstream ss2("dig#142#B10");
   * dig_t<10> d2;
   * ss2 >> d2;  // d2.m_d = 2 (formato alternativo)
   * ```
   *
   * @note Acepta ambos formatos para máxima flexibilidad de entrada
   * @note Valida que la base del formato coincida con la plantilla
   * @note El número se normaliza automáticamente (número % Base)
   */
  /**
   * @brief Operador de entrada desde istream (operator>>)
   *
   * @tparam Base Base del sistema numérico (debe ser > 1)
   * @param is Stream de entrada (std::istream)
   * @param arg dig_t donde almacenar el valor parseado
   * @return Referencia al istream para encadenamiento
   *
   * @details
   * Parsea un dígito desde un stream de entrada soportando ambos formatos:
   * - Formato estricto: "d[n]Bbase" (salida estándar)
   * - Formato legacy: "dig#n#Bbase" (compatibilidad hacia atrás)
   *
   * Esta implementación delega al método `from_string()` para garantizar
   * consistencia en el análisis sintáctico y soporte completo del formato dual.
   *
   * Formatos de entrada soportados:
   * 1. `d[n]B` - Formato estricto con corchetes
   * 2. `dig#n#B` - Formato legacy con almohadillas
   *
   * Donde:
   * - `n`: Valor del dígito
   * - Base implícita del template
   *
   * @example
   * ```cpp
   * std::istringstream iss1("d[7]B10");
   * dig_t<10> d1;
   * iss1 >> d1;  // d1.get() == 7
   *
   * std::istringstream iss2("dig#5#B10");
   * dig_t<10> d2;
   * iss2 >> d2;  // d2.get() == 5
   * ```
   *
   * @throws std::invalid_argument Si el formato no es válido o el valor excede la base
   */
  template <std::uint64_t Base>
    requires(Base > 1)
  std::istream &operator>>(std::istream &is, dig_t<Base> &arg)
  {
    std::string input_str;
    is >> input_str; // Leer toda la cadena de una vez

    if (is.fail())
    {
      return is;
    }

    try
    {
      // Delegar al parsing unificado de from_string()
      arg = dig_t<Base>::from_string(input_str);
    }
    catch (const std::exception &)
    {
      is.setstate(std::ios::failbit);
    }

    return is;
  }

  /**
   * @brief Operador de salida hacia ostream (operator<<)
   *
   * @tparam Base Base del sistema numérico (debe ser > 1)
   * @param os Stream de salida (std::ostream)
   * @param arg dig_t a serializar
   * @return Referencia al ostream para encadenamiento
   *
   * @details
   * Serializa el dígito usando el formato clásico con corchetes: "d[valor]Bbase"
   *
   * Formato de salida: `d[n]B`
   * - `d`: Identificador de dígito
   * - `[n]`: Valor del dígito entre corchetes
   * - `B`: Indicador de base seguido del valor de la base
   *
   * @example
   * ```cpp
   * dig_t<10> d(7);
   * std::cout << d;  // Salida: "d[7]B10"
   *
   * dig_t<16> h(15);
   * std::cout << h;  // Salida: "d[15]B16"
   * ```
   *
   * @note Diferencia con to_string(): usa [] en lugar de # como separadores
   * @note Los valores se convierten a std::int64_t para compatibilidad de salida
   * @note Formato complementario al operador>> que usa dig#n#B
   */
  template <std::uint64_t Base>
    requires(Base > 1)
  std::ostream &operator<<(std::ostream &os, dig_t<Base> arg)
  {
    os << "d[" << static_cast<std::int64_t>(arg())
       << "]B" << static_cast<std::int64_t>(Base);
    return os;
  }

} // namespace NumRepr
#endif // DIG_T__HPP___INCLUDED
