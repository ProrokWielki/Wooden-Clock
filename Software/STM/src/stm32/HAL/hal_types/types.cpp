#include <cassert>
#include <cstdint>

#include <HAL/types.hpp>

uint32_t to_register_value(GPIO_Types::PortMode portMode)
{
    switch (portMode)
    {
        case GPIO_Types::PortMode::Input:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::PortMode::Output:
            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::PortMode::Alternate:
            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::PortMode::Analog:
            return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        default:
            assert(false && "wrong port mode");
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    }
}

uint32_t to_register_value(GPIO_Types::AlternateFunction alternateFunction)
{
    switch (alternateFunction)
    {
        case GPIO_Types::AlternateFunction::AF0:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::AlternateFunction::AF1:
            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::AlternateFunction::AF2:
            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::AlternateFunction::AF3:
            return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::AlternateFunction::AF4:
            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::AlternateFunction::AF5:
            return 5;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::AlternateFunction::AF6:
            return 6;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::AlternateFunction::AF7:
            return 7;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::AlternateFunction::AF8:
            return 8;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::AlternateFunction::AF9:
            return 9;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::AlternateFunction::AF10:
            return 10;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::AlternateFunction::AF11:
            return 11;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::AlternateFunction::AF12:
            return 12;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::AlternateFunction::AF13:
            return 13;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::AlternateFunction::AF14:
            return 14;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::AlternateFunction::AF15:
            return 15;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        default:
            assert(false && "wrong alternate function");
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    }
}

uint32_t to_register_value(GPIO_Types::SignalLevel signalLevel)
{
    switch (signalLevel)
    {
        case GPIO_Types::SignalLevel::High:
            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::SignalLevel::Low:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        default:
            assert(false && "wrong signal level");
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    };
}

uint32_t to_register_value(GPIO_Types::PortPullUpPullDown portPullUpPullDown)
{
    switch (portPullUpPullDown)
    {
        case GPIO_Types::PortPullUpPullDown::None:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::PortPullUpPullDown::PullUp:
            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::PortPullUpPullDown::PullDown:
            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        default:
            assert(false && "wrong internal ressitor");
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    };
}

uint32_t to_register_value(GPIO_Types::PortOutputSpeed portOutputSpeed)
{
    switch (portOutputSpeed)
    {
        case GPIO_Types::PortOutputSpeed::Low:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::PortOutputSpeed::Medium:
            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::PortOutputSpeed::High:
            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::PortOutputSpeed::VeryHigh:
            return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        default:
            assert(false && "wrong port output speed");
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    };
}

uint32_t to_register_value(GPIO_Types::PortOutputType portOutputType)
{
    switch (portOutputType)
    {
        case GPIO_Types::PortOutputType::PushPull:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case GPIO_Types::PortOutputType::OpenDrain:
            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        default:
            assert(false && "wrong port output type");
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    };
}

