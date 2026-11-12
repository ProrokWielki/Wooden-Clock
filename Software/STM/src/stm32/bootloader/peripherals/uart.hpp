#pragma once

#include <stm32l452xx.h>

#include <cstdint>
#include <span>

namespace UART
{

__attribute__((section(".flasher_section"), noinline)) static void send_byte(uint8_t data)
{
    while (!(UART4->ISR & (1 << 7)))
        ;
    UART4->TDR = static_cast<uint16_t>(data);
}

__attribute__((section(".flasher_section"), noinline)) static void send_data(const std::span<const uint8_t> & data)
{
    for (auto const byte : data)
    {
        send_byte(byte);
    }
}

__attribute__((section(".flasher_section"), noinline)) static uint8_t get_byte()
{
    while (!(UART4->ISR & (1 << 5)))
        ;
    return UART4->RDR;
}

__attribute__((section(".flasher_section"), noinline)) static std::span<uint8_t> get_data(std::span<uint8_t> read_buffer)
{
    for (auto & byte : read_buffer)
    {
        byte = get_byte();
    }
    return read_buffer;
}

}  // namespace UART