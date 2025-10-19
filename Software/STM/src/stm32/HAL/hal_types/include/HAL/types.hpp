/**
 * @file types.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-12
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include <cstdint>

namespace GPIO_Types
{

/// Stores possible modes of any GPIO
enum class PortMode
{
    Input = 0,      //!< Input
    Output = 1,     //!< Output
    Alternate = 2,  //!< Alternate
    Analog = 3      //!< Analog
};

/// Stores possible output types of any GPIO
enum class PortOutputType
{
    PushPull,  //!< Push-Pull output
    OpenDrain  //!< Open drain output
};

/// Stores possible output speeds of any GPIO
enum class PortOutputSpeed
{
    Low,      //!< Low speed
    Medium,   //!< Medium speed
    High,     //!< High speed
    VeryHigh  //!<  Very high speed

};

/// Stores possible pulling resistors configuration of any GPIO
enum class PortPullUpPullDown
{
    None,     //!< No pulling resistor
    PullUp,   //!< Pull up resistor
    PullDown  //!< Pull down resistor

};

/// Stores possible alternate functions of any GPIO
enum class AlternateFunction
{
    AF0,   //!< Alternate function 0
    AF1,   //!< Alternate function 1
    AF2,   //!< Alternate function 2
    AF3,   //!< Alternate function 3
    AF4,   //!< Alternate function 4
    AF5,   //!< Alternate function 5
    AF6,   //!< Alternate function 6
    AF7,   //!< Alternate function 7
    AF8,   //!< Alternate function 8
    AF9,   //!< Alternate function 9
    AF10,  //!< Alternate function 10
    AF11,  //!< Alternate function 11
    AF12,  //!< Alternate function 12
    AF13,  //!< Alternate function 13
    AF14,  //!< Alternate function 14
    AF15   //!< Alternate function 15

};

/// Stores possible logical states of any GPIO
enum class SignalLevel
{
    Low,  //!< Low state
    High  //!< High state
};

/// Stores possible GPIO Ports
enum class Port
{
    A,  //!< PortA
    B,  //!< PortB
    C,  //!< PortC
    D,  //!< PortD
    E,  //!< PortE

};

enum class PortRegister
{
    MODER,
    OTYPER,
    OSPEEDR,
    PUPDR,
    AFRL,
    AFRH,
    BSRR,
    BRR,
    ODR,
    IDR
};

}  // namespace GPIO_Types

enum class Peripheral
{
    I2C_1,
    I2C_2,
    I2C_3,
    I2C_4,
    USART_1,
    USART_2,
    USART_3,
    UART_4,
    LOW_POWER_UART_1,
    SPI_1,
    SPI_2,
    SPI_3,
    TIMER_1,
    TIMER_2,
    TIMER_3,
    TIMER_6,
    TIMER_7,
    TIMER_15,
    TIMER_16,
    LOW_POWER_TIMER_1,
    LOW_POWER_TIMER_2,
    OP_AMP,
    DAC_1,
    USB_FS,
    CAN_1,
    DFSDM_1,
    SAI_1,
    SDMMC_1,
    FIRE_WALL,
    EXTERNAL_FLASH,
    DMA_2,
    DMA_1,
    ADC,
    GPIO_A,
    GPIO_B,
    GPIO_C,
    GPIO_D,
    GPIO_E,
    GPIO_H,
    QSPI,
    CRC_UNIT,
    TOUCH_SENSE,
    RANDOM_NUMBER_GENERATOR,
    AES,
    LCD,
    RTC_APB,
    RTC_1,
    WINDOW_WATCHDOG,
    CLOCK_RECOVERY_SYSTEM,
    POWER_INTERFACE,
    SINGLE_WIRE,
    SYSTEM_CONFIG
};

enum class ClockRegister
{
    AHB1,
    AHB2,
    AHB3,
    APB1_1,
    APB1_2,
    APB2,
    PLL_CONFIG,
    CCIPR,
    CCIPR2,
    BDCR,
    CR
};

enum class PllSource
{
    NoClock,
    MSI,
    HSI16,
    HSE,
};

enum class PllDivisionFactor
{
    Division1,
    Division2,
    Division3,
    Division4,
    Division5,
    Division6,
    Division7,
    Division8,
};

enum class PllPDivisionFactor
{
    Division7,
    Division17,
};

enum class Pll48DivisionFactor
{
    Division2,
    Division4,
    Division6,
    Division8,
};

enum class PllClkDivisionFactor
{
    Division2,
    Division4,
    Division6,
    Division8,
};

enum class VcoDivisionFactor
{
    PLLP_Control,
    Division2,
    Division3,
    Division4,
    Division5,
    Division6,
    Division7,
    Division8,
    Division9,
    Division10,
    Division11,
    Division12,
    Division13,
    Division14,
    Division15,
    Division16,
    Division17,
    Division18,
    Division19,
    Division20,
    Division21,
    Division22,
    Division23,
    Division24,
    Division25,
    Division26,
    Division27,
    Division28,
    Division29,
    Division30,
    Division31,
};

enum class ClockSource
{
    PCLK,
    SYSTEM_CLOCK,
    LSI,
    MSI,
    HSI16,
    HSI48,
    HSE,
    LSE,
    PCLK1,
    PLL_ADC_CLOCK,
    PLL_48_M1_CLOCK,
    PLL_48_M2_CLOCK,
    PLL_SAI_CLOCK,
    PLL_P_CLOCK,
    SAI_EXTERNAL_CLOCK,
    N0_CLOCK,
};

enum class PeripheralWithSelectableClockSource
{
    USART_1,
    USART_2,
    USART_3,
    UART_4,
    LOW_POWER_UART_1,
    I2C_1,
    I2C_2,
    I2C_3,
    I2C_4,
    LOW_POWER_TIMER_1,
    LOW_POWER_TIMER_2,
    SAI_1,
    CLK_48MHZ,
    ADC,
    SINGLE_WIRE,
    RTC_1,
};

namespace I2C_Types
{

enum class I2CNumber
{
    I2C_1,
    I2C_2,
    I2C_3,
    I2C_4,
};

enum class Register
{
    CR1,
    CR2,
    OAR1,
    OAR2,
    TIMINGR,
    TIMEOUTR,
    ISR,
    ICR,
    PECR,
    RXDR,
    TXDR,
};

/// Enumerator for the I2C interrupts
enum class Interrupt
{
    TransmitInterrupt,           ///< Transmit interrupt.
    ReceiveInterrupt,            ///< Receive interrupt.
    AddressMatchInterrupt,       ///< Address match interrupt.
    NAKReceivedInterrupt,        ///< NAK received interrupt.
    STOPDetectedInterrupt,       ///< Stop detected interrupt.
    TransferCompletedInterrupt,  ///< Transfer complete interrupt.
    ErrorDetectedInterrupt       ///< Error detected interrupt.

};

enum class DigitalFilter
{
    Disabled,  ///< Digital filter disabled
    Clock1,    ///< Digital filter set to 1 clock.
    Clock2,    ///< Digital filter set to 2 clocks.
    Clock3,    ///< Digital filter set to 3 clocks.
    Clock4,    ///< Digital filter set to 4 clocks.
    Clock5,    ///< Digital filter set to 5 clocks.
    Clock6,    ///< Digital filter set to 6 clocks.
    Clock7,    ///< Digital filter set to 7 clocks.
    Clock8,    ///< Digital filter set to 8 clocks.
    Clock9,    ///< Digital filter set to 9 clocks.
    Clock10,   ///< Digital filter set to 10 clocks.
    Clock11,   ///< Digital filter set to 11 clocks.
    Clock12,   ///< Digital filter set to 12 clocks.
    Clock13,   ///< Digital filter set to 13 clocks.
    Clock14,   ///< Digital filter set to 14 clocks.
    Clock15,   ///< Digital filter set to 15 clocks.

};

/// Enumerates DMA requests
enum class DMARequest
{
    Transmit,  ///< DMA transmit request.
    Receive    ///< DMA receive request.

};

/// Enumerates I2C address length
enum class AddressLength
{
    bits7,  ///< 7 bits long address
    bits10  ///< 10 bits long address

};

/// Enumerates I2C options
enum class Option
{
    AutoEnd,  ///< Auto end option
    Reload    ///< Reload option
};

/// Enumerates I2C transfer directions
enum class TransferDirection
{
    READ,  ///< Read from the slave
    WRITE  ///< Write to the slave
};

}  // namespace I2C_Types

namespace DMA_Types
{

enum class DmaNumber
{
    DMA_1,
    DMA_2,
};

enum class Channel
{
    Channel1,
    Channel2,
    Channel3,
    Channel4,
    Channel5,
    Channel6,
    Channel7,
};

enum class DmaRegister
{
    ISR,
    IFCR,
    CCR,
    CNDTR,
    CPAR,
    CMAR,
    CSELR,
};

/**
 * @brief DMA priorities
 */
