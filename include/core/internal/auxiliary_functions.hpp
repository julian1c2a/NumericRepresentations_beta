#ifndef NUMREPR_CORE_INTERNAL_AUXILIARY_FUNCTIONS_HPP_INCLUDED
#define NUMREPR_CORE_INTERNAL_AUXILIARY_FUNCTIONS_HPP_INCLUDED

#include <bit>
#include <cstddef>
#include <cstdint>
// #include <cmath>
#include <type_traits>
#include <tuple>
#include <expected>
#include <concepts>
#include "basic_types.hpp"

namespace NumRepr {
  namespace auxiliary_functions {
  
  /**
   * @brief Calcula la raíz cuadrada entera por defecto de un número entero no negativo.
   * @details Esta función calcula la parte entera de la raíz cuadrada de un número no negativo `n` dado.
   * Encuentra el entero más grande `r` tal que `r*r <= n`.
   * Para mayor eficiencia, utiliza una combinación de una tabla de búsqueda para valores pequeños y el método
   * de Newton-Raphson para valores más grandes.
   *
   * @tparam T El tipo del entero, que debe ser un tipo integral.
   * @param n El entero no negativo cuya raíz cuadrada se va a calcular.
   * @return La raíz cuadrada entera por defecto de `n`.
   *
   * @pre `n` debe ser no negativo.
   * @post El valor devuelto `r` satisface `r*r <= n` y `(r+1)*(r+1) > n`.
   *
   * @par Properties
   * - Para `n = 0`, el resultado es `0`.
   * - Para `n = 1`, el resultado es `1`.
   * - La función es monotónicamente creciente: si `a > b`, entonces `floorsqrt(a) >= floorsqrt(b)`.
   * - `floorsqrt(n*n) == n` para cualquier `n` no negativo.
   *
   * @par Invariants
   * - Para la iteración de Newton-Raphson, la secuencia de estimaciones `x_k` converge monotónicamente desde arriba hacia la verdadera raíz cuadrada.
   *
   * @par Things that should never happen
   * - La función no debe entrar en un bucle infinito.
   * - La función no debe devolver un valor `r` tal que `r*r > n`.
   * - La función no debe desbordarse durante los cálculos intermedios si `n` está dentro del rango del tipo `T`.
   */
  template <typename T> constexpr
  T floorsqrt(T n) noexcept {
      /// VALORES PREESTABLECIDO COMO EN UNA TABLA
      /// AL MODO LOOKUP TABLES
      if (n == 0)                  return 0;
      if (n >= 1 && n < 4)         return 1;
      if (n >= 4 && n < 9)         return 2;
      if (n >= 9 && n < 16)        return 3;
      if (n >= 16 && n < 25)       return 4;
      if (n >= 25 && n < 36)       return 5;
      if (n >= 36 && n < 49)       return 6;
      if (n >= 49 && n < 64)       return 7;
      if (n >= 64 && n < 81)       return 8;
      if (n >= 81 && n < 100)      return 9;
      if (n >= 100 && n < 121)     return 10;
      if (n >= 121 && n < 144)     return 11;
      if (n >= 144 && n < 169)     return 12;
      if (n >= 169 && n < 196)     return 13;
      if (n >= 196 && n < 225)     return 14;
      if (n >= 225 && n < 256)     return 15;
      if (n >= 256 && n < 289)     return 16;
      if (n >= 289 && n < 324)     return 17;
      if (n >= 324 && n < 361)     return 18;
      if (n >= 361 && n < 400)     return 19;
      if (n >= 400 && n < 441)     return 20;
      if (n >= 441 && n < 484)     return 21;
      if (n >= 484 && n < 529)     return 22;

      // std::bit_width requiere un tipo sin signo.
      using UnsignedT = std::make_unsigned_t<T>;
      T x0 = T(1) << (std::bit_width(static_cast<UnsignedT>(n)) / 2);
      
      // La iteración de Newton-Raphson converge desde arriba si la conjetura es >= sqrt(n).
      // Si nuestra conjetura x0 es una subestimación, la primera iteración x1 será mayor.
      // Nos aseguramos de que la conjetura inicial sea siempre una sobreestimación o igual.
      if (x0 * x0 < n) {
          x0 = x0 * 2;
      }
      
      T x1 = (x0 + n / x0) / 2;
      while (x1 < x0) {
          x0 = x1;
          x1 = (x0 + n / x0) / 2;
      }
      
      // La iteración se detiene cuando x0 <= sqrt(n).
      // x0 es el resultado correcto.
      return x0;
  }

