/**
 * @file core/dig_t.hpp
 * @brief Copia adaptada de include/dig_t.hpp para el nuevo layout
 */

#ifndef CORE_DIG_T_HPP_INCLUDED
#define CORE_DIG_T_HPP_INCLUDED

#include <array>
#include <string>
#include <stdexcept>

#include "internal/basic_types.hpp"
#include "internal/auxiliary_functions.hpp"

namespace NumRepr {

  using type_traits::maxbase;
  using type_traits::sig_SInt_for_UInt_t;
  using type_traits::sig_UInt_for_UInt_t;
  using type_traits::sqrt_max;
  using type_traits::suitable_base;
  using type_traits::uint_type_for_radix_c;

  template <std::uint64_t B>
    requires(B > 1)
  struct dig_t {
    // Validación explícita de la restricción de base máxima
    static_assert(B <= std::numeric_limits<std::uint32_t>::max(),
                  "dig_t: Base B must be <= UINT32_MAX (4294967296). "
                  "This restriction ensures that digit multiplications (B-1)×(B-1) "
                  "fit within uint64_t without overflow.");
    
    /**
     * @brief Tipo entero sin signo para almacenar un dígito en base B
     * @details Selecciona automáticamente el tipo entero sin signo más pequeño 
     *          capaz de representar valores de 0 a B-1:
     *          - B ∈ [2, 256]: uint8_t
     *          - B ∈ [257, 65536]: uint16_t
     *          - B ∈ [65537, 4294967296]: uint32_t (máximo soportado)
     * 
     * @note RESTRICCIÓN: La base B debe ser <= UINT32_MAX (4294967296)
     * @note Esta restricción existe porque las multiplicaciones de dígitos
     *       (B-1) × (B-1) deben caber en el tipo superior sin overflow.
     *       Con B <= UINT32_MAX, el producto cabe en uint64_t (sig_uint_t).
     * 
     * @warning Bases mayores a UINT32_MAX causarán error de compilación con
     *          mensaje claro gracias al static_assert anterior.
     */
    using uint_t = 
        typename type_traits::TypeFromIntNumber_t<static_cast<uint64_t>(B)>;

  private:
    /// @brief Valor del dígito: único dato/estado de la clase
    /// @details Siempre normalizado en el rango [0, B-1]
    uint_t m_d;

  public:
    // =========================================================================
    // TIPOS AUXILIARES PÚBLICOS
    // =========================================================================
    // Estos tipos permiten trabajar con dig_t sin necesidad de conocer los
    // detalles de implementación. Ejemplo:
    //   typename dig_t<10>::sig_uint_t valor;  // tipo superior sin signo
    //   typename dig_t<10>::uintspair par;     // par de valores
    
    /// @brief Tipo entero sin signo superior para evitar overflow en multiplicaciones
    /// @details Tipo con el doble de bits que uint_t (ej: uint16_t si uint_t es uint8_t)
    using sig_uint_t = typename type_traits::sig_UInt_for_UInt_t<uint_t>;
    
    /// @brief Tipo entero con signo correspondiente a sig_uint_t
    using sig_sint_t = typename type_traits::sig_SInt_for_UInt_t<uint_t>;
    
    /// @brief Par de enteros [carry, result] para operaciones multi-precisión
    /// @details Usado en mult() para retornar {dígito_alto, dígito_bajo}
    using uintspair = std::array<uint_t, 2>;
    
    /// @brief Par de dig_t [carry, result]
    /// @note Actualmente NO UTILIZADO en el código
    using digspair = std::array<dig_t, 2>;
    
    /// @brief Lista de B pares (tabla 1D de multiplicación parcial)
    /// @note Actualmente NO UTILIZADO en el código
    using uintspairlist = std::array<uintspair, B>;
    
    /// @brief Tabla completa BxB de multiplicación
    /// @note Actualmente NO UTILIZADO en el código
    using uintspairtbl = std::array<uintspairlist, B>;

    /**
     * @brief Multiplicación de dos dígitos en tiempo de compilación
     * @details Calcula n × m retornando {carry, resultado} como par [dígito_alto, dígito_bajo].
     *          Diseñada para construir tablas constexpr de multiplicación.
     *          Segura contra overflow: usa sig_uint_t cuando B > sqrt(max(uint_t)).
     * 
     * @tparam n Primer dígito (0 <= n < B)
     * @tparam m Segundo dígito (0 <= m < B)
     * 
     * @return uintspair {n×m / B, n×m % B} = {carry, digit_resultado}
     * 
     * @note Optimización automática según tamaño de B:
     *       - B <= sqrt(max(uint_t)): multiplicación directa en uint_t
     *       - B > sqrt(max(uint_t)): usa sig_uint_t (tipo superior) para evitar overflow
     * 
     * @code
     * // Ejemplo: dig_t<10>::mult<7, 8>() retorna {5, 6} porque 7×8=56 = 5×10 + 6
     * constexpr auto result = dig_t<10>::mult<7, 8>();
     * static_assert(result[0] == 5);  // carry
     * static_assert(result[1] == 6);  // dígito resultado
     * @endcode
     */
    template <uint_t n, uint_t m>
      requires((n < B) && (m < B))
    static consteval uintspair mult() noexcept {
      if constexpr (B > type_traits::sqrt_max<uint_t>()) {
        constexpr sig_uint_t sup_n{n};
        constexpr sig_uint_t sup_m{m};
        constexpr sig_uint_t result{sup_n * sup_m};
        constexpr uint_t ret_1{result / B};
        constexpr uint_t ret_0{result % B};
        constexpr uintspair ret{ret_1, ret_0};
        return ret;
      }
      else {
        constexpr uint_t result{n * m};
        constexpr uint_t ret_1{result / B};
        constexpr uint_t ret_0{result % B};
        constexpr uintspair ret{ret_1, ret_0};
        return ret;
      }
    }

  public:
    // =========================================================================
    // CONVERSIONES Y ACCESO AL VALOR
    // =========================================================================
    
    /**
     * @brief Conversión explícita a uint_t (tipo nativo del dígito)
     * @return Valor del dígito como uint_t
     * @note Conversión explícita - requiere static_cast<uint_t>(digit)
     */
    constexpr explicit operator uint_t() const noexcept { return m_d; }
    
    /**
     * @brief Obtiene el valor del dígito
     * @return Valor del dígito en el rango [0, B-1]
     * @note FORMA PREFERIDA para acceder al valor. Usado ampliamente en el código.
     * @see operator()() para sintaxis alternativa (deprecated)
     */
    constexpr uint_t get() const noexcept { return m_d; }
    
