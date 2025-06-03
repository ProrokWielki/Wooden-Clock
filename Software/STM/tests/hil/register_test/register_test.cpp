#include <cstdint>

#include <testing_framework.hpp>

#include <stm32l452xx.h>

#include <HAL/Register.hpp>

constexpr uint32_t CAN_FMR_RESET_VALUE{0x2A1C'0E01};

RegisterTest(RegisterTest, getValue, [](Test * test) {
    Register can_fmr{&(CAN->FMR)};

    EXPECT_EQ(CAN->FMR, CAN_FMR_RESET_VALUE);

    EXPECT_EQ(can_fmr.get_value(0, 32), CAN_FMR_RESET_VALUE);
    EXPECT_EQ(can_fmr.get_value(8, 8), 0x0E);
});

RegisterTest(RegisterTest, SetValue, [](Test * test) {
    Register rcc_apb1enr1{&(RCC->APB1ENR1)};

    RCC->APB1ENR1 = 0;
    EXPECT_EQ(RCC->APB1ENR1, 0);

    rcc_apb1enr1.set_value(0b1'0101, 21, 4);  // set one bit over the size

    EXPECT_EQ(RCC->APB1ENR1, 0b0101 << 21);  // check if it wasn't set
});

RegisterTest(RegisterTest, SetValueOverridesBitsToSet, [](Test * test) {
    Register rcc_apb1enr1{&(RCC->APB1ENR1)};

    RCC->APB1ENR1 = 0xf000'0000;
    EXPECT_EQ(RCC->APB1ENR1, 0xf000'0000);

    rcc_apb1enr1.set_value(0, 28, 4);

    EXPECT_EQ(RCC->APB1ENR1, 0);
});

RegisterTest(RegisterTest, GetBit, [](Test * test) {
    Register exti_imr1{&(EXTI->IMR1)};

    EXPECT_EQ(EXTI->IMR1, 0xFF820000);

    EXPECT_EQ(exti_imr1.get_bit(15), 0);
    EXPECT_EQ(exti_imr1.get_bit(23), 1);
});

RegisterTest(RegisterTest, SetBit, [](Test * test) {
    Register rcc_ahb2enr{&(RCC->AHB2ENR)};

    RCC->AHB2ENR = 0;
    EXPECT_EQ(RCC->AHB2ENR, 0);

    rcc_ahb2enr.set_bit(18);
    EXPECT_EQ(RCC->AHB2ENR, 1 << 18);
});

RegisterTest(RegisterTest, ClearBit, [](Test * test) {
    Register rcc_ahb2enr{&(RCC->AHB2ENR)};

    RCC->AHB2ENR = 4;
    EXPECT_EQ(RCC->AHB2ENR, 4);

    rcc_ahb2enr.clear_bit(2);
    EXPECT_EQ(RCC->AHB2ENR, 0);
});

RegisterTest(RegisterTest, GetAddress, [](Test * test) {
    Register rcc_ahb2enr{&(RCC->AHB2ENR)};

    EXPECT_EQ(reinterpret_cast<uint32_t>(&(RCC->AHB2ENR)), rcc_ahb2enr.get_address());
});

RegisterTest(RegisterTest, ToogleBit, [](Test * test) {
    Register rcc_ahb2enr{&(RCC->AHB2ENR)};

    RCC->AHB2ENR = 0;
    EXPECT_EQ(RCC->AHB2ENR, 0);

    rcc_ahb2enr.toggle_bit(18);
    EXPECT_EQ(RCC->AHB2ENR, 1 << 18);

    rcc_ahb2enr.toggle_bit(18);
    EXPECT_EQ(RCC->AHB2ENR, 0);
});

RegisterTest(RegisterTest, Read, [](Test * test) {
    Register can_fmr{&(CAN->FMR)};

    EXPECT_EQ(CAN->FMR, CAN_FMR_RESET_VALUE);
    EXPECT_EQ(can_fmr.read(), CAN_FMR_RESET_VALUE);
});

RegisterTest(RegisterTest, Write, [](Test * test) {
    Register rcc_apb1enr1{&(RCC->APB1ENR1)};

    RCC->APB1ENR1 = 0;
    EXPECT_EQ(RCC->APB1ENR1, 0);

    rcc_apb1enr1.write(static_cast<uint32_t>(705537));

    EXPECT_EQ(RCC->APB1ENR1, 705537);
});
