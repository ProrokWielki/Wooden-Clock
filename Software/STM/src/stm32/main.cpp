#include <cassert>

#include "APP.hpp"
#include <BSP/BSP.hpp>
#include <HAL/HAL.hpp>

#include <HAL/RTC.hpp>

#include "Assets/Images/Images.hpp"

#include <stm32l452xx.h>

int main()
{
    HAL::init();
    BSP::init();

    BSP::display.set_frame_buffer(Mario_pixel_map);

    NVIC_EnableIRQ(DMA1_Channel2_IRQn);
    NVIC_EnableIRQ(DMA1_Channel4_IRQn);
    NVIC_EnableIRQ(DMA2_Channel7_IRQn);
    NVIC_EnableIRQ(DMA2_Channel2_IRQn);
    NVIC_EnableIRQ(USART3_IRQn);
    NVIC_EnableIRQ(TIM2_IRQn);

    APP_init();

    for (;;)
    {
    }
    return 0;
}