    /**
     * @brief Conversión explícita a sig_uint_t (tipo superior sin signo)
     * @return Valor del dígito convertido a tipo superior
     * @note Útil para operaciones que requieren más bits (evitar overflow)
     */
    constexpr explicit operator sig_uint_t() const noexcept { 
        return static_cast<sig_uint_t>(m_d); 
    }
    
    /**
     * @brief Conversión explícita a sig_sint_t (tipo superior con signo)
     * @return Valor del dígito convertido a tipo con signo superior
     * @note Útil para operaciones aritméticas que requieren signo
     */
    constexpr explicit operator sig_sint_t() const noexcept { 
        return static_cast<sig_sint_t>(m_d); 
    }
    
    /**
     * @brief Sintaxis funcional para obtener el valor del dígito
     * @return Valor del dígito en el rango [0, B-1]
     * @deprecated Use get() en su lugar. Mantenido por compatibilidad.
     * @note Mismo comportamiento que get() pero con sintaxis digit()
     */
    [[deprecated("Use get() instead")]]
    constexpr uint_t operator()() const noexcept { return m_d; }
    
    // =========================================================================
    // MODIFICADORES DEL VALOR
    // =========================================================================
    
    /// @brief Establece el valor del dígito a 0
    constexpr void set_0() noexcept { m_d = 0; }
    
    /// @brief Establece el valor del dígito a 1
    constexpr void set_1() noexcept { m_d = 1; }
    
    /// @brief Establece el valor del dígito a B-1 (máximo valor)
    constexpr void set_Bm1() noexcept { m_d = B - 1; }
    
    /// @brief Establece el valor del dígito a B-2
    constexpr void set_Bm2() noexcept { m_d = B - 2; }
    
    /// @brief Copia el valor desde otro dígito
    /// @param d Dígito fuente
    constexpr void set_dig(dig_t d) noexcept { m_d = d.m_d; }
    
    /// @brief Establece el valor desde un entero (normalizado módulo B)
    /// @param di Valor entero a asignar (se normaliza automáticamente)
    constexpr void set_dig(uint_t di) noexcept { m_d = di % B; }

  public:
    // =========================================================================
    // PROPIEDADES ALGEBRAICAS Y TEORÍA DE ANILLOS
    // =========================================================================
    
    /**
     * @brief Determina si la base B es un número primo
     * @return true si B es primo, false en caso contrario
     * 
     * @details TEORÍA DE ANILLOS: Cuando B es primo, ℤ/Bℤ forma un cuerpo 
     *          conmutativo finito (campo de Galois GF(B)). En este caso:
     *          - Todo elemento no nulo tiene inverso multiplicativo
     *          - No existen divisores de cero (excepto el 0)
     *          - Se pueden realizar divisiones (excepto por 0)
     * 
     * @note Evaluada en tiempo de compilación (consteval)
     * @see is_unit() - verifica si un dígito específico tiene inverso
     * @see mult_inv() - calcula el inverso multiplicativo
     */
    consteval static bool is_prime() noexcept {
      return auxiliary_functions::is_prime(static_cast<std::size_t>(B));
    }

    // =========================================================================
    // CONSTANTES ESTÁTICAS - Dígitos especiales
    // =========================================================================

    consteval static dig_t dig_max() noexcept { return dig_t(B - 1u); };
    consteval static dig_t dig_submax() noexcept { return dig_t(B - 2u); }
    consteval static dig_t dig_Bm1() noexcept { return dig_t(B - 1u); }
    consteval static dig_t dig_Bm2() noexcept { return dig_t(B - 2u); }
    consteval static dig_t dig_0() noexcept { return dig_t(); }
    consteval static dig_t dig_1() noexcept { return dig_t(1u); }

    consteval static uint_t ui_max() noexcept { return uint_t(B - 1u); }
    consteval static uint_t ui_submax() noexcept { return uint_t(B - 2u); }
    consteval static uint_t ui_Bm1() noexcept { return uint_t(B - 1u); }
    consteval static uint_t ui_Bm2() noexcept { return uint_t(B - 2u); }
    consteval static uint_t ui_0() noexcept { return uint_t(0u); }
    consteval static uint_t ui_1() noexcept { return uint_t(1u); }

    consteval static sig_uint_t sui_B() noexcept { 
        return static_cast<sig_uint_t>(B); }
    consteval static sig_uint_t sui_max() noexcept { 
        return static_cast<sig_uint_t>(B - 1u); }
    consteval static sig_uint_t sui_submax() noexcept { 
        return static_cast<sig_uint_t>(B - 2u); }
    consteval static sig_uint_t sui_0() noexcept { 
        return static_cast<sig_uint_t>(0u); }
    consteval static sig_uint_t sui_1() noexcept { 
        return static_cast<sig_uint_t>(1u); }

    consteval static sig_sint_t ssi_B() noexcept { 
        return static_cast<sig_sint_t>(B); }
    consteval static sig_sint_t ssi_max() noexcept { 
        return static_cast<sig_sint_t>(B - 1u); }
    consteval static sig_sint_t ssi_submax() noexcept { 
        return static_cast<sig_sint_t>(B - 2u); }
    consteval static sig_sint_t ssi_0() noexcept { 
        return static_cast<sig_sint_t>(0u); }
    consteval static sig_sint_t ssi_1() noexcept { 
        return static_cast<sig_sint_t>(1u); }

  public:
    // =========================================================================
    // CONSTRUCTORES
    // =========================================================================
    
    /**
     * @brief Constructor por defecto - inicializa el dígito a 0
     * @details Adelantado aquí por necesidad (usado antes de otros constructores).
     *          Inicializa m_d = 0, representando el elemento neutro de la suma
     *          en el anillo ℤ/Bℤ.
     * 
     * @note consteval: puede evaluarse en tiempo de compilación
     * @note noexcept: no lanza excepciones
     */
    consteval inline dig_t() noexcept : m_d(0u) {}

  private:
    // =========================================================================
    // FUNCIÓN PRIVADA DE NORMALIZACIÓN
    // =========================================================================
    
