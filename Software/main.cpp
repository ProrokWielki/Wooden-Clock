#include <stdint.h>

#include "APP.hpp"
#include "BSP.hpp"
#include "HAL.hpp"

#include "Assets/Images/Images.hpp"

int main(void)
{

    HAL::init();
    BSP::init();

    BSP::display.set_frame_buffer(Arrows1);

    while (HAL::BUTTON2.get_input_value() == eLow or HAL::BUTTON.get_input_value() == eLow or HAL::BUTTON3.get_input_value() == eLow or
           HAL::BUTTON4.get_input_value() == eLow)
    {
        ;
    }

    NVIC_EnableIRQ(DMA1_Channel2_IRQn);
    NVIC_EnableIRQ(DMA1_Channel4_IRQn);
    NVIC_EnableIRQ(DMA2_Channel7_IRQn);
    NVIC_EnableIRQ(DMA2_Channel2_IRQn);
    NVIC_EnableIRQ(TIM2_IRQn);

    APP_init();

    for (;;)
    {
    }
    return 0;
}
