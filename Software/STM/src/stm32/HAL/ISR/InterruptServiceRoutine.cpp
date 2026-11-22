/**
 * InterrupServiceRoutine.cpp
 *
 *  Created on: 26-02-2019
 *  @author: Paweł Warzecha
 */

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
    HAL::get().DMA1_2.transfer_complete_callback();
}
void DMA1_Channel3_IRQHandler(void)  // NOLINT(readability-identifier-naming)
{
    HAL::get().DMA1_3.transfer_complete_callback();
}
void DMA1_Channel4_IRQHandler(void)  // NOLINT(readability-identifier-naming)
{
    HAL::get().DMA1_4.transfer_complete_callback();
}
void DMA2_Channel7_IRQHandler(void)  // NOLINT(readability-identifier-naming)
{
    HAL::get().DMA2_7.transfer_complete_callback();
}
void DMA2_Channel2_IRQHandler(void)  // NOLINT(readability-identifier-naming)
{
    HAL::get().DMA2_2.transfer_complete_callback();
}

void I2C1_EV_IRQHandler()  // NOLINT(readability-identifier-naming)
{
    HAL::get().I2C_1.transfer_stop_callback();
}

void I2C2_EV_IRQHandler()  // NOLINT(readability-identifier-naming)
{
    HAL::get().I2C_2.transfer_stop_callback();
}

void I2C3_EV_IRQHandler()  // NOLINT(readability-identifier-naming)
{
    HAL::get().I2C_3.transfer_stop_callback();
}

void I2C4_EV_IRQHandler()  // NOLINT(readability-identifier-naming)
{
    HAL::get().I2C_4.transfer_stop_callback();
}

void USART3_IRQHandler(void)  // NOLINT(readability-identifier-naming)
{
    HAL::get().USART_3.handle_interrupts();
}
void UART4_IRQHandler(void)  // NOLINT(readability-identifier-naming)
{
    HAL::get().USART_4.handle_interrupts();
}

void SysTick_Handler(void)  // NOLINT(readability-identifier-naming)
{
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
        xPortSysTickHandler();
}

void TIM2_IRQHandler(void)  // NOLINT(readability-identifier-naming)
{
    BSP::get().display.draw_next_line();
    HAL::get().Timer2.clear_interrupt_flag(timer_types::Interrupt::UPDATE);
}

}  // namespace ISR
}
