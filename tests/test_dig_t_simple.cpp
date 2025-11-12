#include <iostream>
#include <cassert>
#include "core/dig_t.hpp"

using namespace NumRepr;

int main()
{
    std::cout << "=== Testing dig_t.hpp (Basic Functionality) ===\n";

    try
    {
        // Test 1: Basic construction and value access
        std::cout << "Test 1: Basic construction...\n";
        dig_t<10> d1; // Default constructor
        assert(d1.get() == 0);

        dig_t<10> d2(5); // Constructor with value
        assert(d2.get() == 5);

        dig_t<10> d3(15);      // Constructor with modular value
        assert(d3.get() == 5); // 15 % 10 = 5

        std::cout << "✓ Basic construction tests passed\n";

        // Test 2: Different bases
        std::cout << "Test 2: Different bases...\n";
        dig_t<2> bin(1);
        assert(bin.get() == 1);

        dig_t<16> hex(15);
        assert(hex.get() == 15);

        dig_t<100> big(99);
        assert(big.get() == 99);

        std::cout << "✓ Different bases tests passed\n";

        // Test 3: Static constants
        std::cout << "Test 3: Static constants...\n";
        constexpr auto max_val = dig_t<10>::ui_max();
        constexpr auto zero_val = dig_t<10>::ui_0();
        constexpr auto one_val = dig_t<10>::ui_1();

        assert(max_val == 9); // B - 1 = 10 - 1 = 9
        assert(zero_val == 0);
        assert(one_val == 1);

        std::cout << "✓ Static constants tests passed\n";

        // Test 4: Type conversions
        std::cout << "Test 4: Type conversions...\n";
        dig_t<10> d(7);

        // Test conversion to uint_t
        auto uint_val = static_cast<typename dig_t<10>::uint_t>(d);
        assert(uint_val == 7);

        // Test get() method
        assert(d.get() == 7);

        // Test operator()
        assert(d() == 7);

        std::cout << "✓ Type conversion tests passed\n";

        // Test 5: Copy and assignment
        std::cout << "Test 5: Copy and assignment...\n";
        dig_t<10> original(8);
        dig_t<10> copy = original; // Copy constructor
        assert(copy.get() == 8);

        dig_t<10> assigned(0);
        assigned = original; // Assignment operator
        assert(assigned.get() == 8);

        std::cout << "✓ Copy and assignment tests passed\n";

        // Test 6: Modular behavior
        std::cout << "Test 6: Modular behavior...\n";
        dig_t<5> mod_test1(7); // 7 % 5 = 2
        assert(mod_test1.get() == 2);

        dig_t<3> mod_test2(10); // 10 % 3 = 1
        assert(mod_test2.get() == 1);

        std::cout << "✓ Modular behavior tests passed\n";

        std::cout << "\n✅ All dig_t.hpp basic tests PASSED!\n";
        std::cout << "Headers are ready for production use.\n";

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cout << "\n❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cout << "\n❌ Test failed with unknown exception\n";
        return 1;
    }
}