  /**
   * @brief Calcula la raíz cuadrada entera por exceso (techo) de un número.
   * @tparam T El tipo de dato del número, debe ser un tipo integral.
   * @param n El número no negativo del que se calculará la raíz.
   * @return La raíz cuadrada entera por exceso de n.
   *
   * @pre `n` debe ser no negativo.
   * @post El valor devuelto `r` satisface `r*r >= n` y `(r-1)*(r-1) < n`.
   *
   * @par Properties
   * - Para `n = 0`, el resultado es `0`.
   * - Para `n = 1`, el resultado es `1`.
   * - Para `n` tal que `is_perfect_square(n)` es true, el resultado es `ceilsqrt(n)`.
   * - Para `n` tal que `is_perfect_square(n)` es true, `ceilsqrt(n)*ceilsqrt(n) == n`.
   * - La función es monotónicamente creciente: si `a > b`, entonces `ceilsqrt(a) >= ceilsqrt(b)`.
   * - `ceilsqrt(n*n) == n` para cualquier `n` no negativo.
   *
   * @par Invariants
   * 
   *
   * @par Things that should never happen
   * - La función no debe entrar en un bucle infinito.
   * - La función no debe devolver un valor `r` tal que `r*r < n`.
   * - La función no debe desbordarse durante los cálculos intermedios si `n` está dentro del rango del tipo `T`.
   */
  template <typename T>
  constexpr T ceilsqrt(T n) noexcept {
      if (n == 0) return 0;
      T root = floorsqrt(n);
      // Si n no es un cuadrado perfecto, la raíz cuadrada entera superior es root + 1.
      return (root * root == n) ? root : root + 1;
  }

  /**
   * @brief Comprueba si un número es un cuadrado perfecto.
   * @tparam T El tipo de dato del número, debe ser un tipo integral.
   * @param n El número a comprobar.
   * @return true si n es un cuadrado perfecto, false en caso contrario.
   *
   * @pre `n` negativo daría necesariamente false.
   * @post 'Existe un entero r tal que r*r == n, r == ceilsqrt(n) == floorsqrt(n)'.
   *
   * @par Properties
   * - Para `n = 0`, el resultado es `true`.
   * - Para `n = 1`, el resultado es `true`.
   * - Para `n = 2`, el resultado es `false`.
   * - Para `n = 3`, el resultado es `false`.
   * - Para `n = 4`, el resultado es `true`.
   * - Para `n = 5`, el resultado es `false`.
   * - Para `n = 6`, el resultado es `false`.
   * - Para `n = 7`, el resultado es `false`.
   * - Para `n = 8`, el resultado es `false`.
   * - Para `n = 9`, el resultado es `true`.
   * - Para `n = 10`, el resultado es `false`.
   * - Para `n = 11`, el resultado es `false`.
   * - Para `n = 12`, el resultado es `false`.
   * - Para `n = 13`, el resultado es `false`.
   * - Para `n = 14`, el resultado es `false`.
   * - Para `n = 15`, el resultado es `false`.
   * - Para `n = 16`, el resultado es `true`.
   * - Para `n = 25`, el resultado es `true`.
   * - Para `n = 36`, el resultado es `true`.
   * - Para `n = 49`, el resultado es `true`.
   * - Para `n = 64`, el resultado es `true`.
   * - Para `n = 81`, el resultado es `true`.
   * - Para `n = 100`, el resultado es `true`.
   * - Para `n` tal que `is_perfect_square(n)` es true, `ceilsqrt(n) == floorsqrt(n)`.
   * - Si `r^2 == n`, entonces `(r+1)^2 == n + (2r + 1)`.
   * - Si `n` y `m` son cuadrados perfectos consecutivos, entonces para todo 'k' en el rango (n, m), `is_perfect_square(k)` es false.
   * no puede ser cuadrado perfecto.
   * - Si `n,m,l` son cuadrados perfectos, tales que `n < m < l`, entonces `l-m > m-n.
   *
   * @par Invariants
   * 
   *
   * @par Things that should never happen
   * - La función no debe entrar en un bucle infinito.
   * - La función no debe desbordarse durante los cálculos intermedios si `n` está dentro del rango del tipo `T`.
   */
  template<typename T>
  constexpr bool is_perfect_square(T n) noexcept {
    if ((n == 0)||(n == 1)) return true;
    T root = floorsqrt(n);
    return root * root == n;
  }

  // --- Backward compatibility wrappers for std::size_t ---
  // This overload is kept for compatibility with code that might call it with 3 arguments.
  constexpr inline
  std::size_t ceilsqrt(std::size_t n, std::size_t, std::size_t) noexcept {
    return ceilsqrt<std::size_t>(n);
  }

  constexpr inline
  std::size_t ceilsqrt(std::size_t n) noexcept {
    return ceilsqrt<std::size_t>(n);
  }