uint32_t to_clock_source_value(PeripheralWithSelectableClockSource peripheral, ClockSource clock_source)
{
    switch (peripheral)
    {
        case PeripheralWithSelectableClockSource::I2C_1:
        case PeripheralWithSelectableClockSource::I2C_2:
        case PeripheralWithSelectableClockSource::I2C_3:
        case PeripheralWithSelectableClockSource::I2C_4:
            switch (clock_source)
            {
                case ClockSource::HSI16:
                    return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::PCLK:
                    return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::SYSTEM_CLOCK:
                    return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::LSE:
                case ClockSource::HSE:
                case ClockSource::LSI:
                case ClockSource::MSI:
                case ClockSource::HSI48:
                case ClockSource::PCLK1:
                case ClockSource::PLL_ADC_CLOCK:
                case ClockSource::PLL_48_M1_CLOCK:
                case ClockSource::PLL_48_M2_CLOCK:
                case ClockSource::PLL_SAI_CLOCK:
                case ClockSource::PLL_P_CLOCK:
                case ClockSource::SAI_EXTERNAL_CLOCK:
                case ClockSource::N0_CLOCK:
                default:
                    assert(false && "invalid clock source");
                    return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            };
        case PeripheralWithSelectableClockSource::USART_1:
        case PeripheralWithSelectableClockSource::USART_2:
        case PeripheralWithSelectableClockSource::USART_3:
        case PeripheralWithSelectableClockSource::UART_4:
        case PeripheralWithSelectableClockSource::LOW_POWER_UART_1:
            switch (clock_source)
            {
                case ClockSource::PCLK:
                    return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::SYSTEM_CLOCK:
                    return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::LSE:
                    return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::HSI16:
                    return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::LSI:
                case ClockSource::MSI:
                case ClockSource::HSE:
                case ClockSource::HSI48:
                case ClockSource::PCLK1:
                case ClockSource::PLL_ADC_CLOCK:
                case ClockSource::PLL_48_M1_CLOCK:
                case ClockSource::PLL_48_M2_CLOCK:
                case ClockSource::PLL_SAI_CLOCK:
                case ClockSource::PLL_P_CLOCK:
                case ClockSource::SAI_EXTERNAL_CLOCK:
                case ClockSource::N0_CLOCK:
                default:
                    assert(false && "invalid clock source");
                    return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            }

        case PeripheralWithSelectableClockSource::ADC:
            switch (clock_source)
            {
                case ClockSource::N0_CLOCK:
                    return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::SYSTEM_CLOCK:
                    return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::PLL_ADC_CLOCK:
                    return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::PCLK:
                case ClockSource::LSI:
                case ClockSource::MSI:
                case ClockSource::HSI16:
                case ClockSource::HSI48:
                case ClockSource::LSE:
                case ClockSource::HSE:
                case ClockSource::PCLK1:
                case ClockSource::PLL_48_M1_CLOCK:
                case ClockSource::PLL_48_M2_CLOCK:
                case ClockSource::PLL_SAI_CLOCK:
                case ClockSource::PLL_P_CLOCK:
                case ClockSource::SAI_EXTERNAL_CLOCK:
                default:
                    assert(false && "invalid clock source");
                    return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            }
        case PeripheralWithSelectableClockSource::CLK_48MHZ:
            switch (clock_source)
            {
                case ClockSource::HSI48:
                    return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::PLL_48_M1_CLOCK:
                    return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::PLL_48_M2_CLOCK:
                    return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::MSI:
                    return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::PCLK:
                case ClockSource::SYSTEM_CLOCK:
                case ClockSource::LSI:
                case ClockSource::HSI16:
                case ClockSource::LSE:
                case ClockSource::HSE:
                case ClockSource::PCLK1:
                case ClockSource::PLL_ADC_CLOCK:
                case ClockSource::PLL_SAI_CLOCK:
                case ClockSource::PLL_P_CLOCK:
                case ClockSource::SAI_EXTERNAL_CLOCK:
                case ClockSource::N0_CLOCK:
                default:
                    assert(false && "invalid clock source");
                    return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            }
        case PeripheralWithSelectableClockSource::LOW_POWER_TIMER_1:
        case PeripheralWithSelectableClockSource::LOW_POWER_TIMER_2:
            switch (clock_source)
            {
                case ClockSource::PCLK:
                    return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::LSI:
                    return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::HSI16:
                    return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::LSE:
                    return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::SYSTEM_CLOCK:
                case ClockSource::MSI:
                case ClockSource::HSI48:
                case ClockSource::HSE:
                case ClockSource::PCLK1:
                case ClockSource::PLL_ADC_CLOCK:
                case ClockSource::PLL_48_M1_CLOCK:
                case ClockSource::PLL_48_M2_CLOCK:
                case ClockSource::PLL_SAI_CLOCK:
                case ClockSource::PLL_P_CLOCK:
                case ClockSource::SAI_EXTERNAL_CLOCK:
                case ClockSource::N0_CLOCK:
                default:
                    assert(false && "invalid clock source");
                    return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            }

        case PeripheralWithSelectableClockSource::SINGLE_WIRE:
            switch (clock_source)
            {
                case ClockSource::PCLK1:
                    return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::HSI16:
                    return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::PLL_SAI_CLOCK:
                case ClockSource::PLL_P_CLOCK:
                case ClockSource::SAI_EXTERNAL_CLOCK:
                case ClockSource::PCLK:
                case ClockSource::SYSTEM_CLOCK:
                case ClockSource::LSI:
                case ClockSource::MSI:
                case ClockSource::HSI48:
                case ClockSource::LSE:
                case ClockSource::HSE:
                case ClockSource::PLL_ADC_CLOCK:
                case ClockSource::PLL_48_M1_CLOCK:
                case ClockSource::PLL_48_M2_CLOCK:
                case ClockSource::N0_CLOCK:
                default:
                    assert(false && "invalid clock source");
                    return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            }

        case PeripheralWithSelectableClockSource::SAI_1:
            switch (clock_source)
            {
                case ClockSource::PLL_SAI_CLOCK:
                    return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::PLL_P_CLOCK:
                    return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::SAI_EXTERNAL_CLOCK:
                    return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::PCLK:
                case ClockSource::SYSTEM_CLOCK:
                case ClockSource::LSI:
                case ClockSource::MSI:
                case ClockSource::HSI16:
                case ClockSource::HSI48:
                case ClockSource::LSE:
                case ClockSource::HSE:
                case ClockSource::PCLK1:
                case ClockSource::PLL_ADC_CLOCK:
                case ClockSource::PLL_48_M1_CLOCK:
                case ClockSource::PLL_48_M2_CLOCK:
                case ClockSource::N0_CLOCK:
                default:
                    assert(false && "invalid clock source");
                    return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            }
        case PeripheralWithSelectableClockSource::RTC_1:
            switch (clock_source)
            {
                case ClockSource::N0_CLOCK:
                    return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::LSE:
                    return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::LSI:
                    return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::HSE:
                    return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case ClockSource::PCLK:
                case ClockSource::SYSTEM_CLOCK:
                case ClockSource::MSI:
                case ClockSource::HSI16:
                case ClockSource::HSI48:
                case ClockSource::PCLK1:
                case ClockSource::PLL_ADC_CLOCK:
                case ClockSource::PLL_48_M1_CLOCK:
                case ClockSource::PLL_48_M2_CLOCK:
                default:
                    assert(false && "invalid clock source");
                    return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            }
        default:
            assert(false && "Unsupported peripheral.");
            return 0;
    };
}

uint8_t to_clock_source_position(PeripheralWithSelectableClockSource peripheral)
{
    switch (peripheral)
    {
        case PeripheralWithSelectableClockSource::USART_1:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case PeripheralWithSelectableClockSource::USART_2:
            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case PeripheralWithSelectableClockSource::USART_3:
            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case PeripheralWithSelectableClockSource::UART_4:
            return 6;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case PeripheralWithSelectableClockSource::LOW_POWER_UART_1:
            return 10;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case PeripheralWithSelectableClockSource::I2C_1:
            return 12;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case PeripheralWithSelectableClockSource::I2C_2:
            return 14;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case PeripheralWithSelectableClockSource::I2C_3:
            return 16;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case PeripheralWithSelectableClockSource::I2C_4:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case PeripheralWithSelectableClockSource::ADC:
            return 28;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case PeripheralWithSelectableClockSource::CLK_48MHZ:
            return 26;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case PeripheralWithSelectableClockSource::LOW_POWER_TIMER_1:
            return 18;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case PeripheralWithSelectableClockSource::LOW_POWER_TIMER_2:
            return 20;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case PeripheralWithSelectableClockSource::SINGLE_WIRE:
            return 30;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case PeripheralWithSelectableClockSource::SAI_1:
            return 22;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case PeripheralWithSelectableClockSource::RTC_1:
            return 8;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        default:
            assert(false && "invalid peripheral");
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    }
}