enum class Priority
{
    Low,      //!< Low low priority
    Medium,   //!< Medium medium priority
    High,     //!< High high priority
    VeryHigh  //!< VeryHigh very high priority
};

/**
 * @brief DMA data size.
 */
enum class DataSize
{
    Bits8,   //!< Bits8 8 bits data size
    Bits16,  //!< Bits16 16 bits data size
    Bits32   //!< Bits32 32 bits data size
};

/**
 * @brief DMA requests.
 */
enum class Request
{
    ADC_1,
    ADC_2,
    DFSDM_1_FLT0,
    DFSDM_1_FLT1,
    SPI_1_RX,
    SPI_1_TX,
    SPI_2_RX,
    SPI_2_TX,
    SAI_1_A,
    SAI_1_B,
    USART_3_TX,
    USART_3_RX,
    USART_1_TX,
    USART_1_RX,
    USART_2_RX,
    USART_2_TX,
    I2C_3_TX,
    I2C_3_RX,
    I2C_2_TX,
    I2C_2_RX,
    I2C_1_TX,
    I2C_1_RX,
    TIM_2_CH3,
    TIM_2_UP,
    TIM_16_CH1,
    TIM_16_UP,
    TIM_2_CH1,
    TIM_2_CH2,
    TIM_2_CH4,
    TIM_3_CH3,
    TIM_3_CH4,
    TIM_3_UP,
    TIM_7_UP,
    DAC_CH2,
    QUAD_SPI,
    TIM_3_CH1,
    TIM_3_TRIG,
    TIM_6_UP,
    DAC_CH1,
    TIM_1_CH1,
    TIM_1_CH2,
    TIM_1_CH4,
    TIM_1_TRIG,
    TIM_1_COM,
    TIM_15_CH1,
    TIM_15_UP,
    TIM_15_TRIG,
    TIM_15_COM,
    TIM_1_UP,
    TIM_1_CH3,
    I2C_4_RX,
    I2C_4_TX,
    UART_4_TX,
    UART_4_RX,
    SPI_3_RX,
    SPI_3_TX,
    SWPMI_1_RX,
    SWPMI_1_TX,
    LPUART_1_TX,
    LPUART_1_RX,
    AES_IN,
    AES_OUT,
    SDMMC_1,
};

