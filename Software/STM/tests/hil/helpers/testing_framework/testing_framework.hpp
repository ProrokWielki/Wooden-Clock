#pragma once

#include <functional>
#include <string>
#include <utility>
#include <vector>

#define RegisterTest(Name, CaseName, TestBody) Test Name##CaseName{#Name, #CaseName, TestBody};

#define EXPECT_EQ(lhs, rhs)                                                                                                                                    \
    test->expectations.push_back(std::make_pair<std::string, std::pair<std::string, std::string>>(                                                             \
    std::string(std::string(__FILE__) + ":" + std::to_string(__LINE__)), std::make_pair<std::string, std::string>(std::to_string(lhs), std::to_string(rhs))))

#define EXPECT_TRUE(val) EXPECT_EQ(val, true)
#define EXPECT_FALSE(val) EXPECT_EQ(val, false)

class Test
{
public:
    Test(std::string test_name, std::string test_case_name, std::function<void(Test *)> test_function);
    void execute();

    std::vector<std::pair<std::string, std::pair<std::string, std::string>>> expectations{};

private:
    std::string test_name_;
    std::string test_case_name_;
    std::function<void(Test *)> test_function_;
};

static std::vector<Test *> tests{};
