/**
 * InterrupServiceRoutine.cpp
 *
 *  Created on: 26-02-2019
 *  @author: Paweł Warzecha
 */

#include <stm32l452xx.h>

#include <FreeRTOS.h>
#include <task.h>

#include <BSP/BSP.hpp>
#include <HAL/HAL.hpp>

extern "C" {

namespace ISR
{
extern void xPortSysTickHandler();  // NOLINT(readability-identifier-naming)

void DMA1_Channel2_IRQHandler(void)  // NOLINT(readability-identifier-naming)
{
    HAL::DMA1_2.transfer_complete_callback();
}
void DMA1_Channel4_IRQHandler(void)  // NOLINT(readability-identifier-naming)
{
    HAL::DMA1_4.transfer_complete_callback();
}
void DMA2_Channel7_IRQHandler(void)  // NOLINT(readability-identifier-naming)
{
    HAL::DMA2_7.transfer_complete_callback();
}
void DMA2_Channel2_IRQHandler(void)  // NOLINT(readability-identifier-naming)
{
    HAL::DMA2_2.transfer_complete_callback();
}
void USART3_IRQHandler(void)  // NOLINT(readability-identifier-naming)
{
    const uint8_t a = USART3->RDR;
    if (HAL::head > 30)
    {
        HAL::head = 0;
    }
    HAL::uart_buffer[HAL::head] = a;
    HAL::head += 1;
    switch (a)
    {
        case 'u':
            HAL::up = true;
            break;
        case 'd':
            HAL::down = true;
            break;
        case 'l':
            HAL::left = true;
            break;
        case 'r':
            HAL::right = true;
            break;
        case 'w':
            HAL::reset = true;
            break;
        case 'k':
            HAL::parse_time = true;
            break;
    }
    USART3->ICR |= 0b0000'0000'0001'0010'0000'1101'11101'1111;  // clear all interrupts TODO: make it right
}

void SysTick_Handler(void)  // NOLINT(readability-identifier-naming)
{
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
        xPortSysTickHandler();
}

void TIM2_IRQHandler(void)  // NOLINT(readability-identifier-naming)
{
    BSP::display.draw_next_line();
    HAL::Timer2.clear_interrupt_flag(timer_types::Interrupt::UPDATE);
}

void Dispaly_Redrawn(void)
{
}

}  // namespace ISR
}  // namespace ISR
