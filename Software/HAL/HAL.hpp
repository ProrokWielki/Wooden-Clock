/**
 *  @file HAL.hpp
 *
 *  Created on: 21-11-2018
 *  @author: Paweł Warzecha
 */

#ifndef HAL_HAL_HPP_
#define HAL_HAL_HPP_

#include "Clock/Clock.hpp"
#include "DMA/DMA.hpp"
#include "GPIO/GPIO.hpp"
#include "I2C/I2C.hpp"

#include "74HC595/74HC595.hpp"
#include "TLC59208F/TLC59208F.hpp"

namespace HAL
{

typedef GPIO<GPIOA_BASE, 9> I2C1_SCL;
typedef GPIO<GPIOA_BASE, 10> I2C1_SDA;

typedef GPIO<GPIOB_BASE, 6> I2C4_SCL;
typedef GPIO<GPIOB_BASE, 7> I2C4_SDA;
typedef GPIO<GPIOB_BASE, 10> I2C2_SCL;
typedef GPIO<GPIOB_BASE, 11> I2C2_SDA;
typedef GPIO<GPIOB_BASE, 13> PB13;

typedef GPIO<GPIOC_BASE, 0> I2C3_SCL;
typedef GPIO<GPIOC_BASE, 1> I2C3_SDA;

typedef DMA<DMA1_BASE, 2, DMA1_Channel2_BASE> DMA1_2;
typedef DMA<DMA1_BASE, 4, DMA1_Channel4_BASE> DMA1_4;
typedef DMA<DMA2_BASE, 2, DMA2_Channel2_BASE> DMA2_2;
typedef DMA<DMA2_BASE, 7, DMA2_Channel7_BASE> DMA2_7;

typedef I2C<I2C1_BASE, DMA2_7> I2C_1;
typedef I2C<I2C2_BASE, DMA1_4> I2C_2;
typedef I2C<I2C3_BASE, DMA1_2> I2C_3;
typedef I2C<I2C4_BASE, DMA2_2> I2C_4;

typedef SR_74HC595<GPIO<GPIOC_BASE, 7>, GPIO<GPIOC_BASE, 8>, GPIO<GPIOC_BASE, 9>, GPIO<GPIOB_BASE, 14>, GPIO<GPIOB_BASE, 15>> ROW_MULTIPLEXER;

typedef TLC59208F<I2C_1, 0x40, GPIO<GPIOC_BASE, 6>> COLUIMNS_1;
typedef TLC59208F<I2C_2, 0x42, GPIO<GPIOC_BASE, 6>> COLUIMNS_2;
typedef TLC59208F<I2C_3, 0x44, GPIO<GPIOC_BASE, 6>> COLUIMNS_3;
typedef TLC59208F<I2C_4, 0x46, GPIO<GPIOC_BASE, 6>> COLUIMNS_4;

void init(void);

}  // namespace HAL

#endif /* HAL_HAL_HPP_ */
