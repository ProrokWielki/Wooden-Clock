/*
 * HAL.cpp
 *
 *  Created on: 21-11-2018
 *      Author: Paweł Warzecha
 */

#include "HAL.hpp"

#include <stm32l4xx.h>

GPIO HAL::I2C1_SCL(GPIOA, 9);
GPIO HAL::I2C1_SDA(GPIOA, 10);
GPIO HAL::I2C4_SCL(GPIOB, 6);
GPIO HAL::I2C4_SDA(GPIOB, 7);
GPIO HAL::I2C2_SCL(GPIOB, 10);
GPIO HAL::I2C2_SDA(GPIOB, 11);
GPIO HAL::I2C3_SCL(GPIOC, 0);
GPIO HAL::I2C3_SDA(GPIOC, 1);
GPIO HAL::TLC_RESET(GPIOC, 6);
GPIO HAL::SR_DATAIN(GPIOC, 7);
GPIO HAL::SR_RCLOCK(GPIOC, 8);
GPIO HAL::SR_SCLOCK(GPIOC, 9);
GPIO HAL::SR_OE(GPIOB, 14);
GPIO HAL::SR_CLEAR(GPIOB, 15);
GPIO HAL::BUTTON(GPIOA, 2);
GPIO HAL::BUTTON2(GPIOA, 3);
GPIO HAL::BUTTON3(GPIOC, 4);
GPIO HAL::BUTTON4(GPIOA, 12);
DMA HAL::DMA1_2(DMA1, DMA1_Channel2, 2);
DMA HAL::DMA1_4(DMA1, DMA1_Channel4, 4);
DMA HAL::DMA2_2(DMA2, DMA2_Channel2, 2);
DMA HAL::DMA2_7(DMA2, DMA2_Channel7, 7);
I2C HAL::I2C_1(I2C1, &DMA2_7);
I2C HAL::I2C_2(I2C2, &DMA1_4);
I2C HAL::I2C_3(I2C3, &DMA1_2);
I2C HAL::I2C_4(I2C4, &DMA2_2);
TLC59208F HAL::TLC59208F_4(I2C_4, 0x46, TLC_RESET);
SR_74HC595 HAL::SR_74HC595_1(SR_DATAIN, SR_RCLOCK, SR_SCLOCK, SR_OE, SR_CLEAR);
TLC59208F HAL::TLC59208F_3(I2C_3, 0x44, TLC_RESET);
TLC59208F HAL::TLC59208F_2(I2C_2, 0x42, TLC_RESET);
TLC59208F HAL::TLC59208F_1(I2C_1, 0x40, TLC_RESET);
Timer HAL::Timer2(TIM2);

void HAL::init()
{
    clock_init();
    SystemCoreClockUpdate();

    Timer_init();
    GPIO_Init();
    DMA_init();
    I2C_init();

    TLC59208F_init();
    SR_74HC595_init();

    DMA2_CSELR->CSELR |= (5 << 24);
    DMA1_CSELR->CSELR |= ((3 << 12) | (3 << 4));

    TIM2->DIER |= (1 << 0);
}

void HAL::clock_init(void)
{
    // M = 1
    // N = 10
    // R = 2
    // P = 7
    // Q = 2

    //  while((RCC->CR & RCC_CR_PLLRDY) == 0);

    FLASH->ACR |= FLASH_ACR_LATENCY_4WS;  // Latency set to 4 wait states
    FLASH->ACR |= FLASH_ACR_PRFTEN;       // Prefetch enable
    FLASH->ACR |= FLASH_ACR_DCEN;         // Data cashe enable
    FLASH->ACR |= FLASH_ACR_ICEN;         // Instruction cashe enable

    RCC->CR |= RCC_CR_HSION;

    while ((RCC->CR & RCC_CR_HSIRDY) == 0)
        ;

    RCC->PLLCFGR = (2 << 0) | (10 << 8) | (1 << 24);

    RCC->CR |= RCC_CR_PLLON;  // HSI turned on

    while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        ;

    RCC->CFGR |= (3 << 0);
}

