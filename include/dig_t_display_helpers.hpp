/**
 * @file dig_t_display_helpers.hpp
 * @brief Funciones helper para visualización correcta de dig_t
 *
 * Resuelve el problema de uint8_t siendo interpretado como carácter ASCII
 * en lugar de número cuando se usa con std::cout.
 */

#ifndef DIG_T_DISPLAY_HELPERS_HPP
#define DIG_T_DISPLAY_HELPERS_HPP

#include <iostream>
#include <type_traits>
#include "dig_t.hpp"

namespace NumRepr
{
    namespace display_helpers
    {

        /**
         * @brief Helper para visualizar dig_t correctamente independiente del tipo interno
         * @tparam Base Base del sistema numérico
         * @param digit Dígito a mostrar
         * @return Valor convertido apropiadamente para std::cout
         *
         * @details
         * Automáticamente convierte uint8_t a int para evitar interpretación como ASCII.
         * Para otros tipos (uint16_t, uint32_t, etc.) retorna el valor directamente.
         *
         * @example
         * ```cpp
         * dig_t<10> d{5};
         * std::cout << display(d);  // Siempre muestra "5", nunca carácter ASCII
         * ```
         */
        template <unsigned Base>
        constexpr auto display(const dig_t<Base> &digit) noexcept
        {
            using uint_t = typename dig_t<Base>::uint_t;

            if constexpr (std::is_same_v<uint_t, uint8_t>)
            {
                // Convertir uint8_t a int para visualización correcta
                return static_cast<int>(digit.get());
            }
            else
            {
                // Otros tipos se muestran correctamente sin conversión
                return digit.get();
            }
        }

        /**
         * @brief Operador de inserción mejorado para dig_t
         * @tparam Base Base del sistema numérico
         * @param os Stream de salida
         * @param digit Dígito a mostrar
         * @return Referencia al stream para encadenamiento
         *
         * @details
         * Permite usar dig_t directamente con std::cout sin preocuparse por uint8_t.
         * Automáticamente aplica la conversión apropiada.
         *
         * @example
         * ```cpp
         * dig_t<10> d{7};
         * std::cout << d;  // Funciona correctamente, muestra "7"
         * ```
         */
        template <unsigned Base>
        std::ostream &operator<<(std::ostream &os, const dig_t<Base> &digit)
        {
            return os << display(digit);
        }

        /**
         * @brief Helper para mostrar información de tipo interno
         * @tparam Base Base del sistema numérico
         * @return Nombre del tipo interno como string
         */
        template <unsigned Base>
        constexpr const char *type_name() noexcept
        {
            using uint_t = typename dig_t<Base>::uint_t;

            if constexpr (std::is_same_v<uint_t, uint8_t>)
            {
                return "uint8_t";
            }
            else if constexpr (std::is_same_v<uint_t, uint16_t>)
            {
                return "uint16_t";
            }
            else if constexpr (std::is_same_v<uint_t, uint32_t>)
            {
                return "uint32_t";
            }
            else if constexpr (std::is_same_v<uint_t, uint64_t>)
            {
                return "uint64_t";
            }
            else
            {
                return "unknown";
            }
        }

    } // namespace display_helpers

    // Importar funciones al namespace principal para facilidad de uso
    using display_helpers::display;
    using display_helpers::type_name;

} // namespace NumRepr

#endif // DIG_T_DISPLAY_HELPERS_HPP