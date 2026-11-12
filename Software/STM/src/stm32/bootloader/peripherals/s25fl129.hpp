#pragma once

#include <stm32l452xx.h>

#include "qspi.hpp"

#include <cstdint>
#include <span>

namespace S25FL129
{

__attribute__((section(".flasher_section"), noinline)) static void enable_write()
{
    QSPI::send_command(0x06);
}

__attribute__((section(".flasher_section"), noinline)) static bool is_write_enabled()
{
    std::array<uint8_t, 1> buffer{};
    auto status = QSPI::read_data_from_register(0x05, buffer);

    uint8_t val = status[0];

    return (val & 0x02) != 0;
}

__attribute__((section(".flasher_section"), noinline)) static bool is_write_in_progress()
{
    std::array<uint8_t, 1> buffer{};
    auto status = QSPI::read_data_from_register(0x05, buffer);
    return (status[0] & 0x01) != 0;
}

__attribute__((section(".flasher_section"), noinline)) static void erase_256kb_sector(uint32_t sector)
{
    enable_write();

    if (!is_write_enabled())
    {
        return;
    }

    QSPI::send_command(0xD8, sector * 0x40000);

    while (is_write_in_progress())
        ;
}

__attribute__((section(".flasher_section"), noinline)) static void write_data(uint32_t address, std::span<uint8_t> data)
{
    while (is_write_in_progress())
        ;

    std::array<uint8_t, 1> sr_buffer{};
    std::array<uint8_t, 1> cr_buffer{};

    auto sr_value = QSPI::read_data_from_register(0x05, sr_buffer);
    auto cr_value = QSPI::read_data_from_register(0x35, cr_buffer);

    std::array<uint8_t, 2> data_to_send{sr_value[0], static_cast<uint8_t>(cr_value[0] | 0x02)};

    enable_write();

    while (!is_write_enabled())
    {
    }

    QSPI::write_data(0x01, {data_to_send});

    while (is_write_in_progress())
        ;

    constexpr uint32_t WRITE_SIZE{256};
    for (size_t offset = 0; offset < data.size(); offset += WRITE_SIZE)
    {

        const size_t remaining = data.size() - offset;
        const size_t chunk = remaining < WRITE_SIZE ? remaining : WRITE_SIZE;

        enable_write();

        constexpr uint32_t EXTERNAL_FLASH_OFFSET{0x90000000};
        QSPI::write_data(0x32, address - EXTERNAL_FLASH_OFFSET + offset, data.subspan(offset, chunk));

        while (is_write_in_progress())
            ;
    }
}
}  // namespace S25FL129