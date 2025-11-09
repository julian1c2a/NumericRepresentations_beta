#include "include/nat_reg_digs_t.hpp"
#include <iostream>

using namespace NumRepr;
using Binary4 = nat_reg_digs_t<2, 4>;

int main()
{
    std::cout << "Test constructores paso a paso" << std::endl;

    std::cout << "\n1. Constructor por defecto:" << std::endl;
    Binary4 bin_default;
    std::cout << "✅ Constructor por defecto: " << bin_default.to_string() << std::endl;

    std::cout << "\n2. Constructor copia:" << std::endl;
    try
    {
        Binary4 original = Binary4::regd_1();
        Binary4 copia(original);
        std::cout << "✅ Constructor copia: " << copia.to_string() << std::endl;
    }
    catch (...)
    {
        std::cout << "❌ Error en constructor copia" << std::endl;
    }

    return 0;
}