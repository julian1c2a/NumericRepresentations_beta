#include "include/nat_reg_digs_t.hpp"
#include <iostream>

using namespace NumRepr;

int main()
{
    std::cout << "=== TEST MÍNIMO - Factory Methods de reg_digs_t ===" << std::endl;

    // Primero probar los factory de la clase base
    try
    {
        std::cout << "\nProbando reg_digs_t<2,4>::regd_0()..." << std::endl;
        constexpr auto reg_base_0 = reg_digs_t<2, 4>::regd_0();
        std::cout << "✅ reg_digs_t::regd_0() funciona" << std::endl;

        std::cout << "\nProbando reg_digs_t<2,4>::regd_1()..." << std::endl;
        constexpr auto reg_base_1 = reg_digs_t<2, 4>::regd_1();
        std::cout << "✅ reg_digs_t::regd_1() funciona" << std::endl;
    }
    catch (...)
    {
        std::cout << "❌ Error en factory methods de reg_digs_t" << std::endl;
        return 1;
    }

    // Luego probar constructor de movimiento de nat_reg_digs_t
    try
    {
        std::cout << "\nProbando constructor nat_reg_digs_t desde reg_digs_t..." << std::endl;
        auto reg_temp = reg_digs_t<2, 4>::regd_0();
        nat_reg_digs_t<2, 4> nat_from_move{std::move(reg_temp)};
        std::cout << "✅ Constructor movimiento funciona" << std::endl;
    }
    catch (...)
    {
        std::cout << "❌ Error en constructor de movimiento" << std::endl;
        return 1;
    }

    std::cout << "\n🎯 TODOS LOS COMPONENTES BASE FUNCIONAN" << std::endl;
    return 0;
}