  /**
   * @brief Comprueba si un número es una potencia de 2.
   * @param num El número a comprobar.
   * @return true si el número es una potencia de 2, false en caso contrario.
   *
   * @pre `n` no será negativo ni `0`.
   *
   * @post 
   *
   * @par Properties
   * - `is_prime(n) and is_power_of_2(n)` entonces `n == 2`.
   * - Existen exactamente 64 potencias de 2 en el rango de uint64_t: 2^0, 2^1, 2^2, ..., 2^63.
   * 
   * @par Invariants
   * - Si `n` es una potencia de 2, entonces, siempre que el cociente sea distinto de 1
   * el resto de dividir por 2 será 0, en las sucesivas divisiones del cociente.
   * - Si `n` no es una potencia de 2, entonces, en algún momento, el resto de dividir por 2 será 1,
   * sin ser el cociente 1.
   * - La única potencia de 2 que es impar es 2^0 == 1.
   * - Si `n` es potencia de 2, entonces `n & (n - 1) == 0`.
   * 
   * @par Things that should never happen
   * - La función no debe entrar en un bucle infinito.
   * - La función no debe desbordarse durante los cálculos intermedios si `n` 
   * está dentro del rango del tipo `T`.
   */
  template <std::uint64_t num>
  consteval
  bool is_power_of_2_ct() noexcept { 
    return num > 0 && (num & (num - 1)) == 0; 
  }
  /**
   * @brief Comprueba si un número es una potencia de 2, 
   * pero nos aseguramos que sea en tiempo de compilación. 
   * `_ct` es compile time
   */
  template <std::integral T>
  constexpr inline
  bool is_power_of_2(T num) noexcept { 
    return num > 0 && (num & (num - 1)) == 0; 
  }

  enum class factor_error {
    invalid_range,
    domain_error
  };

  /**
   * @brief Busca recursivamente un factor impar de un número en un rango en tiempo de compilación.
   * @details Esta es una función auxiliar para `is_prime`. Realiza una búsqueda
   * recursiva en el rango de enteros `[low, high)` para encontrar un entero `k`
   * tal que `2*k + 1` es un factor de `n`.
   *
   * @tparam T El tipo integral.
   * @tparam n El número a factorizar.
   * @tparam low El límite inferior (inclusivo) del rango de búsqueda para `k`.
   * @tparam high El límite superior (exclusivo) del rango de búsqueda para `k`.
   * @return `true` si se encuentra un `k` en `[low, high)` tal que `(2*k + 1)` divide a `n`.
   *         `false` en caso contrario.
   *
   * @pre `n > high`, `high > low` y `low > 1`.
   *
   * @post `find_factor_ct` es true si se encuentra un factor en el rango, false en caso contrario.
   */
   template <std::integral T, T n, T low, T high>
        requires ( (low > 1) && (high > low) && (n > high) )
   consteval bool find_factor_ct() noexcept {
    if constexpr (low + 1 >= high) {
        return (n % (2 * low + 1)) == 0;
    } else {
        constexpr auto mid = std::midpoint(low, high);
        return find_factor_ct<T, n, low, mid>() || find_factor_ct<T, n, mid, high>();
    }
  }

  /**
   * @brief Busca recursivamente un factor impar de un número en un rango.
   * @details Esta es una función auxiliar para `is_prime`. Realiza una búsqueda
   * recursiva en el rango de enteros `[low, high)` para encontrar un entero `k`
   * tal que `2*k + 1` es un factor de `n`.
   *
   * @param n El número a factorizar.
   * @param low El límite inferior (inclusivo) del rango de búsqueda para `k`.
   * @param high El límite superior (exclusivo) del rango de búsqueda para `k`.
   * @return Un `std::expected<bool, factor_error>`. Contiene `true` si se encuentra un factor,
   *         `false` si no se encuentra. Contiene un error si los parámetros de entrada son inválidos.
   *
   * @pre `n > high`, `high > low` y `low > 1`.
   *
   * @post Si el valor es `true`, existe un entero `k` con `low <= k < high` tal que `n % (2*k + 1) == 0`.
   * @post Si el valor es `false`, para todo `k` con `low <= k < high`, `n % (2*k + 1) != 0`.
   */
  template <std::integral T>
  constexpr inline
  std::expected<bool, factor_error> find_factor(T n, T low, T high) noexcept {
    if (low <= 1) return std::unexpected(factor_error::domain_error);
    if (n <= high) return std::unexpected(factor_error::domain_error);
    if (high <= low) return false; // Empty range, no factor found.

    const auto mid{std::midpoint(low, high)};
    if (low + 1 >= high) {
        return (n % (2 * low + 1)) == 0;
    }

    auto res_low = find_factor(n, low, mid);
    if (!res_low) return res_low; // propagate error
    if (*res_low) return true; // found

    return find_factor(n, mid, high);
  }
  
