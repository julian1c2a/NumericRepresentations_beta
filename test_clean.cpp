#include <iostream>
#include <array>

int main()
{
    std::cout << "Test basico sin dig_t" << std::endl;

    std::array<int, 3> arr = {1, 2, 3};

    for (size_t i = 0; i < 3; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}