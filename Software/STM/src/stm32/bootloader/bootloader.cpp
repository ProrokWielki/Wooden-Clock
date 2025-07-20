
void flash() __attribute__((section(".flasher_section"))) __attribute__((noinline));

void flash()
{
    // disable screen and stop everything.
    HAL::SR_74HC595_1.output_enable(false);
    __disable_irq();
    vTaskSuspendAll();

    // erase 254 pages - in the 255th is this function :)
    /// erase
    FLASH->KEYR = 0x45670123;
    FLASH->KEYR = 0xCDEF89AB;

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

    SCB->AIRCR = ((0x5FAUL << 16) | (1 << 2));

    for (;;)
    {
        asm("nop");
    }
}