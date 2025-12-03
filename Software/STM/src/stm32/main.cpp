#include "APP.hpp"
#include <BSP/BSP.hpp>
#include <HAL/HAL.hpp>

#include "Assets/Images/Images.hpp"
#include <widgets/Image.hpp>

#include <stm32l452xx.h>

int main()
{
    HAL::get().init();
    BSP::get().init();

    BSP::get().display.set_frame_buffer(BSP::get().frame_buffer1);

    NVIC_EnableIRQ(DMA1_Channel2_IRQn);
    NVIC_EnableIRQ(DMA1_Channel4_IRQn);
    NVIC_EnableIRQ(DMA2_Channel7_IRQn);
    NVIC_EnableIRQ(DMA2_Channel2_IRQn);
    NVIC_EnableIRQ(USART3_IRQn);
    NVIC_EnableIRQ(TIM2_IRQn);

    app_init();

    for (;;)
    {
    }
    return 0;
}