/**
 * @brief Read direction
 */
enum class ReadDirection
{
    ReadFromPeripheral,  //!< ReadFromPeripheral read for peripheral
    ReadFromMemory       //!< ReadFromMemory read from memory
};

/**
 * @brief DMA interrupts
 */
enum class Interrupt
{
    TransferError,      //!< TransferError transfer error interrupt
    HalfTransfer,       //!< HalfTransfer half transfer interrupt
    TransferCompleted,  //!< TransferCompleted transfer complete interrupt
};

}  // namespace DMA_Types

namespace SPI_types
{

enum class SPI_Number
{
    SPI_1,
    SPI_2,
    SPI_3
};

enum class Register
{
    CR1,
    CR2,
    SR,
    DR,
    CRCPR,
    RXCRCR,
    TXCRCR,
};

enum class SPIForamt : uint8_t
{
    MSB_first,
    LSB_first
};

enum class SPIMode : uint8_t
{
    slave,
    master
};

enum class SPIPolarity : uint8_t
{
    idle_low,
    idle_high
};

enum class SPIPhase : uint8_t
{
    data_on_first_edge,
    data_on_second_edge
};

enum class SPIDataSize : uint8_t
{
    _4bits = 3,
    _5bits = 4,
    _6bits = 5,
    _7bits = 6,
    _8bits = 7,
    _9bits = 8,
    _10bits = 9,
    _11bits = 10,
    _12bits = 11,
    _13bits = 12,
    _14bits = 13,
    _15bits = 14,
    _16bits = 15
};

enum class BaudRatePrescaller
{
    Prescaller_2,
    Prescaller_4,
    Prescaller_8,
    Prescaller_16,
    Prescaller_32,
    Prescaller_64,
    Prescaller_128,
    Prescaller_256,

};

}  // namespace SPI_types

namespace RTC_types
{
enum class Register
{
    TR,
    DR,
    SSR,
    ICSR,
    PRER,
    WUTR,
    CR,
    WPR,
    CALR,
    SHIFTR,
    TSTR,
    TSDR,
    TSSSR,
    ALRMAR,
    ALRMASSR,
    ALARMBR,
    ALRMBSSR,
    ISR,
};
}

