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

  typedef GPIO<GPIOA_BASE, 9> I2C1_SCL;
  typedef GPIO<GPIOA_BASE, 10> I2C1_SDA;

  typedef GPIO<GPIOB_BASE, 6> I2C4_SCL;
  typedef GPIO<GPIOB_BASE, 7> I2C4_SDA;
  typedef GPIO<GPIOB_BASE, 10> I2C2_SCL;
  typedef GPIO<GPIOB_BASE, 11> I2C2_SDA;
  typedef GPIO<GPIOB_BASE, 13> PB13;
  typedef GPIO<GPIOB_BASE, 14> OUTPUT_EN;
  typedef GPIO<GPIOB_BASE, 15> RESET;

  typedef GPIO<GPIOC_BASE, 0> I2C3_SCL;
  typedef GPIO<GPIOC_BASE, 1> I2C3_SDA;
  typedef GPIO<GPIOC_BASE, 6> TI_RESET;
  typedef GPIO<GPIOC_BASE, 7> DATA_IN;
  typedef GPIO<GPIOC_BASE, 8> CLOCK;
  typedef GPIO<GPIOC_BASE, 9> TRIGGER;

  typedef I2C<I2C1_BASE> I2C_1;
  typedef I2C<I2C2_BASE> I2C_2;
  typedef I2C<I2C3_BASE> I2C_3;
  typedef I2C<I2C4_BASE> I2C_4;

  void  init(void);
}

#endif /* HAL_HAL_HPP_ */
