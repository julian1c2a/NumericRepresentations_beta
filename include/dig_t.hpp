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

#include "basic_types.hpp"
#include "auxiliary_types.hpp"
#include "auxiliary_functions.hpp"

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
   */
  template <std::uint64_t B>
    requires(B > 1)
  struct dig_t
  {
    /**
     * @brief Tipo entero sin signo apropiado para almacenar valores en base B
     *
     * Se selecciona automáticamente el tipo mínimo necesario (uint8_t, uint16_t, etc.)
     * que puede contener todos los valores válidos [0, B-1].
     */
    using uint_t = typename type_traits::TypeFromIntNumber_t<static_cast<uint64_t>(B)>;

  private:
    /**
     * @brief Valor del dígito almacenado
     *
     * Siempre se mantiene en el rango [0, B-1] mediante operaciones modulares.
     */
    uint_t m_d;

  public:
    /**
     * @brief Tipo entero sin signo de mayor capacidad para operaciones intermedias
     *
     * @details
     * El prefijo "sig_" significa "**siguiente**" (español: next/higher capacity), NO "signed".
     * Se obtiene el siguiente tipo entero sin signo de mayor capacidad que uint_t.
     *
     * Usado para evitar overflow en multiplicaciones antes de aplicar módulo.
     *
     * **Ejemplos:**
     * - Si uint_t es uint8_t  → sig_uint_t será uint16_t
     * - Si uint_t es uint16_t → sig_uint_t será uint32_t
     * - Si uint_t es uint32_t → sig_uint_t será uint64_t
     *
     * @note Crítico para parsing correcto de números grandes (ej: 999999 % 10)
     */
    using sig_uint_t = typename type_traits::sig_UInt_for_UInt_t<uint_t>;

    /**
     * @brief Tipo entero CON SIGNO de mayor capacidad para operaciones intermedias
     *
     * @details
     * El prefijo "sig_" significa "**siguiente**" (español: next/higher capacity), NO "signed".
     * Se obtiene el siguiente tipo entero CON SIGNO de mayor capacidad que uint_t.
     *
     * Usado para operaciones que requieren números negativos intermedios,
     * como restas que pueden generar valores temporalmente negativos.
     *
     * **Ejemplos:**
     * - Si uint_t es uint8_t  → sig_sint_t será int16_t
     * - Si uint_t es uint16_t → sig_sint_t será int32_t
     * - Si uint_t es uint32_t → sig_sint_t será int64_t
     */
    using sig_sint_t = typename type_traits::sig_SInt_for_UInt_t<uint_t>;

    /** @brief Par de enteros para operaciones de multiplicación (carry, resultado) */
    using uintspair = std::array<uint_t, 2>;

    /** @brief Par de dígitos para operaciones especializadas */
    using digspair = std::array<dig_t, 2>;

    /** @brief Lista de pares para tablas de multiplicación */
    using uintspairlist = std::array<uintspair, B>;

    /** @brief Tabla completa de multiplicación B×B */
    using uintspairtbl = std::array<uintspairlist, B>;

    /**
     * @brief Calcula el producto de dos dígitos con carry en tiempo de compilación
     *
     * @tparam n Primer dígito multiplicando (debe ser < B)
     * @tparam m Segundo dígito multiplicando (debe ser < B)
     * @return Par {carry, resultado} donde resultado = (n*m) % B y carry = (n*m) / B
     *
     * @details
     * Esta función template consteval realiza multiplicación con detección automática
     * de overflow. Si B es grande, usa tipos de precisión superior para evitar overflow.
     *
     * @note Actualmente no utilizada - preparada para futuras optimizaciones de tablas
     * @warning Los parámetros deben satisfacer n < B && m < B
     */
    template <uint_t n, uint_t m>
      requires((n < B) && (m < B))
    static consteval uintspair mult() noexcept
    {
      if constexpr (B > type_traits::sqrt_max<uint_t>())
      {
        constexpr sig_uint_t sup_n{n};
        constexpr sig_uint_t sup_m{m};
        constexpr sig_uint_t result{sup_n * sup_m};
        constexpr uint_t ret_1{result / B}; // "DECENAS"
        constexpr uint_t ret_0{result % B}; // "UNIDADES"
        constexpr uintspair ret{ret_1, ret_0};
        return ret;
      }
      else
      {
        constexpr uint_t result{n * m};
        constexpr uint_t ret_1{result / B}; // "DECENAS"
        constexpr uint_t ret_0{result % B}; // "UNIDADES"
        constexpr uintspair ret{ret_1, ret_0};
        return ret;
      }
    }
    /// PARA B=3 2*2									      1       COMIENZAN POR 2
    /// B-2
    /// PARA B=4 2*2 2*3 3*4							  3       COMIENZAN POR 2 B-2, 3
    /// B-3
    /// PARA B=5 2*2 2*3 2*4 3*3 3*4 4*4		6       COMIENZAN POR 2 B-2, 3 B-3, 4
    /// B-4 PARA B=6 2*2 2*3 2*4 2*5 3*3 3*4 3*5 4*4 4*5 5*5
    ///                                    10       COMIENZAN POR 2 B-2, 3 B-3, 4 B-4, 5 B-5
    /// PARA B=r 2*2 2*(2+1) ... 2*(r-1)		r-1  r
    ///                                     COMIENZAN POR 2 B-2, 3 B-3, 4 B-4, 5 B-1, ... , r-1 B-r+1
    ///			                   3*3		 ... 3*(r-1) r-2
    ///						                     ...
    ///			                (r-1)*(r-1)... r-(r-1)
    ///													_______
    ///							           (r-2)r-(r-1)*r/2 + 1
    ///                     =  [2(r-2)-((r-2)+1)]r/2 + 1
    ///							        =  ((r-3)r + 2)/2
    ///                     =	 (r^2 - 3r + 2) / 2
    ///                     =  a r^2 + b r + c
    ///							   				------------------
    ///													1 = a  9 + b 3 + c
    ///													3 = a 16 + b 4 + c
    ///													6 = a 25 + b 5 + c
    ///													------------------
    ///													1 = a  9 + b 3 + c
    ///  												2 = a  7 + b 1
    ///													------------------
    ///													5 = a 16 + b 2
    ///													------------------
    ///													1 = a  9 + b 3 + c
    ///													2 = a  7 + b
    ///                         1 = a  2
    ///													------------------
    ///													c = 2/2
    ///                         b = -3/2
    ///                         a =  1/2
    ///													------------------
    ///													SIZE = (B^2 - 3B + 2)/2 	2+3+4+...+B-1 = 1+2+3+4+...+B-1 - 1 =
    ///                         = (B-1)B/2 - 2(B-1)/2   = (B^2 - B - 2B +2)/2 =  (B^2-3B+2)/2
    ///
    /// FALTARIA HACERLAS SOLO PARA BASES MAYORES QUE 2
    /// CODE NEW USING TYPES :
    /// using pair_map = std::pair<uintspair,uintspair>;
    /// CODE MULTTABLE:
    ///		static consteval std::array<pair_map,(B^2 - 3B + 2)/2>
    /// multtable{make_multtables()};
    /// CODE FOR MAKE_MULTTABLES():
    ///		static consteval
    ///		std::array<pair_map,(B^2 - 3B + 2)/2> make_multtables() noexcept
    ///{ 			std::array<pair_map,(B^2 - 3B + 2)/2>	ret;
    ///			/// ESTO QUE SIGUE HABRIA QUE HACERLO POR UNROOLING LOOP EN
    /// COMPILE TIME
    ///			/// YA QUE IDX E IDY NO SON CONSTANTES EN TIEMPO DE
    /// COMPILACION
    ///			///	LO MEJOR ES HACERLO EN UNA CLASE TEMPLATE POR
    /// RECURSION 			for(size_t idx{2} ; idx < B ; ++idx) { 				for(size_t idy{idx} ; idy
    ///< B ; ++idy) { 					make_pair(make_array(idx,idy),mult<idx,idy>());
    ///				}
    ///			}
    ///		}

  public:
    constexpr explicit operator uint_t() const noexcept { return m_d; }

    constexpr uint_t get() const noexcept { return (m_d); }

    constexpr explicit operator sig_uint_t() const noexcept
    {
      return static_cast<sig_uint_t>(m_d);
    }

    constexpr explicit operator sig_sint_t() const noexcept
    {
      return static_cast<sig_sint_t>(m_d);
    }
    /// dig_t<10> a{3};
    /// a()->3 (como uint)
    constexpr uint_t operator()() const noexcept { return (m_d); }
    /// dig_t<10> digito{4};
    /// digito() devuelve un 4 de tipo uchint

    constexpr void set_0() noexcept { m_d = 0; }
    constexpr void set_1() noexcept { m_d = 1; }
    constexpr void set_Bm1() noexcept { m_d = B - 1; }
    constexpr void set_Bm2() noexcept { m_d = B - 2; }
    constexpr void set_dig(dig_t d) noexcept { m_d = d.m_d; }
    constexpr void set_dig(uint_t di) noexcept { m_d = di % B; }

  public:
    ////////////////////////////////////////////////////////////////////////////
    consteval static bool is_prime() noexcept
    {
      return auxiliary_functions::is_prime(static_cast<std::size_t>(B));
    }

    // ========================================================================
    /// @name Constructores de dígitos especiales
    /// @{

    /** @brief Crea el dígito máximo (B-1) */
    consteval static dig_t dig_max() noexcept { return dig_t(B - 1u); };

    /** @brief Crea el dígito submáximo (B-2) */
    consteval static dig_t dig_submax() noexcept { return dig_t(B - 2u); }

    /** @brief Alias para dig_max() - dígito B-1 */
    consteval static dig_t dig_Bm1() noexcept { return dig_t(B - 1u); }

    /** @brief Alias para dig_submax() - dígito B-2 */
    consteval static dig_t dig_Bm2() noexcept { return dig_t(B - 2u); }

    /** @brief Crea el dígito cero (elemento neutro aditivo) */
    consteval static dig_t dig_0() noexcept { return dig_t(); }

    /** @brief Crea el dígito uno (elemento neutro multiplicativo) */
    consteval static dig_t dig_1() noexcept { return dig_t(1u); }

    /// @}

    // ========================================================================
    /// @name Constructores de valores uint_t especiales
    /// @{

    /** @brief Valor uint_t máximo (B-1) */
    consteval static uint_t ui_max() noexcept { return uint_t(B - 1u); }

    /** @brief Valor uint_t submáximo (B-2) */
    consteval static uint_t ui_submax() noexcept { return uint_t(B - 2u); }

    /** @brief Alias para ui_max() */
    consteval static uint_t ui_Bm1() noexcept { return uint_t(B - 1u); }

    /** @brief Alias para ui_submax() */
    consteval static uint_t ui_Bm2() noexcept { return uint_t(B - 2u); }

    /** @brief Valor uint_t cero */
    consteval static uint_t ui_0() noexcept { return uint_t(0u); }

    /** @brief Valor uint_t uno */
    consteval static uint_t ui_1() noexcept { return uint_t(1u); }

    /// @}

    /// @name Constructores de valores sig_uint_t especiales
    /// @{

    /** @brief Valor de la base B en tipo sig_uint_t */
    consteval static sig_uint_t sui_B() noexcept
    {
      return static_cast<sig_uint_t>(B);
    }

    /** @brief Valor sig_uint_t máximo (B-1) */
    consteval static sig_uint_t sui_max() noexcept
    {
      return static_cast<sig_uint_t>(B - 1u);
    }

    /** @brief Valor sig_uint_t submáximo (B-2) */
    consteval static sig_uint_t sui_submax() noexcept
    {
      return static_cast<sig_uint_t>(B - 2u);
    }

    /** @brief Valor sig_uint_t cero */
    consteval static sig_uint_t sui_0() noexcept
    {
      return static_cast<sig_uint_t>(0u);
    }

    /** @brief Valor sig_uint_t uno */
    consteval static sig_uint_t sui_1() noexcept
    {
      return static_cast<sig_uint_t>(1u);
    }

    /// @}

    /// @name Constructores de valores sig_sint_t especiales
    /// @{

    /** @brief Valor de la base B en tipo sig_sint_t */
    consteval static sig_sint_t ssi_B() noexcept
    {
      return static_cast<sig_sint_t>(B);
    }

    /** @brief Valor sig_sint_t máximo (B-1) */
    consteval static sig_sint_t ssi_max() noexcept
    {
      return static_cast<sig_sint_t>(B - 1u);
    }

    /** @brief Valor sig_sint_t submáximo (B-2) */
    consteval static sig_sint_t ssi_submax() noexcept
    {
      return static_cast<sig_sint_t>(B - 2u);
    }
    /** @brief Valor sig_sint_t cero */
    consteval static sig_sint_t ssi_0() noexcept
    {
      return static_cast<sig_sint_t>(0u);
    }

    /** @brief Valor sig_sint_t uno */
    consteval static sig_sint_t ssi_1() noexcept
    {
      return static_cast<sig_sint_t>(1u);
    }

    /// @}

  public:
    // ========================================================================
    /// @name Constructores
    /// @{

    /**
     * @brief Constructor por defecto - crea dígito cero
     *
     * Inicializa el dígito con valor 0, que es el elemento neutro aditivo.
     * Es consteval para optimización en tiempo de compilación.
     */
    consteval inline dig_t() noexcept : m_d(0u) {}

  private:
    /**
     * @brief Normaliza cualquier valor entero al rango [0, B-1]
     *
     * @tparam Int_t Tipo entero (con o sin signo) que cumple integral_c concept
     * @param arg Valor a normalizar
     * @return Valor normalizado en el rango [0, B-1]
     *
     * @details
     * Realiza la operación modular arg % B considerando:
     * - Tipos con y sin signo
     * - Diferentes tamaños de tipos (evita overflow)
     * - Valores negativos (los convierte correctamente a positivos)
     *
     * @note Es la función clave que garantiza que todos los valores estén en rango válido
     */
    template <type_traits::integral_c Int_t>
    constexpr static inline uint_t normaliza(Int_t arg) noexcept
    {
      if constexpr (std::is_same_v<Int_t, uint_t>)
      {
        return (arg % B);
      }
      else if constexpr (std::is_signed_v<Int_t>)
      {
        if constexpr (type_traits::maxbase<Int_t>() >=
                      type_traits::maxbase<sig_sint_t>())
        {
          constexpr Int_t sint_0{0}; // ssi_0()
          constexpr Int_t sint_B{B}; // ssi_B()
          Int_t cparg{arg};
          if (arg < sint_0)
          {
            Int_t coc{(-arg) / sint_B};
            coc *= sint_B;
            cparg += coc;
            if (cparg < 0)
              cparg += sint_B;
            if (cparg >= sint_B)
              cparg -= sint_B;
          }
          else
          {
            cparg %= sint_B;
          }
          return static_cast<uint_t>(cparg);
        }
        else
        {
          constexpr sig_sint_t sint_0{0};
          constexpr sig_sint_t sint_B{B};
          sig_sint_t cparg{arg};
          if (arg < sint_0)
          {
            sig_sint_t coc{(-arg) / sint_B};
            coc *= sint_B;
            cparg += coc;
            if (cparg < 0)
              cparg += sint_B;
            if (cparg >= sint_B)
              cparg -= sint_B;
          }
          else
          {
            cparg %= sint_B;
          }
          return static_cast<uint_t>(cparg);
        }
      }
      else
      {
        if constexpr (maxbase<Int_t>() < maxbase<uint_t>())
        {
          constexpr sig_uint_t uint_B{B};
          sig_uint_t cparg{arg};
          if (arg >= uint_B)
          {
            cparg %= uint_B;
          }
          return static_cast<uint_t>(cparg);
        }
        else
        {
          constexpr Int_t uint_B{B};
          Int_t cparg{arg};
          if (arg >= uint_B)
          {
            cparg %= uint_B;
          }
          return static_cast<uint_t>(cparg);
        }
      }
    }

  public:
    /**
     * @brief Constructor desde cualquier tipo entero
     *
     * @tparam Int_t Tipo entero que debe satisfacer el concept integral_c
     * @param arg Valor entero a convertir en dígito
     *
     * @details
     * Convierte cualquier valor entero al rango [0, B-1] usando aritmética modular.
     * Si arg = 1524 y B = 10, entonces m_d = 4 (1524 % 10).
     * Maneja correctamente valores negativos y tipos de diferentes tamaños.
     *
     * @note El valor almacenado siempre estará en [0, B-1] independientemente del input
     */
    template <type_traits::integral_c Int_t>
    constexpr dig_t(Int_t arg) noexcept : m_d(normaliza<Int_t>(arg)) {}

    /**
     * @brief Constructor de copia por defecto
     *
     * Crea una copia exacta de otro dig_t. Es noexcept y constexpr
     * para optimizaciones máximas.
     */
    constexpr dig_t(const dig_t &) noexcept = default;

    /**
     * @brief Constructor de movimiento por defecto
     *
     * Transfiere la propiedad de un dig_t temporal. Como el tipo es trivial,
     * es equivalente a la copia pero expresa intención de movimiento.
     */
    constexpr dig_t(dig_t &&) noexcept = default;

    /**
     * @brief Constructor desde std::string
     *
     * @param str String con formato "d[n]B" o "dig#n#B" donde n es el valor y B la base
     * @throws std::invalid_argument si el formato es incorrecto o la base no coincide
     *
     * @details
     * Parsea un string con cualquiera de los formatos soportados:
     * - Formato estricto: "d[número]Bbase"
     * - Formato alternativo: "dig#número#Bbase"
     * - Valida que la base del string coincida con B
     * - El número se normaliza automáticamente (número % B)
     *
     * @example
     * ```cpp
     * dig_t<10> a("d[7]B10");      // a.m_d = 7 (formato estricto)
     * dig_t<10> b("dig#17#B10");   // b.m_d = 7 (formato alternativo)
     * dig_t<10> c("d[123]B10");    // c.m_d = 3 (123 % 10 = 3)
     * ```
     *
     * @note Acepta ambos formatos para máxima flexibilidad de entrada
     */
    explicit dig_t(const std::string &str);

    /**
     * @brief Constructor desde const char*
     *
     * @param str C-string con formato "d[n]B" o "dig#n#B" donde n es el valor y B la base
     * @throws std::invalid_argument si el formato es incorrecto o la base no coincide
     *
     * @details
     * Parsea un C-string con cualquiera de los formatos soportados.
     * Convierte a std::string internamente y usa el constructor de string.
     *
     * @example
     * ```cpp
     * dig_t<10> a("d[5]B10");       // a.m_d = 5 (formato estricto)
     * const char* str = "dig#25#B10";
     * dig_t<10> b(str);             // b.m_d = 5 (formato alternativo)
     * dig_t<10> c("d[125]B10");     // c.m_d = 5 (125 % 10 = 5)
     * ```
     *
     * @note Wrapper constexpr sobre from_cstr()
     */
    explicit constexpr dig_t(const char *str);

    /// PODEMOS PASAR ARGUMENTOS POR COPIA, REFERENCIA (PUNTEROS) Y MOVIMIENTO
    /// COPIA 		: COPIA EL ARGUMENTO LITERALMENTE PARA PASARLO: EL ORIGINAL
    /// INTACTO REFERENCIA: COPIA LA DIRECCION DEL ARGUMENTO
    ///             (SI ES CONST EL COMPILADOR NO TE DEJA COMPILAR SI LO CAMBIAS)
    /// MOVIMIENTO: SI EL ARGUMETO NO SE VA A UTILIZAR MAS SE LE PASA LA PROPIEDAD
    /// A LA FUNCION

    // ========================================================================
    /// @name Funciones de parsing desde strings
    /// @{

    /**
     * @brief Crea un dig_t desde std::string con parsing
     *
     * @param str String con formato "d[n]B" o "dig#n#B"
     * @return dig_t construido desde el string
     * @throws std::invalid_argument si el formato es incorrecto o la base no coincide
     *
     * @details
     * Función estática que parsea un string y crea un dig_t.
     * Acepta ambos formatos: estricto y alternativo.
     *
     * @example
     * ```cpp
     * auto a = dig_t<10>::from_string("d[25]B10");     // a.m_d = 5 (estricto)
     * auto b = dig_t<16>::from_string("dig#255#B16");  // b.m_d = 15 (alternativo)
     * auto c = dig_t<10>::from_string("d[125]B10");    // c.m_d = 5 (125 % 10)
     * ```
     *
     * @note Alternativa estática al constructor desde string
     */
    static dig_t from_string(const std::string &str);

    /**
     * @brief Crea un dig_t desde const char* con parsing
     *
     * @param str C-string con formato "d[n]B" o "dig#n#B"
     * @return dig_t construido desde el C-string
     * @throws std::invalid_argument si el formato es incorrecto o la base no coincide
     *
     * @details
     * Función estática que parsea un C-string y crea un dig_t.
     * Convierte a std::string internamente y usa from_string().
     *
     * @example
     * ```cpp
     * auto a = dig_t<10>::from_cstr("d[42]B10");    // a.m_d = 2 (estricto)
     * const char* str = "dig#100#B7";
     * auto b = dig_t<7>::from_cstr(str);           // b.m_d = 2 (alternativo)
     * auto c = dig_t<10>::from_cstr("d[142]B10");  // c.m_d = 2 (142 % 10)
     * ```
     *
     * @note Parser constexpr que usa parse_impl() directamente
     */
    static constexpr dig_t from_cstr(const char *str);

    /// @}

    /************************************/
    /*								  */
    /*	OPERADORES DE ASIGNACION	  */
    /*								  */
    /************************************/

    /// SOBRECARGA DEL OPERATOR=() MEDIANTE REFERENCIA CTE DESDE UN INT_T
    template <type_traits::integral_c Int_t>
    constexpr const dig_t &operator=(const Int_t &a) noexcept
    {
      if constexpr (std::is_same_v<Int_t, uint_t>)
      {
        if (&a != &m_d)
        {
          m_d = normaliza<Int_t>(a);
        }
      }
      else
      {
        m_d = normaliza<Int_t>(a);
      }
      return (*this);
    }
    /// SOBRECARGA DEL OPERATOR=() MEDIANTE REFERENCIA CTE DESDE UN DIG_T
    constexpr dig_t &operator=(const dig_t &) noexcept = default;
    /// SOBRECARGA DEL OPERATOR=() MEDIANTE MOVIMIENTO DESDE UN DIG_T
    constexpr dig_t &operator=(dig_t &&) noexcept = default;
    /// a y b son digitos;
    /// a = std::move(b);
    /// a es identico a b; en b puede no queda nada;

    ///*************************************///
    ///< SENTIDO DE LA DIVISION DE DIGITOS >///
    ///*************************************///

    constexpr bool is_unit() const noexcept
    { // FROM FINITE RINGS

      ///******************************************///
      ///< Es B COPRIMO con m_d ?                 >///
      ///< Es max_comun_divisor(B,m_d)==1 ? 		>///
      ///******************************************///

      if constexpr (is_prime())
      {
        if (!is_0())
        {
          return true;
        }
        else
        {
          return false;
        }
      }
      else
      {
        if (is_1())
          return true;
        else if (std::gcd(B, m_d) != ui_1())
          return false;
        else
          return true;
      }
    }

    constexpr bool is_0_divisor() const noexcept
    { // FROM FINITE RINGS

      ///******************************************///
      ///< Es B NO ES COPRIMO con m_d ?			>///
      ///< Es max_comun_divisor(B,m_d)!=1 ?       >///
      ///******************************************///

      if constexpr (is_prime())
      {
        if (is_0())
        {
          return true;
        }
        else
        {
          return false;
        }
      }
      else
      {
        if (is_0())
          return true;
        else if (std::gcd(B, m_d) != ui_1())
          return true;
        else
          return false;
      }
    }

    constexpr dig_t mult_inv() const noexcept
    { // FROM FINITE RINGS

      if (is_unit())
      {
        if (is_1())
          return dig_1();
        else if (is_Bm1())
          return dig_max();
        else
        {
          for (dig_t index(2); !is_Bm1(); ++index)
            if (index.is_unit())
            {
              if (((*this) * index).is_1())
                return index;
            }
          return dig_0(); /// NUNCA DEBERIA LLEGAR AQUI
                          /// SOLO PARA EVITAR EL WARNING
        }
      }
      else
        return dig_0();
    }

    /**************************************/
    /*									*/
    /*	FUNCIONES PARA CONOCER EL CARRY	*/
    /*									*/
    /**************************************/

    constexpr static dig_t sum_carry(dig_t arg_1, dig_t arg_2) noexcept
    {

      if constexpr (B <= type_traits::middle_max<uint_t>())
      {
        if constexpr ((B % 2) == 0)
        {
          constexpr uint_t Bdiv2{B / 2};
          if ((arg_1() < Bdiv2) && (arg_2() < Bdiv2))
          {
            return dig_0();
          }
          else if ((arg_1() >= Bdiv2) && (arg_2() >= Bdiv2))
          {
            return dig_1();
          }
          else if (arg_1() >= B - arg_2())
          {
            return dig_1();
          }
          else
          {
            return dig_0();
          }
        }
        else
        {
          constexpr uint_t Bdiv2_1{B / 2};
          constexpr uint_t Bdiv2_2{(B / 2) + 1};
          if (((arg_1() < Bdiv2_1) && (arg_2() < Bdiv2_2)) ||
              ((arg_1() < Bdiv2_2) && (arg_2() < Bdiv2_1)))
          {
            return dig_0();
          }
          else if (((arg_1() >= Bdiv2_1) && (arg_2() >= Bdiv2_2)) ||
                   ((arg_1() >= Bdiv2_2) && (arg_2() >= Bdiv2_1)))
          {
            return dig_1();
          }
          else if (arg_1() >= B - arg_2())
          {
            return dig_1();
          }
          else
          {
            return dig_0();
          }
        }
      }
      else
      {
        if constexpr ((B % 2) == 0)
        {
          constexpr sig_uint_t Bdiv2{B / 2};
          if ((arg_1() < Bdiv2) && (arg_2() < Bdiv2))
          {
            return dig_0();
          }
          else if ((arg_1() >= Bdiv2) && (arg_2() >= Bdiv2))
          {
            return dig_1();
          }
          else if (arg_1() >= B - arg_2())
          {
            return dig_1();
          }
          else
          {
            return dig_0();
          }
        }
        else
        {
          constexpr sig_uint_t Bdiv2_1{B / 2};
          constexpr sig_uint_t Bdiv2_2{(B / 2) + 1};
          if (((arg_1() < Bdiv2_1) && (arg_2() < Bdiv2_2)) ||
              ((arg_1() < Bdiv2_2) && (arg_2() < Bdiv2_1)))
          {
            return dig_0();
          }
          else if (((arg_1() >= Bdiv2_1) && (arg_2() >= Bdiv2_2)) ||
                   ((arg_1() >= Bdiv2_2) && (arg_2() >= Bdiv2_1)))
          {
            return dig_1();
          }
          else if (arg_1() >= B - arg_2())
          {
            return dig_1();
          }
          else
          {
            return dig_0();
          }
        }
      }
    }

    /************************************/
    /*								  */
    /*	OPERADORES & &= | |=    	  */
    /*  FUNCIONAN COMO MAX Y MIN		  */
    /*								  */
    /************************************/

    /**
     * @brief Operador AND bitwise (implementado como mínimo de dígitos)
     *
     * @param arg Dígito con el cual comparar
     * @return El menor de los dos dígitos
     *
     * @details
     * Implementación basada en analogía con aritmética de dígitos:
     * En base 2, & opera bit a bit. En base B, & opera dígito a dígito
     * como el mínimo, manteniendo la misma filosofía posicional.
     *
     * Comportamiento: retorna min(*this, arg)
     *
     * @example
     * ```cpp
     * dig_t<10> a(7);
     * dig_t<10> b(3);
     * dig_t<10> c = a & b;  // c = 3 (min(7,3))
     *
     * // Analogía: en base 2: 1&0=0 (min), en base B: a&b=min(a,b)
     * ```
     *
     * @note Equivalente a std::min(*this, arg) pero con semántica bitwise
     */
    constexpr dig_t operator&(const dig_t &arg) const noexcept
    {
      return (((*this) <= arg) ? (*this) : arg);
    }

    /**
     * @brief Operador AND bitwise con asignación (implementado como mínimo)
     *
     * @param arg Dígito con el cual comparar y potencialmente asignar
     * @return Referencia a este objeto después de la operación
     *
     * @details
     * Implementación basada en analogía con aritmética de dígitos:
     * Asigna el mínimo entre *this y arg a *this.
     *
     * Comportamiento:
     * - Si arg < *this: *this = arg
     * - Si arg >= *this: no cambia
     *
     * @example
     * ```cpp
     * dig_t<10> a(7);
     * dig_t<10> b(3);
     * a &= b;  // a = 3 (min(7,3))
     *
     * dig_t<10> c(2);
     * a &= c;  // a = 2 (min(3,2))
     * ```
     *
     * @note Equivalente a *this = std::min(*this, arg)
     */
    constexpr const dig_t &operator&=(dig_t arg) noexcept
    {
      if (arg < (*this))
        (*this) = arg;
      return (*this);
    }

    /**
     * @brief Operador OR bitwise (implementado como máximo de dígitos)
     *
     * @param arg Dígito con el cual comparar
     * @return El mayor de los dos dígitos
     *
     * @details
     * Implementación basada en analogía con aritmética de dígitos:
     * En base 2, | opera bit a bit. En base B, | opera dígito a dígito
     * como el máximo, manteniendo la misma filosofía posicional.
     *
     * Comportamiento: retorna max(*this, arg)
     *
     * @example
     * ```cpp
     * dig_t<10> a(7);
     * dig_t<10> b(3);
     * dig_t<10> c = a | b;  // c = 7 (max(7,3))
     *
     * // Analogía: en base 2: 1|0=1 (max), en base B: a|b=max(a,b)
     * ```
     *
     * @note Equivalente a std::max(*this, arg) pero con semántica bitwise
     */
    constexpr dig_t operator|(const dig_t &arg) const noexcept
    {
      return (((*this) >= arg) ? (*this) : arg);
    }

    /**
     * @brief Operador OR bitwise con asignación (implementado como máximo)
     *
     * @param arg Dígito con el cual comparar y potencialmente asignar
     * @return Referencia a este objeto después de la operación
     *
     * @details
     * Implementación basada en analogía con aritmética de dígitos:
     * Asigna el máximo entre *this y arg a *this.
     *
     * Comportamiento:
     * - Si arg > *this: *this = arg
     * - Si arg <= *this: no cambia
     *
     * @example
     * ```cpp
     * dig_t<10> a(3);
     * dig_t<10> b(7);
     * a |= b;  // a = 7 (max(3,7))
     *
     * dig_t<10> c(5);
     * a |= c;  // a = 7 (max(7,5))
     * ```
     *
     * @note Equivalente a *this = std::max(*this, arg)
     */
    constexpr const dig_t &operator|=(dig_t arg) noexcept
    {
      if (arg > (*this))
        (*this) = arg;
      return (*this);
    }

    /******************************************************/
    /*													*/
    /*	OPERADORES *^n *^=n                             */
    /*  FUNCIONAN COMO Power(*,n) y n = Power(*,n)		*/
    /*	DONDE n ES NATURAL                              */
    /*													*/
    /******************************************************/

    template <type_traits::unsigned_integral_c UIntType>
    constexpr const dig_t &operator^=(UIntType exp) noexcept
    {
      dig_t &cthis{*this};
      if (exp == 0)
      {
        cthis = dig_1();
        return (cthis);
      }
      else if (exp == 1)
      {
        return (cthis);
      }
      else if (exp == 2)
      {
        cthis *= cthis;
        return (cthis);
      }
      else
      {
        const dig_t vthis{*this};
        cthis *= vthis;
        for (UIntType ix{2}; ix < exp; ++ix)
        {
          cthis *= vthis;
        }
        return (cthis);
      }
    }

    template <type_traits::unsigned_integral_c UIntType>
    constexpr dig_t operator^(UIntType exp) const noexcept
    {
      dig_t cpthis{*this};
      cpthis ^= exp;
      return cpthis;
    }

    /****************************************/
    /*				               		  */
    /* OPERADORES COMPARACION				  */
    /*				                	  */
    /****************************************/
    /*                                    */
    /*    OPERADORES DE COMPARACIÓN       */
    /*                                    */
    /****************************************/

    /**
     * @brief Operador de igualdad
     *
     * @param a Dígito a comparar
     * @return true si ambos dígitos tienen el mismo valor, false en caso contrario
     *
     * @details
     * Compara los valores internos de los dígitos directamente.
     *
     * @example
     * ```cpp
     * dig_t<10> a(5);
     * dig_t<10> b(5);
     * dig_t<10> c(3);
     *
     * bool eq1 = (a == b);  // true
     * bool eq2 = (a == c);  // false
     * ```
     *
     * @note Comparación O(1) basada en valores uint_t
     */
    constexpr bool operator==(dig_t a) const noexcept
    {
      return ((a.m_d == m_d) ? true : false);
    }

    /**
     * @brief Operador de desigualdad
     *
     * @param a Dígito a comparar
     * @return true si los dígitos tienen valores diferentes, false si son iguales
     *
     * @details
     * Compara los valores internos de los dígitos directamente.
     *
     * @example
     * ```cpp
     * dig_t<10> a(5);
     * dig_t<10> b(3);
     * dig_t<10> c(5);
     *
     * bool neq1 = (a != b);  // true
     * bool neq2 = (a != c);  // false
     * ```
     *
     * @note Comparación O(1) basada en valores uint_t
     */
    constexpr bool operator!=(dig_t a) const noexcept
    {
      return ((a.m_d != m_d) ? true : false);
    }

    /**
     * @brief Operador mayor o igual que
     *
     * @param a Dígito a comparar
     * @return true si *this >= a, false en caso contrario
     *
     * @details
     * Compara si el valor de este dígito es mayor o igual que el argumento.
     *
     * @example
     * ```cpp
     * dig_t<10> a(7);
     * dig_t<10> b(5);
     * dig_t<10> c(7);
     *
     * bool ge1 = (a >= b);  // true (7 >= 5)
     * bool ge2 = (a >= c);  // true (7 >= 7)
     * bool ge3 = (b >= a);  // false (5 >= 7)
     * ```
     *
     * @note Comparación O(1) basada en valores uint_t
     */
    constexpr bool operator>=(dig_t a) const noexcept
    {
      return ((a.m_d <= m_d) ? true : false);
    }

    /**
     * @brief Operador mayor que
     *
     * @param a Dígito a comparar
     * @return true si *this > a, false en caso contrario
     *
     * @details
     * Compara si el valor de este dígito es estrictamente mayor que el argumento.
     *
     * @example
     * ```cpp
     * dig_t<10> a(7);
     * dig_t<10> b(5);
     * dig_t<10> c(7);
     *
     * bool gt1 = (a > b);  // true (7 > 5)
     * bool gt2 = (a > c);  // false (7 > 7)
     * bool gt3 = (b > a);  // false (5 > 7)
     * ```
     *
     * @note Comparación O(1) basada en valores uint_t
     */
    constexpr bool operator>(dig_t a) const noexcept
    {
      return ((a.m_d < m_d) ? true : false);
    }

    /**
     * @brief Operador menor o igual que
     *
     * @param a Dígito a comparar
     * @return true si *this <= a, false en caso contrario
     *
     * @details
     * Compara si el valor de este dígito es menor o igual que el argumento.
     *
     * @example
     * ```cpp
     * dig_t<10> a(5);
     * dig_t<10> b(7);
     * dig_t<10> c(5);
     *
     * bool le1 = (a <= b);  // true (5 <= 7)
     * bool le2 = (a <= c);  // true (5 <= 5)
     * bool le3 = (b <= a);  // false (7 <= 5)
     * ```
     *
     * @note Comparación O(1) basada en valores uint_t
     */
    constexpr bool operator<=(dig_t a) const noexcept
    {
      return ((a.m_d >= m_d) ? true : false);
    }

    /**
     * @brief Operador menor que
     *
     * @param a Dígito a comparar
     * @return true si *this < a, false en caso contrario
     *
     * @details
     * Compara si el valor de este dígito es estrictamente menor que el argumento.
     *
     * @example
     * ```cpp
     * dig_t<10> a(5);
     * dig_t<10> b(7);
     * dig_t<10> c(5);
     *
     * bool lt1 = (a < b);  // true (5 < 7)
     * bool lt2 = (a < c);  // false (5 < 5)
     * bool lt3 = (b < a);  // false (7 < 5)
     * ```
     *
     * @note Comparación O(1) basada en valores uint_t
     */
    constexpr bool operator<(dig_t a) const noexcept
    {
      return ((a.m_d > m_d) ? true : false);
    }

    /**
     * @brief Operador de comparación de tres vías (spaceship operator C++20)
     *
     * @param rhs Dígito derecho de la comparación
     * @return std::strong_ordering indicando la relación entre los dígitos
     *
     * @details
     * Operador moderno de C++20 que permite comparaciones de tres vías.
     * Genera automáticamente todos los operadores de comparación.
     *
     * Valores de retorno:
     * - std::strong_ordering::less: *this < rhs
     * - std::strong_ordering::equal: *this == rhs
     * - std::strong_ordering::greater: *this > rhs
     *
     * @example
     * ```cpp
     * dig_t<10> a(5);
     * dig_t<10> b(7);
     *
     * auto result = a <=> b;  // std::strong_ordering::less
     *
     * // Permite usar todos los operadores de comparación:
     * bool lt = (a < b);   // true, generado automáticamente
     * bool ge = (a >= b);  // false, generado automáticamente
     * ```
     *
     * @note Método propio de C++20 con strong_ordering (orden total)
     */
    constexpr std::strong_ordering operator<=>(dig_t rhs) const noexcept
    {
      const auto lhs_d{m_d};
      const auto rhs_d{rhs.m_d};
      return ((lhs_d < rhs_d) ? std::strong_ordering::less
                              : ((lhs_d > rhs_d) ? std::strong_ordering::greater
                                                 : std::strong_ordering::equal));
    }

    /**
     * @brief Operador de igualdad con tipos enteros (template)
     *
     * @tparam Int_t Tipo entero (signed o unsigned)
     * @param rhs Valor entero a comparar
     * @return true si *this == normaliza(rhs), false en caso contrario
     *
     * @details
     * Compara el dígito con un valor entero, normalizando automáticamente
     * el entero antes de la comparación.
     *
     * Proceso:
     * 1. Normaliza rhs: normaliza<Int_t>(rhs)
     * 2. Compara: m_d == valor_normalizado
     *
     * @example
     * ```cpp
     * dig_t<10> a(3);
     *
     * bool eq1 = (a == 3);   // true
     * bool eq2 = (a == 13);  // true (13 % 10 = 3)
     * bool eq3 = (a == 5);   // false
     * ```
     *
     * @note Siempre dig_t @ Int_t -> bool, nunca Int_t @ dig_t
     */
    template <type_traits::integral_c Int_t>
    constexpr bool operator==(Int_t rhs) noexcept
    {
      const dig_t &lhs{*this};
      return ((lhs.m_d == normaliza<Int_t>(rhs)) ? true : false);
    }

    /**
     * @brief Operador de comparación de tres vías con tipos enteros (template C++20)
     *
     * @tparam Int_t Tipo entero (signed o unsigned)
     * @param rhs Valor entero a comparar
     * @return std::weak_ordering indicando la relación entre el dígito y el entero
     *
     * @details
     * Operador moderno de C++20 que establece un **orden parcial** sobre los enteros.
     * Dos valores son equivalentes si a ≡ b (mod B).
     *
     * Proceso:
     * 1. Normaliza rhs: rhs_B = normaliza<Int_t>(rhs)
     * 2. Compara *this con rhs_B
     *
     * Valores de retorno:
     * - std::weak_ordering::less: *this < normaliza(rhs)
     * - std::weak_ordering::equivalent: *this ≡ rhs (mod B)
     * - std::weak_ordering::greater: *this > normaliza(rhs)
     *
     * @example
     * ```cpp
     * dig_t<10> a(3);
     *
     * auto r1 = a <=> 3;   // equivalent (3 ≡ 3 mod 10)
     * auto r2 = a <=> 13;  // equivalent (3 ≡ 13 mod 10)
     * auto r3 = a <=> 5;   // less (3 < 5)
     * auto r4 = a <=> 1;   // greater (3 > 1)
     * ```
     *
     * @note weak_ordering porque enteros pueden ser equivalentes módulo B
     * @note Establece orden parcial: a ∼ b si a ≡ b (mod B)
     */
    template <type_traits::integral_c Int_t>
    constexpr std::weak_ordering operator<=>(Int_t rhs) const noexcept
    {
      const dig_t &lhs{*this};
      const uint_t rhs_B{normaliza<Int_t>(rhs)};
      return ((lhs() < rhs_B)   ? std::weak_ordering::less
              : (lhs() > rhs_B) ? std::weak_ordering::greater
                                : std::weak_ordering::equivalent);
    }

    // ========================================================================
    /// @name Operadores aritméticos con asignación
    /// @{

    /**
     * @brief Operador de suma con asignación (aritmética modular)
     *
     * @param arg Dígito a sumar
     * @return Referencia a este objeto después de la suma
     *
     * @details
     * Realiza la operación: *this = (*this + arg) % B
     *
     * Optimizaciones implementadas:
     * - Si B es pequeño: usa uint_t directamente
     * - Si B es grande: usa sig_uint_t para evitar overflow
     *
     * @example
     * ```cpp
     * dig_t<10> a(7);
     * dig_t<10> b(8);
     * a += b;  // a = 5 (15 % 10)
     * ```
     *
     * @note Es constexpr para optimización en tiempo de compilación
     * @note noexcept garantizado - no puede fallar
     */
    constexpr const dig_t &operator+=(dig_t arg) noexcept
    {
      dig_t &cthis{*this};
      if constexpr (B < type_traits::middle_max<uint_t>())
      {
        m_d += arg.m_d;
        if (m_d >= B)
          m_d -= B;
        return (cthis);
      }
      else
      {
        sig_uint_t tmp{m_d};
        tmp += (arg.m_d);
        if (tmp >= B)
          tmp -= B;
        m_d = static_cast<uint_t>(tmp);
        return (cthis);
      }
    }

    /**
     * @brief Operador de suma con asignación desde cualquier tipo entero
     *
     * @tparam Int_t Tipo entero que debe satisfacer integral_c concept
     * @param arg Valor entero a sumar
     * @return Referencia a este objeto después de la suma
     *
     * @details
     * Normaliza arg al rango [0, B-1] y luego suma modularmente:
     * *this = (*this + (arg % B)) % B
     *
     * Soporta cualquier tipo entero (con/sin signo, diferentes tamaños).
     *
     * @example
     * ```cpp
     * dig_t<10> a(3);
     * a += 27;     // a = 0 (30 % 10)
     * a += -5;     // a = 5 (manejo correcto de negativos)
     * ```
     */
    template <type_traits::integral_c Int_t>
    constexpr const dig_t &operator+=(Int_t arg) noexcept
    {
      if constexpr (B >= type_traits::middle_max<uint_t>())
      {
        const sig_uint_t arg1{normaliza<Int_t>(arg)};
        sig_uint_t arg2{m_d};
        arg2 += arg1;
        if (arg2 >= static_cast<Int_t>(B))
          arg2 -= static_cast<Int_t>(B);
        m_d = static_cast<uint_t>(arg2);
        return (*this);
      }
      else
      {
        const uint_t arg1{normaliza<Int_t>(arg)};
        uint_t arg2{m_d};
        arg2 += arg1;
        if (arg2 >= static_cast<Int_t>(B))
          arg2 -= static_cast<Int_t>(B);
        m_d = static_cast<uint_t>(arg2);
        return (*this);
      }
    }

    /**
     * @brief Operador de resta con asignación (aritmética modular)
     *
     * @param arg Dígito a restar
     * @return Referencia a este objeto después de la resta
     *
     * @details
     * Realiza la operación: *this = (*this - arg + B) % B
     *
     * Maneja correctamente el caso donde *this < arg, sumando B para
     * mantener el resultado en rango positivo [0, B-1].
     *
     * @example
     * ```cpp
     * dig_t<10> a(3);
     * dig_t<10> b(7);
     * a -= b;  // a = 6 (3 - 7 + 10 = 6)
     * ```
     *
     * @note Usa sig_sint_t para manejar valores negativos temporales
     */
    constexpr const dig_t &operator-=(dig_t arg) noexcept
    {
      sig_sint_t cp_dm{m_d};
      cp_dm -= arg.m_d;
      if (cp_dm < 0)
        cp_dm += ssi_B();
      m_d = cp_dm;
      return (*this);
    }

    /**
     * @brief Operador de resta con asignación desde cualquier tipo entero
     *
     * @tparam Int_t Tipo entero que debe satisfacer integral_c concept
     * @param arg Valor entero a restar
     * @return Referencia a este objeto después de la resta
     *
     * @details
     * Normaliza arg y realiza resta modular: *this = (*this - (arg % B) + B) % B
     *
     * @example
     * ```cpp
     * dig_t<10> a(2);
     * a -= 15;  // a = 7 (2 - 5 + 10 = 7, donde 15%10=5)
     * ```
     */
    template <type_traits::integral_c Int_t>
    constexpr const dig_t &operator-=(Int_t arg) noexcept
    {
      sig_sint_t tmp{normaliza<Int_t>(arg)};
      sig_sint_t este{m_d};
      este -= tmp;
      if (este < static_cast<sig_sint_t>(0))
        este += ssi_B();
      m_d = este;
      return (*this);
    }

    /**
     * @brief Operador de multiplicación con asignación (aritmética modular)
     *
     * @param arg Dígito por el cual multiplicar
     * @return Referencia a este objeto después de la multiplicación
     *
     * @details
     * Realiza la operación: *this = (*this * arg) % B
     *
     * Optimizaciones implementadas:
     * - Si B < sqrt_max<uint_t>(): usa uint_t (no hay riesgo de overflow)
     * - Si B >= sqrt_max<uint_t>(): usa sig_uint_t para evitar overflow
     *
     * @example
     * ```cpp
     * dig_t<10> a(7);
     * dig_t<10> b(8);
     * a *= b;  // a = 6 (56 % 10)
     * ```
     *
     * @note La detección de overflow es automática en tiempo de compilación
     */
    constexpr const dig_t &operator*=(dig_t arg) noexcept
    {
      if constexpr (B < type_traits::sqrt_max<uint_t>())
      {
        m_d *= arg.m_d;
        m_d %= B;
        return (*this);
      }
      else
      {
        sig_uint_t tmp{m_d};
        tmp *= arg.m_d;
        tmp %= static_cast<sig_uint_t>(B);
        m_d = static_cast<uint_t>(tmp);
        return (*this);
      }
    }

    /**
     * @brief Operador de multiplicación con asignación para tipos enteros (template)
     *
     * @tparam Int_t Tipo entero (signed o unsigned)
     * @param arg Valor entero por el cual multiplicar
     * @return Referencia a este objeto después de la multiplicación
     *
     * @details
     * Realiza la operación: *this = (*this * normaliza(arg)) % B
     *
     * Optimizaciones por tipo:
     * - Si Int_t es signed y sizeof(Int_t) > sizeof(uint_t): usa sig_SInt_for_SInt_t
     * - Si Int_t es signed y sizeof(Int_t) <= sizeof(uint_t): usa sig_sint_t
     * - Si Int_t es unsigned y sizeof(Int_t) > sizeof(uint_t): usa sig_UInt_for_UInt_t
     * - Si Int_t es unsigned y sizeof(Int_t) <= sizeof(uint_t): usa sig_uint_t
     *
     * @example
     * ```cpp
     * dig_t<10> a(3);
     * a *= 15;  // a = 5 (45 % 10)
     * a *= -7;  // a = 5 (35 % 10) si B > 5
     * ```
     *
     * @note El argumento se normaliza automáticamente antes de la operación
     */
    template <type_traits::integral_c Int_t>
    constexpr const dig_t &operator*=(Int_t arg) noexcept
    {
      const Int_t tmp{normaliza<Int_t>(arg)};
      if constexpr (std::is_signed_v<Int_t>)
      {
        if constexpr (sizeof(Int_t) > sizeof(uint_t))
        {
          using SIG2_SINT_T = type_traits::sig_SInt_for_SInt_t<Int_t>;
          const SIG2_SINT_T norm_arg{tmp};
          SIG2_SINT_T este{m_d};
          este *= norm_arg;
          este %= static_cast<SIG2_SINT_T>(B);
          m_d = static_cast<uint_t>(este);
          return (*this);
        }
        else
        {
          const sig_sint_t norm_arg{tmp};
          sig_sint_t este{m_d};
          este *= norm_arg;
          este %= static_cast<sig_sint_t>(B);
          m_d = static_cast<uint_t>(este);
          return (*this);
        }
      }
      else
      {
        if constexpr (sizeof(Int_t) > sizeof(uint_t))
        {
          using SIG2_UINT_T = type_traits::sig_UInt_for_UInt_t<Int_t>;
          const SIG2_UINT_T norm_arg{tmp};
          SIG2_UINT_T este{m_d};
          este *= norm_arg;
          este %= static_cast<SIG2_UINT_T>(B);
          m_d = static_cast<uint_t>(este);
          return (*this);
        }
        else
        {
          const sig_uint_t norm_arg{tmp};
          sig_uint_t este{m_d};
          este *= norm_arg;
          este %= static_cast<sig_uint_t>(B);
          m_d = static_cast<uint_t>(este);
          return (*this);
        }
      }
    }

    /**
     * @brief Operador de división con asignación
     *
     * @param arg Dígito divisor
     * @return Referencia a este objeto después de la división
     *
     * @details
     * Realiza la operación: *this = *this / arg (división entera)
     *
     * Comportamiento:
     * - Si arg != 0: realiza la división entera m_d /= arg.m_d
     * - Si arg == 0: no realiza operación (evita división por cero)
     *
     * @example
     * ```cpp
     * dig_t<10> a(7);
     * dig_t<10> b(3);
     * a /= b;  // a = 2 (7/3 = 2)
     * ```
     *
     * @warning No arroja excepción en división por cero, simplemente no opera
     */
    constexpr const dig_t &operator/=(dig_t arg) noexcept
    {
      if (arg.m_d != ui_0())
        m_d /= arg.m_d;
      return (*this);
    }

    /**
     * @brief Operador de división con asignación para tipos enteros (template)
     *
     * @tparam Int_t Tipo entero (signed o unsigned)
     * @param arg Valor entero divisor
     * @return Referencia a este objeto después de la división
     *
     * @details
     * Realiza la operación: *this = *this / normaliza(arg)
     *
     * Proceso:
     * 1. Normaliza el argumento: cparg = normaliza<Int_t>(arg)
     * 2. Crea dig_t temporal: tmp{cparg}
     * 3. Si tmp != 0: realiza *this /= tmp
     * 4. Si tmp == 0: no opera (evita división por cero)
     *
     * @example
     * ```cpp
     * dig_t<10> a(8);
     * a /= 3;   // a = 2 (8/3 = 2)
     * a /= -1;  // a = 2 (no cambia si normaliza(-1) == 0)
     * ```
     *
     * @note El argumento se normaliza automáticamente antes de la división
     */
    template <type_traits::integral_c Int_t>
    constexpr const dig_t &operator/=(Int_t arg) noexcept
    {
      uint_t cparg{normaliza<Int_t>(arg)};
      dig_t tmp{cparg};
      if (tmp != dig_0())
        (*this) /= tmp;
      return (*this);
    }

    /**
     * @brief Operador de módulo con asignación
     *
     * @param arg Dígito divisor para el módulo
     * @return Referencia a este objeto después del módulo
     *
     * @details
     * Realiza la operación: *this = *this % arg
     *
     * Comportamiento:
     * - Si arg != 0: calcula el resto de la división m_d %= arg.m_d
     * - Si arg == 0: no realiza operación (evita módulo por cero)
     *
     * @example
     * ```cpp
     * dig_t<10> a(7);
     * dig_t<10> b(3);
     * a %= b;  // a = 1 (7 % 3 = 1)
     * ```
     *
     * @warning No arroja excepción en módulo por cero, simplemente no opera
     */
    constexpr const dig_t &operator%=(dig_t arg) noexcept
    {
      if (arg.m_d != ui_0())
        m_d %= arg.m_d;
      return (*this);
    }

    /**
     * @brief Operador de módulo con asignación para tipos enteros (template)
     *
     * @tparam Int_t Tipo entero (signed o unsigned)
     * @param arg Valor entero divisor para el módulo
     * @return Referencia a este objeto después del módulo
     *
     * @details
     * Realiza la operación: *this = *this % normaliza(arg)
     *
     * Proceso:
     * 1. Normaliza el argumento: cparg = dig_t{normaliza<Int_t>(arg)}
     * 2. Si cparg != 0: realiza *this %= cparg
     * 3. Si cparg == 0: no opera (evita módulo por cero)
     *
     * @example
     * ```cpp
     * dig_t<10> a(8);
     * a %= 3;   // a = 2 (8 % 3 = 2)
     * a %= 7;   // a = 2 (2 % 7 = 2)
     * ```
     *
     * @note El argumento se normaliza automáticamente antes del módulo
     */
    template <type_traits::integral_c Int_t>
    constexpr const dig_t &
    operator%=(Int_t arg) noexcept
    {
      dig_t cparg{normaliza<Int_t>(arg)};
      if (cparg != dig_0())
        (*this) %= cparg;
      return (*this);
    }
    /// Tengo serias dudas que la division y el resto euclideo tengan cabida
    /// entre los operadores aritmeticos de un tipo dig_t
    /// DUDA SATISFECHA: TIENEN CABIDA PORQUE EL INVERSO MULTIPLICATIVO ETC.
    /// SOLO NOS SIRVE SI ESTUVIERAMOS CONSTRUYENDO NUMEROS DE UN ANILLO FINITO

    /********************************/
    /*			     			  */
    /* 		  PRE Y POST 		  */
    /*			CIRCULARES		  */
    /*							  */
    /********************************/

    /**
     * @brief Operador de pre-incremento circular
     *
     * @return Referencia a este objeto después del incremento
     *
     * @details
     * Incrementa el valor en 1 con aritmética circular:
     * - Si m_d < ui_max(): incrementa normalmente (++m_d)
     * - Si m_d == ui_max(): vuelve a 0 (m_d = ui_0())
     *
     * La aritmética es circular dentro del rango [0, B-1]
     *
     * @example
     * ```cpp
     * dig_t<10> a(8);
     * ++a;  // a = 9
     * ++a;  // a = 0 (circular: 9+1 en base 10 vuelve a 0)
     * ```
     *
     * @note Implementa aritmética modular: (m_d + 1) % B
     */
    constexpr const dig_t &operator++() noexcept
    {
      (m_d < ui_max()) ? (++m_d) : (m_d = ui_0());
      return (*this);
    }

    /**
     * @brief Operador de post-incremento circular
     *
     * @param int Parámetro dummy para distinguir del pre-incremento
     * @return Copia del objeto antes del incremento
     *
     * @details
     * Incrementa el valor en 1 con aritmética circular, pero retorna
     * el valor original:
     * 1. Guarda una copia del estado actual
     * 2. Aplica el pre-incremento (++(*this))
     * 3. Retorna la copia del estado original
     *
     * @example
     * ```cpp
     * dig_t<10> a(8);
     * dig_t<10> b = a++;  // b = 8, a = 9
     * dig_t<10> c = a++;  // c = 9, a = 0 (circular)
     * ```
     *
     * @note Menos eficiente que pre-incremento por la copia temporal
     */
    constexpr dig_t operator++(int) noexcept
    {
      dig_t ret(*this);
      ++(*this);
      return ret;
    }

    /**
     * @brief Operador de pre-decremento circular
     *
     * @return Referencia a este objeto después del decremento
     *
     * @details
     * Decrementa el valor en 1 con aritmética circular:
     * - Si m_d > ui_0(): decrementa normalmente (--m_d)
     * - Si m_d == ui_0(): va al máximo (m_d = ui_max())
     *
     * La aritmética es circular dentro del rango [0, B-1]
     *
     * @example
     * ```cpp
     * dig_t<10> a(1);
     * --a;  // a = 0
     * --a;  // a = 9 (circular: 0-1 en base 10 va a 9)
     * ```
     *
     * @note Implementa aritmética modular: (m_d - 1 + B) % B
     */
    constexpr const dig_t &operator--() noexcept
    {
      if (m_d > ui_0())
      {
        --m_d;
      }
      else
      {
        m_d = ui_max();
      }
      return (*this);
    }

    /**
     * @brief Operador de post-decremento circular
     *
     * @param int Parámetro dummy para distinguir del pre-decremento
     * @return Copia del objeto antes del decremento
     *
     * @details
     * Decrementa el valor en 1 con aritmética circular, pero retorna
     * el valor original:
     * 1. Guarda una copia del estado actual
     * 2. Aplica el pre-decremento (--(*this))
     * 3. Retorna la copia del estado original
     *
     * @example
     * ```cpp
     * dig_t<10> a(1);
     * dig_t<10> b = a--;  // b = 1, a = 0
     * dig_t<10> c = a--;  // c = 0, a = 9 (circular)
     * ```
     *
     * @note Menos eficiente que pre-decremento por la copia temporal
     */
    constexpr dig_t operator--(int) noexcept
    {
      dig_t ret(*this);
      --(*this);
      return ret;
    }

    /****************************************/
    /*									  */
    /*    OPERADORES ARITMETICOS   		  */
    /*									  */
    /****************************************/

    /**
     * @brief Operador de suma binario
     *
     * @param arg Dígito a sumar
     * @return Nuevo dig_t con el resultado de la suma
     *
     * @details
     * Realiza la operación: resultado = *this + arg
     *
     * Implementación:
     * 1. Crea una copia de *this: ret(*this)
     * 2. Aplica suma con asignación: ret += arg
     * 3. Retorna la copia modificada
     *
     * La suma es modular: (a + b) % B
     *
     * @example
     * ```cpp
     * dig_t<10> a(7);
     * dig_t<10> b(5);
     * dig_t<10> c = a + b;  // c = 2 (12 % 10)
     * // a y b permanecen sin cambios
     * ```
     *
     * @note No modifica los operandos originales
     */
    constexpr dig_t operator+(dig_t arg) const noexcept
    {
      dig_t ret(*this);
      ret += arg;
      return ret;
    }

    /**
     * @brief Operador de resta binario
     *
     * @param arg Dígito a restar
     * @return Nuevo dig_t con el resultado de la resta
     *
     * @details
     * Realiza la operación: resultado = *this - arg
     *
     * Implementación:
     * 1. Crea una copia de *this: ret(*this)
     * 2. Aplica resta con asignación: ret -= arg
     * 3. Retorna la copia modificada
     *
     * La resta es modular: (*this - arg + B) % B
     *
     * @example
     * ```cpp
     * dig_t<10> a(3);
     * dig_t<10> b(5);
     * dig_t<10> c = a - b;  // c = 8 (3-5+10 = 8)
     * // a y b permanecen sin cambios
     * ```
     *
     * @note No modifica los operandos originales
     */
    constexpr dig_t operator-(dig_t arg) const noexcept
    {
      dig_t ret(*this);
      ret -= arg;
      return ret;
    }

    /**
     * @brief Operador de multiplicación binario
     *
     * @param arg Dígito por el cual multiplicar
     * @return Nuevo dig_t con el resultado de la multiplicación
     *
     * @details
     * Realiza la operación: resultado = *this * arg
     *
     * Implementación:
     * 1. Crea una copia de *this: ret(*this)
     * 2. Aplica multiplicación con asignación: ret *= arg
     * 3. Retorna la copia modificada
     *
     * La multiplicación es modular: (*this * arg) % B
     *
     * @example
     * ```cpp
     * dig_t<10> a(7);
     * dig_t<10> b(8);
     * dig_t<10> c = a * b;  // c = 6 (56 % 10)
     * // a y b permanecen sin cambios
     * ```
     *
     * @note No modifica los operandos originales
     */
    constexpr dig_t operator*(dig_t arg) const noexcept
    {
      dig_t ret(*this);
      ret *= arg;
      return ret;
    }

    /**
     * @brief Operador de división binario
     *
     * @param arg Dígito divisor
     * @return Nuevo dig_t con el resultado de la división
     *
     * @details
     * Realiza la operación: resultado = *this / arg (división entera)
     *
     * Implementación:
     * 1. Crea una copia de *this: ret(*this)
     * 2. Aplica división con asignación: ret /= arg
     * 3. Retorna la copia modificada
     *
     * Comportamiento:
     * - Si arg != 0: división entera normal
     * - Si arg == 0: no opera, mantiene el valor original
     *
     * @example
     * ```cpp
     * dig_t<10> a(7);
     * dig_t<10> b(3);
     * dig_t<10> c = a / b;  // c = 2 (7/3 = 2)
     * // a y b permanecen sin cambios
     * ```
     *
     * @note No modifica los operandos originales
     * @warning No arroja excepción en división por cero
     */
    constexpr dig_t operator/(dig_t arg) const noexcept
    {
      dig_t ret(*this);
      ret /= arg;
      return ret;
    }

    /**
     * @brief Operador de módulo binario
     *
     * @param arg Dígito divisor para el módulo
     * @return Nuevo dig_t con el resultado del módulo
     *
     * @details
     * Realiza la operación: resultado = *this % arg
     *
     * Implementación:
     * 1. Crea una copia de *this: ret(*this)
     * 2. Aplica módulo con asignación: ret %= arg
     * 3. Retorna la copia modificada
     *
     * Comportamiento:
     * - Si arg != 0: resto de la división entera
     * - Si arg == 0: no opera, mantiene el valor original
     *
     * @example
     * ```cpp
     * dig_t<10> a(7);
     * dig_t<10> b(3);
     * dig_t<10> c = a % b;  // c = 1 (7 % 3 = 1)
     * // a y b permanecen sin cambios
     * ```
     *
     * @note No modifica los operandos originales
     * @warning No arroja excepción en módulo por cero
     */
    constexpr dig_t operator%(dig_t arg) const noexcept
    {
      dig_t ret(*this);
      ret %= arg;
      return ret;
    }

    /**
     * @brief Operador de suma binario para tipos enteros (template)
     *
     * @tparam Int_type Tipo entero (signed o unsigned)
     * @param arg Valor entero a sumar
     * @return Nuevo dig_t con el resultado de la suma
     *
     * @details
     * Realiza la operación: resultado = *this + normaliza(arg)
     *
     * Implementación:
     * 1. Crea una copia de *this: ret(*this)
     * 2. Normaliza el argumento y suma: ret += normaliza<Int_type>(arg)
     * 3. Retorna la copia modificada
     *
     * @example
     * ```cpp
     * dig_t<10> a(7);
     * dig_t<10> b = a + 15;  // b = 2 (7+5 = 12, 12%10 = 2)
     * dig_t<10> c = a + -3;  // c = 4 (7+7 = 14, 14%10 = 4) si normaliza(-3)=7
     * ```
     *
     * @note El argumento se normaliza automáticamente antes de la suma
     */
    template <type_traits::integral_c Int_type>
    constexpr dig_t operator+(Int_type arg) const noexcept
    {
      dig_t ret(*this);
      ret += normaliza<Int_type>(arg);
      return ret;
    }

    /**
     * @brief Operador de resta binario para tipos enteros (template)
     *
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
