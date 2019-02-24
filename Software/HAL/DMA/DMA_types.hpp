/**
  * DMA_types.hpp
  *
  *  Created on: 30-11-2018
  *  @author: Paweł Warzecha
  */

#ifndef HAL_DMA_DMA_TYPES_HPP_
#define HAL_DMA_DMA_TYPES_HPP_

typedef enum
{
  eMemeoryToMemory,
  eMemmoryToPeriphery,
  ePeripheryToMemory,
  ePeripheryToPeriphery
}DMATransferType_t;

typedef enum
{
  eLow,
  eMedium,
  eHigh,
  eVeryHigh
}DMAPriority_t;

typedef enum
{
  e8Bits,
  e16Bits,
  e32Bits
}DMAMemeorySize_t;

typedef enum
{
  e8Bits,
  e16Bits,
  e32Bits
}DMAPeripherySize_t;

typedef enum
{
  eMemoryIncrement = DMA_CCR_MINC_Pos,
  ePeripheryIncrement = DMA_CCR_PINC_Pos,
  eCircularMode = DMA_CCR_CIRC_Pos
}DMAOptions_t;

typedef enum
{
  eTransferError = DMA_CCR_TEIE_Pos,
  eHalfTransfer = DMA_CCR_HTIE_Pos,
  eTransferCompleted = DMA_CCR_TCIE_Pos
}DMAInterrupts_t;
#endif /* HAL_DMA_DMA_TYPES_HPP_ */
