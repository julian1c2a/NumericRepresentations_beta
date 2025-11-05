/**
 * @file test_pack2array.cpp
 * @brief Test simplificado para pack2array de utilities.hpp
 */

#include <array>
#include <iostream>

// Definiciones simplificadas del tipo básico
namespace numeric_representations_ns
{
    template <unsigned Base>
    class dig_t
    {
    public:
        constexpr dig_t(unsigned v = 0) : value(v) {}
        constexpr operator unsigned() const { return value; }

    private:
        unsigned value;
    };
}

using dig_t = numeric_representations_ns::dig_t<10>;

// Test simplificado para MSVC de pack2array
namespace utilities
{
    template <class... Ts>
    constexpr bool all_are_the_same_type_c = (std::is_same_v<Ts, Ts> && ...);

    template <class... Ts>
    constexpr bool there_is_one_or_more_c = (sizeof...(Ts) > 0);

    namespace ugly_pack_details
    {
        template <typename... Ts>
            requires(all_are_the_same_type_c<Ts...> && there_is_one_or_more_c<Ts...>)
        struct pack2array
        {
            static constexpr std::size_t size = sizeof...(Ts);
            using inner_type = std::common_type_t<Ts...>;
            using array_type = std::array<inner_type, size>;

            // Versión más simple para MSVC
            constexpr array_type operator()(Ts... args) const noexcept
            {
                return array_type{args...};
            }

            using elem_type = inner_type;
        };
    }
}

int main()
{
    std::cout << "Testeo pack2array con dig_t...\n";

    constexpr dig_t d1{1}, d2{2}, d3{3};

    // Test 1: Crear pack2array functor
    constexpr auto packer = utilities::ugly_pack_details::pack2array<dig_t, dig_t, dig_t>{};

    // Test 2: Usar el functor para crear array
    constexpr auto array_result = packer(d1, d2, d3);

    std::cout << "Array creado: ";
    for (size_t i = 0; i < array_result.size(); ++i)
    {
        std::cout << static_cast<unsigned>(array_result[i]) << " ";
    }
    std::cout << std::endl;

    std::cout << "Test pack2array completado exitosamente!\n";
    return 0;
}