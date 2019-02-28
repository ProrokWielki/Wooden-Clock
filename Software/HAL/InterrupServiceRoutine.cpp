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
    HAL::PB13::toogle_output_value();
    DMA1->IFCR |= ((1 << 6) | (1 << 4) | (1 << 5) | (1 << 7));
    NVIC_ClearPendingIRQ(DMA1_Channel2_IRQn);
}
void DMA1_Channel4_IRQHandler(void)
{
    HAL::PB13::toogle_output_value();
    DMA1->IFCR |= ((1 << 12) | (1 << 13) | (1 << 14) | (1 << 15));
    NVIC_ClearPendingIRQ(DMA1_Channel4_IRQn);
}
void DMA1_Channel6_IRQHandler(void)
{
    HAL::PB13::toogle_output_value();
    DMA1->IFCR |= ((1 << 20) | (1 << 21) | (1 << 22) | (1 << 23));
    NVIC_ClearPendingIRQ(DMA1_Channel6_IRQn);
}
void DMA2_Channel2_IRQHandler(void)
{
    HAL::PB13::toogle_output_value();
    DMA2->IFCR |= ((1 << 6) | (1 << 4) | (1 << 5) | (1 << 7));
    NVIC_ClearPendingIRQ(DMA2_Channel2_IRQn);
}
}  // namespace ISR
}  // namespace ISR
