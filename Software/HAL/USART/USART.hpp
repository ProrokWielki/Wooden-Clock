/**
 *  @file USART.hpp
 *
 *  @brief Wrapper for the USARTs.
 *
 *  Created on: 02-05-2020
 *  @author: Paweł Warzecha
 */
#ifndef HAL_USART_USART_HPP_
#define HAL_USART_USART_HPP_

#include <stm32l4xx.h>

#include "../DMA/DMA.hpp"
#include "../Register/Register.hpp"

class USART
{

    USART(USART_TypeDef usart, DMA * dma = nullptr)
    : CR1(usart->CR1), CR2(usart->CR2), CR3(usart->CR3), BRR(usart->BRR), GTPR(usart->GTP), ROTR(usart->ROT), RQR(usart->RQR), ISR(usart->ISR), ICR(usart->ICR),
      RDR(usart->RDR), TDR(usart->TDR), dma_(dma)
    {
    }

private:
    Register CR1;
    Register CR2;
    Register CR3;
    Register BRR;
    Register GTPR;
    Register ROTR;
    Register RQR;
    Register ISR;
    Register ICR;
    Register RDR;
    Register TDR;

    DMA * dma_;
};

#endif /* HAL_USART_USART_HPP_ */
