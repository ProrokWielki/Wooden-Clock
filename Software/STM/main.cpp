#include <cmath>
#include <stdint.h>

#include "APP.hpp"
#include "BSP.hpp"
#include "HAL.hpp"

#include "DRV/LSM9DS1/LSM9DS1.hpp"

#include "Assets/Images/Images.hpp"

int main(void)
{
    /// erase
    FLASH->KEYR = 0x45670123;
    FLASH->KEYR = 0xCDEF89AB;

    while(FLASH->SR & (1<<16))
    {}

    FLASH->SR |= (0b11<<14) | (0b1111111 << 3) | 2 ;

    FLASH->CR |= (1<<1) | (81<<3) | (1<<16);

    while(FLASH->SR & (1<<16))
    {}

    FLASH->CR &= ~(1<<1);

    // program
    while(FLASH->SR & (1<<16))
    {}
    FLASH->SR |= (0b11<<14) | (0b1111111 << 3) | 2 ;

    FLASH->CR |= 1;

    *(uint32_t*)0x8028800 = (uint32_t)0xefbeadde;
    // while(FLASH->SR & (1<<16))
    // {}

    // auto sr_register = FLASH->SR;

    *(uint32_t*)0x8028804 = (uint32_t)0xefbeadde;
    while(FLASH->SR & (1<<16))
    {}
    auto sr_register = FLASH->SR;
    FLASH->CR &= ~(1);

    // *(uint16_t*)0x8028802 = 0xbeef;


    // while(FLASH->SR & (1<<16))
    // {}

    // FLASH->CR &= ~(1);

    HAL::init();
    BSP::init();

    BSP::display.set_frame_buffer(Arrows1);

    NVIC_EnableIRQ(DMA1_Channel2_IRQn);
    NVIC_EnableIRQ(DMA1_Channel4_IRQn);
    NVIC_EnableIRQ(DMA2_Channel7_IRQn);
    NVIC_EnableIRQ(DMA2_Channel2_IRQn);
    NVIC_EnableIRQ(USART3_IRQn);
    NVIC_EnableIRQ(TIM2_IRQn);

    APP_init();

    for (;;)
    {
    }
    return 0;
}
