#include <iostream>
#include "core/dig_t.hpp"
#include "base_num_t.hpp"
#include "nat_num_t.hpp"
#include "int_num_t.hpp"

int main() {
    std::cout << "Probando NumericRepresentations C++23..." << std::endl;
    
    // Test dig_t
    constexpr std::uint64_t BASE = 10;
    using dig = NumRepr::dig_t<BASE>;
    
    dig d1{5};
    dig d2{3};
    dig result = d1 + d2;
    
    std::cout << "dig_t<10>: " << d1() << " + " << d2() << " = " << result() << std::endl;
    
    // Test nat_num_t
    using nat_num = NumRepr::nat_num_t<BASE>;
    
    nat_num n1{42};
    nat_num n2{58};
    nat_num n3 = n1 + n2;
    
    std::cout << "nat_num_t<10>: 42 + 58 = " << n3.to_string() << std::endl;
    
    // Test int_num_t
    using int_num = NumRepr::int_num_t<BASE>;
    
    int_num i1{-15};
    int_num i2{25};
    int_num i3 = i1 + i2;
    
    std::cout << "int_num_t<10>: -15 + 25 = " << i3.to_string() << std::endl;
    
    std::cout << "¡Todas las pruebas compilaron correctamente!" << std::endl;
    
    return 0;
}