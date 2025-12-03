/**
 * @file cmisi_bridge.hpp
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

#include <HAL/types.hpp>

volatile uint32_t * to_address(GPIO_Types::Port port, GPIO_Types::PortRegister portRegister);
volatile uint32_t * to_address(ClockRegister clock_register);
volatile uint32_t * to_address(SysConfigRegister sys_config_register);
volatile uint32_t * to_address(I2C_Types::I2CNumber i2c, I2C_Types::Register i2c_register);
volatile uint32_t * to_address(DMA_Types::DmaNumber dma, DMA_Types::Channel channel, DMA_Types::DmaRegister dma_register);
volatile uint32_t * to_address(SPI_types::SPI_Number spi, SPI_types::Register spi_register);
volatile uint32_t * to_address(RTC_types::Register rtc_register);
volatile uint32_t * to_address(Power_Types::Register power_register);
volatile uint32_t * to_address(timer_types::Timer_number timer, timer_types::Register timer_register);
volatile uint32_t * to_address(Usart_Types::UsartNumber usart, Usart_Types::Register usart_register);
volatile uint16_t * to_16bit_register_address(Usart_Types::UsartNumber usart, Usart_Types::Register usart_register);
