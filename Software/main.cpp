#include <stdint.h>
#include <string.h>

#include "Display/Display.hpp"
#include "HAL.hpp"

#include "APP.hpp"
#include "APP/Assets/Images/Images.hpp"

int main(void)
{

    NVIC_EnableIRQ(DMA1_Channel2_IRQn);
    NVIC_EnableIRQ(DMA1_Channel4_IRQn);
    NVIC_EnableIRQ(DMA2_Channel7_IRQn);
    NVIC_EnableIRQ(DMA2_Channel2_IRQn);

    HAL::init();

    SystemCoreClockUpdate();

    while (HAL::BUTTON2::get_input_value() == eLow)
    {
        ;
    }

    DMA2_CSELR->CSELR |= (5 << 24);
    DMA1_CSELR->CSELR |= ((3 << 12) | (3 << 4));

    APP_init();

    for (;;)
    {
    }
    return 0;
}