  /**
   * @brief Comprueba si un número es primo en tiempo de compilación.
   * @tparam n El número a comprobar.
   * @return true si n es primo, false en caso contrario.
  *
   * @pre `n` debe ser no negativo.
   * @post El valor devuelto `r` satisface `r*r <= n` y `(r+1)*(r+1) > n`.
   *
   * @invariant
   * - La función siempre termina (los naturales tienen una buena ordenación, el mínimo es 1).
   * - Los valores intermedios no causan desbordamiento (serán menores que el que se le pasa).
   * - Para todo `k en [2, ceilsqrt_ct<n>()]`, si `n % k != 0`, entonces `n` no es primo.
   * Se puede comprobar sacando el primer factor `f` y verificando que `n % f != 0`. 
   * - Si `is_prime_ct<n>()` entonces `para todo k en [2, ceilsqrt_ct<n>()], n % k == 0`.
   * Esto se puede testear con números aleatorios una vez sabemos que `is_prime_ct<n>()` es true.
   *
   * @par Properties
   * - Para `n = 0`, no se compila.
   * - Para `n = 1`, no se compila.
   * - Para `n = 2`, el resultado es `true`.
   * - Para `n = 3`, el resultado es `true`.
   * - Para `n = 4`, el resultado es `false`.
   * - Para `n = 5`, el resultado es `true`.
   * - Para `n = 6`, el resultado es `false`.
   * - Para `n = 7`, el resultado es `true`.
   * - Para `n = 8`, el resultado es `false`.
   * - Para `n = 9`, el resultado es `false`.
   * - Para `n = 10`, el resultado es `false`.
   * - Para `n = 11`, el resultado es `true`.
   * - Para `n = 12`, el resultado es `false`.
   * - Para `n = 13`, el resultado es `true`.
   * - Para `n = 14`, el resultado es `false`.
   * - Para `n = 15`, el resultado es `false`.
   * - Para `n = 16`, el resultado es `false`.
   * - Para `n = 17`, el resultado es `true`.
   * - Para `n = 18`, el resultado es `false`.
   * - Para `n = 19`, el resultado es `true`.
   * - Para `n = 20`, el resultado es `false`.
   * - Para `n = 21`, el resultado es `false`.
   * - Para `n = 22`, el resultado es `false`.
   * - Para `n = 23`, el resultado es `true`.
   * - Para `n = 24`, el resultado es `false`.
   * - Para `n = 25`, el resultado es `false`.
   * - Para `n = 36`, el resultado es `false`.
   * - Para `n = std::numeric_limits<std::uint64_t>::max()`, el resultado es `true`.
   * - Hay grandes tablas para probar aleatoriamente.
   *
   * @par Invariants
   * 
   *
   * @par Things that should never happen
   * - La función no debe entrar en un bucle infinito.
   * - Si `n != 2`, entonces no se puede dar que `is_prime_ct<n>() && is_prime_ct<n+1>()`.
   * - La función no debe desbordarse durante los cálculos intermedios si `n` está dentro del rango del tipo `T`.
   *
   * @note
   */
  template <std::uint64_t n>
  consteval
  bool is_prime_ct() noexcept {
    if constexpr (n < 2) return false;
    else if constexpr (n == 2 || n == 3) return true;
    else if constexpr (n % 2 == 0 || n % 3 == 0) return false;
    else if constexpr (n % 5 == 0 || n % 7 == 0 || n % 11 == 0) return false;
    else if constexpr (n % 13 == 0 || n % 17 == 0 || n % 19 == 0 || n % 23 == 0) return false;
    else if constexpr (n % 29 == 0 || n % 31 == 0 || n % 37 == 0 || n % 41 == 0) return false;
    else if constexpr (n % 43 == 0 || n % 47 == 0 || n % 53 == 0 || n % 59 == 0) return false;
    else if constexpr ( n < 3600) return true; 
    else {
      // sabemos que si n es primo es mayor que 3600
      constexpr std::uint64_t high = (ceilsqrt(n) + 1) / 2;
      constexpr std::uint64_t low = 2;
      if constexpr (high <= low) { // if range is invalid or empty
          return true; // No factors to check
      } else {
          return !find_factor_ct<std::uint64_t, n, low, high>();
      }
    }
  }

  /**
   * @brief Comprueba si un número es primo.
   * @param n El número a comprobar.
   * @return true si n es primo, false en caso contrario.
   */
  template <std::integral T>
  constexpr inline
  bool is_prime(T n) noexcept {
    if (n < 2) return false;
    else if (n == 2 || n == 3) return true;
    else if (n % 2 == 0 || n % 3 == 0) return false;
    else if (n % 5 == 0 || n % 7 == 0 || n % 11 == 0) return false;
    else if (n % 13 == 0 || n % 17 == 0 || n % 19 == 0 || n % 23 == 0) return false;
    else if (n % 29 == 0 || n % 31 == 0 || n % 37 == 0 || n % 41 == 0 || n % 43 == 0 ) return false;
    else if (n % 47 == 0 || n % 53 == 0 || n % 59 == 0 || n % 67 == 0 || n % 71 == 0 || n % 73 == 0) return false;
    else if ( n < 3600) return true; 
    else {
      auto result = find_factor(n, static_cast<T>(2), (ceilsqrt(n) + 1) / 2);
      // If find_factor returns an error (e.g. invalid range for small n),
      // it means no odd factors were checked, so the number is prime in this context.
      // value_or(false) means if error, no factor was found.
      return !result.value_or(false);
    }
  }