    /**
     * @brief Normaliza un entero arbitrario al rango [0, B-1]
     * @details Método estático fundamental: reduce cualquier entero (positivo o
     *          negativo) módulo B. Maneja correctamente valores negativos 
     *          asegurando que el resultado esté siempre en [0, B-1].
     * 
     * @tparam Int_t Tipo entero (signed/unsigned, cualquier tamaño)
     * @param arg Valor a normalizar
     * @return Valor normalizado en [0, B-1]
     * 
     * @note Optimizaciones según tipo:
     *       - Si Int_t == uint_t: simple módulo
     *       - Si signed: manejo especial para negativos
     *       - Si tipo mayor que sig_sint_t: usa tipo superior para evitar overflow
     */
    template <type_traits::integral_c Int_t>
    constexpr static inline uint_t normaliza(Int_t arg) noexcept {
      if constexpr (std::is_same_v<Int_t, uint_t>) { return (arg % B); }
      else if constexpr (std::is_signed_v<Int_t>) {
        if constexpr (
            type_traits::maxbase<Int_t>() >= type_traits::maxbase<sig_sint_t>()) {
          constexpr Int_t sint_0{0};
          constexpr Int_t sint_B{B};
          Int_t cparg{arg};
          if (arg < sint_0) {
            Int_t coc{(-arg) / sint_B};
            coc *= sint_B;
            cparg += coc;
            if (cparg < 0)
              cparg += sint_B;
            if (cparg >= sint_B)
              cparg -= sint_B;
          }
          else { cparg %= sint_B; }
          return static_cast<uint_t>(cparg);
        } else {
          constexpr sig_sint_t sint_0{0};
          constexpr sig_sint_t sint_B{B};
          sig_sint_t cparg{arg};
          if (arg < sint_0) {
            sig_sint_t coc{(-arg) / sint_B};
            coc *= sint_B;
            cparg += coc;
            if (cparg < 0)
              cparg += sint_B;
            if (cparg >= sint_B)
              cparg -= sint_B;
          } else { cparg %= sint_B; }
          
          return static_cast<uint_t>(cparg);
        }
      } else {
        if constexpr (maxbase<Int_t>() < maxbase<uint_t>()) {
          constexpr sig_uint_t uint_B{B};
          sig_uint_t cparg{arg};
          if (arg >= uint_B) { cparg %= uint_B; }
          return static_cast<uint_t>(cparg);
        } else {
          constexpr Int_t uint_B{B};
          Int_t cparg{arg};
          if (arg >= uint_B) { cparg %= uint_B; }
          return static_cast<uint_t>(cparg);
        }
      }
    }

  public:
    // =========================================================================
    // CONSTRUCTORES (continuación)
    // =========================================================================
    // NOTA: Constructor por defecto dig_t() ya declarado anteriormente
    
    /**
     * @brief Constructor desde un entero arbitrario
     * @tparam Int_t Tipo entero (signed/unsigned, cualquier tamaño)
     * @param arg Valor a convertir en dígito
     * @details Normaliza automáticamente el argumento al rango [0, B-1]
     *          mediante la función normaliza(). Acepta valores negativos.
     * 
     * @note constexpr: puede evaluarse en tiempo de compilación
     * @code
     * dig_t<10> d1(7);     // d1 = 7
     * dig_t<10> d2(15);    // d2 = 5 (15 % 10)
     * dig_t<10> d3(-3);    // d3 = 7 ((-3 % 10 + 10) % 10)
     * @endcode
     */
    template <type_traits::integral_c Int_t>
    constexpr dig_t(Int_t arg) noexcept : m_d(normaliza<Int_t>(arg)) {}
    
    /**
     * @brief Constructor de copia
     * @param other Dígito a copiar
     * @note Implementación por defecto del compilador
     */
    constexpr dig_t(const dig_t &) noexcept = default;
    
    /**
     * @brief Constructor de movimiento
     * @param other Dígito a mover
     * @note Implementación por defecto del compilador
     */
    constexpr dig_t(dig_t &&) noexcept = default;

    /**
     * @brief Constructor desde std::string (explícito)
     * @param str Cadena en formato "d[N]BM" o "dig#N#BM" donde N es el valor y M la base
     * @throws std::invalid_argument si el formato es inválido o M != B
     * @note Explícito: previene conversiones implícitas accidentales
     * @see from_string() para versión estática
     */
    explicit dig_t(const std::string &str);
    
    /**
     * @brief Constructor desde C-string (explícito, constexpr)
     * @param str Cadena en formato "d[N]BM" o "dig#N#BM" donde N es el valor y M la base
     * @throws std::invalid_argument si el formato es inválido o M != B
     * @note constexpr: puede evaluarse en tiempo de compilación
     * @see from_cstr() para versión estática
     */
    explicit constexpr dig_t(const char *str);

    // =========================================================================
    // FUNCIONES ESTÁTICAS DE PARSING
    // =========================================================================
    
    /**
     * @brief Crea un dígito desde std::string
     * @param str Cadena en formato "d[N]BM" o "dig#N#BM"
     * @return Dígito construido desde la cadena
     * @throws std::invalid_argument si el formato es inválido
     */
    static dig_t from_string(const std::string &str);
    
    /**
     * @brief Crea un dígito desde C-string (constexpr)
     * @param str Cadena en formato "d[N]BM" o "dig#N#BM"
     * @return Dígito construido desde la cadena
     * @throws std::invalid_argument si el formato es inválido
     */
    static constexpr dig_t from_cstr(const char *str);

    // =========================================================================
    // OPERADORES DE ASIGNACIÓN
    // =========================================================================
    
    /**
     * @brief Asignación desde un entero
     * @tparam Int_t Tipo entero (signed/unsigned, cualquier tamaño)
     * @param a Valor a asignar (se normaliza automáticamente)
     * @return Referencia a *this
     * @note Incluye optimización para evitar auto-asignación cuando Int_t == uint_t
     */
    template <type_traits::integral_c Int_t>
    constexpr const dig_t &operator=(const Int_t &a) noexcept {
      if constexpr (std::is_same_v<Int_t, uint_t>) {
        if (&a != &m_d) { m_d = normaliza<Int_t>(a); }
      } else { m_d = normaliza<Int_t>(a); }
      return (*this);
    }
    
    /// @brief Asignación de copia (implementación por defecto)
    constexpr dig_t &operator=(const dig_t &) noexcept = default;
    
    /// @brief Asignación por movimiento (implementación por defecto)
    constexpr dig_t &operator=(dig_t &&) noexcept = default;

    // =========================================================================
    // TEORÍA DE ANILLOS - Unidades e Inversos
    // =========================================================================
    
