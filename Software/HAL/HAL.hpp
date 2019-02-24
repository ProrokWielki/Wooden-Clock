/*
 * HAL.hpp
 *
 *  Created on: 21-11-2018
 *      Author: Pawe� Warzecha
 */

#ifndef HAL_HAL_HPP_
#define HAL_HAL_HPP_

#include "I2C/I2C.hpp"
#include "GPIO/GPIO.hpp"
#include "Clock/Clock.hpp"

namespace HAL
{

  typedef GPIO<GPIOA_BASE, 9> PA9;
  typedef GPIO<GPIOA_BASE, 10> PA10;

  typedef GPIO<GPIOB_BASE, 6> PB6;
  typedef GPIO<GPIOB_BASE, 7> PB7;
  typedef GPIO<GPIOB_BASE, 10> PB10;
  typedef GPIO<GPIOB_BASE, 11> PB11;
  typedef GPIO<GPIOB_BASE, 14> PB14;
  typedef GPIO<GPIOB_BASE, 13> PB13;
  typedef GPIO<GPIOB_BASE, 15> PB15;

  typedef GPIO<GPIOC_BASE, 0> PC0;
  typedef GPIO<GPIOC_BASE, 1> PC1;
  typedef GPIO<GPIOC_BASE, 6> PC6;
  typedef GPIO<GPIOC_BASE, 7> PC7;
  typedef GPIO<GPIOC_BASE, 8> PC8;
  typedef GPIO<GPIOC_BASE, 9> PC9;

  typedef I2C<I2C1_BASE> I2C_1;
  typedef I2C<I2C2_BASE> I2C_2;
  typedef I2C<I2C3_BASE> I2C_3;
  typedef I2C<I2C4_BASE> I2C_4;

  void
  init(void);
}

#endif /* HAL_HAL_HPP_ */
