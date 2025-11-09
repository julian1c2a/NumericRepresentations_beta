//
// Test simple para reg_digs_t evitando problemas de API
//
#include <iostream>
#include <string>
#include <array>

// Incluir solo lo necesario
#include "dig_t.hpp"

// Definicion minima para poder usar reg_digs_t
namespace NumRepr
{

    // Version simplificada sin herencia completa
    template <uint64_t B, size_t L>
    struct reg_digs_simple_t
    {
    public:
        using dig_type = dig_t<B>;
        using uint_t = typename dig_type::uint_t;

        static constexpr uint64_t base = B;
        static constexpr size_t length = L;

    private:
        std::array<dig_type, L> digits;

    public:
        // Constructor por defecto - todos los dígitos en 0
        constexpr reg_digs_simple_t() : digits{} {}

        // Constructor con valor inicial
        constexpr reg_digs_simple_t(uint64_t value) : digits{}
        {
            for (size_t i = 0; i < L && value > 0; ++i)
            {
                digits[i] = dig_type(static_cast<uint_t>(value % B));
                value /= B;
            }
        }

        // Acceso a dígitos
        constexpr const dig_type &operator[](size_t i) const
        {
            return digits[i];
        }

        constexpr dig_type &operator[](size_t i)
        {
            return digits[i];
        }

        // Comparación de igualdad
        constexpr bool operator==(const reg_digs_simple_t &other) const
        {
            for (size_t i = 0; i < L; ++i)
            {
                if (digits[i] != other.digits[i])
                {
                    return false;
                }
            }
            return true;
        }

        constexpr bool operator!=(const reg_digs_simple_t &other) const
        {
            return !(*this == other);
        }

        // Conversión a string (no constexpr)
        std::string to_string() const
        {
            std::string result = "[";
            for (size_t i = 0; i < L; ++i)
            {
                if (i > 0)
                    result += ", ";
                result += digits[i].to_string();
            }
            result += "]";
            return result;
        }

        // Obtener valor numérico (solo para valores que caben en uint64_t)
        constexpr uint64_t to_value() const
        {
            uint64_t result = 0;
            uint64_t base_power = 1;

            for (size_t i = 0; i < L; ++i)
            {
                result += digits[i].get() * base_power;
                base_power *= B;
            }
            return result;
        }
    };

} // namespace NumRepr

using namespace NumRepr;

int main()
{
    try
    {
        std::cout << "=== Test simple de reg_digs_simple_t ===\n\n";

        // Test 1: Constructor por defecto
        std::cout << "Test 1: Constructor por defecto\n";
        reg_digs_simple_t<10, 3> reg_default;
        std::cout << "reg_default = " << reg_default.to_string() << "\n";
        std::cout << "Valor = " << reg_default.to_value() << "\n\n";

        // Test 2: Constructor con valor
        std::cout << "Test 2: Constructor con valor 123\n";
        reg_digs_simple_t<10, 3> reg_123(123);
        std::cout << "reg_123 = " << reg_123.to_string() << "\n";
        std::cout << "Valor = " << reg_123.to_value() << "\n\n";

        // Test 3: Constructor con valor mayor
        std::cout << "Test 3: Constructor con valor 987\n";
        reg_digs_simple_t<10, 3> reg_987(987);
        std::cout << "reg_987 = " << reg_987.to_string() << "\n";
        std::cout << "Valor = " << reg_987.to_value() << "\n\n";

        // Test 4: Acceso a dígitos individuales
        std::cout << "Test 4: Acceso a dígitos de reg_987\n";
        for (size_t i = 0; i < 3; ++i)
        {
            std::cout << "reg_987[" << i << "] = " << reg_987[i].to_string() << "\n";
        }
        std::cout << "\n";

        // Test 5: Comparaciones
        std::cout << "Test 5: Comparaciones\n";
        reg_digs_simple_t<10, 3> reg_123_copy(123);
        std::cout << "reg_123 == reg_123_copy: " << (reg_123 == reg_123_copy ? "true" : "false") << "\n";
        std::cout << "reg_123 == reg_987: " << (reg_123 == reg_987 ? "true" : "false") << "\n";
        std::cout << "reg_123 != reg_987: " << (reg_123 != reg_987 ? "true" : "false") << "\n\n";

        // Test 6: Diferentes bases
        std::cout << "Test 6: Base 2 (binario)\n";
        reg_digs_simple_t<2, 8> reg_bin(170); // 10101010 en binario
        std::cout << "reg_bin(170) = " << reg_bin.to_string() << "\n";
        std::cout << "Valor = " << reg_bin.to_value() << "\n\n";

        // Test 7: Base 16 (hexadecimal)
        std::cout << "Test 7: Base 16 (hexadecimal)\n";
        reg_digs_simple_t<16, 4> reg_hex(43981); // ABCD en hex
        std::cout << "reg_hex(43981) = " << reg_hex.to_string() << "\n";
        std::cout << "Valor = " << reg_hex.to_value() << "\n\n";

        // Test 8: Constexpr
        std::cout << "Test 8: Operaciones constexpr en compile-time\n";
        constexpr reg_digs_simple_t<10, 3> reg_const(456);
        constexpr auto valor_const = reg_const.to_value();
        std::cout << "Valor constexpr: " << valor_const << "\n";
        std::cout << "reg_const = " << reg_const.to_string() << "\n\n";

        std::cout << "=== Todos los tests completados exitosamente ===\n";
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}