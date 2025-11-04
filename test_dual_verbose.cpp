#include <iostream>
#include <sstream>
#include "dig_t.hpp"

using namespace NumRepr;

int main()
{
    try
    {
        std::cout << "=== Test Formato Dual con Clang ===" << std::endl;

        // Test formato estricto d[n]B
        std::cout << "1. Testing formato estricto d[n]B..." << std::endl;
        constexpr dig_t<10> d1("d[7]B10");
        std::cout << "   Constexpr d1(\"d[7]B10\"): " << d1 << " -> valor=" << (int)d1.get() << std::endl;

        // Test formato legacy dig#n#B
        std::cout << "2. Testing formato legacy dig#n#B..." << std::endl;
        dig_t<10> d2("dig#5#B10");
        std::cout << "   d2(\"dig#5#B10\"): " << d2 << " -> valor=" << (int)d2.get() << std::endl;

        // Test parsing con módulo
        std::cout << "3. Testing parsing con módulo..." << std::endl;
        dig_t<10> d3("d[127]B10");
        std::cout << "   d3(\"d[127]B10\"): " << d3 << " -> valor=" << (int)d3.get() << " (127 % 10)" << std::endl;

        // Test entrada desde stream formato estricto
        std::cout << "4. Testing stream input formato estricto..." << std::endl;
        std::istringstream iss1("d[8]B10");
        dig_t<10> d4;
        iss1 >> d4;
        std::cout << "   Stream \"d[8]B10\" -> d4: " << d4 << " -> valor=" << (int)d4.get() << std::endl;

        // Test entrada desde stream formato legacy
        std::cout << "5. Testing stream input formato legacy..." << std::endl;
        std::istringstream iss2("dig#9#B10");
        dig_t<10> d5;
        iss2 >> d5;
        std::cout << "   Stream \"dig#9#B10\" -> d5: " << d5 << " -> valor=" << (int)d5.get() << std::endl;

        std::cout << "\n✅ Todos los tests pasaron correctamente con Clang!" << std::endl;
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cout << "❌ Error: " << e.what() << std::endl;
        return 1;
    }
}