  /**
   * @brief Calcula el máximo común divisor (MCD) de dos números.
   * Algoritmo de Euclides.
   * @param a El primer número.
   * @param b El segundo número.
   * @return El MCD de a y b.
   */
  constexpr inline
  std::uint64_t gcd(std::uint64_t a, std::uint64_t b) noexcept {
    if (a == 0) return b;
    if (b == 0) return a;
    if (a == 1) return 1;
    if (b == 1) return 1;
    if (a == b) return a;
    while (b != 0) { 
      const auto temp = b; 
      b = a % b; 
      a = temp; 
    }
    return a;
  }

  /**
   * @brief Calcula el mínimo común múltiplo (mcm) de dos números, 
   * sabiendo que `lcm(a,b)*gcd(a,b) == a*b.`
   * @param a El primer número.
   * @param b El segundo número.
   * @return El mcm de a y b.
   */
  constexpr inline
  std::uint64_t lcm(std::uint64_t a, std::uint64_t b) noexcept { 
    return (a == 0 || b == 0) ? 0 : (std::min(a, b) / gcd(a, b)) * std::max(a, b);
  }

  /**
   * @brief Calcula en tiempo de compilación el exponente máximo para una base dada que no desborda un uint64_t.
   * @details El valor se determina a partir de una tabla precalculada de valores.
   * @tparam base La base para la cual calcular el exponente máximo.
   * @return El exponente máximo seguro.
   * @note La tabla de valores fue obtenida con Maxima CAS. Ejemplos:
   * - [2, 63], [3, 40], [10, 19], [16, 15]
   */
  template <std::uint64_t base>
  consteval std::size_t max_exponent_for_base_ct() noexcept {
      if constexpr (base < 2) return std::numeric_limits<std::uint64_t>::max();
      else if constexpr (base == 2) return 63;
      else if constexpr (base == 3) return 40;
      else if constexpr (base == 4) return 31;
      else if constexpr (base == 5) return 27;
      else if constexpr (base == 6) return 24;
      else if constexpr (base == 7) return 22;
      else if constexpr (base == 8) return 21;
      else if constexpr (base == 9) return 20;
      else if constexpr (base == 10) return 19;
      else if constexpr (base == 11) return 18;
      else if constexpr (base >= 12 && base < 14) return 17;
      else if constexpr (base >= 14 && base < 16) return 16;
      else if constexpr (base >= 16 && base < 20) return 15;
      else if constexpr (base >= 20 && base < 24) return 14;
      else if constexpr (base >= 24 && base < 31) return 13;
      else if constexpr (base >= 31 && base < 41) return 12;
      else if constexpr (base >= 41 && base < 57) return 11;
      else if constexpr (base >= 57 && base < 85) return 10;
      else if constexpr (base >= 85 && base < 139) return 9;
      else if constexpr (base >= 139 && base < 256) return 8;
      else if constexpr (base >= 256ull && base < 566ull) return 7;
      else if constexpr (base >= 566ull && base < 1626ull) return 6;
      else if constexpr (base >= 1626ull && base < 7132ull) return 5;
      else if constexpr (base >= 7132ull && base < 65536ull) return 4;
      else if constexpr (base >= 65536ull && base < 2642246ull) return 3;
      else if constexpr (base >= 2642246ull && base < 4294967296ull) return 2;
      else return 1;
  }

  /**
   * @brief Calcula en tiempo de ejecución el exponente máximo para una base dada que no desborda un uint64_t.
   * @param base La base para la cual calcular el exponente máximo.
   * @return El exponente máximo seguro.
   */
  constexpr std::size_t max_exponent_for_base(std::uint64_t base) noexcept {
      if (base < 2) return std::numeric_limits<std::uint64_t>::max();
      else if (base == 2) return 63;
      else if (base == 3) return 40;
      else if (base == 4) return 31;
      else if (base == 5) return 27;
      else if (base == 6) return 24;
      else if (base == 7) return 22;
      else if (base == 8) return 21;
      else if (base == 9) return 20;
      else if (base == 10) return 19;
      else if (base == 11) return 18;
      else if (base >= 12 && base < 14) return 17;
      else if (base >= 14 && base < 16) return 16;
      else if (base >= 16 && base < 20) return 15;
      else if (base >= 20 && base < 24) return 14;
      else if (base >= 24 && base < 31) return 13;
      else if (base >= 31 && base < 41) return 12;
      else if (base >= 41 && base < 57) return 11;
      else if (base >= 57 && base < 85) return 10;
      else if (base >= 85 && base < 139) return 9;
      else if (base >= 139 && base < 256) return 8;
      else if (base >= 256 && base < 566) return 7;
      else if (base >= 566 && base < 1626) return 6;
      else if (base >= 1626 && base < 7132) return 5;
      else if (base >= 7132 && base < 65536) return 4;
      else if (base >= 65536 && base < 2642246) return 3;
      else if (base >= 2642246 && base < 4294967296) return 2;
      else return 1;
  }

