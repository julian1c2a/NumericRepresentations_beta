#include <iostream>

enum class test_enum : int
{
    value1 = 1,
    value2 = 2
};

int main()
{
    std::cout << "Basic test compilation works!" << std::endl;
    std::cout << "test_enum::value1 = " << static_cast<int>(test_enum::value1) << std::endl;
    return 0;
}