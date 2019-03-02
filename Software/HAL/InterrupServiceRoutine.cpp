/**
 * InterrupServiceRoutine.cpp
 *
 *  Created on: 26-02-2019
 *  @author: Paweł Warzecha
 */

#include "HAL.hpp"

extern "C" {

namespace ISR
{
void DMA1_Channel2_IRQHandler(void)
{
    HAL::DMA1_2::transfer_complete_callback();
}
void DMA1_Channel4_IRQHandler(void)
{
    HAL::DMA1_4::transfer_complete_callback();
}
void DMA2_Channel7_IRQHandler(void)
{
    HAL::DMA2_7::transfer_complete_callback();
}
void DMA2_Channel2_IRQHandler(void)
{
    HAL::DMA2_2::transfer_complete_callback();
}
}  // namespace ISR
}  // namespace ISR