    /**
     * @brief Verifica si el dígito es una unidad en ℤ/Bℤ
     * @return true si existe inverso multiplicativo, false en caso contrario
     * 
     * @details TEORÍA: Un elemento es unidad (tiene inverso) si:
     *          - B es primo: todos los elementos ≠ 0 son unidades
     *          - B no primo: solo si gcd(elemento, B) = 1
     * 
     * @note Si B es primo (cuerpo), solo 0 no es unidad
     * @see mult_inv() para calcular el inverso
     */
    constexpr bool is_unit() const noexcept {
      if constexpr (is_prime()) {
        if (!is_0()) { return true; } 
        else { return false; }
      } else {
        if (is_1()) return true;
        else if (std::gcd(B, m_d) != ui_1()) return false;
        else return true;
      }
    }

    /// FUNCIÓN IS_0_DIVISOR DESDE EL PUNTO DE VISTA DE UN 
    /// ANILLO CONMUTATIVO
    /// VERDADERO SSI EXISTE ALGÚN ELEMENTO NO NULO QUE MULTIPLICADO
    /// POR ESTE DÉ CERO
    constexpr bool is_0_divisor() const noexcept {
      if constexpr (is_prime()) {
        if (is_0()) { return true; } 
        else { return false; }
      } else {
        if (is_0()) return true;
        else if (std::gcd(B, m_d) != ui_1()) return true;
        else return false;
      }
    }

    /// FUNCIÓN MULT_INV SI ES UNA UNIDAD
    /// DEL ANILLO CONMUTATIVO Z/BZ
    /// DIGITO.MULT_INV()*DIGITO = 1 MOD B
    constexpr dig_t mult_inv() const noexcept {
      if (is_unit()) {
        if (is_1()) return dig_1();
        else if (is_Bm1()) return dig_max();
        else {
          for (dig_t index(2); !is_Bm1(); ++index)
            if (index.is_unit()) {
              if (((*this) * index).is_1()) return index;
            }
          return dig_0();
        }
      } else return dig_0();
    }

    /// FUNCIÓN SUM_CARRY (ACARREO DE LA SUMA)
    /// DEVUELVE EL CARRY DE LA SUMA DE DOS DÍGITOS
    /// PARA NO DAR OVERFLOW EN NINGÚN MOMENTO.
    /// HACE UNA  BIFURCACIÓN SI LA BASE ES MAYOR
    /// MID = type_traits::middle_max<uint_t>()
    /// DENTRO DE ESTAS RAMAS SE BIFURCA SI ES PAR O IMPAR
    constexpr static dig_t sum_carry(dig_t arg_1, dig_t arg_2) noexcept {
      if constexpr (B <= type_traits::middle_max<uint_t>()) { // B <= MID
        if constexpr ((B % 2) == 0) { /// B PAR
          constexpr uint_t Bdiv2{B / 2};
          /// NOS ASEGURAMOS QUE ENTRE LOS DOS ARGUMENTOS 
          /// NO SUPERAMOS EL MÁXIMO DEL TIPO UINT_T
          if ((arg_1() < Bdiv2) && (arg_2() < Bdiv2)) { return dig_0(); } /// NO HAY ACARREO
          else if ((arg_1() >= Bdiv2) && (arg_2() >= Bdiv2)) { return dig_1(); } /// HAY ACARREO
          else if (arg_1() >= B - arg_2()) { return dig_1(); } /// HAY ACARREO (CONDICIÓN LÍMITE)
          else { return dig_0(); } /// NO HAY ACARREO (CONDICIÓN LÍMITE)
        } 
        else { // B IMPAR
          constexpr uint_t Bdiv2_1{B / 2};
          constexpr uint_t Bdiv2_2{(B / 2) + 1};
          /// NOS ASEGURAMOS QUE ENTRE LOS DOS ARGUMENTOS 
          /// NO SUPERAMOS EL MÁXIMO DEL TIPO UINT_T
          /// SON DOS CONDICIONES SIMÉTRICAS
          if (((arg_1() < Bdiv2_1) && (arg_2() < Bdiv2_2)) ||
              ((arg_1() < Bdiv2_2) && (arg_2() < Bdiv2_1)))  /// NO HAY ACARREO 
            { return dig_0(); }
          else if (((arg_1() >= Bdiv2_1) && (arg_2() >= Bdiv2_2)) ||
                   ((arg_1() >= Bdiv2_2) && (arg_2() >= Bdiv2_1)))  /// HAY ACARREO 
            { return dig_1(); }
          else if (arg_1() >= B - arg_2()) { return dig_1(); } /// HAY ACARREO (CONDICIÓN LÍMITE)
          else { return dig_0(); } /// NO HAY ACARREO (CONDICIÓN LÍMITE)
        }
      } else { // B > MID
        if constexpr ((B % 2) == 0) { // B PAR
          constexpr sig_uint_t Bdiv2{B / 2};
          /// NOS ASEGURAMOS QUE ENTRE LOS DOS ARGUMENTOS 
          /// NO SUPERAMOS EL MÁXIMO DEL TIPO UINT_T
          if ((arg_1() < Bdiv2) && (arg_2() < Bdiv2)) { return dig_0(); } /// NO HAY ACARREO
          else if ((arg_1() >= Bdiv2) && (arg_2() >= Bdiv2)) { return dig_1(); } /// HAY ACARREO
          else if (arg_1() >= B - arg_2()) { return dig_1(); } /// HAY ACARREO (CONDICIÓN LÍMITE)
          else { return dig_0(); } /// NO HAY ACARREO (CONDICIÓN LÍMITE)
        }
        else { // B IMPAR
          constexpr sig_uint_t Bdiv2_1{B / 2};
          constexpr sig_uint_t Bdiv2_2{(B / 2) + 1};
            /// NOS ASEGURAMOS QUE ENTRE LOS DOS ARGUMENTOS
            /// NO SUPERAMOS EL MÁXIMO DEL TIPO UINT_T
            /// SON DOS CONDICIONES SIMÉTRICAS
          if (((arg_1() < Bdiv2_1) && (arg_2() < Bdiv2_2)) ||
              ((arg_1() < Bdiv2_2) && (arg_2() < Bdiv2_1)))  /// NO HAY ACARREO
            { return dig_0(); }
          else if (((arg_1() >= Bdiv2_1) && (arg_2() >= Bdiv2_2)) ||
                   ((arg_1() >= Bdiv2_2) && (arg_2() >= Bdiv2_1)))  /// HAY ACARREO
            { return dig_1(); }
          else if (arg_1() >= B - arg_2()) { return dig_1(); } /// HAY ACARREO (CONDICIÓN LÍMITE)
          else { return dig_0(); } /// NO HAY ACARREO (CONDICIÓN LÍMITE)
        }
      }
    }

