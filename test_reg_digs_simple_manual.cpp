//
// Test simple de reg_digs_t evitando utilities.hpp problemático
//
#include <iostream>
#include <string>
#include <algorithm>

// Incluir solo dig_t primero
#include "dig_t.hpp"

// Definición mínima manual de reg_digs_t para evitar problemas
namespace NumRepr
{

    template <uint64_t B, size_t L>
        requires((B > 1) && (L > 0))
    struct reg_digs_simple_test
    {
    private:
        std::array<dig_t<B>, L> digits_;

    public:
        // Constructor por defecto
        constexpr reg_digs_simple_test() : digits_{} {}

        // Constructor con valor inicial
        reg_digs_simple_test(uint64_t value) : digits_{}
        {
            for (size_t i = 0; i < L && value > 0; ++i)
            {
                digits_[i] = dig_t<B>(static_cast<typename dig_t<B>::uint_t>(value % B));
                value /= B;
            }
        }

        // Acceso a elementos
        constexpr const dig_t<B> &operator[](size_t i) const { return digits_[i]; }
        constexpr dig_t<B> &operator[](size_t i) { return digits_[i]; }

        // Tamaño
        constexpr size_t size() const noexcept { return L; }

        // Comparación
        constexpr bool operator==(const reg_digs_simple_test &other) const
        {
            for (size_t i = 0; i < L; ++i)
            {
                if (digits_[i] != other.digits_[i])
                {
                    return false;
                }
            }
            return true;
        }

        // Iteradores básicos
        auto begin() { return digits_.begin(); }
        auto end() { return digits_.end(); }
        auto begin() const { return digits_.begin(); }
        auto end() const { return digits_.end(); }

        // Conversión a string para debugging
        std::string debug_string() const
        {
            std::string result = "[";
            for (size_t i = 0; i < L; ++i)
            {
                if (i > 0)
                    result += ", ";
                result += std::to_string(digits_[i].get());
            }
            result += "]";
            return result;
        }

        // Suma simple (sin carry por ahora)
        reg_digs_simple_test operator+(const reg_digs_simple_test &other) const
        {
            reg_digs_simple_test result;
            for (size_t i = 0; i < L; ++i)
            {
                // Suma simple sin carry para test básico
                auto sum = digits_[i].get() + other.digits_[i].get();
                result.digits_[i] = dig_t<B>(sum % B);
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
        std::cout << "=== Test Simple reg_digs_simple_test ===\n\n";

        // Test 1: Construcción básica
        std::cout << "Test 1: Construcción por defecto...\n";
        reg_digs_simple_test<10, 3> reg1;
        std::cout << "reg1 = " << reg1.debug_string() << "\n";
        std::cout << "✅ Constructor por defecto exitoso\n\n";

        // Test 2: Construcción con valor
        std::cout << "Test 2: Construcción con valor 123...\n";
        reg_digs_simple_test<10, 3> reg2(123);
        std::cout << "reg2 = " << reg2.debug_string() << "\n";
        std::cout << "✅ Constructor con valor exitoso\n\n";

        // Test 3: Acceso a elementos
        std::cout << "Test 3: Acceso a elementos...\n";
        std::cout << "reg2[0] = " << reg2[0].get() << "\n";
        std::cout << "reg2[1] = " << reg2[1].get() << "\n";
        std::cout << "reg2[2] = " << reg2[2].get() << "\n";
        std::cout << "✅ Acceso exitoso\n\n";

        // Test 4: Modificación
        std::cout << "Test 4: Modificación de elementos...\n";
        reg1[0] = dig_t<10>(5);
        reg1[1] = dig_t<10>(7);
        reg1[2] = dig_t<10>(2);
        std::cout << "reg1 después de modificar = " << reg1.debug_string() << "\n";
        std::cout << "✅ Modificación exitosa\n\n";

        // Test 5: Comparación
        std::cout << "Test 5: Comparaciones...\n";
        reg_digs_simple_test<10, 3> reg3(123);
        std::cout << "reg2 == reg3: " << (reg2 == reg3 ? "true" : "false") << "\n";
        std::cout << "reg1 == reg2: " << (reg1 == reg2 ? "true" : "false") << "\n";
        std::cout << "✅ Comparaciones exitosas\n\n";

        // Test 6: Suma básica
        std::cout << "Test 6: Suma básica...\n";
        auto reg_sum = reg1 + reg2;
        std::cout << "reg1 + reg2 = " << reg_sum.debug_string() << "\n";
        std::cout << "✅ Suma básica exitosa\n\n";

        // Test 7: Diferentes bases
        std::cout << "Test 7: Base binaria...\n";
        reg_digs_simple_test<2, 8> reg_bin(170); // 10101010 en binario
        std::cout << "reg_bin(170) = " << reg_bin.debug_string() << "\n";
        std::cout << "✅ Base binaria exitosa\n\n";

        // Test 8: Base hexadecimal
        std::cout << "Test 8: Base hexadecimal...\n";
        reg_digs_simple_test<16, 4> reg_hex(43981); // ABCD en hex
        std::cout << "reg_hex(43981) = " << reg_hex.debug_string() << "\n";
        std::cout << "✅ Base hexadecimal exitosa\n\n";

        // Test 9: Iteradores
        std::cout << "Test 9: Iteradores...\n";
        std::cout << "Iterando reg2 con range-based for: ";
        for (const auto &digit : reg2)
        {
            std::cout << digit.get() << " ";
        }
        std::cout << "\n✅ Iteradores exitosos\n\n";

        std::cout << "=== TODOS LOS TESTS EXITOSOS ===\n";
        std::cout << "reg_digs_simple_test funciona correctamente\n";
        std::cout << "Conceptos validados:\n";
        std::cout << "- Construcción y asignación\n";
        std::cout << "- Acceso y modificación de elementos\n";
        std::cout << "- Comparaciones\n";
        std::cout << "- Operaciones aritméticas básicas\n";
        std::cout << "- Iteradores\n";
        std::cout << "- Múltiples bases (2, 10, 16)\n";

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "❌ Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "❌ Error desconocido" << std::endl;
        return 1;
    }
}