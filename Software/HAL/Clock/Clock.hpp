/*
 *  Clock.hpp
 *
 *  Created on: 13-11-2018
 *  Author: Paweł Warzecha
 */

#ifndef HAL_CLOCK_CLOCK_HPP_
#define HAL_CLOCK_CLOCK_HPP_

#include <stdint.h>
#include <stm32l4xx.h>

template<const uint32_t CLOCK_ADDRESS>
class Clock{

public:

protected:

private:

  /// Constructor, it is private so the class can't be instantiated.
  Clock(){}

  constexpr volatile static uint32_t adrCR          = (uint32_t)(&(((RCC_TypeDef *) CLOCK_ADDRESS)->CR));
  constexpr volatile static uint32_t adrPLLCFGR     = (uint32_t)(&(((RCC_TypeDef *) CLOCK_ADDRESS)->PLLCFGR));
  constexpr volatile static uint32_t adrPLLSAI1CFGR = (uint32_t)(&(((RCC_TypeDef *) CLOCK_ADDRESS)->PLLSAI1CFGR));
  constexpr volatile static uint32_t adrCIER        = (uint32_t)(&(((RCC_TypeDef *) CLOCK_ADDRESS)->CIER));
  constexpr volatile static uint32_t adrCIFR        = (uint32_t)(&(((RCC_TypeDef *) CLOCK_ADDRESS)->CIFR));
  constexpr volatile static uint32_t adrCICR        = (uint32_t)(&(((RCC_TypeDef *) CLOCK_ADDRESS)->CICR));
  constexpr volatile static uint32_t adrAHB1RSTR    = (uint32_t)(&(((RCC_TypeDef *) CLOCK_ADDRESS)->AHB1RSTR));
  constexpr volatile static uint32_t adrAHB2RSTR    = (uint32_t)(&(((RCC_TypeDef *) CLOCK_ADDRESS)->AHB2RSTR));
  constexpr volatile static uint32_t adrAHB3RSTR    = (uint32_t)(&(((RCC_TypeDef *) CLOCK_ADDRESS)->AHB3RSTR));
  constexpr volatile static uint32_t adrAPB1RSTR2   = (uint32_t)(&(((RCC_TypeDef *) CLOCK_ADDRESS)->APB1RSTR2));
  constexpr volatile static uint32_t adrAPB2RSTR    = (uint32_t)(&(((RCC_TypeDef *) CLOCK_ADDRESS)->APB2RSTR));
  constexpr volatile static uint32_t adrAHB1ENR     = (uint32_t)(&(((RCC_TypeDef *) CLOCK_ADDRESS)->AHB1ENR));
  constexpr volatile static uint32_t adrAHB2ENR     = (uint32_t)(&(((RCC_TypeDef *) CLOCK_ADDRESS)->AHB2ENR));
  constexpr volatile static uint32_t adrAHB3ENR     = (uint32_t)(&(((RCC_TypeDef *) CLOCK_ADDRESS)->AHB3ENR));
  constexpr volatile static uint32_t adrAPB1ENR1    = (uint32_t)(&(((RCC_TypeDef *) CLOCK_ADDRESS)->APB1ENR1));
  constexpr volatile static uint32_t adrAPB1ENR2    = (uint32_t)(&(((RCC_TypeDef *) CLOCK_ADDRESS)->APB1ENR2));
  constexpr volatile static uint32_t adrAPB2ENR     = (uint32_t)(&(((RCC_TypeDef *) CLOCK_ADDRESS)->APB2ENR));
};

#endif /* HAL_CLOCK_CLOCK_HPP_ */
