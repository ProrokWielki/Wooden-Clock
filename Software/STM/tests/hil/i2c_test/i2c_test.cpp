#include <cstdint>
#include <testing_framework.hpp>

#include <HAL/Clock.hpp>
#include <HAL/GPIO.hpp>
#include <HAL/I2C.hpp>
#include <HAL/SysConfig.hpp>

#include <stm32l452xx.h>

RegisterTest(I2cTest, I2c1, [](Test * test) {
    constexpr uint8_t I2C_1_SCL_PIN_NUMBER{9};
    constexpr uint8_t I2C_1_SDA_PIN_NUMBER{10};

    constexpr uint8_t TLC_RESET_PIN_NUMBER{9};

    Clock clock{};
    SysConfig sys_config{};

    GPIO I2C1_SCL(clock, sys_config, GPIO_Types::Port::A, I2C_1_SCL_PIN_NUMBER);
    GPIO I2C1_SDA(clock, sys_config, GPIO_Types::Port::A, I2C_1_SDA_PIN_NUMBER);

    GPIO TLC_RESET(clock, sys_config, GPIO_Types::Port::C, TLC_RESET_PIN_NUMBER);

    TLC_RESET.set_mode(GPIO_Types::PortMode::Output);
    TLC_RESET.set_speed(GPIO_Types::PortOutputSpeed::VeryHigh);
    TLC_RESET.set_output_high();

    I2C sut = I2C(clock, sys_config, I2C_Types::I2CNumber::I2C_1, I2C1_SCL, I2C1_SDA, 20000);

    uint8_t device_address[] = {0x42 >> 1};
    uint8_t register_address[] = {0x10};  // SUBADR3
    uint8_t received_data[10] = {};

    std::span<uint8_t> received = std::span<uint8_t>(received_data, 10);

    sut.set_slave_address(device_address[0], I2C_Types::AddressLength::bits7);
    sut.read_data_from_register(register_address[0], received, 1);

    EXPECT_EQ(received_data[0], 0b10011000);
});

RegisterTest(I2cTest, I2c2, [](Test * test) {
    constexpr uint8_t I2C_2_SCL_PIN_NUMBER{10};
    constexpr uint8_t I2C_2_SDA_PIN_NUMBER{11};

    constexpr uint8_t TLC_RESET_PIN_NUMBER{9};

    Clock clock{};
    SysConfig sys_config{};

    GPIO I2C2_SCL(clock, sys_config, GPIO_Types::Port::B, I2C_2_SCL_PIN_NUMBER);
    GPIO I2C2_SDA(clock, sys_config, GPIO_Types::Port::B, I2C_2_SDA_PIN_NUMBER);

    GPIO TLC_RESET(clock, sys_config, GPIO_Types::Port::C, TLC_RESET_PIN_NUMBER);

    TLC_RESET.set_mode(GPIO_Types::PortMode::Output);
    TLC_RESET.set_speed(GPIO_Types::PortOutputSpeed::VeryHigh);
    TLC_RESET.set_output_high();

    I2C sut = I2C(clock, sys_config, I2C_Types::I2CNumber::I2C_2, I2C2_SCL, I2C2_SDA, 20000);

    uint8_t device_address[] = {0x46 >> 1};
    uint8_t register_address[] = {0x10};  // SUBADR3
    uint8_t received_data[10] = {};

    std::span<uint8_t> received = std::span<uint8_t>(received_data, 10);

    sut.set_slave_address(device_address[0], I2C_Types::AddressLength::bits7);
    sut.read_data_from_register(register_address[0], received, 1);

    EXPECT_EQ(received_data[0], 0b10011000);
});

RegisterTest(I2cTest, I2c3, [](Test * test) {
    constexpr uint8_t I2C_3_SCL_PIN_NUMBER{0};
    constexpr uint8_t I2C_3_SDA_PIN_NUMBER{1};

    constexpr uint8_t TLC_RESET_PIN_NUMBER{9};

    Clock clock{};
    SysConfig sys_config{};

    GPIO I2C3_SCL(clock, sys_config, GPIO_Types::Port::C, I2C_3_SCL_PIN_NUMBER);
    GPIO I2C3_SDA(clock, sys_config, GPIO_Types::Port::C, I2C_3_SDA_PIN_NUMBER);

    GPIO TLC_RESET(clock, sys_config, GPIO_Types::Port::C, TLC_RESET_PIN_NUMBER);

    TLC_RESET.set_mode(GPIO_Types::PortMode::Output);
    TLC_RESET.set_speed(GPIO_Types::PortOutputSpeed::VeryHigh);
    TLC_RESET.set_output_high();

    I2C sut = I2C(clock, sys_config, I2C_Types::I2CNumber::I2C_3, I2C3_SCL, I2C3_SDA, 20000);

    uint8_t device_address[] = {0x44 >> 1};
    uint8_t register_address[] = {0x10};  // SUBADR3
    uint8_t received_data[10] = {};

    std::span<uint8_t> received = std::span<uint8_t>(received_data, 10);

    sut.set_slave_address(device_address[0], I2C_Types::AddressLength::bits7);
    sut.read_data_from_register(register_address[0], received, 1);

    EXPECT_EQ(received_data[0], 0b10011000);
});

RegisterTest(I2cTest, I2c4, [](Test * test) {
    constexpr uint8_t I2C_4_SCL_PIN_NUMBER{6};
    constexpr uint8_t I2C_4_SDA_PIN_NUMBER{7};

    constexpr uint8_t TLC_RESET_PIN_NUMBER{9};

    Clock clock{};
    SysConfig sys_config{};

    GPIO I2C4_SCL(clock, sys_config, GPIO_Types::Port::B, I2C_4_SCL_PIN_NUMBER);
    GPIO I2C4_SDA(clock, sys_config, GPIO_Types::Port::B, I2C_4_SDA_PIN_NUMBER);

    GPIO TLC_RESET(clock, sys_config, GPIO_Types::Port::C, TLC_RESET_PIN_NUMBER);

    TLC_RESET.set_mode(GPIO_Types::PortMode::Output);
    TLC_RESET.set_speed(GPIO_Types::PortOutputSpeed::VeryHigh);
    TLC_RESET.set_output_high();

    I2C sut = I2C(clock, sys_config, I2C_Types::I2CNumber::I2C_4, I2C4_SCL, I2C4_SDA, 20000);

    uint8_t device_address[] = {0x40 >> 1};
    uint8_t register_address[] = {0x10};  // SUBADR3
    uint8_t received_data[10] = {};

    std::span<uint8_t> received = std::span<uint8_t>(received_data, 10);

    sut.set_slave_address(device_address[0], I2C_Types::AddressLength::bits7);
    sut.read_data_from_register(register_address[0], received, 1);

    EXPECT_EQ(received_data[0], 0b10011000);
});