void HAL::I2C_init(void)
{
    RCC->CCIPR |= RCC_CCIPR_I2C1SEL_0;
    RCC->CCIPR |= RCC_CCIPR_I2C2SEL_0;
    RCC->CCIPR |= RCC_CCIPR_I2C3SEL_0;
    RCC->CCIPR2 |= RCC_CCIPR2_I2C4SEL_0;

    /* Clock enable */
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN;  // Enable clock for I2C1
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C2EN;  // Enable clock for I2C2
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C3EN;  // Enable clock for I2C3
    RCC->APB1ENR2 |= RCC_APB1ENR2_I2C4EN;  // Enable clock for I2C4

    /* Fast-mode Plus enable */
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C1_FMP;  // Enable FM+ for I2C1
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C2_FMP;  // Enable FM+ for I2C2
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C3_FMP;  // Enable FM+ for I2C3
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C4_FMP;  // Enable FM+ for I2C4

    SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C_PB6_FMP |  // Enable FM+ on PB6
                     SYSCFG_CFGR1_I2C_PB7_FMP;   // Enable FM+ on PB7

    /* I2C set timing*/
    I2C_1.set_timing(4, 1, 0, 3, 6);
    I2C_2.set_timing(4, 1, 0, 3, 6);
    I2C_3.set_timing(4, 1, 0, 3, 6);
    I2C_4.set_timing(4, 1, 0, 3, 6);

    /* I2C periphery enable */
    I2C_1.enable();
    I2C_2.enable();
    I2C_3.enable();
    I2C_4.enable();
}

void HAL::GPIO_Init(void)
{
    /* Clock enable */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;  // Enable clock for GPIOA
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;  // Enable clock for GPIOB
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;  // Enable clock for GPIOC

    /* Set I2C Pins */

    /* I2C1 SCL PA9 */
    I2C1_SCL.set_as_I2C_pin(eAF4);

    /* I2C1 SDA PA10 */
    I2C1_SDA.set_as_I2C_pin(eAF4);

    /* I2C2 SCL PB10 */
    I2C2_SCL.set_as_I2C_pin(eAF4);

    /* I2C2 SDA PB11 */
    I2C2_SDA.set_as_I2C_pin(eAF4);
    /* I2C3 SCL PC0 */
    I2C3_SCL.set_as_I2C_pin(eAF4);

    /* I2C3 SDA PC1 */
    I2C3_SDA.set_as_I2C_pin(eAF4);

    /* I2C4 SCL PB6 */
    I2C4_SCL.set_as_I2C_pin(eAF5);

    /* I2C4 SDA PB7 */
    I2C4_SDA.set_as_I2C_pin(eAF5);

    BUTTON.set_mode(eInput);
    BUTTON.set_pullUp_pullDown(eNone);

    BUTTON2.set_mode(eInput);
    BUTTON2.set_pullUp_pullDown(eNone);

    BUTTON3.set_mode(eInput);
    BUTTON3.set_pullUp_pullDown(eNone);

    BUTTON4.set_mode(eInput);
    BUTTON4.set_pullUp_pullDown(eNone);
}

void HAL::DMA_init()
{
    RCC->AHB1ENR |= ((1 << 0) | (1 << 1));
}

void HAL::Timer_init()
{
    RCC->APB1ENR1 |= (1 << 0);

    Timer2.set_relode_value(625);
    Timer2.set_prescaler_value(79);
    Timer2.enable();
}

void HAL::NVIC_init(void)
{
    NVIC_EnableIRQ(DMA1_Channel2_IRQn);
    NVIC_EnableIRQ(DMA1_Channel4_IRQn);
    NVIC_EnableIRQ(DMA2_Channel7_IRQn);
    NVIC_EnableIRQ(DMA2_Channel2_IRQn);
    NVIC_EnableIRQ(TIM2_IRQn);
}

void HAL::TLC59208F_init(void)
{
    uint8_t first[] = {0, 0x08};
    uint8_t second[] = {0xAA, 0xAA};

    TLC59208F_1.init();
    TLC59208F_2.init();
    TLC59208F_3.init();
    TLC59208F_4.init();

    TLC59208F_1.set_registers_values(0x00, first, 2);
    TLC59208F_2.set_registers_values(0x00, first, 2);
    TLC59208F_3.set_registers_values(0x00, first, 2);
    TLC59208F_4.set_registers_values(0x00, first, 2);

    TLC59208F_1.set_registers_values(0x0C, second, 2);
    TLC59208F_2.set_registers_values(0x0C, second, 2);
    TLC59208F_3.set_registers_values(0x0C, second, 2);
    TLC59208F_4.set_registers_values(0x0C, second, 2);
}

void HAL::SR_74HC595_init(void)
{
    SR_74HC595_1.init();
    for (uint8_t i = 0; i < 32; i++)
        SR_74HC595_1.shift_bit(eHigh);
}
