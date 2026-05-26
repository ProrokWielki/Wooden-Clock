
#include "bootloader.hpp"

#include <FreeRTOS.h>
#include <task.h>

#include <stm32l452xx.h>

static void send_byte(uint8_t data) __attribute__((section(".flasher_section")));
static uint32_t get_data() __attribute__((section(".flasher_section")));
static uint8_t get_byte() __attribute__((section(".flasher_section")));

void send_byte(uint8_t data)
{
    while (!(UART4->ISR & (1 << 7)))
        ;
    UART4->TDR = static_cast<uint16_t>(data);
}

void send_data(uint32_t data)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        uint8_t byte_to_send = (data >> ((3 - i) * 8)) & 0xFF;
        send_byte(byte_to_send);
    }
}

uint32_t get_data()
{
    uint32_t data_to_write{0};
    for (uint8_t i = 0; i < 4; i++)
    {
        uint8_t data = get_byte();
        data_to_write |= (static_cast<uint32_t>(data) << ((3 - i) * 8));
    }
    return data_to_write;
}

uint8_t get_byte()
{
    while (!(UART4->ISR & (1 << 5)))
        ;
    return UART4->RDR;
}

void flash()
{
    // disable screen and stop everything.
    // HAL::SR_74HC595_1.output_enable(false);
    __disable_irq();
    vTaskSuspendAll();

    // erase 254 pages - in the 255th is this function :)
    /// erase
    FLASH->KEYR = 0x45670123;
    FLASH->KEYR = 0xCDEF89AB;

    send_byte('g');

    while (true)
    {
        auto data = get_byte();

        if (data != 0xBE)
            continue;

        send_byte('g');

        uint32_t data_to_write = get_data();
        send_data(data_to_write);

        if (data_to_write == 0x12345678)
        {
            break;
        }
    }

    while (FLASH->SR & (1 << 16))
    {
    }

    FLASH->SR |= (0b11 << 14) | (0b1111111 << 3) | 2;

    FLASH->CR |= (1 << 1) | (81 << 3) | (1 << 16);

    while (FLASH->SR & (1 << 16))
    {
    }

    FLASH->CR &= ~(1 << 1);

    // program
    while (FLASH->SR & (1 << 16))
    {
    }
    FLASH->SR |= (0b11 << 14) | (0b1111111 << 3) | 2;

    FLASH->CR |= 1;

    *(uint32_t *)0x8028800 = (uint32_t)0xefbeadde;
    // while(FLASH->SR & (1<<16))
    // {}

    // auto sr_register = FLASH->SR;

    *(uint32_t *)0x8028804 = (uint32_t)0xefbeadde;
    while (FLASH->SR & (1 << 16))
    {
    }
    // auto sr_register = FLASH->SR;
    FLASH->CR &= ~(1);

    // *(uint16_t*)0x8028802 = 0xbeef;

    // while(FLASH->SR & (1<<16))
    // {}

    // FLASH->CR &= ~(1);

    // write recived data to the flash

    // reset
    SCB->AIRCR = ((0x5FAUL << 16) | (1 << 2));

    for (;;)
    {
        asm("nop");
    }
}
