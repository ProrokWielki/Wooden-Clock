#pragma once

#include <stm32l452xx.h>

#include <cstdint>

namespace QSPI
{

__attribute__((section(".flasher_section"), noinline)) static bool is_busy()
{
    constexpr static uint8_t BUSY_BIT_POSITION{5};
    return QUADSPI->SR & (1 << BUSY_BIT_POSITION);
}

__attribute__((section(".flasher_section"), noinline)) static void send_command(uint8_t command)
{
    while (is_busy())
        ;

    uint32_t ccr_value = QUADSPI->CCR;
    ccr_value &= ~((3 << 8) | (3 << 10) | (3 << 12) | (3 << 14) | (0b11111 << 18) | (3 << 24) | (3 << 26) | (0xff));

    ccr_value |= (1 << 8);   // 1 line instruction
    ccr_value |= (0 << 10);  // no address
    ccr_value |= (0 << 24);  // no data
    ccr_value |= (0 << 26);  // indirect write

    constexpr static uint8_t INSTRUCTION_BIT_POSITION{0};
    ccr_value |= (command << INSTRUCTION_BIT_POSITION);  // Set the instruction

    QUADSPI->CCR = ccr_value;
}

__attribute__((section(".flasher_section"), noinline)) static void send_command(uint8_t command, uint32_t address)
{
    while (is_busy())
        ;

    uint32_t ccr_value = QUADSPI->CCR;
    ccr_value &= ~((3 << 8) | (3 << 10) | (3 << 12) | (3 << 14) | (0b11111 << 18) | (3 << 24) | (3 << 26) | (0xff));

    ccr_value |= (1 << 8);   // 1 line instruction
    ccr_value |= (1 << 10);  // 1 line address
    ccr_value |= (2 << 12);  // 24-bit address
    ccr_value |= (0 << 24);  // no data
    ccr_value |= (0 << 26);  // indirect write

    constexpr static uint8_t INSTRUCTION_BIT_POSITION{0};
    ccr_value |= (command << INSTRUCTION_BIT_POSITION);  // Set the instruction

    QUADSPI->CCR = ccr_value;
    QUADSPI->AR = address;
}

__attribute__((section(".flasher_section"), noinline)) static std::span<uint8_t> read_data_from_register(uint8_t instruction,
                                                                                                         std::span<uint8_t> buffer_for_read_data)
{
    while (is_busy())
        ;

    QUADSPI->DLR = buffer_for_read_data.size() - 1;

    uint32_t ccr_value = 0;

    ccr_value |= (1 << 8);   // 1 line instruction
    ccr_value |= (0 << 10);  // no address
    ccr_value |= (1 << 24);  // 1 line data
    ccr_value |= (1 << 26);  // indirect read

    constexpr static uint8_t INSTRUCTION_BIT_POSITION{0};
    ccr_value |= (instruction << INSTRUCTION_BIT_POSITION);  // Set the instruction

    QUADSPI->CCR = ccr_value;

    for (unsigned char & i : buffer_for_read_data)
    {
        while (!((QUADSPI->SR & (1 << 2)) | (QUADSPI->SR & (1 << 1))))
            ;
        i = (uint8_t)(QUADSPI->DR);
    }

    return buffer_for_read_data;
}

__attribute__((section(".flasher_section"), noinline)) static void write_data(uint8_t instruction, const std::span<uint8_t> data_to_write)
{
    while (is_busy())
        ;

    QUADSPI->FCR = QUADSPI_FCR_CTCF;

    auto size = data_to_write.size() - 1;

    QUADSPI->DLR = size;

    uint32_t ccr_value = 0;

    ccr_value |= (1 << 8);   // 1 line instruction
    ccr_value |= (0 << 10);  // no address
    ccr_value |= (1 << 24);  // 1 line data
    ccr_value |= (0 << 26);  // 1 indirect write

    constexpr static uint8_t INSTRUCTION_BIT_POSITION{0};
    ccr_value |= (instruction << INSTRUCTION_BIT_POSITION);  // Set the instruction

    QUADSPI->CCR = ccr_value;

    auto * dr = reinterpret_cast<volatile uint8_t *>(&QUADSPI->DR);
    for (const auto data : data_to_write)
    {
        while (!((QUADSPI->SR & (1 << 2))))
            ;
        *dr = data;
    }

    while (!((QUADSPI->SR & (1 << 1))))
        ;

    QUADSPI->FCR = QUADSPI_FCR_CTCF;
}

__attribute__((section(".flasher_section"), noinline)) static void write_data(uint8_t instruction, uint32_t address, const std::span<uint8_t> data_to_write)
{
    while (is_busy())
        ;

    QUADSPI->FCR = QUADSPI_FCR_CTCF;

    auto size = data_to_write.size() - 1;

    QUADSPI->DLR = size;

    QUADSPI->AR = (address);

    uint32_t ccr_value = QUADSPI->CCR;
    ccr_value &= ~((3 << 8) | (3 << 10) | (3 << 12) | (3 << 14) | (0b11111 << 18) | (3 << 24) | (3 << 26) | (0xff));

    ccr_value |= (1 << 8);   // 1 line instruction
    ccr_value |= (1 << 10);  // 1 line address
    ccr_value |= (2 << 12);  // 24-bit address
    ccr_value |= (3 << 24);  // 4 line data
    ccr_value |= (0 << 26);  // 1 indirect write

    constexpr static uint8_t INSTRUCTION_BIT_POSITION{0};
    ccr_value |= (instruction << INSTRUCTION_BIT_POSITION);  // Set the instruction

    QUADSPI->CCR = ccr_value;

    auto * dr = reinterpret_cast<volatile uint8_t *>(&QUADSPI->DR);
    for (const auto data : data_to_write)
    {
        while (!((QUADSPI->SR & (1 << 2)) | (QUADSPI->SR & (1 << 1))))
            ;
        *dr = data;
    }

    while (!((QUADSPI->SR & (1 << 1))))
        ;

    QUADSPI->FCR = QUADSPI_FCR_CTCF;
}
}  // namespace QSPI