    /// SOBRECARGAS DE OPERADORES ARITMÉTICOS Y LÓGICOS BITWISE

    /// OPERADOR DE MULTIPLICACIÓN BOOLEANA BIT A BIT
    constexpr 
    dig_t operator&(const dig_t &arg) const noexcept { return (((*this) <= arg) ? (*this) : arg); }
    
    /// OPERADOR DE MULTIPLICACIÓN BOOLEANA BIT A BIT CON ASIGNACIÓN
    constexpr 
    const dig_t &operator&=(dig_t arg) noexcept {
      if (arg < (*this)) (*this) = arg;
      return (*this);
    }
    
    /// OPERADOR DE SUMA BOOLEANA BIT A BIT
    constexpr 
    dig_t operator|(const dig_t &arg) const noexcept { 
        return (((*this) >= arg) ? (*this) : arg); 
    }
    
    /// OPERADOR DE SUMA BOOLEANA BIT A BIT CON ASIGNACIÓN
    constexpr 
    const dig_t &operator|=(dig_t arg) noexcept {
      if (arg > (*this)) (*this) = arg;
      return (*this);
    }

    /// OPERADOR DE EXPONENCIACIÓN CON ASIGNACIÓN DADO UN  ELEMENTO DE TIPO ENTERO
    template <type_traits::unsigned_integral_c UIntType> constexpr 
    const dig_t &operator^=(UIntType exp) noexcept {
      dig_t &cthis{*this};
      if (exp == 0) {
        cthis = dig_1();
        return (cthis);
      } else if (exp == 1) {
        return (cthis);
      } else if (exp == 2) {
        cthis *= cthis;
        return (cthis);
      } else {
        const dig_t vthis{*this};
        cthis *= vthis;
        for (UIntType ix{2}; ix < exp; ++ix) { cthis *= vthis; }
        return (cthis);
      }
    }

    /// OPERADOR DE EXPONENCIACIÓN DADO UN  ELEMENTO DE TIPO ENTERO
    template <type_traits::unsigned_integral_c UIntType>
    constexpr dig_t operator^(UIntType exp) const noexcept
    {
      dig_t cpthis{*this};
      cpthis ^= exp;
      return cpthis;
    }

    /// OPERADORES DE COMPARACIÓN (DELEGADAS A LA DE LOS TIPOS ENTEROS QUE ENCIERRAN)
    /// COMPARACIÓN DIG_T @ DIG_T
    /// DEVUELVE BOOLEANO
    /// ESTO SE PUEDE HACER ASÍ PORQUE M_D SIEMPRE ESTÁ NORMALIZADO
    constexpr bool operator==(dig_t a) const noexcept { return ((a.m_d == m_d) ? true : false); }
    constexpr bool operator!=(dig_t a) const noexcept { return ((a.m_d != m_d) ? true : false); }
    constexpr bool operator>=(dig_t a) const noexcept { return ((a.m_d <= m_d) ? true : false); }
    constexpr bool operator>(dig_t a) const noexcept { return ((a.m_d < m_d) ? true : false); }
    constexpr bool operator<=(dig_t a) const noexcept { return ((a.m_d >= m_d) ? true : false); }
    constexpr bool operator<(dig_t a) const noexcept { return ((a.m_d > m_d) ? true : false); }

    /// OPERADOR DE COMPARACIÓN TOTAL NAVE_ESPACIAL
    /// DEVUELVE std::strong_ordering (ORDEN FUERTE)
    /// COMPARACIÓN DIG_T @ DIG_T
    constexpr 
    std::strong_ordering operator<=>(dig_t rhs) const noexcept {
      const auto lhs_d{m_d};
      const auto rhs_d{rhs.m_d};
      return ((lhs_d < rhs_d) ? std::strong_ordering::less
                              : ((lhs_d > rhs_d) ? std::strong_ordering::greater
                                                 : std::strong_ordering::equal));
    }

    /// IGUALDAD CON UN ENTERO (MÓDULO LA BASE)
    /// COMPARACIÓN DIG_T @ INT_T
    template <type_traits::integral_c Int_t> constexpr 
    bool operator==(Int_t rhs) noexcept {
      const dig_t &lhs{*this};
      return ((lhs.m_d == normaliza<Int_t>(rhs)) ? true : false);
    }

    /// OPERADOR DE COMPARACIÓN TOTAL NAVE_ESPACIAL CON UN ENTERO
    /// DEVUELVE std::weak_ordering (ORDEN DÉBIL)
    /// COMPARACIÓN DIG_T @ INT_T
    template <type_traits::integral_c Int_t> constexpr 
    std::weak_ordering operator<=>(Int_t rhs) const noexcept {
      const dig_t &lhs{*this};
      const uint_t rhs_B{normaliza<Int_t>(rhs)};
      return ((lhs() < rhs_B)   ? std::weak_ordering::less
                                : (lhs() > rhs_B) ? std::weak_ordering::greater
                                                  : std::weak_ordering::equivalent);
    }

    /// SOBRECARGAS DE OPERADORES ARITMÉTICOS CON ASIGNACIÓN

    /// OPERADOR DE SUMA CON ASIGNACIÓN
    /// DIG_T += DIG_T
    constexpr 
    const dig_t &operator+=(dig_t arg) noexcept {
      dig_t &cthis{*this};
      if constexpr (B < type_traits::middle_max<uint_t>()) {
        m_d += arg.m_d;
        if (m_d >= B) m_d -= B;
        return (cthis);
      } else {
        sig_uint_t tmp{m_d};
        tmp += (arg.m_d);
        if (tmp >= B) tmp -= B;
        m_d = static_cast<uint_t>(tmp);
        return (cthis);
      }
    }

    /// OPERADOR DE SUMA CON ASIGNACIÓN DESDE UN ENTERO
    /// DIG_T += INT_T
    template <type_traits::integral_c Int_t> constexpr 
    const dig_t &operator+=(Int_t arg) noexcept {
      if constexpr (B >= type_traits::middle_max<uint_t>()) {
        const sig_uint_t arg1{normaliza<Int_t>(arg)};
        sig_uint_t arg2{m_d};
        arg2 += arg1;
        if (arg2 >= static_cast<Int_t>(B)) arg2 -= static_cast<Int_t>(B);
        m_d = static_cast<uint_t>(arg2);
        return (*this);
      } else {
        const uint_t arg1{normaliza<Int_t>(arg)};
        uint_t arg2{m_d};
        arg2 += arg1;
        if (arg2 >= static_cast<Int_t>(B)) arg2 -= static_cast<Int_t>(B);
        m_d = static_cast<uint_t>(arg2);
        return (*this);
      }
    }