uint8_t to_bit_position(Peripheral peripheral)
{
    switch (peripheral)
    {
        case Peripheral::EXTERNAL_FLASH:
            return 8;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::DMA_1:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::DMA_2:
            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::ADC:
            return 13;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::GPIO_A:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::GPIO_B:
            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::GPIO_C:
            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::GPIO_D:
            return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::GPIO_E:
            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::GPIO_H:
            return 7;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::QSPI:
            return 8;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::LOW_POWER_TIMER_1:
            return 31;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::OP_AMP:
            return 30;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::DAC_1:
            return 29;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::USB_FS:
            return 26;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::CAN_1:
            return 25;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::I2C_1:
            return 21;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::I2C_2:
            return 22;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::I2C_3:
            return 23;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::USART_2:
            return 17;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::USART_3:
            return 18;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::UART_4:
            return 19;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::SPI_3:
            return 15;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::SPI_2:
            return 14;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::TIMER_2:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::TIMER_3:
            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::TIMER_6:
            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::LOW_POWER_TIMER_2:
            return 5;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::I2C_4:
            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::LOW_POWER_UART_1:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::USART_1:
            return 14;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::SPI_1:
            return 12;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::TIMER_1:
            return 11;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::TIMER_15:
            return 16;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::TIMER_16:
            return 17;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::SDMMC_1:
            return 10;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::FIRE_WALL:
            return 7;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::SAI_1:
            return 21;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::DFSDM_1:
            return 24;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::CRC_UNIT:
            return 12;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::TOUCH_SENSE:
        case Peripheral::AES:
            return 16;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::RANDOM_NUMBER_GENERATOR:
            return 18;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::LCD:
            return 9;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::RTC_APB:
            return 10;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::WINDOW_WATCHDOG:
            return 11;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::CLOCK_RECOVERY_SYSTEM:
            return 24;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::POWER_INTERFACE:
            return 28;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::TIMER_7:
            return 5;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::SINGLE_WIRE:
            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::SYSTEM_CONFIG:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case Peripheral::RTC_1:
            return 15;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        default:
            assert(false && "invalid peripheral");
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    };
}

Peripheral to_peripheral(GPIO_Types::Port port)
{
    switch (port)
    {
        case GPIO_Types::Port::A:
            return Peripheral::GPIO_A;
        case GPIO_Types::Port::B:
            return Peripheral::GPIO_B;
        case GPIO_Types::Port::C:
            return Peripheral::GPIO_C;
        case GPIO_Types::Port::D:
            return Peripheral::GPIO_D;
        case GPIO_Types::Port::E:
            return Peripheral::GPIO_E;
        default:
            assert(false && "Invalid port");
            return Peripheral::GPIO_A;
    };
}

Peripheral to_peripheral(Usart_Types::UsartNumber usart)
{
    switch (usart)
    {
        case Usart_Types::UsartNumber::USART_1:
            return Peripheral::USART_1;
        case Usart_Types::UsartNumber::USART_2:
            return Peripheral::USART_2;
        case Usart_Types::UsartNumber::USART_3:
            return Peripheral::USART_3;
        case Usart_Types::UsartNumber::UART_4:
            return Peripheral::UART_4;
        case Usart_Types::UsartNumber::LOW_POWER_UART_1:
            return Peripheral::LOW_POWER_UART_1;
        default:
            assert(false && "Invalid USART number");
            return Peripheral::USART_1;
    };
}

uint8_t to_enable_bit_position(ClockSource clock_source)
{
    switch (clock_source)
    {
        case ClockSource::LSE:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case ClockSource::HSI48:
        case ClockSource::PLL_48_M1_CLOCK:
        case ClockSource::PLL_48_M2_CLOCK:
        case ClockSource::MSI:
        case ClockSource::PCLK:
        case ClockSource::SYSTEM_CLOCK:
        case ClockSource::LSI:
        case ClockSource::HSI16:
        case ClockSource::HSE:
        case ClockSource::PCLK1:
        case ClockSource::PLL_ADC_CLOCK:
        case ClockSource::PLL_SAI_CLOCK:
        case ClockSource::PLL_P_CLOCK:
        case ClockSource::SAI_EXTERNAL_CLOCK:
        case ClockSource::N0_CLOCK:
            assert(false && "not implemented");
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        default:
            assert(false && "invalid clock source");
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    }
}

uint8_t to_ready_bit_position(ClockSource clock_source)
{
    switch (clock_source)
    {
        case ClockSource::LSE:
            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case ClockSource::HSI48:
        case ClockSource::PLL_48_M1_CLOCK:
        case ClockSource::PLL_48_M2_CLOCK:
        case ClockSource::MSI:
        case ClockSource::PCLK:
        case ClockSource::SYSTEM_CLOCK:
        case ClockSource::LSI:
        case ClockSource::HSI16:
        case ClockSource::HSE:
        case ClockSource::PCLK1:
        case ClockSource::PLL_ADC_CLOCK:
        case ClockSource::PLL_SAI_CLOCK:
        case ClockSource::PLL_P_CLOCK:
        case ClockSource::SAI_EXTERNAL_CLOCK:
        case ClockSource::N0_CLOCK:
            assert(false && "not implemented");
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        default:
            assert(false && "invalid clock source");
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    }
}

