#pragma once

#include <stm32l452xx.h>

#include <cstdint>

namespace InternalFlash
{

__attribute__((section(".flasher_section"), noinline)) static void unlock()
{
    FLASH->KEYR = 0x45670123;
    FLASH->KEYR = 0xCDEF89AB;
}

__attribute__((section(".flasher_section"), noinline)) static void erase_page(uint8_t page)
{

    while (FLASH->SR & (1 << 16))
    {
    }

    FLASH->SR |= (0b11 << 14) | (0b1111111 << 3) | 2;

    const auto cr = FLASH->CR;

    FLASH->CR = cr | ((1 << 1) | (page << 3) | (1 << 16));

    while (FLASH->SR & (1 << 16))
    {
    }

    FLASH->CR &= ~(1 << 1);
}

__attribute__((section(".flasher_section"), noinline)) static void write_page(uint32_t page_address, pb_byte_t const * const data, uint32_t size)
{
    while (FLASH->SR & (1 << 16))
    {
    }
    FLASH->SR |= (0b11 << 14) | (0b1111111 << 3) | 2;

    FLASH->CR |= 1;

    uint32_t * current_address = (uint32_t *)page_address;
    for (uint32_t i = 0; i < size; i += 4)
    {
        while (FLASH->SR & (1 << 16))
            ;
        uint32_t data_to_write = static_cast<uint32_t>(data[i + 3]) << 24 | static_cast<uint32_t>(data[i + 2]) << 16 | static_cast<uint32_t>(data[i + 1]) << 8 |
                                 static_cast<uint32_t>(data[i]);

        *current_address = data_to_write;
        ++current_address;
    }

    while (FLASH->SR & (1 << 16))
    {
    }
    // auto sr_register = FLASH->SR;
    FLASH->CR &= ~(1);
}
}  // namespace InternalFlash