  /**
   * @brief Calcula la potencia de un número en tiempo de compilación.
   * @tparam base La base.
   * @tparam exponent El exponente.
   * @return base elevado al exponente.
   */
  template <std::uint64_t base, std::size_t exponent>
    requires (exponent <= max_exponent_for_base_ct<base>())
  consteval
  std::uint64_t int_pow_ct() noexcept {
    if constexpr (exponent == 0) { return 1; }
    else if constexpr (exponent == 1) { return base; }
    else if constexpr (base == 0) { return 0; }
    else if constexpr (base == 1) { return 1; }
    else {
      std::uint64_t result = 1;
      std::uint64_t current_base = base;
      std::uint32_t exp = exponent;
      while (exp > 0) {
        if (exp & 1) { result *= current_base; }
        current_base *= current_base;
        exp >>= 1;
      }
      return result;
    }
  }

  /**
   * @brief Calcula la potencia de un número en tiempo de ejecución.
   * @param base La base.
   * @param exponent El exponente.
   * @return base elevado al exponente, o 0 si ocurre un desbordamiento.
   */
  constexpr inline std::uint64_t int_pow(std::uint64_t base,
                                         std::uint32_t exponent) noexcept {
    if (exponent <= max_exponent_for_base(base)) {
      // safe to compute
      if (exponent == 0) return 1;
      if (exponent == 1) return base;
      if (base == 0) return 0;
      if (base == 1) return 1;
      std::uint64_t result = 1;
      std::uint64_t current_base = base;
      while (exponent > 0) {
        if (exponent & 1) { result *= current_base; }
        current_base *= current_base;
        exponent >>= 1;
      }
      return result;
    } else {
      return 0; // overflow case
    }
  }

  /**
   * @brief Comprueba si un número es un cuadrado perfecto (sobrecarga para uint64_t).
   * @param n El número a comprobar.
   * @return true si n es un cuadrado perfecto, false en caso contrario.
   */
  constexpr inline
  bool is_perfect_square(std::uint64_t n) noexcept {
    if (n == 0 || n == 1) { return true; }
    const auto root = ceilsqrt(n);
    return root * root == n;
  }

  // forward declaration for integer log2 (definition appears below)
  constexpr std::uint64_t int_log2(std::uint64_t n) noexcept;
  // forward declaration for count_digits_base (defined below)
  constexpr std::size_t count_digits_base(std::uint64_t n, std::uint64_t base) noexcept;

  /**
   * @brief Calcula el logaritmo entero en tiempo de compilación.
   * @tparam base La base del logaritmo.
   * @tparam n El número del que se calcula el logaritmo.
   * @return El logaritmo entero de n en base `base`.
   */
  template <std::uint64_t base, std::int64_t n> consteval
  std::int64_t int_log_ct() noexcept {
    if constexpr (n <= 0) {
      return -1; // Not in domain of the function log_base(n)
                 // Domain(log_base) = ]0, +infinity[ = [1, +infinity[
    } else if constexpr (n < base) {
      return 0;
    } else {
      return 1 + int_log_ct<base, n / base>();
    }
  }

  /**
   * @brief Calcula el logaritmo entero en tiempo de ejecución.
   * @param base La base del logaritmo.
   * @param n El número del que se calcula el logaritmo.
   * @return El logaritmo entero de n en base `base`.
   */
  constexpr std::int64_t int_log(std::uint64_t base, std::int64_t n) noexcept {
    if (n <= 0) {
      return -1; // Not in domain of the function log_base(n)
                 // Domain(log_base) = ]0, +infinity[ = [1, +infinity[
    } else if (n < base) {
      return 0;
    } else {
      return 1 + int_log(base, n / base);
    }
  }

  /**
   * @brief Cuenta el número de dígitos de un número en base 10.
   * @param n El número.
   * @return El número de dígitos en base 10.
   */
  constexpr inline
  std::size_t count_digits_base10(std::uint64_t n) noexcept { 
    return count_digits_base(n, 10);
  }

  /**
   * @brief Checks if base^exponent is less than or equal to a limit using exponentiation by squaring.
   * @param b The base.
   * @param exp The exponent.
   * @param limit The limit to check against.
   * @return True if b^exp <= limit, false otherwise. This function is overflow-safe.
   */
  constexpr inline bool pow_leq_limit(std::uint64_t b, std::uint32_t exp, std::uint64_t limit) noexcept {
    if (b == 0) return 0 <= limit;
    if (b == 1) return 1 <= limit;
    
    std::uint64_t result = 1;
    std::uint64_t cur = b;
    std::uint32_t e = exp;

    while (e > 0) {
      if (e & 1u) {
        if (result > limit / cur) return false; // would exceed limit
        result *= cur;
      }
      e >>= 1u;
      if (e > 0) {
        if (cur > std::numeric_limits<std::uint64_t>::max() / cur) {
            // cur * cur would overflow, so the mathematical result is definitely > limit.
            return false;
        }
        cur *= cur;
      }
    }
    return result <= limit;
  }

