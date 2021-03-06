/**
 * InterrupServiceRoutine.cpp
 *
 *  Created on: 26-02-2019
 *  @author: Paweł Warzecha
 */

#include <FreeRTOS.h>
#include <task.h>

#include "BSP.hpp"
#include "HAL.hpp"

extern "C" {

namespace ISR
{
extern void xPortSysTickHandler();

void DMA1_Channel2_IRQHandler(void)
{
    HAL::DMA1_2.transfer_complete_callback();
}
void DMA1_Channel4_IRQHandler(void)
{
    HAL::DMA1_4.transfer_complete_callback();
}
void DMA2_Channel7_IRQHandler(void)
{
    HAL::DMA2_7.transfer_complete_callback();
}
void DMA2_Channel2_IRQHandler(void)
{
    HAL::DMA2_2.transfer_complete_callback();
}
void USART3_IRQHandler(void)
{
    uint8_t a = USART3->RDR;
    // switch (a)
    // {
    //     case 'u':
    //         HAL::up = true;
    //         break;
    //     case 'd':
    //         HAL::down = true;
    //         break;
    //     case 'l':
    //         HAL::left = true;
    //         break;
    //     case 'r':
    //         HAL::right = true;
    //         break;
    //     case 'w':
    //         HAL::reset = true;
    //         break;
    // }
    USART3->ICR |= (1 << 3);
}

void SysTick_Handler(void)
{
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
        xPortSysTickHandler();
}

void TIM2_IRQHandler(void)
{
    TIM2->SR = 0;
    BSP::display.draw_next_line();
}

void Dispaly_Redrawn(void)
{
}

}  // namespace ISR
}  // namespace ISR
