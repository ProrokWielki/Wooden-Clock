#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <HAL/types.hpp>

#include "../../../../src/stm32/HAL/Clock/include/HAL/Clock.hpp"
struct SetClockSourceData {
    PeripheralWithSelectableClockSource peripheral;
    ClockSource clock_source;
    uint8_t expected_value;
    uint8_t expected_position;
    uint8_t expected_length;
};

std::string to_peripheral_name(PeripheralWithSelectableClockSource peripheral)
{
    switch (peripheral)
    {
        case PeripheralWithSelectableClockSource::USART_1:
            return "USART_1";
        case PeripheralWithSelectableClockSource::USART_2:
            return "USART_2";
        case PeripheralWithSelectableClockSource::USART_3:
            return "USART_3";
        case PeripheralWithSelectableClockSource::UART_4:
            return "UART_4";
        case PeripheralWithSelectableClockSource::LOW_POWER_UART_1:
            return "LOW_POWER_UART_1";
        case PeripheralWithSelectableClockSource::I2C_1:
            return "I2C_1";
        case PeripheralWithSelectableClockSource::I2C_2:
            return "I2C_2";
        case PeripheralWithSelectableClockSource::I2C_3:
            return "I2C_3";
        case PeripheralWithSelectableClockSource::I2C_4:
            return "I2C_4";
        case PeripheralWithSelectableClockSource::LOW_POWER_TIMER_1:
            return "LOW_POWER_TIMER_1";
        case PeripheralWithSelectableClockSource::LOW_POWER_TIMER_2:
            return "LOW_POWER_TIMER_2";
        case PeripheralWithSelectableClockSource::SAI_1:
            return "SAI_1";
        case PeripheralWithSelectableClockSource::CLK_48MHZ:
            return "CLK_48MHZ";
        case PeripheralWithSelectableClockSource::ADC:
            return "ADC";
        case PeripheralWithSelectableClockSource::SINGLE_WIRE:
            return "SINGLE_WIRE";
        default:
            assert(false && "Unsupported peripheral");
    };
}

std::string to_clock_source_name(ClockSource clock_source)
{
    switch (clock_source)
    {
        case ClockSource::PCLK:
            return "PCLK";
        case ClockSource::SYSTEM_CLOCK:
            return "SYSTEM_CLOCK";
        case ClockSource::LSI:
            return "LSI";
        case ClockSource::MSI:
            return "MSI";
        case ClockSource::HSI16:
            return "HSI16";
        case ClockSource::HSI48:
            return "HSI48";
        case ClockSource::LSE:
            return "LSE";
        case ClockSource::PCLK1:
            return "PCLK1";
        case ClockSource::PLL_ADC_CLOCK:
            return "PLL_ADC_CLOCK";
        case ClockSource::PLL_48_M1_CLOCK:
            return "PLL_48_M1_CLOCK";
        case ClockSource::PLL_48_M2_CLOCK:
            return "PLL_48_M2_CLOCK";
        case ClockSource::PLL_SAI_CLOCK:
            return "PLL_SAI_CLOCK";
        case ClockSource::PLL_P_CLOCK:
            return "PLL_P_CLOCK";
        case ClockSource::SAI_EXTERNAL_CLOCK:
            return "SAI_EXTERNAL_CLOCK";
        case ClockSource::N0_CLOCK:
            return "N0_CLOCK";
        default:
            assert(false && "Unsupported clock source.");
    };
}