bool is_clock_source_supported(PeripheralWithSelectableClockSource peripheral, ClockSource clock_source)
{
    switch (peripheral)
    {
        case PeripheralWithSelectableClockSource::I2C_1:
        case PeripheralWithSelectableClockSource::I2C_2:
        case PeripheralWithSelectableClockSource::I2C_3:
        case PeripheralWithSelectableClockSource::I2C_4:
            switch (clock_source)
            {
                case ClockSource::HSI16:
                case ClockSource::PCLK:
                case ClockSource::SYSTEM_CLOCK:
                    return true;
                case ClockSource::LSE:
                case ClockSource::LSI:
                case ClockSource::MSI:
                case ClockSource::HSI48:
                case ClockSource::PCLK1:
                case ClockSource::PLL_ADC_CLOCK:
                case ClockSource::PLL_48_M1_CLOCK:
                case ClockSource::PLL_48_M2_CLOCK:
                case ClockSource::PLL_SAI_CLOCK:
                case ClockSource::PLL_P_CLOCK:
                case ClockSource::SAI_EXTERNAL_CLOCK:
                case ClockSource::N0_CLOCK:
                    return false;
                default:
                    assert(false && "invalid clock source");
                    return false;
            };
        case PeripheralWithSelectableClockSource::USART_1:
        case PeripheralWithSelectableClockSource::USART_2:
        case PeripheralWithSelectableClockSource::USART_3:
        case PeripheralWithSelectableClockSource::UART_4:
        case PeripheralWithSelectableClockSource::LOW_POWER_UART_1:
            switch (clock_source)
            {
                case ClockSource::PCLK:
                case ClockSource::SYSTEM_CLOCK:
                case ClockSource::LSE:
                case ClockSource::HSI16:
                    return true;
                case ClockSource::LSI:
                case ClockSource::MSI:
                case ClockSource::HSE:
                case ClockSource::HSI48:
                case ClockSource::PCLK1:
                case ClockSource::PLL_ADC_CLOCK:
                case ClockSource::PLL_48_M1_CLOCK:
                case ClockSource::PLL_48_M2_CLOCK:
                case ClockSource::PLL_SAI_CLOCK:
                case ClockSource::PLL_P_CLOCK:
                case ClockSource::SAI_EXTERNAL_CLOCK:
                case ClockSource::N0_CLOCK:
                    return false;
                default:
                    assert(false && "invalid clock source");
                    return false;
            }

        case PeripheralWithSelectableClockSource::ADC:
            switch (clock_source)
            {
                case ClockSource::N0_CLOCK:
                case ClockSource::SYSTEM_CLOCK:
                case ClockSource::PLL_ADC_CLOCK:
                    return true;
                case ClockSource::PCLK:
                case ClockSource::LSI:
                case ClockSource::MSI:
                case ClockSource::HSI16:
                case ClockSource::HSI48:
                case ClockSource::LSE:
                case ClockSource::HSE:
                case ClockSource::PCLK1:
                case ClockSource::PLL_48_M1_CLOCK:
                case ClockSource::PLL_48_M2_CLOCK:
                case ClockSource::PLL_SAI_CLOCK:
                case ClockSource::PLL_P_CLOCK:
                case ClockSource::SAI_EXTERNAL_CLOCK:
                    return false;
                default:
                    assert(false && "invalid clock source");
                    return false;
            }
        case PeripheralWithSelectableClockSource::CLK_48MHZ:
            switch (clock_source)
            {
                case ClockSource::HSI48:
                case ClockSource::PLL_48_M1_CLOCK:
                case ClockSource::PLL_48_M2_CLOCK:
                case ClockSource::MSI:
                    return true;
                case ClockSource::PCLK:
                case ClockSource::SYSTEM_CLOCK:
                case ClockSource::LSI:
                case ClockSource::HSI16:
                case ClockSource::LSE:
                case ClockSource::HSE:
                case ClockSource::PCLK1:
                case ClockSource::PLL_ADC_CLOCK:
                case ClockSource::PLL_SAI_CLOCK:
                case ClockSource::PLL_P_CLOCK:
                case ClockSource::SAI_EXTERNAL_CLOCK:
                case ClockSource::N0_CLOCK:
                    return false;
                default:
                    assert(false && "invalid clock source");
                    return false;
            }
        case PeripheralWithSelectableClockSource::LOW_POWER_TIMER_1:
        case PeripheralWithSelectableClockSource::LOW_POWER_TIMER_2:
            switch (clock_source)
            {
                case ClockSource::PCLK:
                case ClockSource::LSI:
                case ClockSource::HSI16:
                case ClockSource::LSE:
                    return true;
                case ClockSource::SYSTEM_CLOCK:
                case ClockSource::MSI:
                case ClockSource::HSI48:
                case ClockSource::PCLK1:
                case ClockSource::HSE:
                case ClockSource::PLL_ADC_CLOCK:
                case ClockSource::PLL_48_M1_CLOCK:
                case ClockSource::PLL_48_M2_CLOCK:
                case ClockSource::PLL_SAI_CLOCK:
                case ClockSource::PLL_P_CLOCK:
                case ClockSource::SAI_EXTERNAL_CLOCK:
                case ClockSource::N0_CLOCK:
                    return false;
                default:
                    assert(false && "invalid clock source");
                    return false;
            }

        case PeripheralWithSelectableClockSource::SINGLE_WIRE:
            switch (clock_source)
            {
                case ClockSource::PCLK1:
                case ClockSource::HSI16:
                    return true;
                case ClockSource::PLL_SAI_CLOCK:
                case ClockSource::PLL_P_CLOCK:
                case ClockSource::SAI_EXTERNAL_CLOCK:
                case ClockSource::PCLK:
                case ClockSource::SYSTEM_CLOCK:
                case ClockSource::LSI:
                case ClockSource::MSI:
                case ClockSource::HSI48:
                case ClockSource::LSE:
                case ClockSource::HSE:
                case ClockSource::PLL_ADC_CLOCK:
                case ClockSource::PLL_48_M1_CLOCK:
                case ClockSource::PLL_48_M2_CLOCK:
                case ClockSource::N0_CLOCK:
                    return false;
                default:
                    assert(false && "invalid clock source");
                    return false;
            }

        case PeripheralWithSelectableClockSource::SAI_1:
            switch (clock_source)
            {
                case ClockSource::PLL_SAI_CLOCK:
                case ClockSource::PLL_P_CLOCK:
                case ClockSource::SAI_EXTERNAL_CLOCK:
                    return true;
                case ClockSource::PCLK:
                case ClockSource::SYSTEM_CLOCK:
                case ClockSource::LSI:
                case ClockSource::MSI:
                case ClockSource::HSI16:
                case ClockSource::HSI48:
                case ClockSource::LSE:
                case ClockSource::HSE:
                case ClockSource::PCLK1:
                case ClockSource::PLL_ADC_CLOCK:
                case ClockSource::PLL_48_M1_CLOCK:
                case ClockSource::PLL_48_M2_CLOCK:
                case ClockSource::N0_CLOCK:
                    return false;
                default:
                    assert(false && "invalid clock source");
                    return false;
            }
        case PeripheralWithSelectableClockSource::RTC_1:
            switch (clock_source)
            {
                case ClockSource::N0_CLOCK:
                case ClockSource::LSE:
                case ClockSource::LSI:
                case ClockSource::HSE:
                    return true;
                case ClockSource::PCLK:
                case ClockSource::SYSTEM_CLOCK:
                case ClockSource::MSI:
                case ClockSource::HSI16:
                case ClockSource::HSI48:
                case ClockSource::PCLK1:
                case ClockSource::PLL_ADC_CLOCK:
                case ClockSource::PLL_48_M1_CLOCK:
                case ClockSource::PLL_48_M2_CLOCK:
                    return false;
                default:
                    assert(false && "invalid clock source");
                    return false;
            }
        default:
            assert(false && "Unsupported peripheral.");
            return false;
    };
}

uint8_t to_peripheral_clock_select_field_length(PeripheralWithSelectableClockSource peripheral)
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
        case PeripheralWithSelectableClockSource::I2C_4:
        case PeripheralWithSelectableClockSource::LOW_POWER_TIMER_1:
        case PeripheralWithSelectableClockSource::LOW_POWER_TIMER_2:
        case PeripheralWithSelectableClockSource::SAI_1:
        case PeripheralWithSelectableClockSource::CLK_48MHZ:
        case PeripheralWithSelectableClockSource::ADC:
        case PeripheralWithSelectableClockSource::RTC_1:
            return 2;
        case PeripheralWithSelectableClockSource::SINGLE_WIRE:
            return 1;
        default:
            assert(false && "Unsupported peripheral.");
            return 0;
    };
}

