/**
 * BSP.cpp
 *
 *  Created on: 06-03-2019
 *  @author: Paweł Warzecha
 */

#include "BSP.hpp"
#include "HAL.hpp"

namespace ISR
{
extern "C" void Dispaly_Redrawn(void);
}

Display BSP::display(32, 32, nullptr);

Button BSP::button_right(HAL::BUTTON1, eHigh);
Button BSP::button_down(HAL::BUTTON2, eHigh);
Button BSP::button_up(HAL::BUTTON3, eHigh);
Button BSP::button_left(HAL::BUTTON4, eHigh);

void BSP::init()
{
    display.init();
}
