/*
 * HAL.cpp
 *
 *  Created on: 21-11-2018
 *      Author: Paweł Warzecha
 */

#include "HAL.hpp"

#include <stm32l4xx.h>

namespace HAL
{

  void clock_init(void) {
    // M = 1
    // N = 10
    // R = 2
    // P = 7
    // Q = 2

  //  while((RCC->CR & RCC_CR_PLLRDY) == 0);

    FLASH->ACR |= FLASH_ACR_LATENCY_4WS; // Latency set to 4 wait states
    FLASH->ACR |= FLASH_ACR_PRFTEN; // Prefetch enable
    FLASH->ACR |= FLASH_ACR_DCEN; // Data cashe enable
    FLASH->ACR |= FLASH_ACR_ICEN; // Instruction cashe enable

    RCC->CR |= RCC_CR_HSION;

    while ((RCC->CR & RCC_CR_HSIRDY) == 0)
      ;

    RCC->PLLCFGR = (2 << 0) | (10 << 8) | (1 << 24);

    RCC->CR |= RCC_CR_PLLON; // HSI turned on

    while ((RCC->CR & RCC_CR_PLLRDY) == 0)
      ;

    RCC->CFGR |= (3 << 0);

  }

  void I2C_init(void) {

    RCC->CCIPR |= RCC_CCIPR_I2C1SEL_0;
    RCC->CCIPR |= RCC_CCIPR_I2C2SEL_0;
    RCC->CCIPR |= RCC_CCIPR_I2C3SEL_0;
    RCC->CCIPR2 |= RCC_CCIPR2_I2C4SEL_0;

    /* Clock enable */
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN; //Enable clock for I2C1
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C2EN; //Enable clock for I2C2
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C3EN; //Enable clock for I2C3
    RCC->APB1ENR2 |= RCC_APB1ENR2_I2C4EN; //Enable clock for I2C4

    /* Fast-mode Plus enable */
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C1_FMP; //Enable FM+ for I2C1
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C2_FMP; //Enable FM+ for I2C2
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C3_FMP; //Enable FM+ for I2C3
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C4_FMP; //Enable FM+ for I2C4

    SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C_PB6_FMP | // Enable FM+ on PB6
        SYSCFG_CFGR1_I2C_PB7_FMP;  // Enable FM+ on PB7

    /* I2C set timing*/
    I2C_1::set_timing(0, 7, 0, 41, 145);
    I2C_2::set_timing(0, 7, 0, 41, 145);
    I2C_3::set_timing(0, 7, 0, 41, 145);
    I2C_4::set_timing(0, 7, 0, 41, 145);

    /* I2C periphery enable */
    I2C_1::enable();
    I2C_2::enable();
    I2C_3::enable();
    I2C_4::enable();
  }

  void GPIO_Init(void) {
    /* Clock enable */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; // Enable clock for GPIOA
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN; // Enable clock for GPIOB
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN; // Enable clock for GPIOC

    /* Set I2C Pins */

    /* I2C1 SCL PA9 */
    PA9::set_as_I2C_pin(eAF4);

    /* I2C1 SDA PA10 */
    PA10::set_as_I2C_pin(eAF4);

    /* I2C2 SCL PB10 */
    PB10::set_as_I2C_pin(eAF4);

    /* I2C2 SDA PB11 */
    PB11::set_as_I2C_pin(eAF4);
    /* I2C3 SCL PC0 */
    PC0::set_as_I2C_pin(eAF4);

    /* I2C3 SDA PC1 */
    PC1::set_as_I2C_pin(eAF4);

    /* I2C4 SCL PB6 */
    PB6::set_as_I2C_pin(eAF5);

    /* I2C4 SDA PB7 */
    PB7::set_as_I2C_pin(eAF5);

    /* HC595 Pins */

    /* Reset PB15 */
    PB15::set_mode(eOutput);
    PB15::set_speed(eVeryHighSpeed);

    /* OutputEnable PB14 */
    PB14::set_mode(eOutput);
    PB14::set_speed(eVeryHighSpeed);

    /* I2C Reset PC6 */
    PC6::set_mode(eOutput);
    PC6::set_speed(eVeryHighSpeed);

    /* DataIn PC7 */
    PC7::set_mode(eOutput);
    PC7::set_speed(eVeryHighSpeed);

    /* Clock PC8 */
    PC8::set_mode(eOutput);
    PC8::set_speed(eVeryHighSpeed);

    /* Latch PC9 */
    PC9::set_mode(eOutput);
    PC9::set_speed(eVeryHighSpeed);

  }


  void init(void)
  {
    clock_init();
    GPIO_Init();
    I2C_init();
  }
}