std::string to_peripheral_name(Peripheral peripheral)
{
    switch (peripheral)
    {
        case Peripheral::I2C_1:
            return "I2C_1";
        case Peripheral::I2C_2:
            return "I2C_2";
        case Peripheral::I2C_3:
            return "I2C_3";
        case Peripheral::I2C_4:
            return "I2C_4";
        case Peripheral::USART_1:
            return "USART_1";
        case Peripheral::USART_2:
            return "USART_2";
        case Peripheral::USART_3:
            return "USART_3";
        case Peripheral::UART_4:
            return "UART_4";
        case Peripheral::LOW_POWER_UART_1:
            return "LOW_POWER_UART_1";
        case Peripheral::SPI_1:
            return "SPI_1";
        case Peripheral::SPI_2:
            return "SPI_2";
        case Peripheral::SPI_3:
            return "SPI_3";
        case Peripheral::TIMER_1:
            return "TIMER_1";
        case Peripheral::TIMER_2:
            return "TIMER_2";
        case Peripheral::TIMER_3:
            return "TIMER_3";
        case Peripheral::TIMER_6:
            return "TIMER_6";
        case Peripheral::TIMER_7:
            return "TIMER_7";
        case Peripheral::TIMER_15:
            return "TIMER_15";
        case Peripheral::TIMER_16:
            return "TIMER_16";
        case Peripheral::LOW_POWER_TIMER_1:
            return "LOW_POWER_TIMER_1";
        case Peripheral::LOW_POWER_TIMER_2:
            return "LOW_POWER_TIMER_2";
        case Peripheral::OP_AMP:
            return "OP_AMP";
        case Peripheral::DAC_1:
            return "DAC_1";
        case Peripheral::USB_FS:
            return "USB_FS";
        case Peripheral::CAN_1:
            return "CAN_1";
        case Peripheral::DFSDM_1:
            return "DFSDM_1";
        case Peripheral::SAI_1:
            return "SAI_1";
        case Peripheral::SDMMC_1:
            return "SDMMC_1";
        case Peripheral::FIRE_WALL:
            return "FIRE_WALL";
        case Peripheral::EXTERNAL_FLASH:
            return "EXTERNAL_FLASH";
        case Peripheral::DMA_2:
            return "DMA_2";
        case Peripheral::DMA_1:
            return "DMA_1";
        case Peripheral::ADC:
            return "ADC";
        case Peripheral::GPIO_A:
            return "GPIO_A";
        case Peripheral::GPIO_B:
            return "GPIO_B";
        case Peripheral::GPIO_C:
            return "GPIO_C";
        case Peripheral::GPIO_D:
            return "GPIO_D";
        case Peripheral::GPIO_E:
            return "GPIO_E";
        case Peripheral::GPIO_H:
            return "GPIO_H";
        case Peripheral::QSPI:
            return "QSPI";
        case Peripheral::CRC_UNIT:
            return "CRC_UNIT";
        case Peripheral::TOUCH_SENSE:
            return "TOUCH_SENSE";
        case Peripheral::RANDOM_NUMBER_GENERATOR:
            return "RANDOM_NUMBER_GENERATOR";
        case Peripheral::AES:
            return "AES";
        case Peripheral::LCD:
            return "LCD";
        case Peripheral::RTC_APB:
            return "RTC_APB";
        case Peripheral::WINDOW_WATCHDOG:
            return "WINDOW_WATCHDOG";
        case Peripheral::CLOCK_RECOVERY_SYSTEM:
            return "CLOCK_RECOVERY_SYSTEM";
        case Peripheral::POWER_INTERFACE:
            return "POWER_INTERFACE";
        case Peripheral::SINGLE_WIRE:
            return "SINGLE_WIRE";
        case Peripheral::SYSTEM_CONFIG:
            return "SYSTEM_CONFIG";
        default:
            assert(false && "Unsupported peripheral.");
    };
}

class ClockTestAhb1: public testing::TestWithParam<std::pair<Peripheral, uint8_t>>
{
};
class ClockTestAhb2: public testing::TestWithParam<std::pair<Peripheral, uint8_t>>
{
};
class ClockTestAhb3: public testing::TestWithParam<std::pair<Peripheral, uint8_t>>
{
};
class ClockTestApb1_1: public testing::TestWithParam<std::pair<Peripheral, uint8_t>>
{
};
class ClockTestApb1_2: public testing::TestWithParam<std::pair<Peripheral, uint8_t>>
{
};
class ClockTestApb2: public testing::TestWithParam<std::pair<Peripheral, uint8_t>>
{
};
class ClockTestCciprValidClockSource: public testing::TestWithParam<SetClockSourceData>
{
};
class ClockTestCcipr2ValidClockSource: public testing::TestWithParam<SetClockSourceData>
{
};
class ClockTestInvalidClockSource: public testing::TestWithParam<SetClockSourceData>
{
};

TEST_P(ClockTestAhb1, EnableClock)
{
    Clock sut{};

    EXPECT_CALL(sut.AHB1, set_bit(GetParam().second));

    sut.enable_clock_for(GetParam().first);
}

TEST_P(ClockTestAhb2, EnableClock)
{
    Clock sut{};

    EXPECT_CALL(sut.AHB2, set_bit(GetParam().second));

    sut.enable_clock_for(GetParam().first);
}

TEST_P(ClockTestAhb3, EnableClock)
{
    Clock sut{};

    EXPECT_CALL(sut.AHB3, set_bit(GetParam().second));

    sut.enable_clock_for(GetParam().first);
}

TEST_P(ClockTestApb1_1, EnableClock)
{
    Clock sut{};

    EXPECT_CALL(sut.APB1_1, set_bit(GetParam().second));

    sut.enable_clock_for(GetParam().first);
}