Peripheral to_peripheral(I2C_Types::I2CNumber i2c)
{
    switch (i2c)
    {
        case I2C_Types::I2CNumber::I2C_1:
            return Peripheral::I2C_1;
        case I2C_Types::I2CNumber::I2C_2:
            return Peripheral::I2C_2;
        case I2C_Types::I2CNumber::I2C_3:
            return Peripheral::I2C_3;
        case I2C_Types::I2CNumber::I2C_4:
            return Peripheral::I2C_4;
        default:
            assert(false && "Invalid I2C.");
            return Peripheral::I2C_1;
    };
}

uint8_t to_bit_position(I2C_Types::Interrupt interrupt)
{
    switch (interrupt)
    {
        case I2C_Types::Interrupt::TransmitInterrupt:
            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::Interrupt::ReceiveInterrupt:
            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::Interrupt::AddressMatchInterrupt:
            return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::Interrupt::NAKReceivedInterrupt:
            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::Interrupt::STOPDetectedInterrupt:
            return 5;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::Interrupt::TransferCompletedInterrupt:
            return 6;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::Interrupt::ErrorDetectedInterrupt:
            return 7;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        default:
            assert(false && "invalid I2C_Types::Interrupt");
            return 0;
    };
}

uint8_t to_bit_position(I2C_Types::DMARequest request)
{
    switch (request)
    {
        case I2C_Types::DMARequest::Transmit:
            return 14;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::DMARequest::Receive:
            return 15;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        default:
            assert(false && "invalid dma request");
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    };
}

uint8_t to_bit_position(I2C_Types::Option option)
{
    switch (option)
    {

        case I2C_Types::Option::AutoEnd:
            return 25;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::Option::Reload:
            return 24;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        default:
            assert(false && "invalid option");
            return 0;
    };
}

uint32_t to_value(I2C_Types::DigitalFilter digital_filter)
{
    switch (digital_filter)
    {
        case I2C_Types::DigitalFilter::Disabled:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::DigitalFilter::Clock1:
            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::DigitalFilter::Clock2:
            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::DigitalFilter::Clock3:
            return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::DigitalFilter::Clock4:
            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::DigitalFilter::Clock5:
            return 5;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::DigitalFilter::Clock6:
            return 6;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::DigitalFilter::Clock7:
            return 7;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::DigitalFilter::Clock8:
            return 8;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::DigitalFilter::Clock9:
            return 9;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::DigitalFilter::Clock10:
            return 10;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::DigitalFilter::Clock11:
            return 11;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::DigitalFilter::Clock12:
            return 12;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::DigitalFilter::Clock13:
            return 13;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::DigitalFilter::Clock14:
            return 14;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case I2C_Types::DigitalFilter::Clock15:
            return 15;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        default:
            assert(false && "invalid digital filter");
            return 0;
    };
}

uint32_t to_value(SPI_types::BaudRatePrescaller baudrate_prescaller)
{
    switch (baudrate_prescaller)
    {
        case SPI_types::BaudRatePrescaller::Prescaller_2:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case SPI_types::BaudRatePrescaller::Prescaller_4:
            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case SPI_types::BaudRatePrescaller::Prescaller_8:
            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case SPI_types::BaudRatePrescaller::Prescaller_16:
            return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case SPI_types::BaudRatePrescaller::Prescaller_32:
            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case SPI_types::BaudRatePrescaller::Prescaller_64:
            return 5;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case SPI_types::BaudRatePrescaller::Prescaller_128:
            return 6;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case SPI_types::BaudRatePrescaller::Prescaller_256:
            return 7;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        default:
            assert(false && "invalid baudrate prescaller");
            return 0;
    };
}

uint32_t to_value(Power_Types::WriteProtectionState state)
{
    switch (state)
    {
        case Power_Types::WriteProtectionState::Disabled:
            return 1;
        case Power_Types::WriteProtectionState::Enabled:
            return 0;
        default:
            assert(false && "Invalid state.");
            return 0;
    };
}

uint32_t to_value(I2C_Types::TransferDirection transfer_direction)
{
    switch (transfer_direction)
    {
        case I2C_Types::TransferDirection::WRITE:
            return 0;
        case I2C_Types::TransferDirection::READ:
            return 1;
        default:
            assert(false && "Invalid transfer direction.");
            return 0;
    };
}

PeripheralWithSelectableClockSource to_peripheral_with_clock_select(I2C_Types::I2CNumber i2c)
{
    switch (i2c)
    {
        case I2C_Types::I2CNumber::I2C_1:
            return PeripheralWithSelectableClockSource::I2C_1;
        case I2C_Types::I2CNumber::I2C_2:
            return PeripheralWithSelectableClockSource::I2C_2;
        case I2C_Types::I2CNumber::I2C_3:
            return PeripheralWithSelectableClockSource::I2C_3;
        case I2C_Types::I2CNumber::I2C_4:
            return PeripheralWithSelectableClockSource::I2C_4;
        default:
            assert(false && "Invalid I2C.");
            return PeripheralWithSelectableClockSource::I2C_1;
    };
}

Peripheral to_peripheral(DMA_Types::DmaNumber dma)
{
    switch (dma)
    {
        case DMA_Types::DmaNumber::DMA_1:
            return Peripheral::DMA_1;
        case DMA_Types::DmaNumber::DMA_2:
            return Peripheral::DMA_2;
        default:
            assert(false && "Invalid dma.");
            return Peripheral::DMA_1;
    }
}

uint8_t to_bit_position(DMA_Types::Interrupt interrupt)
{
    switch (interrupt)
    {
        case DMA_Types::Interrupt::TransferCompleted:
            return 1;
        case DMA_Types::Interrupt::HalfTransfer:
            return 2;
        case DMA_Types::Interrupt::TransferError:
            return 3;
        default:
            assert(false && "invalid dma interrupt");
            return 0;
    }
}

