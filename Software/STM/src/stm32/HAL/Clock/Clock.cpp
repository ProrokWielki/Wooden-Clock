/**
 * @file Clock.cpp
 * @author Pawel Warzecha
 * @brief
 * @version 0.1
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <cassert>

#include <HAL/Register.hpp>
#include <HAL/types.hpp>

#include "cmsis_bridge/cmsis_bridge.hpp"
#include "include/HAL/Clock.hpp"

Clock::Clock()
: AHB1(to_address(ClockRegister::AHB1)), AHB2(to_address(ClockRegister::AHB2)), AHB3(to_address(ClockRegister::AHB3)),
  APB1_1(to_address(ClockRegister::APB1_1)), APB1_2(to_address(ClockRegister::APB1_2)), APB2(to_address(ClockRegister::APB2)),
  PLL_CONFIG(to_address(ClockRegister::PLL_CONFIG)), CCIPR(to_address(ClockRegister::CCIPR)), CCIPR2(to_address(ClockRegister::CCIPR2))
{
}

void Clock::enable_clock_for(Peripheral peripheral)
{
    Register<uint32_t> & peripheral_clock_register{get_peripheral_clock_register(peripheral)};

    peripheral_clock_register.set_bit(to_bit_position(peripheral));
}

void Clock::set_clock_source_for(PeripheralWithSelectableClockSource peripheral, ClockSource clock_source)
{
    assert(is_clock_source_supported(peripheral, clock_source) && "Unsupported clock source.");

    Register<uint32_t> & peripheral_clock_source_register{get_peripheral_clock_source_register(peripheral)};
    peripheral_clock_source_register.set_value(to_clock_source_value(peripheral, clock_source), to_clock_source_position(peripheral),
                                               to_peripheral_clock_select_field_length(peripheral));
}

[[nodiscard]] uint32_t Clock::get_clock_frequency() const
{
    constexpr uint32_t CLOCK_FREQUENCY{80'000'000}; //TODO: Get from RCC->CFGR
    return CLOCK_FREQUENCY;
}

Register<uint32_t> & Clock::get_peripheral_clock_register(Peripheral peripheral)
{
    switch (peripheral)
    {
        case Peripheral::EXTERNAL_FLASH:
        case Peripheral::DMA_2:
        case Peripheral::DMA_1:
        case Peripheral::TOUCH_SENSE:
        case Peripheral::CRC_UNIT:
            return AHB1;
        case Peripheral::ADC:
        case Peripheral::AES:
        case Peripheral::RANDOM_NUMBER_GENERATOR:
        case Peripheral::GPIO_A:
        case Peripheral::GPIO_B:
        case Peripheral::GPIO_C:
        case Peripheral::GPIO_D:
        case Peripheral::GPIO_E:
        case Peripheral::GPIO_H:
            return AHB2;
        case Peripheral::QSPI:
            return AHB3;
        case Peripheral::LOW_POWER_TIMER_1:
        case Peripheral::OP_AMP:
        case Peripheral::DAC_1:
        case Peripheral::USB_FS:
        case Peripheral::CAN_1:
        case Peripheral::I2C_1:
        case Peripheral::I2C_2:
        case Peripheral::I2C_3:
        case Peripheral::USART_2:
        case Peripheral::USART_3:
        case Peripheral::UART_4:
        case Peripheral::SPI_3:
        case Peripheral::SPI_2:
        case Peripheral::TIMER_2:
        case Peripheral::TIMER_3:
        case Peripheral::TIMER_6:
        case Peripheral::TIMER_7:
        case Peripheral::LCD:
        case Peripheral::WINDOW_WATCHDOG:
        case Peripheral::CLOCK_RECOVERY_SYSTEM:
        case Peripheral::POWER_INTERFACE:
        case Peripheral::RTC_APB:
            return APB1_1;
        case Peripheral::LOW_POWER_TIMER_2:
        case Peripheral::I2C_4:
        case Peripheral::LOW_POWER_UART_1:
        case Peripheral::SINGLE_WIRE:
            return APB1_2;
        case Peripheral::USART_1:
        case Peripheral::SPI_1:
        case Peripheral::TIMER_1:
        case Peripheral::TIMER_15:
        case Peripheral::TIMER_16:
        case Peripheral::SDMMC_1:
        case Peripheral::FIRE_WALL:
        case Peripheral::SAI_1:
        case Peripheral::DFSDM_1:
        case Peripheral::SYSTEM_CONFIG:
            return APB2;
        default:
            assert(false && "invalid peripheral");
            return APB1_1;
    };
}

Register<uint32_t> & Clock::get_peripheral_clock_source_register(PeripheralWithSelectableClockSource peripheral)
{
    switch (peripheral)
    {
        case PeripheralWithSelectableClockSource::USART_1:
        case PeripheralWithSelectableClockSource::USART_2:
        case PeripheralWithSelectableClockSource::USART_3:
        case PeripheralWithSelectableClockSource::UART_4:
        case PeripheralWithSelectableClockSource::LOW_POWER_UART_1:
        case PeripheralWithSelectableClockSource::I2C_1:
        case PeripheralWithSelectableClockSource::I2C_2:
        case PeripheralWithSelectableClockSource::I2C_3:
        case PeripheralWithSelectableClockSource::ADC:
        case PeripheralWithSelectableClockSource::CLK_48MHZ:
        case PeripheralWithSelectableClockSource::LOW_POWER_TIMER_1:
        case PeripheralWithSelectableClockSource::LOW_POWER_TIMER_2:
        case PeripheralWithSelectableClockSource::SINGLE_WIRE:
        case PeripheralWithSelectableClockSource::SAI_1:
            return CCIPR;
        case PeripheralWithSelectableClockSource::I2C_4:
            return CCIPR2;
        default:
            assert(false && "invalid peripheral");
            return CCIPR;
    }
}