TEST_P(ClockTestApb1_2, EnableClock)
{
    Clock sut{};

    EXPECT_CALL(sut.APB1_2, set_bit(GetParam().second));

    sut.enable_clock_for(GetParam().first);
}

TEST_P(ClockTestApb2, EnableClock)
{
    Clock sut{};

    EXPECT_CALL(sut.APB2, set_bit(GetParam().second));

    sut.enable_clock_for(GetParam().first);
}

TEST_P(ClockTestCciprValidClockSource, SetClockSource)
{
    Clock sut{};

    EXPECT_CALL(sut.CCIPR, set_value(GetParam().expected_value, GetParam().expected_position, GetParam().expected_length));

    sut.set_clock_source_for(GetParam().peripheral, GetParam().clock_source);
}

TEST_P(ClockTestCcipr2ValidClockSource, SetClockSource)
{
    Clock sut{};

    EXPECT_CALL(sut.CCIPR2, set_value(GetParam().expected_value, GetParam().expected_position, GetParam().expected_length));

    sut.set_clock_source_for(GetParam().peripheral, GetParam().clock_source);
}

TEST_P(ClockTestInvalidClockSource, SetClockSource)
{
    Clock sut{};

    EXPECT_DEATH(sut.set_clock_source_for(GetParam().peripheral, GetParam().clock_source), "");
}

INSTANTIATE_TEST_SUITE_P(Ahb1, ClockTestAhb1,
                         testing::Values(std::make_pair<Peripheral, uint8_t>(Peripheral::DMA_1, 0), std::make_pair<Peripheral, uint8_t>(Peripheral::DMA_2, 1),
                                         std::make_pair<Peripheral, uint8_t>(Peripheral::EXTERNAL_FLASH, 8),
                                         std::make_pair<Peripheral, uint8_t>(Peripheral::CRC_UNIT, 12),
                                         std::make_pair<Peripheral, uint8_t>(Peripheral::TOUCH_SENSE, 16)));

INSTANTIATE_TEST_SUITE_P(Ahb2, ClockTestAhb2,
                         testing::Values(std::make_pair<Peripheral, uint8_t>(Peripheral::GPIO_A, 0), std::make_pair<Peripheral, uint8_t>(Peripheral::GPIO_B, 1),
                                         std::make_pair<Peripheral, uint8_t>(Peripheral::GPIO_C, 2), std::make_pair<Peripheral, uint8_t>(Peripheral::GPIO_D, 3),
                                         std::make_pair<Peripheral, uint8_t>(Peripheral::GPIO_E, 4), std::make_pair<Peripheral, uint8_t>(Peripheral::GPIO_H, 7),
                                         std::make_pair<Peripheral, uint8_t>(Peripheral::ADC, 13), std::make_pair<Peripheral, uint8_t>(Peripheral::AES, 16),
                                         std::make_pair<Peripheral, uint8_t>(Peripheral::RANDOM_NUMBER_GENERATOR, 18)));

INSTANTIATE_TEST_SUITE_P(Ahb3, ClockTestAhb3, testing::Values(std::make_pair<Peripheral, uint8_t>(Peripheral::QSPI, 8)),
                         [](const testing::TestParamInfo<std::pair<Peripheral, uint8_t>> & info) { return to_peripheral_name(info.param.first); });

INSTANTIATE_TEST_SUITE_P(
Apb1_1, ClockTestApb1_1,
testing::Values(std::make_pair<Peripheral, uint8_t>(Peripheral::TIMER_2, 0), std::make_pair<Peripheral, uint8_t>(Peripheral::TIMER_3, 1),
                std::make_pair<Peripheral, uint8_t>(Peripheral::TIMER_6, 4), std::make_pair<Peripheral, uint8_t>(Peripheral::TIMER_7, 5),
                std::make_pair<Peripheral, uint8_t>(Peripheral::LCD, 9), std::make_pair<Peripheral, uint8_t>(Peripheral::RTC_APB, 10),
                std::make_pair<Peripheral, uint8_t>(Peripheral::WINDOW_WATCHDOG, 11), std::make_pair<Peripheral, uint8_t>(Peripheral::SPI_2, 14),
                std::make_pair<Peripheral, uint8_t>(Peripheral::SPI_3, 15), std::make_pair<Peripheral, uint8_t>(Peripheral::USART_2, 17),
                std::make_pair<Peripheral, uint8_t>(Peripheral::USART_3, 18), std::make_pair<Peripheral, uint8_t>(Peripheral::UART_4, 19),
                std::make_pair<Peripheral, uint8_t>(Peripheral::I2C_1, 21), std::make_pair<Peripheral, uint8_t>(Peripheral::I2C_2, 22),
                std::make_pair<Peripheral, uint8_t>(Peripheral::I2C_3, 23), std::make_pair<Peripheral, uint8_t>(Peripheral::CLOCK_RECOVERY_SYSTEM, 24),
                std::make_pair<Peripheral, uint8_t>(Peripheral::CAN_1, 25), std::make_pair<Peripheral, uint8_t>(Peripheral::USB_FS, 26),
                std::make_pair<Peripheral, uint8_t>(Peripheral::POWER_INTERFACE, 28), std::make_pair<Peripheral, uint8_t>(Peripheral::DAC_1, 29),
                std::make_pair<Peripheral, uint8_t>(Peripheral::OP_AMP, 30), std::make_pair<Peripheral, uint8_t>(Peripheral::LOW_POWER_TIMER_1, 31)),
[](const testing::TestParamInfo<std::pair<Peripheral, uint8_t>> & info) { return to_peripheral_name(info.param.first); });