uint8_t to_bit_position(DMA_Types::Channel channel, DMA_Types::Interrupt interrupt)
{
    uint8_t return_value{0};

    switch (channel)
    {
        case DMA_Types::Channel::Channel1:
            return_value = 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            break;
        case DMA_Types::Channel::Channel2:
            return_value = 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            break;
        case DMA_Types::Channel::Channel3:
            return_value = 8;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            break;
        case DMA_Types::Channel::Channel4:
            return_value = 12;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            break;
        case DMA_Types::Channel::Channel5:
            return_value = 16;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            break;
        case DMA_Types::Channel::Channel6:
            return_value = 20;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            break;
        case DMA_Types::Channel::Channel7:
            return_value = 24;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            break;
        default:
            assert(false && "invalid dma channel");
            return 0;
    }

    switch (interrupt)
    {
        case DMA_Types::Interrupt::TransferCompleted:
            return return_value + 1;
        case DMA_Types::Interrupt::HalfTransfer:
            return return_value + 2;
        case DMA_Types::Interrupt::TransferError:
            return return_value + 3;
        default:
            assert(false && "invalid dma interrupt");
            return 0;
    }
}

uint8_t to_bit_position(timer_types::Interrupt interrupt)
{
    switch (interrupt)
    {
        case timer_types::Interrupt::CAPTURE_COMPARE_1:
            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case timer_types::Interrupt::CAPTURE_COMPARE_2:
            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case timer_types::Interrupt::CAPTURE_COMPARE_3:
            return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case timer_types::Interrupt::CAPTURE_COMPARE_4:
            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case timer_types::Interrupt::CAPTURE_COMPARE_OVERCAPTURE_1:
            return 9;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case timer_types::Interrupt::CAPTURE_COMPARE_OVERCAPTURE_2:
            return 10;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case timer_types::Interrupt::CAPTURE_COMPARE_OVERCAPTURE_3:
            return 11;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case timer_types::Interrupt::CAPTURE_COMPARE_OVERCAPTURE_4:
            return 12;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case timer_types::Interrupt::TRIGGER:
            return 6;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case timer_types::Interrupt::UPDATE:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        default:
            assert(false && "invalid timer interrupt");
            return 0;
    }
}

uint8_t to_start_position(DMA_Types::Channel channel)
{
    switch (channel)
    {
        case DMA_Types::Channel::Channel1:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case DMA_Types::Channel::Channel2:
            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case DMA_Types::Channel::Channel3:
            return 8;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case DMA_Types::Channel::Channel4:
            return 12;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case DMA_Types::Channel::Channel5:
            return 16;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case DMA_Types::Channel::Channel6:
            return 20;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case DMA_Types::Channel::Channel7:
            return 24;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        default:
            assert(false && "invalid dma channel");
            return 0;
    };
}

uint8_t to_bit_position(I2C_Types::I2CNumber number, I2C_Types::Mode mode)
{
    switch (mode)
    {
        case I2C_Types::Mode::FAST_PLUS:

            switch (number)
            {
                case I2C_Types::I2CNumber::I2C_1:
                    return 20;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case I2C_Types::I2CNumber::I2C_2:
                    return 21;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case I2C_Types::I2CNumber::I2C_3:
                    return 22;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                case I2C_Types::I2CNumber::I2C_4:
                    return 23;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                default:
                    assert(false && "invalid i2c");
                    return 0;
            }
        case I2C_Types::Mode::FAST:
        case I2C_Types::Mode::STANDARD:
            assert(false && "mode does not need to be set");
            return 0;
        default:
            assert(false && "invalid mode");
            return 0;
    };
}

uint8_t to_bit_position(GPIO_Types::Port port, uint8_t pin_number, I2C_Types::Mode mode)
{
    switch (mode)
    {
        case I2C_Types::Mode::FAST_PLUS:

            switch (port)
            {
                case GPIO_Types::Port::B:
                    switch (pin_number)
                    {
                        case 6:         // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                            return 16;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case 7:         // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                            return 17;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case 8:         // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                            return 18;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case 9:         // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                            return 19;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        default:
                            assert(false && "mode does not need to be set");
                            return 0;
                    }
                case GPIO_Types::Port::A:
                case GPIO_Types::Port::C:
                case GPIO_Types::Port::D:
                case GPIO_Types::Port::E:
                    assert(false && "mode does not need to be set");
                    return 0;
                default:
                    assert(false && "invalid port");
                    return 0;
            }
        case I2C_Types::Mode::FAST:
        case I2C_Types::Mode::STANDARD:
            assert(false && "mode does not need to be set");
            return 0;
        default:
            assert(false && "invalid mode");
            return 0;
    }
}

uint32_t to_value(DMA_Types::Priority priority)
{
    switch (priority)
    {
        case DMA_Types::Priority::Low:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case DMA_Types::Priority::Medium:
            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case DMA_Types::Priority::High:
            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case DMA_Types::Priority::VeryHigh:
            return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        default:
            assert(false && "invalid dma priority");
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    }
}

uint32_t to_value(DMA_Types::DataSize memory_size)
{
    switch (memory_size)
    {
        case DMA_Types::DataSize::Bits8:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case DMA_Types::DataSize::Bits16:
            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case DMA_Types::DataSize::Bits32:
            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        default:
            assert(false && "invalid size");
            return 0;
    }
}

uint32_t to_value(DMA_Types::ReadDirection read_direction)
{
    switch (read_direction)
    {
        case DMA_Types::ReadDirection::ReadFromPeripheral:
            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        case DMA_Types::ReadDirection::ReadFromMemory:
            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        default:
            assert(false && "invalid read direction");
            return 0;
    }
}

