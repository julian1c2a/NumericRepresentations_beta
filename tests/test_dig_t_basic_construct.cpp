#include <iostream>
#include <core/dig_t.hpp>

int main()
{
    std::cout << "=== Test de construcción básica dig_t ===" << std::endl;

    try
    {
        std::cout << "1. Creando dig_t<10>..." << std::endl;
        NumRepr::dig_t<10> d1(5u);
        std::cout << "   ✅ dig_t<10>(5) creado exitosamente" << std::endl;

        std::cout << "2. Obteniendo valor..." << std::endl;
        auto valor = d1.get();
        std::cout << "   ✅ Valor obtenido: " << valor << std::endl;

        std::cout << "3. Creando segundo dig_t..." << std::endl;
        NumRepr::dig_t<10> d2(3u);
        std::cout << "   ✅ dig_t<10>(3) creado exitosamente" << std::endl;

        std::cout << "4. Finalizando test..." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "❌ Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cout << "❌ Error desconocido" << std::endl;
        return 1;
    }

    std::cout << "✅ Test completado exitosamente" << std::endl;
    return 0;
}