/**
  * DMA.hpp
  *
  *  Created on: 13-11-2018
  *  @author: Paweł Warzecha
  */

#ifndef HAL_DMA_DMA_HPP_
#define HAL_DMA_DMA_HPP_

#include <stdint.h>
#include <stm32l4xx.h>

#include "../Register/Register.hpp"

#include "DMA_types.hpp"

constexpr static uint8_t PRIORITY_LEVEL_FIELD_BIT_LENGTH = 2;

template<const uint32_t DMA_CHANNEL_ADDRESS>
  class DMA
  {
  public:

  static void set_priority(DMAPriority_t eDMAPriority)
  {
    CCR::set_value(eDMAPriority, DMA_CCR_PL_Pos, PRIORITY_LEVEL_FIELD_BIT_LENGTH);
  }

  protected:

  private:
    DMA(){};

    constexpr volatile static uint32_t adrCCR = (uint32_t)(&(((DMA_Channel_TypeDef *) DMA_CHANNEL_ADDRESS)->CCR));

    typedef Register<adrCCR> CCR;

};

#endif /* HAL_DMA_DMA_HPP_ */
