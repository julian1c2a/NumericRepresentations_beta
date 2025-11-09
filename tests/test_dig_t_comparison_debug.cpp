#include <iostream>
#include "../include/dig_t.hpp"

int main()
{
    std::cout << "=== Debug de operadores de comparacion ===" << std::endl;

    try
    {
        NumRepr::dig_t<5> d(3u);
        NumRepr::dig_t<5> e(8u); // 8 % 5 = 3, igual que d!

        std::cout << "d(3u) = " << static_cast<int>(d.get()) << std::endl;
        std::cout << "e(8u) = " << static_cast<int>(e.get()) << " (8 % 5)" << std::endl;

        std::cout << "d == e: " << (d == e) << std::endl;
        std::cout << "d < e: " << (d < e) << std::endl;
        std::cout << "d > e: " << (d > e) << std::endl;

        // Probemos con valores diferentes
        NumRepr::dig_t<5> f(1u);
        NumRepr::dig_t<5> g(4u);

        std::cout << "\nf(1u) = " << static_cast<int>(f.get()) << std::endl;
        std::cout << "g(4u) = " << static_cast<int>(g.get()) << std::endl;

        std::cout << "f == g: " << (f == g) << std::endl;
        std::cout << "f < g: " << (f < g) << std::endl;
        std::cout << "f > g: " << (f > g) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Debug completado" << std::endl;
    return 0;
}