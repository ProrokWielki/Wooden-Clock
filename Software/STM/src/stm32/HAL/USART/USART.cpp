#include <bits/ranges_base.h>
#include <cstdint>
#include <cstdlib>

#include "HAL/types.hpp"
#include <cmsis_bridge/cmsis_bridge.hpp>

#include <HAL/Clock.hpp>
#include <HAL/USART.hpp>

USART::USART(Clock & clock, Usart_Types::UsartNumber usart_number, GPIO & tx_pin, GPIO & rx_pin, uint32_t baud_rate)
: clock_{clock}, CR1(to_address(usart_number, Usart_Types::Register::CR1)), CR2(to_address(usart_number, Usart_Types::Register::CR2)),
  CR3(to_address(usart_number, Usart_Types::Register::CR3)), BRR(to_address(usart_number, Usart_Types::Register::BRR)),
  GTPR(to_16bit_register_address(usart_number, Usart_Types::Register::GTPR)), RTOR(to_address(usart_number, Usart_Types::Register::RTOR)),
  ISR(to_address(usart_number, Usart_Types::Register::ISR)), ICR(to_address(usart_number, Usart_Types::Register::ICR)),
  RDR(to_16bit_register_address(usart_number, Usart_Types::Register::RDR)), TDR(to_16bit_register_address(usart_number, Usart_Types::Register::TDR))
{
    constexpr static uint8_t ENABLE_BIT_POSITION{0};  // Bit position for USART enable in CR1 register
    constexpr static uint8_t TE_BIT_POSITION{3};      // Bit position for Transmitter Enable in CR1 register
    constexpr static uint8_t RE_BIT_POSITION{2};      // Bit position for Receiver Enable in CR1 register
    constexpr static uint8_t RXNEIE_BIT_POSITION{5};  // Bit position for RXNE interrupt enable in CR1 register
    constexpr static uint8_t PS_BIT_POSITION{9};      // Bit position for Parity Control Enable in CR1 register

    clock.enable_clock_for(to_peripheral(usart_number));

    set_baud_rate(baud_rate);

    if (usart_number == Usart_Types::UsartNumber::UART_4)  // TODO: make generic
    {
        rx_pin.set_as_SPI_pin(GPIO_Types::AlternateFunction::AF8);  // TODO: not spi :)
        tx_pin.set_as_SPI_pin(GPIO_Types::AlternateFunction::AF8);
    }
    else
    {
        rx_pin.set_as_SPI_pin(GPIO_Types::AlternateFunction::AF7);  // TODO: not spi :)
        tx_pin.set_as_SPI_pin(GPIO_Types::AlternateFunction::AF7);
    }

    CR1.set_bit(PS_BIT_POSITION);
    CR1.set_bit(TE_BIT_POSITION);      // Enable Transmitter
    CR1.set_bit(RE_BIT_POSITION);      // Enable Receiver
    CR1.set_bit(RXNEIE_BIT_POSITION);  // Enable RXNE interrupt
    CR1.set_bit(ENABLE_BIT_POSITION);  // Enable USART
}

void USART::set_baud_rate(uint32_t baud_rate)
{
    constexpr static uint8_t OVERSAMPLING_BIT_POSITION{15};  // Bit position for oversampling in CR1 register
    constexpr static uint8_t USARTDIV_VALUE_POSITION{0};     // Bit position for USARTDIV value in BRR register
    constexpr static uint8_t USARTDIV_VALUE_LENGTH{16};      // Length of USARTDIV value in BRR register

    const uint32_t usart_div_wo_oversampling{clock_.get_clock_frequency() / baud_rate};
    const uint32_t usart_div_with_oversampling{2 * clock_.get_clock_frequency() / baud_rate};

    const double real_baud_wo_oversampling{static_cast<double>(clock_.get_clock_frequency()) / static_cast<double>(usart_div_wo_oversampling)};
    const double real_baud_with_oversampling{2.0 * (static_cast<double>(clock_.get_clock_frequency()) / static_cast<double>(usart_div_wo_oversampling))};

    const double usart_div_wo_oversampling_error{std::abs(baud_rate - real_baud_wo_oversampling)};
    const double usart_div_with_oversampling_error{std::abs(baud_rate - real_baud_with_oversampling)};

    if (usart_div_wo_oversampling_error <= usart_div_with_oversampling_error)
    {

        BRR.set_value(usart_div_wo_oversampling, USARTDIV_VALUE_POSITION, USARTDIV_VALUE_LENGTH);
    }
    else
    {
        const uint32_t usart_div_with_oversampling_register_value = (usart_div_with_oversampling & (0xfff0)) | ((usart_div_with_oversampling & 0x000f) >> 1);

        BRR.set_value(usart_div_with_oversampling_register_value, USARTDIV_VALUE_POSITION, USARTDIV_VALUE_LENGTH);
        CR1.set_bit(OVERSAMPLING_BIT_POSITION);
    }
}