INSTANTIATE_TEST_SUITE_P(Apb1_1, ClockTestApb1_2,
                         testing::Values(std::make_pair<Peripheral, uint8_t>(Peripheral::LOW_POWER_UART_1, 0),
                                         std::make_pair<Peripheral, uint8_t>(Peripheral::I2C_4, 1),
                                         std::make_pair<Peripheral, uint8_t>(Peripheral::SINGLE_WIRE, 2),
                                         std::make_pair<Peripheral, uint8_t>(Peripheral::LOW_POWER_TIMER_2, 5)),
                         [](const testing::TestParamInfo<std::pair<Peripheral, uint8_t>> & info) { return to_peripheral_name(info.param.first); });

INSTANTIATE_TEST_SUITE_P(
Apb2, ClockTestApb2,
testing::Values(std::make_pair<Peripheral, uint8_t>(Peripheral::SYSTEM_CONFIG, 0), std::make_pair<Peripheral, uint8_t>(Peripheral::FIRE_WALL, 7),
                std::make_pair<Peripheral, uint8_t>(Peripheral::SDMMC_1, 10), std::make_pair<Peripheral, uint8_t>(Peripheral::TIMER_1, 11),
                std::make_pair<Peripheral, uint8_t>(Peripheral::SPI_1, 12), std::make_pair<Peripheral, uint8_t>(Peripheral::USART_1, 14),
                std::make_pair<Peripheral, uint8_t>(Peripheral::TIMER_15, 16), std::make_pair<Peripheral, uint8_t>(Peripheral::TIMER_16, 17),
                std::make_pair<Peripheral, uint8_t>(Peripheral::SAI_1, 21), std::make_pair<Peripheral, uint8_t>(Peripheral::DFSDM_1, 24)),
[](const testing::TestParamInfo<std::pair<Peripheral, uint8_t>> & info) { return to_peripheral_name(info.param.first); });

