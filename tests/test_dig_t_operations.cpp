#include <iostream>
#include "../include/dig_t.hpp"

int main()
{
    std::cout << "=== Test de operaciones dig_t ===" << std::endl;

    try
    {
        std::cout << "1. Creando dig_t<10> con valores 5 y 3..." << std::endl;
        NumRepr::dig_t<10> d1(5u);
        NumRepr::dig_t<10> d2(3u);

        std::cout << "   d1 = " << static_cast<int>(d1.get()) << std::endl;
        std::cout << "   d2 = " << static_cast<int>(d2.get()) << std::endl;

        std::cout << "2. Probando suma..." << std::endl;
        auto sum = d1 + d2;

        std::cout << "   d1 + d2 = " << static_cast<int>(sum.get()) << std::endl;
        std::cout << "   (esperado: 8)" << std::endl;

        std::cout << "3. Probando suma con overflow..." << std::endl;
        NumRepr::dig_t<10> d3(7u);
        NumRepr::dig_t<10> d4(8u);
        auto overflow_sum = d3 + d4;

        std::cout << "   7 + 8 = " << static_cast<int>(overflow_sum.get()) << std::endl;
        std::cout << "   (esperado: 5, ya que 15 mod 10 = 5)" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cout << "Error desconocido" << std::endl;
        return 1;
    }

    std::cout << "Test completado exitosamente!" << std::endl;
    return 0;
}