    /// OPERADOR DE RESTA CON ASIGNACIÓN
    /// DIG_T -= DIG_T
    constexpr 
    const dig_t &operator-=(dig_t arg) noexcept {
      sig_sint_t cp_dm{m_d};
      cp_dm -= arg.m_d;
      if (cp_dm < 0) cp_dm += ssi_B();
      m_d = cp_dm;
      return (*this);
    }

    /// OPERADOR DE RESTA CON ASIGNACIÓN DESDE UN ENTERO
    /// DIG_T -= INT_T
    template <type_traits::integral_c Int_t> constexpr
    const dig_t &operator-=(Int_t arg) noexcept {
      sig_sint_t tmp{normaliza<Int_t>(arg)};
      sig_sint_t este{m_d};
      este -= tmp;
      if (este < static_cast<sig_sint_t>(0)) este += ssi_B();
      m_d = este;
      return (*this);
    }

    /// OPERADOR DE MULTIPLICACIÓN CON ASIGNACIÓN
    /// DIG_T *= DIG_T
    constexpr 
    const dig_t &operator*=(dig_t arg) noexcept {
      if constexpr (B < type_traits::sqrt_max<uint_t>()) { /// NO OVERFLOW (B SMALL)
        m_d *= arg.m_d;
        m_d %= B;
        return (*this);
      } else {  /// WOULD BE OVERFLOW (B BIGGER THAN SQRT(MAX_UINT_T))
        sig_uint_t tmp{m_d};
        tmp *= arg.m_d;
        tmp %= static_cast<sig_uint_t>(B);
        m_d = static_cast<uint_t>(tmp);
        return (*this);
      }
    }

    /// OPERADOR DE MULTIPLICACIÓN CON ASIGNACIÓN
    /// DIG_T *= INT_T
    template <type_traits::integral_c Int_t> constexpr
    const dig_t &operator*=(Int_t arg) noexcept {
      const Int_t tmp{normaliza<Int_t>(arg)};
      if constexpr (std::is_signed_v<Int_t>) { /// TIPO CON SIGNO
        if constexpr (sizeof(Int_t) > sizeof(uint_t)) { /// TIPO ENTERO MAYOR QUE UINT_T
          using SIG2_SINT_T = type_traits::sig_SInt_for_SInt_t<Int_t>;
          const SIG2_SINT_T norm_arg{tmp};
          SIG2_SINT_T este{m_d};
          este *= norm_arg;
          este %= static_cast<SIG2_SINT_T>(B);
          m_d = static_cast<uint_t>(este);
          return (*this);
        } else { /// TIPO ENTERO MENOR O IGUAL QUE UINT_T
          const sig_sint_t norm_arg{tmp};
          sig_sint_t este{m_d};
          este *= norm_arg;
          este %= static_cast<sig_sint_t>(B);
          m_d = static_cast<uint_t>(este);
          return (*this);
        }
      } else { /// TIPO SIN SIGNO
        if constexpr (sizeof(Int_t) > sizeof(uint_t)) { /// TIPO ENTERO MAYOR QUE UINT_T
          using SIG2_UINT_T = type_traits::sig_UInt_for_UInt_t<Int_t>;
          const SIG2_UINT_T norm_arg{tmp};
          SIG2_UINT_T este{m_d};
          este *= norm_arg;
          este %= static_cast<SIG2_UINT_T>(B);
          m_d = static_cast<uint_t>(este);
          return (*this);
        } else { /// TIPO ENTERO MENOR O IGUAL QUE UINT_T
          const sig_uint_t norm_arg{tmp};
          sig_uint_t este{m_d};
          este *= norm_arg;
          este %= static_cast<sig_uint_t>(B);
          m_d = static_cast<uint_t>(este);
          return (*this);
        }
      }
    }

    /// OPERADOR DE DIVISIÓN CON ASIGNACIÓN
    /// DIG_T /= DIG_T
    constexpr 
    const dig_t &operator/=(dig_t arg) noexcept {
      if (arg.m_d != ui_0()) m_d /= arg.m_d;
      return (*this);
    }

    /// OPERADOR DE DIVISIÓN CON ASIGNACIÓN DESDE UN ENTERO
    /// DIG_T /= INT_T
    template <type_traits::integral_c Int_t> constexpr
    const dig_t &operator/=(Int_t arg) noexcept {
      uint_t cparg{normaliza<Int_t>(arg)};
      dig_t tmp{cparg};
      if (tmp != dig_0()) (*this) /= tmp;
      return (*this);
    }

    /// OPERADOR DE MÓDULO CON ASIGNACIÓN
    /// DIG_T %= DIG_T
    constexpr 
    const dig_t &operator%=(dig_t arg) noexcept {
      if (arg.m_d != ui_0()) m_d %= arg.m_d;
      return (*this);
    }

    /// OPERADOR DE MÓDULO CON ASIGNACIÓN DESDE UN ENTERO
    /// DIG_T %= INT_T
    template <type_traits::integral_c Int_t> constexpr
    const dig_t &operator%=(Int_t arg) noexcept {
      dig_t cparg{normaliza<Int_t>(arg)};
      if (cparg != dig_0()) (*this) %= cparg;
      return (*this);
    }

    /// OPERADORES DE INCREMENTO Y DECREMENTO

    /// OPERADOR DE INCREMENTO (PRE-INCREMENTO)
    constexpr 
    const dig_t &operator++() noexcept {
      (m_d < ui_max()) ? (++m_d) : (m_d = ui_0());
      return (*this);
    }

    /// OPERADOR DE INCREMENTO (POST-INCREMENTO)
    constexpr 
    dig_t operator++(int) noexcept {
      dig_t ret(*this);
      ++(*this);
      return ret;
    }

    /// OPERADOR DE DECREMENTO (PRE-DECREMENTO)
    constexpr 
    const dig_t &operator--() noexcept {
      if (m_d > ui_0()) { --m_d; }
      else { m_d = ui_max(); }
      return (*this);
    }

    /// OPERADOR DE DECREMENTO (POST-DECREMENTO)
    constexpr 
    dig_t operator--(int) noexcept {
      dig_t ret(*this);
      --(*this);
      return ret;
    }