bool is_request_valid(DMA_Types::DmaNumber dma_number, DMA_Types::Channel channel, DMA_Types::Request request)
{
    switch (dma_number)
    {
        case DMA_Types::DmaNumber::DMA_1:
            switch (channel)
            {
                case DMA_Types::Channel::Channel1:
                    switch (request)
                    {
                        case DMA_Types::Request::ADC_1:
                        case DMA_Types::Request::TIM_2_CH3:
                            return true;
                        default:
                            return false;
                    }
                case DMA_Types::Channel::Channel2:
                    switch (request)
                    {
                        case DMA_Types::Request::ADC_2:
                        case DMA_Types::Request::SPI_1_RX:
                        case DMA_Types::Request::USART_3_TX:
                        case DMA_Types::Request::I2C_3_TX:
                        case DMA_Types::Request::TIM_2_UP:
                        case DMA_Types::Request::TIM_3_CH3:
                        case DMA_Types::Request::TIM_1_CH1:
                            return true;
                        default:
                            return false;
                    }
                case DMA_Types::Channel::Channel3:
                    switch (request)
                    {
                        case DMA_Types::Request::SPI_1_TX:
                        case DMA_Types::Request::USART_3_RX:
                        case DMA_Types::Request::I2C_3_RX:
                        case DMA_Types::Request::TIM_16_CH1:
                        case DMA_Types::Request::TIM_16_UP:
                        case DMA_Types::Request::TIM_3_CH4:
                        case DMA_Types::Request::TIM_3_UP:
                        case DMA_Types::Request::TIM_6_UP:
                        case DMA_Types::Request::DAC_CH1:
                        case DMA_Types::Request::TIM_1_CH2:
                            return true;
                        default:
                            return false;
                    }
                case DMA_Types::Channel::Channel4:
                    switch (request)
                    {
                        case DMA_Types::Request::DFSDM_1_FLT0:
                        case DMA_Types::Request::SPI_2_RX:
                        case DMA_Types::Request::USART_1_TX:
                        case DMA_Types::Request::I2C_2_TX:
                        case DMA_Types::Request::TIM_7_UP:
                        case DMA_Types::Request::DAC_CH2:
                        case DMA_Types::Request::TIM_1_CH4:
                        case DMA_Types::Request::TIM_1_TRIG:
                        case DMA_Types::Request::TIM_1_COM:
                            return true;
                        default:
                            return false;
                    }
                case DMA_Types::Channel::Channel5:
                    switch (request)
                    {
                        case DMA_Types::Request::DFSDM_1_FLT1:
                        case DMA_Types::Request::SPI_2_TX:
                        case DMA_Types::Request::USART_1_RX:
                        case DMA_Types::Request::I2C_2_RX:
                        case DMA_Types::Request::TIM_2_CH1:
                        case DMA_Types::Request::QUAD_SPI:
                        case DMA_Types::Request::TIM_15_CH1:
                        case DMA_Types::Request::TIM_15_UP:
                        case DMA_Types::Request::TIM_15_TRIG:
                        case DMA_Types::Request::TIM_15_COM:
                            return true;
                        default:
                            return false;
                    }
                case DMA_Types::Channel::Channel6:
                    switch (request)
                    {
                        case DMA_Types::Request::SAI_1_A:
                        case DMA_Types::Request::USART_2_RX:
                        case DMA_Types::Request::I2C_1_TX:
                        case DMA_Types::Request::TIM_16_CH1:
                        case DMA_Types::Request::TIM_16_UP:
                        case DMA_Types::Request::TIM_3_CH1:
                        case DMA_Types::Request::TIM_3_TRIG:
                        case DMA_Types::Request::TIM_1_UP:
                            return true;
                        default:
                            return false;
                    }
                case DMA_Types::Channel::Channel7:
                    switch (request)
                    {
                        case DMA_Types::Request::SAI_1_B:
                        case DMA_Types::Request::USART_2_TX:
                        case DMA_Types::Request::I2C_1_RX:
                        case DMA_Types::Request::TIM_2_CH2:
                        case DMA_Types::Request::TIM_2_CH4:
                        case DMA_Types::Request::TIM_1_CH3:
                            return true;
                        default:
                            return false;
                    }
                default:
                    return false;
            }
        case DMA_Types::DmaNumber::DMA_2:
            switch (channel)
            {
                case DMA_Types::Channel::Channel1:
                    switch (request)
                    {
                        case DMA_Types::Request::I2C_4_RX:
                        case DMA_Types::Request::SAI_1_A:
                        case DMA_Types::Request::SPI_3_RX:
                        case DMA_Types::Request::SWPMI_1_RX:
                        case DMA_Types::Request::AES_IN:
                            return true;
                        default:
                            return false;
                    }
                case DMA_Types::Channel::Channel2:
                    switch (request)
                    {
                        case DMA_Types::Request::I2C_4_TX:
                        case DMA_Types::Request::SAI_1_B:
                        case DMA_Types::Request::SPI_3_TX:
                        case DMA_Types::Request::SWPMI_1_TX:
                        case DMA_Types::Request::AES_OUT:
                            return true;
                        default:
                            return false;
                    }
                case DMA_Types::Channel::Channel3:
                    switch (request)
                    {
                        case DMA_Types::Request::ADC_1:
                        case DMA_Types::Request::UART_4_RX:
                        case DMA_Types::Request::SPI_1_RX:
                        case DMA_Types::Request::AES_OUT:
                            return true;
                        default:
                            return false;
                    }
                case DMA_Types::Channel::Channel4:
                    switch (request)
                    {
                        case DMA_Types::Request::ADC_2:
                        case DMA_Types::Request::TIM_6_UP:
                        case DMA_Types::Request::DAC_CH1:
                        case DMA_Types::Request::SPI_1_TX:
                        case DMA_Types::Request::SDMMC_1:
                            return true;
                        default:
                            return false;
                    }
                case DMA_Types::Channel::Channel5:
                    switch (request)
                    {
                        case DMA_Types::Request::UART_4_RX:
                        case DMA_Types::Request::TIM_7_UP:
                        case DMA_Types::Request::DAC_CH2:
                        case DMA_Types::Request::AES_IN:
                        case DMA_Types::Request::SDMMC_1:
                            return true;
                        default:
                            return false;
                    }
                case DMA_Types::Channel::Channel6:
                    switch (request)
                    {
                        case DMA_Types::Request::SAI_1_A:
                        case DMA_Types::Request::USART_1_TX:
                        case DMA_Types::Request::LPUART_1_TX:
                        case DMA_Types::Request::I2C_1_RX:
                            return true;
                        default:
                            return false;
                    }
                case DMA_Types::Channel::Channel7:
                    switch (request)
                    {
                        case DMA_Types::Request::SAI_1_B:
                        case DMA_Types::Request::USART_1_RX:
                        case DMA_Types::Request::QUAD_SPI:
                        case DMA_Types::Request::LPUART_1_RX:
                        case DMA_Types::Request::I2C_1_TX:
                            return true;
                        default:
                            return false;
                    }
                default:
                    return false;
            }
    }
    return false;
}

