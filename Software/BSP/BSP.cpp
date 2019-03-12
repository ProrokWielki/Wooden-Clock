/**
 * BSP.cpp
 *
 *  Created on: 06-03-2019
 *  @author: Paweł Warzecha
 */

#include "BSP.hpp"
#include "HAL.hpp"

Display BSP::display(32, 32, nullptr);

Button BSP::buton1(HAL::BUTTON, eHigh);
Button BSP::buton2(HAL::BUTTON2, eHigh);
Button BSP::buton3(HAL::BUTTON3, eHigh);
Button BSP::buton4(HAL::BUTTON4, eHigh);

void BSP::init()
{
    display.init();
}
