#include <functional>
#include <string>

#include "testing_framework.hpp"

static bool all_tests_executed{false};

Test::Test(std::string test_name, std::string test_case_name, std::function<void(Test *)> test_function)
: test_name_{std::move(test_name)}, test_case_name_{std::move(test_case_name)}, test_function_{std::move(test_function)}
{
    tests.push_back(this);
}

void Test::execute()
{
    test_function_(this);
}

int main()
{
    for (const auto & test : tests)
    {
        test->execute();
    }

    all_tests_executed = true;

    while (true)
        ;
}