  /**
   * @brief Cuenta el número de dígitos de un número en una base dada.
   * @param n El número.
   * @param base La base.
   * @return El número de dígitos de n en la base dada.
   */
  constexpr inline
  std::size_t count_digits_base(std::uint64_t n, std::uint64_t base) noexcept { 
    if (base < 2) return 0; // invalid base
    if (n == 0) return 1; // zero has one digit in any base

    // Fast path for base 2 using int_log2
    if (base == 2) {
      return static_cast<std::size_t>(int_log2(n)) + 1u;
    }

    std::uint32_t lo = 0u;
    std::uint32_t hi = 1u;
    while (pow_leq_limit(base, hi, n)) {
      lo = hi;
      hi = hi * 2u;
      if (hi == 0u) break; // overflow guard
    }

    while (lo + 1u < hi) {
      std::uint32_t mid = lo + (hi - lo) / 2u;
      if (pow_leq_limit(base, mid, n)) lo = mid;
      else hi = mid;
    }

    return static_cast<std::size_t>(lo) + 1u;
  }

  // ---- util_functs moved here ----
  template<std::uint64_t>
  consteval std::uint64_t int_pow2ct() noexcept;
  template<std::uint64_t>
  consteval std::uint64_t int_log2ct() noexcept;

  constexpr
  std::uint64_t int_pow2(std::uint64_t) noexcept;
  constexpr
  std::uint64_t int_log2(std::uint64_t) noexcept;

  /**
   * @brief Calcula la potencia de 2 en tiempo de compilación.
   * @tparam n El exponente.
   * @return 2 elevado a n.
   */
  template<std::uint64_t n>
  consteval
  std::uint64_t int_pow2ct() noexcept {
    if constexpr (n == 0) { return 1ull; }
    else if constexpr (n == 1) { return 2ull; }
    else { return (2ull*int_pow2ct<n-1ull>()); }
  }

  /**
   * @brief Calcula la potencia de 2 en tiempo de ejecución.
   * @param n El exponente.
   * @return 2 elevado a n.
   */
  constexpr
  std::uint64_t int_pow2(std::uint64_t n) noexcept {
    if (n == 0) { return 1ull; }
    else if (n == 1) { return 2ull; }
    else { return (2ull*int_pow2(n-1ull)); }
  }

  // Backwards-compatible aliases
  template<std::uint64_t N>
  consteval std::uint64_t pow2ct() noexcept { return int_pow2ct<N>(); }
  constexpr std::uint64_t pow2(std::uint64_t n) noexcept { return int_pow2(n); }

  /**
   * @brief Calcula el logaritmo en base 2 en tiempo de compilación.
   * @tparam n El número.
   * @return El logaritmo entero en base 2 de n.
   */
  template<std::uint64_t n>
    requires (n>0)
  consteval
  std::uint64_t int_log2ct() noexcept {
    return std::bit_width(n) - 1;
  }

  /**
   * @brief Calcula el logaritmo entero en base 2 en tiempo de ejecución.
   * @param n El número.
   * @return El logaritmo entero en base 2 de n.
   */
  constexpr
  std::uint64_t int_log2(std::uint64_t n) noexcept {
    if (n == 0) return 0; // Or handle as an error, though std::bit_width(0) is 0.
    return std::bit_width(n) - 1;
  }

    // Backwards-compatible aliases
    template<std::uint64_t N>
    consteval std::uint64_t log2ct() noexcept { return int_log2ct<N>(); }
    constexpr std::uint64_t log2(std::uint64_t n) noexcept { return int_log2(n); }

    namespace special {
        // NOTE: The following metaprogramming utilities are complex and lack documentation and tests.
        // This section should be reviewed for clarity, purpose, and correctness.

        template <usint_t B, usint_t L>
        consteval inline uint64_t Base_pow_to_Size() noexcept {
            constexpr uint64_t Bc{B};
            if constexpr (L == 0)
                return static_cast<uint64_t>(1);
            else if constexpr (L == 1)
                return static_cast<uint64_t>(Bc);
            else if constexpr (L == 2)
                return static_cast<uint64_t>(Bc * Bc);
            else
                return static_cast<uint64_t>(Bc * Base_pow_to_Size<B, L - 1>());
        }

        template <usint_t Base, usint_t Exp>
        struct pow_B_to_E_t {
            static constexpr uint64_t base = static_cast<uint64_t>(Base);
            static constexpr uint64_t exponent = static_cast<uint64_t>(Exp);
            static constexpr uint64_t value = base * (pow_B_to_E_t<base, exponent - 1>::value);
        };

        template <usint_t Base>
        struct pow_B_to_E_t<Base, 2> {
            static constexpr uint64_t base = static_cast<uint64_t>(Base);
            static constexpr uint64_t exponent = static_cast<uint64_t>(2);
            static constexpr uint64_t value = base * base;
        };

        template <usint_t Base>
        struct pow_B_to_E_t<Base, 1> {
            static constexpr uint64_t base = static_cast<uint64_t>(Base);
            static constexpr uint64_t exponent = static_cast<uint64_t>(1);
            static constexpr uint64_t value = base;
        };