namespace timer_types
{
enum class Timer_number
{
    Timer_1,
    Timer_2,
    Timer_3,
    Timer_6,
    Timer_15,
    Timer_16,
};

enum class Register
{
    ARR,
    PSC,
    CR1,
    SR,
    DIER,
};

enum class Interrupt
{
    UPDATE,
    CAPTURE_COMPARE_1,
    CAPTURE_COMPARE_2,
    CAPTURE_COMPARE_3,
    CAPTURE_COMPARE_4,
    TRIGGER,
    CAPTURE_COMPARE_OVERCAPTURE_1,
    CAPTURE_COMPARE_OVERCAPTURE_2,
    CAPTURE_COMPARE_OVERCAPTURE_3,
    CAPTURE_COMPARE_OVERCAPTURE_4,
};
}  // namespace timer_types

namespace Usart_Types
{
enum class UsartNumber
{
    USART_1,
    USART_2,
    USART_3,
    UART_4,
    LOW_POWER_UART_1
};

enum class Register
{
    CR1,
    CR2,
    CR3,
    BRR,
    GTPR,
    RTOR,
    RQR,
    ISR,
    ICR,
    RDR,
    TDR
};

enum class BaudRate
{
    Baud_4800,
    Baud_9600,
    Baud_19200,
    Baud_38400,
    Baud_57600,
    Baud_115200,
    Baud_230400,
    Baud_460800,
    Baud_921600
};
}  // namespace Usart_Types

namespace Power_Types
{
enum class Register
{
    CR1
};

enum class WriteProtectionState
{
    Enabled,
    Disabled
};
}  // namespace Power_Types

uint32_t to_register_value(GPIO_Types::PortMode portMode);
uint32_t to_register_value(GPIO_Types::AlternateFunction alteranteFunction);
uint32_t to_register_value(GPIO_Types::SignalLevel signalLevel);
uint32_t to_register_value(GPIO_Types::PortPullUpPullDown portPullUpPullDown);
uint32_t to_register_value(GPIO_Types::PortOutputSpeed portOutputSpeed);
uint32_t to_register_value(GPIO_Types::PortOutputType portOutputType);

Peripheral to_peripheral(GPIO_Types::Port port);
Peripheral to_peripheral(I2C_Types::I2CNumber i2c);
Peripheral to_peripheral(DMA_Types::DmaNumber dma);
Peripheral to_peripheral(Usart_Types::UsartNumber usart);

uint32_t to_clock_source_value(PeripheralWithSelectableClockSource peripheral, ClockSource clock_source);
uint8_t to_clock_source_position(PeripheralWithSelectableClockSource peripheral);
bool is_clock_source_supported(PeripheralWithSelectableClockSource peripheral, ClockSource clock_source);
uint8_t to_peripheral_clock_select_field_length(PeripheralWithSelectableClockSource peripheral);

uint8_t to_bit_position(I2C_Types::Interrupt interrupt);
uint8_t to_bit_position(I2C_Types::DMARequest request);
uint8_t to_bit_position(I2C_Types::Option option);
uint8_t to_bit_position(DMA_Types::Interrupt interrupt);
uint8_t to_bit_position(DMA_Types::Channel channel, DMA_Types::Interrupt interrupt);
uint8_t to_bit_position(Peripheral peripheral);
uint8_t to_bit_position(timer_types::Interrupt interrupt);

uint8_t to_enable_bit_position(ClockSource clock_source);

uint8_t to_ready_bit_position(ClockSource clock_source);

uint8_t to_start_position(DMA_Types::Channel channel);

uint32_t to_value(I2C_Types::DigitalFilter digital_filter);
uint32_t to_value(I2C_Types::TransferDirection transfer_direction);
uint32_t to_value(DMA_Types::Priority priority);
uint32_t to_value(DMA_Types::DataSize memory_size);
uint32_t to_value(DMA_Types::DataSize peripheral_size);
uint32_t to_value(DMA_Types::ReadDirection read_direction);
uint32_t to_value(DMA_Types::DmaNumber dma_number, DMA_Types::Channel channel, DMA_Types::Request request);
uint32_t to_value(SPI_types::BaudRatePrescaller baudrate_prescaller);
uint32_t to_value(Power_Types::WriteProtectionState state);

PeripheralWithSelectableClockSource to_peripheral_with_clock_select(I2C_Types::I2CNumber i2c);

bool is_request_valid(DMA_Types::DmaNumber dma_number, DMA_Types::Channel channel, DMA_Types::Request request);
