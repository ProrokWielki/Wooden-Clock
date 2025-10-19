#include <cstdint>

#include <testing_framework.hpp>

#include <stm32l452xx.h>

#include <HAL/Clock.hpp>
#include <HAL/GPIO.hpp>
#include <HAL/types.hpp>

RegisterTest(GpioTest, SetAsOutput, [](Test * test) {
    Clock clock{};

    GPIO sut = GPIO(clock, GPIO_Types::Port::C, 9);
    EXPECT_EQ(RCC->AHB2ENR & (1 << 2), 1 << 2);

    sut.set_mode(GPIO_Types::PortMode::Output);
    EXPECT_EQ(GPIOC->MODER & (3 << 18), 1 << 18);
});

RegisterTest(RegisterTest, SetValue, [](Test * test) {
    Register rcc_apb1enr1{&(RCC->APB1ENR1)};

    RCC->APB1ENR1 = 0;
    EXPECT_EQ(RCC->APB1ENR1, 0);

    rcc_apb1enr1.set_value(0b1'0101, 21, 4);  // set one bit over the size

    EXPECT_EQ(RCC->APB1ENR1, 0b0101 << 21);  // check if it wasn't set
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

    constexpr static uint32_t CAN_FMR_RESET_VALUE{0x2A1C0E01};

    EXPECT_EQ(CAN->FMR, CAN_FMR_RESET_VALUE);
    EXPECT_EQ(can_fmr.read(), CAN_FMR_RESET_VALUE);
});

RegisterTest(RegisterTest, Write, [](Test * test) {
    Register rcc_apb1enr1{&(RCC->APB1ENR1)};

    RCC->APB1ENR1 = 0;
    EXPECT_EQ(RCC->APB1ENR1, 0);

    rcc_apb1enr1.write(705537);

    EXPECT_EQ(RCC->APB1ENR1, 705537);
});