        template <usint_t Base>
        struct pow_B_to_E_t<Base, 0> {
            static constexpr uint64_t base = static_cast<uint64_t>(Base);
            static constexpr uint64_t exponent = static_cast<uint64_t>(0);
            static constexpr uint64_t value = static_cast<uint64_t>(1);
        };

        template <usint_t Base, usint_t Exp>
        constexpr uint64_t Pow_B2L_v = pow_B_to_E_t<Base, Exp>::value;

        template <std::int64_t IntObj_ct, std::int64_t BeginIntObj_ct,
                  std::int64_t EndIntObj_ct, std::int64_t Base,
                  template <std::int64_t, std::int64_t> class Funct_tt>
            requires(
                (BeginIntObj_ct >= EndIntObj_ct) && 
                (IntObj_ct >= BeginIntObj_ct)
            )
        struct tuple_builder_t {
            using type = std::int64_t;
            static constexpr std::int64_t unit = static_cast<std::int64_t>(1);
            static constexpr std::int64_t value{IntObj_ct};
            static constexpr std::int64_t begin_value{BeginIntObj_ct};
            static constexpr std::int64_t end_value{EndIntObj_ct};
            static consteval decltype(auto) build() noexcept { return std::tuple_cat(std::make_tuple(std::make_tuple(value, Funct_tt<Base, value>{}())), tuple_builder_t<value + unit, begin_value, end_value, Base, Funct_tt>::build()); }
        };

        template <std::int64_t BeginIntObj_ct, std::int64_t EndIntObj_ct,
                  std::int64_t Base,
                  template <std::int64_t, std::int64_t> class Funct_tt>
        struct tuple_builder_t<EndIntObj_ct - 1, BeginIntObj_ct, EndIntObj_ct, Base, Funct_tt> {
            using type = std::int64_t;
            static constexpr std::int64_t unit = static_cast<std::int64_t>(1);
            static constexpr std::int64_t value{EndIntObj_ct - unit};
            static constexpr std::int64_t begin_value{BeginIntObj_ct};
            static constexpr std::int64_t end_value{EndIntObj_ct};
            static consteval decltype(auto) build() noexcept { return std::make_tuple(std::make_tuple(value, Funct_tt<Base, value>{}())); }
        };

        template <std::int64_t BeginIntObj_ct, std::int64_t EndIntObj_ct,
                  std::int64_t Base,
                  template <std::int64_t, std::int64_t> class Funct_tt>
            requires(BeginIntObj_ct <= EndIntObj_ct)
        struct tuple_builder_t<BeginIntObj_ct, BeginIntObj_ct, EndIntObj_ct, Base, Funct_tt> {
            using type = std::int64_t;
            static constexpr type unit = 1;
            static constexpr type value{BeginIntObj_ct};
            static constexpr type begin_value{BeginIntObj_ct};
            static constexpr type end_value{EndIntObj_ct};
            static consteval decltype(auto) build() noexcept { 
                return std::tuple_cat(
                    std::make_tuple(
                        std::make_tuple(
                            value, 
                            Funct_tt<Base, value>{}()
                        )
                    ), 
                    tuple_builder_t<
                        begin_value + unit, 
                        begin_value, 
                        end_value, 
                        Base, 
                        Funct_tt
                    >::build()
                ); 
            }
        };

        template <std::int64_t BeginIntObj_ct, std::int64_t EndIntObj_ct,
                  std::int64_t Base,
                  template <std::int64_t, std::int64_t> class Funct_tt>
            requires(BeginIntObj_ct < EndIntObj_ct)
        struct tuple_user_constructor_t {
            static constexpr auto value {
                tuple_builder_t<
                    BeginIntObj_ct, 
                    BeginIntObj_ct, 
                    EndIntObj_ct, 
                    Base, 
                    Funct_tt
                >::build()
            };
        };

        template <std::int64_t BeginIntObj_ct, std::int64_t EndIntObj_ct,
                  std::int64_t Base,
                  template <std::int64_t, std::int64_t> class Funct_tt>
            requires(BeginIntObj_ct < EndIntObj_ct)
        constexpr auto tuple_constr_v = 
            tuple_user_constructor_t<
                BeginIntObj_ct, 
                EndIntObj_ct, 
                Base, 
                Funct_tt
            >::build();

        template <auto B, auto L, typename A>
        constexpr inline uint64_t conversion_to_int(const A &arg) noexcept {
            constexpr uint64_t base{static_cast<uint64_t>(B)};
            uint64_t acc{arg[L - 1]()};
            for (sint64_t ix{L - 2}; ix > -1; --ix) {
                acc *= base;
                acc += static_cast<uint64_t>(arg[ix]());
            };
            return acc;
        }

    } /// CLOSE NAMESPACE special
  } // CLOSE NAMESPACE auxiliary_functions
} // CLOSE NAMESPACE NumRepr

#endif // AUXILIARY_FUNCTIONS_HPP_INCLUDED