    /// SOBRECARGAS DE OPERADORES ARITMÉTICOS
    /// SIMPLES, SE BASAN EN LAS VERSIONES CON ASIGNACIÓN
    /// ESTÁN LO SUFICIENTE OPTIMIZADOS POR EL COMPILADOR
    constexpr dig_t operator+(dig_t arg) const noexcept { dig_t ret(*this); ret += arg; return ret; }
    constexpr dig_t operator-(dig_t arg) const noexcept { dig_t ret(*this); ret -= arg; return ret; }
    constexpr dig_t operator*(dig_t arg) const noexcept { dig_t ret(*this); ret *= arg; return ret; }
    constexpr dig_t operator/(dig_t arg) const noexcept { dig_t ret(*this); ret /= arg; return ret; }
    constexpr dig_t operator%(dig_t arg) const noexcept { dig_t ret(*this); ret %= arg; return ret; }


    /// OPERADORES ARITMÉTICOS SIMPLES CON ENTEROS

    /// OPERADOR DE SUMA CON ENTERO
    template <type_traits::integral_c Int_type> constexpr
    dig_t operator+(Int_type arg) const noexcept { 
        dig_t ret(*this); 
        ret += normaliza<Int_type>(arg); 
        return ret; 
    }

    /// OPERADOR DE RESTA CON ENTERO
    template <type_traits::integral_c Int_type> constexpr
    dig_t operator-(Int_type arg) const noexcept { 
        dig_t ret(*this); 
        const dig_t tmp(normaliza<Int_type>(arg)); 
        ret -= tmp; return ret; 
    }
    
    /// OPERADOR DE MULTIPLICACIÓN CON ENTERO
    template <type_traits::integral_c Int_type> constexpr
    dig_t operator*(Int_type arg) const noexcept { 
        dig_t ret(*this); 
        const dig_t tmp(normaliza<Int_type>(arg)); 
        ret *= tmp; return ret; 
    }
    
    /// OPERADOR DE DIVISIÓN CON ENTERO
    template <type_traits::integral_c Int_type> constexpr
    dig_t operator/(Int_type arg) const noexcept { 
        dig_t ret(*this); 
        const dig_t cparg(normaliza<Int_type>(arg)); 
        if (cparg != dig_0()) ret /= cparg; 
        return ret; 
    }

    /// OPERADOR DE MÓDULO CON ENTERO
    template <type_traits::integral_c Int_type> constexpr
    dig_t operator%(Int_type arg) const noexcept { 
        dig_t ret(*this); 
        const dig_t cparg(normaliza<Int_type>(arg)); 
        if (cparg != dig_0()) ret %= cparg; 
        return ret; 
    }

    /// OPERADORES UNARIOS
    /// OPERADOR DE COMPLEMENTO A LA BASE B MENOS EL DÍGITO
    constexpr dig_t operator~() const noexcept { return dig_t(ui_max() - m_d); }
    /// OPERADOR DE MENOS UNARIO (COMPLEMENTO A LA BASE B)
    constexpr dig_t operator-() const noexcept { return dig_t((m_d == 0) ? 0 : (B - m_d)); }
    /// OPERADOR DE COMPLEMENTO A LA BASE B MENOS EL DÍGITO
    constexpr dig_t C_Bm1() const noexcept { return dig_t(ui_max() - m_d); }
    /// OPERADOR DE MENOS UNARIO (COMPLEMENTO A LA BASE B)
    constexpr dig_t C_B() const noexcept { return dig_t((m_d == 0) ? 0 : (B - m_d)); }
    /// OPERADOR DE COMPLEMENTO A LA BASE B MENOS EL DÍGITO CON ASIGNACIÓN
    constexpr const dig_t &mC_Bm1() noexcept { 
        m_d = (ui_max() - m_d); 
        return (*this); 
    }
    /// OPERADOR DE MENOS UNARIO (COMPLEMENTO A LA BASE B) CON ASIGNACIÓN
    constexpr const dig_t &mC_B() noexcept { 
        (m_d == 0) ? (m_d) : (m_d = (B - m_d)); 
        return (*this); 
    }

    /// FUNCIONES DE CONSULTA DEL VALOR DEL DÍGITO
    constexpr bool is_0() const noexcept { return (m_d == ui_0()); }
    constexpr bool is_1() const noexcept { return (m_d == ui_1()); }
    constexpr bool is_0or1() const noexcept { return ((m_d == ui_0()) || (m_d == ui_1())); }
    constexpr bool is_not_1() const noexcept { return (m_d != ui_1()); }
    constexpr bool is_not_0() const noexcept { return (m_d != ui_0()); }
    constexpr bool is_not_0or1() const noexcept { return (!is_0or1()); }
    constexpr bool is_Bm1() const noexcept { return (m_d == ui_Bm1()); }
    constexpr bool is_not_Bm1() const noexcept { return (m_d != ui_Bm1()); }
    constexpr bool is_Bm1orBm2() const noexcept { return (is_Bm1() || is_Bm2()); }
    constexpr bool is_not_Bm1orBm2() const noexcept { return (is_not_Bm1() && is_not_Bm2()); }
    constexpr bool is_Bm2() const noexcept { return (m_d == ui_Bm2()); }
    constexpr bool is_not_Bm2() const noexcept { return (m_d != ui_Bm2()); }
    constexpr bool is_not_maxormin() const noexcept { return (is_not_0() && is_not_Bm1()); }
    constexpr bool is_maxormin() const noexcept { return (is_0() || is_Bm1()); }
    /// FUNCIONES QUE DETERMINAN SI EL DÍGITO ESTÁ LEJOS O CERCA
    /// DEL VALOR MÁXIMO O MÍNIMO POSIBLE
    /// EN BASE 2 NO TIENEN SENTIDO
    constexpr bool is_far_maxormin() const noexcept { 
        if constexpr (B == 2u) { return false; } 
        else { return (is_not_0() && is_not_Bm1() && is_not_1() && is_not_Bm2()); } 
    }
    constexpr bool is_near_maxormin() const noexcept { 
        if constexpr (B == 2u) { return true; } 
        else { return (is_0() || is_Bm1() || is_1() || is_Bm2()); } 
    }

  private:

    std::string num_to_string() const noexcept {
      const std::int64_t data_member = static_cast<std::int64_t>(this->m_d);
      std::ostringstream fmtr_obj;
      fmtr_obj << data_member;
      const std::string ret{fmtr_obj.str()};
      return ret;
    }

