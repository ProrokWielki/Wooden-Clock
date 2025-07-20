#include <testing_framework.hpp>

RegisterTest(SanityCheck, Check1, [](Test * test) { EXPECT_TRUE(true); });
RegisterTest(SanityCheck, Check2, [](Test * test) { EXPECT_FALSE(false); });
RegisterTest(SanityCheck, Check3, [](Test * test) { EXPECT_EQ(1, 1); });