/**
 * @file cmsis_bridge.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include <cstdint>

#include <gmock/gmock.h>

#include <HAL/types.hpp>

class CmsisBridgeMock
{
public:
    MOCK_METHOD(volatile uint32_t *, to_address, (GPIO_Types::Port, GPIO_Types::PortRegister));
    MOCK_METHOD(volatile uint32_t *, to_address, (ClockRegister));
    MOCK_METHOD(volatile uint32_t *, to_address, (I2C_Types::I2CNumber, I2C_Types::Register));
    MOCK_METHOD(volatile uint32_t *, to_address, (DMA_Types::DmaNumber, DMA_Types::Channel channel, DMA_Types::DmaRegister));
    MOCK_METHOD(volatile uint32_t *, to_address, (SPI_types::SPI_Number, SPI_types::Register));
    MOCK_METHOD(volatile uint32_t *, to_address, (RTC_types::Register));
    MOCK_METHOD(volatile uint32_t *, to_address, (timer_types::Timer_number, timer_types::Register));
    MOCK_METHOD(volatile uint32_t *, to_address, (Usart_Types::UsartNumber, Usart_Types::Register));
    MOCK_METHOD(volatile uint32_t *, to_address, (Power_Types::Register));
    MOCK_METHOD(volatile uint16_t *, to_16bit_register_address, (Usart_Types::UsartNumber, Usart_Types::Register));
};

static CmsisBridgeMock cmsis_bridge_mock;

volatile uint32_t * to_address(GPIO_Types::Port port, GPIO_Types::PortRegister portRegister)
{
    return cmsis_bridge_mock.to_address(port, portRegister);
}

volatile uint32_t * to_address(ClockRegister clock_register)
{
    return cmsis_bridge_mock.to_address(clock_register);
}

volatile uint32_t * to_address(I2C_Types::I2CNumber i2c, I2C_Types::Register i2c_register)
{
    return cmsis_bridge_mock.to_address(i2c, i2c_register);
}
volatile uint32_t * to_address(DMA_Types::DmaNumber dma, DMA_Types::Channel channel, DMA_Types::DmaRegister dma_register)
{
    return cmsis_bridge_mock.to_address(dma, channel, dma_register);
}
volatile uint32_t * to_address(SPI_types::SPI_Number spi, SPI_types::Register spi_register)
{
    return cmsis_bridge_mock.to_address(spi, spi_register);
}
volatile uint32_t * to_address(RTC_types::Register rtc_register)
{
    return cmsis_bridge_mock.to_address(rtc_register);
}
volatile uint32_t * to_address(timer_types::Timer_number timer, timer_types::Register timer_register)
{
    return cmsis_bridge_mock.to_address(timer, timer_register);
}
volatile uint32_t * to_address(Usart_Types::UsartNumber usart, Usart_Types::Register usart_register)
{
    return cmsis_bridge_mock.to_address(usart, usart_register);
}

volatile uint32_t * to_address(Power_Types::Register power_register)
{
    return cmsis_bridge_mock.to_address(power_register);
}

volatile uint16_t * to_16bit_register_address(Usart_Types::UsartNumber usart, Usart_Types::Register usart_register)
{
    return cmsis_bridge_mock.to_16bit_register_address(usart, usart_register);
}