    std::string radix_str() const noexcept {
      constexpr std::int64_t radix = static_cast<std::int64_t>(B);
      std::ostringstream fmtr_obj;
      fmtr_obj << radix;
      const std::string ret{static_cast<std::string>("B") + static_cast<std::string>(fmtr_obj.str())};
      return ret;
    }

    // =========================================================================
    // TODO: MEJORAS PENDIENTES EN PARSING Y SERIALIZACIÓN
    // =========================================================================
    // 
    // 1. **to_cstr consteval**: Crear versión consteval de to_string para C-strings
    //    - Permitiría literales compile-time sin depender de std::to_string
    //    - Formato de salida: "d[N]BM" donde N=valor, M=base
    //    - Beneficio: from_cstr() podría usarse completamente en compile-time
    //
    // 2. **Parser incompleto**: Actualmente solo soporta 2 de 4 combinaciones
    //    La especificación completa debería ser:
    //      formato ::= prefijo separadores número "B" base
    //      prefijo ::= "d" | "dig"
    //      separadores ::= "[" ... "]" | "#" ... "#"
    //    
    //    Estado actual:
    //      ✅ "d[N]BM"     - soportado (línea 992)
    //      ✅ "dig#N#BM"   - soportado (línea 996)
    //      ❌ "d#N#BM"     - NO soportado (falta implementar)
    //      ❌ "dig[N]BM"   - NO soportado (falta implementar)
    //
    //    Razón: parse_impl() asume d→[...] y dig→#...# de forma fija
    //    Solución: Separar detección de prefijo y separadores independientemente
    // =========================================================================

    /// IMPLEMENTACIÓN DE LA FUNCIÓN DE PARSEO DESDE UNA CADENA DE CARACTERES CSTR
    static constexpr 
    std::pair<uint_t, bool> parse_impl(
        const char *str, std::size_t size, 
        std::uint64_t base_template) noexcept {
      if (!str || size < 4) return {0, false};

      std::size_t pos = 0;
      bool is_strict_format = false;

      if (size >= 4 && str[0] == 'd' && str[1] == '[') {
        is_strict_format = true;
        pos = 2;
      }
      else if (size >= 6 && str[0] == 'd' && str[1] == 'i' && str[2] == 'g' && str[3] == '#') {
        is_strict_format = false;
        pos = 4;
      }
      else { return {0, false}; }

      uint_t numero = 0;
      std::size_t digit_count = 0;

      if (is_strict_format) {
        while (pos < size && str[pos] != ']') {
          if (str[pos] >= '0' && str[pos] <= '9') {
            sig_uint_t temp = static_cast<sig_uint_t>(numero) * 10 + (str[pos] - '0');
            numero = static_cast<uint_t>(temp % static_cast<sig_uint_t>(base_template));
            digit_count++;
          } else { return {0, false}; }
          pos++;
        }

        if (pos >= size || str[pos] != ']') return {0, false};
        pos++;
      } else {
        while (pos < size && str[pos] != '#') {
          if (str[pos] >= '0' && str[pos] <= '9') {
            sig_uint_t temp = static_cast<sig_uint_t>(numero) * 10 + (str[pos] - '0');
            numero = static_cast<uint_t>(temp % static_cast<sig_uint_t>(base_template));
            digit_count++;
          } else { return {0, false}; }
          pos++;
        }

        if (pos >= size || str[pos] != '#') return {0, false};
        pos++;
      }

      if (digit_count == 0) return {0, false};

      if (pos >= size || str[pos] != 'B') return {0, false};
      pos++;

      sig_uint_t base_leida = 0;
      std::size_t base_digits = 0;

      while (pos < size && str[pos] >= '0' && str[pos] <= '9') {
        base_leida = base_leida * 10 + (str[pos] - '0');
        base_digits++;
        pos++;
      }

      if (base_digits == 0 || base_leida != base_template)
        return {0, false};

      return {numero, true};
    }

  public:

    /// FUNCIÓN RADIX QUE DEVUELVE LA BASE DEL DÍGITO
    /// UTILIDAD PARA PLANTILLAS GENÉRICAS
    consteval std::uint64_t radix() const { return B; }

    /// FUNCIÓN TO_STRING QUE DEVUELVE LA REPRESENTACIÓN EN CADENA DE CARACTERES
    /// TIPO std::string DE LA FORMA "d[number]Bbase"
    constexpr std::string to_string() const noexcept {
      const std::string num{this->num_to_string()};
      const std::string ret{"d[" + num + "]" + radix_str()};
      return ret;
    }
  }; /// END CLASS DIG_T

  /// FUNCIÓN DE PARSEO DESDE UNA CADENA DE CARACTERES (STATIC)
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

  /// FUNCIÓN DE PARSEO DESDE UNA CADENA DE CARACTERES CSTR (STATIC)
  template <std::uint64_t Base>
    requires(Base > 1)
  constexpr dig_t<Base> dig_t<Base>::from_cstr(const char *str)
  {
    if (str == nullptr)
    {
      throw std::invalid_argument("Null pointer passed to from_cstr");
    }

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

  /// IMPLEMENTACIÓN DE LOS CONSTRUCTORES DESDE CADENA DE CARACTERES
  template <std::uint64_t Base>
    requires(Base > 1)
  dig_t<Base>::dig_t(const std::string &str) : dig_t(from_string(str)) {}

  /// IMPLEMENTACIÓN DE LOS CONSTRUCTORES DESDE CADENA DE CARACTERES CSTR
  template <std::uint64_t Base>
    requires(Base > 1)
  constexpr dig_t<Base>::dig_t(const char *str) : dig_t(from_cstr(str)) {}

    /// SOBRECARGAS DE LOS OPERADORES DE FLUJO
  template <std::uint64_t Base>
    requires(Base > 1)
  std::istream &operator>>(std::istream &is, dig_t<Base> &arg) {
    std::string input_str;
    is >> input_str;

    if (is.fail())
    {
      return is;
    }

    try
    {
      arg = dig_t<Base>::from_string(input_str);
    }
    catch (const std::exception &)
    {
      is.setstate(std::ios::failbit);
    }

    return is;
  }

  /// IMPLEMENTACIÓN DEL OPERADOR DE SALIDA
  template <std::uint64_t Base>
    requires(Base > 1)
  std::ostream &operator<<(std::ostream &os, dig_t<Base> arg) {
    os << "d[" << static_cast<std::int64_t>(arg())
       << "]B" << static_cast<std::int64_t>(Base);
    return os;
  }

} // namespace NumRepr

#endif // CORE_DIG_T_HPP_INCLUDED