INSTANTIATE_TEST_SUITE_P(Ccipr, ClockTestCciprValidClockSource,
                         testing::Values(SetClockSourceData{PeripheralWithSelectableClockSource::SINGLE_WIRE, ClockSource::HSI16, 1, 30, 1},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::SINGLE_WIRE, ClockSource::PCLK1, 0, 30, 1},

                                         SetClockSourceData{PeripheralWithSelectableClockSource::ADC, ClockSource::N0_CLOCK, 0, 28, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::ADC, ClockSource::PLL_ADC_CLOCK, 1, 28, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::ADC, ClockSource::SYSTEM_CLOCK, 3, 28, 2},

                                         SetClockSourceData{PeripheralWithSelectableClockSource::LOW_POWER_TIMER_2, ClockSource::PCLK, 0, 20, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::LOW_POWER_TIMER_2, ClockSource::LSI, 1, 20, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::LOW_POWER_TIMER_2, ClockSource::HSI16, 2, 20, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::LOW_POWER_TIMER_2, ClockSource::LSE, 3, 20, 2},

                                         SetClockSourceData{PeripheralWithSelectableClockSource::LOW_POWER_TIMER_1, ClockSource::PCLK, 0, 18, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::LOW_POWER_TIMER_1, ClockSource::LSI, 1, 18, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::LOW_POWER_TIMER_1, ClockSource::HSI16, 2, 18, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::LOW_POWER_TIMER_1, ClockSource::LSE, 3, 18, 2},

                                         SetClockSourceData{PeripheralWithSelectableClockSource::I2C_3, ClockSource::PCLK, 0, 16, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::I2C_3, ClockSource::SYSTEM_CLOCK, 1, 16, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::I2C_3, ClockSource::HSI16, 2, 16, 2},

                                         SetClockSourceData{PeripheralWithSelectableClockSource::I2C_2, ClockSource::PCLK, 0, 14, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::I2C_2, ClockSource::SYSTEM_CLOCK, 1, 14, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::I2C_2, ClockSource::HSI16, 2, 14, 2},

                                         SetClockSourceData{PeripheralWithSelectableClockSource::I2C_1, ClockSource::PCLK, 0, 12, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::I2C_1, ClockSource::SYSTEM_CLOCK, 1, 12, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::I2C_1, ClockSource::HSI16, 2, 12, 2},

                                         SetClockSourceData{PeripheralWithSelectableClockSource::LOW_POWER_UART_1, ClockSource::PCLK, 0, 10, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::LOW_POWER_UART_1, ClockSource::SYSTEM_CLOCK, 1, 10, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::LOW_POWER_UART_1, ClockSource::HSI16, 2, 10, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::LOW_POWER_UART_1, ClockSource::LSE, 3, 10, 2},

                                         SetClockSourceData{PeripheralWithSelectableClockSource::UART_4, ClockSource::PCLK, 0, 6, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::UART_4, ClockSource::SYSTEM_CLOCK, 1, 6, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::UART_4, ClockSource::HSI16, 2, 6, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::UART_4, ClockSource::LSE, 3, 6, 2},

                                         SetClockSourceData{PeripheralWithSelectableClockSource::USART_3, ClockSource::PCLK, 0, 4, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::USART_3, ClockSource::SYSTEM_CLOCK, 1, 4, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::USART_3, ClockSource::HSI16, 2, 4, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::USART_3, ClockSource::LSE, 3, 4, 2},

                                         SetClockSourceData{PeripheralWithSelectableClockSource::USART_2, ClockSource::PCLK, 0, 2, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::USART_2, ClockSource::SYSTEM_CLOCK, 1, 2, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::USART_2, ClockSource::HSI16, 2, 2, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::USART_2, ClockSource::LSE, 3, 2, 2},

                                         SetClockSourceData{PeripheralWithSelectableClockSource::USART_1, ClockSource::PCLK, 0, 0, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::USART_1, ClockSource::SYSTEM_CLOCK, 1, 0, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::USART_1, ClockSource::HSI16, 2, 0, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::USART_1, ClockSource::LSE, 3, 0, 2},

                                         SetClockSourceData{PeripheralWithSelectableClockSource::SAI_1, ClockSource::PLL_SAI_CLOCK, 0, 22, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::SAI_1, ClockSource::PLL_P_CLOCK, 2, 22, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::SAI_1, ClockSource::SAI_EXTERNAL_CLOCK, 3, 22, 2},

                                         SetClockSourceData{PeripheralWithSelectableClockSource::CLK_48MHZ, ClockSource::HSI48, 0, 26, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::CLK_48MHZ, ClockSource::PLL_48_M2_CLOCK, 1, 26, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::CLK_48MHZ, ClockSource::PLL_48_M1_CLOCK, 2, 26, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::CLK_48MHZ, ClockSource::MSI, 3, 26, 2}),
                         [](const testing::TestParamInfo<SetClockSourceData> & info) {
                             return to_peripheral_name(info.param.peripheral) + "___" + to_clock_source_name(info.param.clock_source);
                         });

INSTANTIATE_TEST_SUITE_P(Ccipr2, ClockTestCcipr2ValidClockSource,
                         testing::Values(SetClockSourceData{PeripheralWithSelectableClockSource::I2C_4, ClockSource::SYSTEM_CLOCK, 1, 0, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::I2C_4, ClockSource::PCLK, 0, 0, 2},
                                         SetClockSourceData{PeripheralWithSelectableClockSource::I2C_4, ClockSource::HSI16, 2, 0, 2}),
                         [](const testing::TestParamInfo<SetClockSourceData> & info) {
                             return to_peripheral_name(info.param.peripheral) + "___" + to_clock_source_name(info.param.clock_source);
                         });

INSTANTIATE_TEST_SUITE_P(InvalidClockSources, ClockTestInvalidClockSource,
                         testing::Values(SetClockSourceData{PeripheralWithSelectableClockSource::I2C_4, ClockSource::LSE, 0, 0, 0}),
                         [](const testing::TestParamInfo<SetClockSourceData> & info) {
                             return to_peripheral_name(info.param.peripheral) + "___" + to_clock_source_name(info.param.clock_source);
                         });