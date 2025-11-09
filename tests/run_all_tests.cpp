#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

// Forward declarations for test functions
extern int test_auxiliary_types_main();
extern int test_auxiliary_functions_main();
extern int test_basic_types_main();
extern int test_dig_t_main();

struct TestSuite
{
    std::string name;
    int (*test_func)();
};

int main()
{
    std::cout << "========================================\n";
    std::cout << " NumericRepresentations - Header Tests\n";
    std::cout << "========================================\n\n";

    std::vector<TestSuite> tests = {
        {"auxiliary_types.hpp", nullptr},
        {"auxiliary_functions.hpp", nullptr},
        {"basic_types.hpp", nullptr},
        {"dig_t.hpp", nullptr}};

    int total_tests = 0;
    int passed_tests = 0;

    std::cout << "Running individual test executables...\n\n";

    for (const auto &test : tests)
    {
        total_tests++;
        std::cout << "Running tests for " << test.name << "...\n";

        // Create test executable name
        std::string test_name = test.name;
        size_t dot_pos = test_name.find('.');
        if (dot_pos != std::string::npos)
        {
            test_name = test_name.substr(0, dot_pos);
        }

        std::string exe_name = "test_" + test_name + ".exe";

        // Run the test executable
        int result = std::system(exe_name.c_str());

        if (result == 0)
        {
            std::cout << "✅ " << test.name << " tests PASSED\n";
            passed_tests++;
        }
        else
        {
            std::cout << "❌ " << test.name << " tests FAILED (exit code: " << result << ")\n";
        }
        std::cout << std::endl;
    }

    std::cout << "========================================\n";
    std::cout << " Test Summary\n";
    std::cout << "========================================\n";
    std::cout << "Total test suites: " << total_tests << "\n";
    std::cout << "Passed: " << passed_tests << "\n";
    std::cout << "Failed: " << (total_tests - passed_tests) << "\n";

    if (passed_tests == total_tests)
    {
        std::cout << "\n🎉 ALL TESTS PASSED! 🎉\n";
        return 0;
    }
    else
    {
        std::cout << "\n💥 Some tests failed. Check output above.\n";
        return 1;
    }
}