uint32_t to_value(DMA_Types::DmaNumber dma_number, DMA_Types::Channel channel, DMA_Types::Request request)
{
    switch (dma_number)
    {
        case DMA_Types::DmaNumber::DMA_1:
            switch (channel)
            {
                case DMA_Types::Channel::Channel1:
                    switch (request)
                    {
                        case DMA_Types::Request::ADC_1:
                            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::TIM_2_CH3:
                            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        default:
                            assert(false && "invalid request");
                            return 0;
                    }
                case DMA_Types::Channel::Channel2:
                    switch (request)
                    {
                        case DMA_Types::Request::ADC_2:
                            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::SPI_1_RX:
                            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::USART_3_TX:
                            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::I2C_3_TX:
                            return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::TIM_2_UP:
                            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::TIM_3_CH3:
                            return 5;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::TIM_1_CH1:
                            return 7;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        default:
                            assert(false && "invalid request");
                            return 0;
                    }
                case DMA_Types::Channel::Channel3:
                    switch (request)
                    {
                        case DMA_Types::Request::SPI_1_TX:
                            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::USART_3_RX:
                            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::I2C_3_RX:
                            return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::TIM_16_CH1:
                        case DMA_Types::Request::TIM_16_UP:
                            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::TIM_3_CH4:
                        case DMA_Types::Request::TIM_3_UP:
                            return 5;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::TIM_6_UP:
                        case DMA_Types::Request::DAC_CH1:
                            return 6;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::TIM_1_CH2:
                            return 7;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        default:
                            assert(false && "invalid request");
                            return 0;
                    }
                case DMA_Types::Channel::Channel4:
                    switch (request)
                    {
                        case DMA_Types::Request::DFSDM_1_FLT0:
                            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::SPI_2_RX:
                            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::USART_1_TX:
                            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::I2C_2_TX:
                            return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::TIM_7_UP:
                        case DMA_Types::Request::DAC_CH2:
                            return 5;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::TIM_1_CH4:
                        case DMA_Types::Request::TIM_1_TRIG:
                        case DMA_Types::Request::TIM_1_COM:
                            return 7;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        default:
                            assert(false && "invalid request");
                            return 0;
                    }
                case DMA_Types::Channel::Channel5:
                    switch (request)
                    {
                        case DMA_Types::Request::DFSDM_1_FLT1:
                            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::SPI_2_TX:
                            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::USART_1_RX:
                            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::I2C_2_RX:
                            return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::TIM_2_CH1:
                            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::QUAD_SPI:
                            return 5;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::TIM_15_CH1:
                        case DMA_Types::Request::TIM_15_UP:
                        case DMA_Types::Request::TIM_15_TRIG:
                        case DMA_Types::Request::TIM_15_COM:
                            return 7;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        default:
                            assert(false && "invalid request");
                            return 0;
                    }
                case DMA_Types::Channel::Channel6:
                    switch (request)
                    {
                        case DMA_Types::Request::SAI_1_A:
                            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::USART_2_RX:
                            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::I2C_1_TX:
                            return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::TIM_16_CH1:
                        case DMA_Types::Request::TIM_16_UP:
                            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::TIM_3_CH1:
                        case DMA_Types::Request::TIM_3_TRIG:
                            return 5;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::TIM_1_UP:
                            return 7;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        default:
                            assert(false && "invalid request");
                            return 0;
                    }
                case DMA_Types::Channel::Channel7:
                    switch (request)
                    {
                        case DMA_Types::Request::SAI_1_B:
                            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::USART_2_TX:
                            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::I2C_1_RX:
                            return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::TIM_2_CH2:
                        case DMA_Types::Request::TIM_2_CH4:
                            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::TIM_1_CH3:
                            return 7;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        default:
                            assert(false && "invalid request");
                            return 0;
                    }
                default:
                    assert(false && "invalid channel");
                    return 0;
            }
        case DMA_Types::DmaNumber::DMA_2:
            switch (channel)
            {
                case DMA_Types::Channel::Channel1:
                    switch (request)
                    {
                        case DMA_Types::Request::I2C_4_RX:
                            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::SAI_1_A:
                            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::SPI_3_RX:
                            return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::SWPMI_1_RX:
                            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::AES_IN:
                            return 6;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        default:
                            assert(false && "invalid request");
                            return 0;
                    }
                case DMA_Types::Channel::Channel2:
                    switch (request)
                    {
                        case DMA_Types::Request::I2C_4_TX:
                            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::SAI_1_B:
                            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::SPI_3_TX:
                            return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::SWPMI_1_TX:
                            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::AES_OUT:
                            return 6;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        default:
                            assert(false && "invalid request");
                            return 0;
                    }
                case DMA_Types::Channel::Channel3:
                    switch (request)
                    {
                        case DMA_Types::Request::ADC_1:
                            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::UART_4_RX:
                            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::SPI_1_RX:
                            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::AES_OUT:
                            return 6;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        default:
                            assert(false && "invalid request");
                            return 0;
                    }
                case DMA_Types::Channel::Channel4:
                    switch (request)
                    {
                        case DMA_Types::Request::ADC_2:
                            return 0;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::TIM_6_UP:
                        case DMA_Types::Request::DAC_CH1:
                            return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::SPI_1_TX:
                            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::SDMMC_1:
                            return 7;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        default:
                            assert(false && "invalid request");
                            return 0;
                    }
                case DMA_Types::Channel::Channel5:
                    switch (request)
                    {
                        case DMA_Types::Request::UART_4_RX:
                            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::TIM_7_UP:
                        case DMA_Types::Request::DAC_CH2:
                            return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::AES_IN:
                            return 6;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::SDMMC_1:
                            return 7;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        default:
                            assert(false && "invalid request");
                            return 0;
                    }
                case DMA_Types::Channel::Channel6:
                    switch (request)
                    {
                        case DMA_Types::Request::SAI_1_A:
                            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::USART_1_TX:
                            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::LPUART_1_TX:
                            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::I2C_1_RX:
                            return 5;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        default:
                            assert(false && "invalid request");
                            return 0;
                    }
                case DMA_Types::Channel::Channel7:
                    switch (request)
                    {
                        case DMA_Types::Request::SAI_1_B:
                            return 1;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::USART_1_RX:
                            return 2;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::QUAD_SPI:
                            return 3;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::LPUART_1_RX:
                            return 4;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        case DMA_Types::Request::I2C_1_TX:
                            return 5;  // NOLINT(cppcoreguidelines-avoid-magic-numbers)
                        default:
                            assert(false && "invalid request");
                            return 0;
                    }
                default:
                    assert(false && "invalid channel");
                    return 0;
            }
    }
    assert(false && "invalid DMA");
    return 0;
}