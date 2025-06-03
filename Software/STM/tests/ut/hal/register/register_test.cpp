#include <gtest/gtest.h>

#include <HAL/Register.hpp>

class RegisterTest: public testing::Test
{
protected:
    uint32_t underling_value{};
    Register<uint32_t> sut{&underling_value};
};

TEST_F(RegisterTest, SetValue)
{
    static constexpr uint32_t SET_VALUE{0x0001'4567};

    sut.set_value(SET_VALUE, 4, 16);

    EXPECT_EQ(underling_value, 0x4567 << 4);
}

TEST_F(RegisterTest, SetValueOverwriteValues)
{
    static constexpr uint32_t SET_VALUE{0x0001'4567};
    underling_value = 0xffff'ffff;

    sut.set_value(SET_VALUE, 0, 32);

    EXPECT_EQ(underling_value, SET_VALUE);
}

TEST_F(RegisterTest, GetValue)
{
    static constexpr uint32_t SET_VALUE{0x8765'4321};

    underling_value = SET_VALUE;

    EXPECT_EQ(sut.get_value(12, 8), 0x54);
}

TEST_F(RegisterTest, ToogleBit)
{
    ASSERT_EQ(underling_value, 0);

    sut.toggle_bit(24);
    EXPECT_EQ(underling_value, 1 << 24);

    sut.toggle_bit(24);
    EXPECT_EQ(underling_value, 0);
}

TEST_F(RegisterTest, SetBit)
{
    ASSERT_EQ(underling_value, 0);

    sut.set_bit(31);
    EXPECT_EQ(underling_value, 1 << 31);
}

TEST_F(RegisterTest, GetBit)
{
    underling_value = 1 << 6 | 1 << 27;

    EXPECT_EQ(sut.get_bit(6), 1);
    EXPECT_EQ(sut.get_bit(27), 1);
    EXPECT_EQ(sut.get_bit(15), 0);
}

TEST_F(RegisterTest, ClearBit)
{
    underling_value = 1 << 21;

    sut.clear_bit(21);
    EXPECT_EQ(underling_value, 0);
}

TEST_F(RegisterTest, Write)
{
    static constexpr uint32_t SET_VALUE{0xdead'beef};

    sut.write(SET_VALUE);
    EXPECT_EQ(underling_value, SET_VALUE);
}

TEST_F(RegisterTest, Read)
{
    static constexpr uint32_t SET_VALUE{0xdead'beef};
    underling_value = SET_VALUE;

    EXPECT_EQ(sut.read(), SET_VALUE);
}

TEST_F(RegisterTest, GetAddress)
{
    uintptr_t underling_value_address{reinterpret_cast<uintptr_t>(&underling_value)};

    EXPECT_EQ(sut.get_address(), underling_value_address);
}
