/**
 * BSP.cpp
 *
 *  Created on: 06-03-2019
 *  @author: Paweł Warzecha
 */

#include "BSP.hpp"

Display BSP::display(32, 32, nullptr);

void BSP::init()
{
    display.init();
}
