/**
 * BSP.cpp
 *
 *  Created on: 06-03-2019
 *  @author: Paweł Warzecha
 */

#include "include/BSP/BSP.hpp"

#include <HAL/HAL.hpp>
#include <array>

namespace ISR
{
extern "C" void Dispaly_Redrawn(void);
}

BSP::BSP()
: display(DISPLAY_WIDTH, DISPLAY_HEIGHT, frame_buffer1.data()), button_right(HAL::BUTTON1, GPIO_Types::SignalLevel::High),
  button_left(HAL::BUTTON4, GPIO_Types::SignalLevel::High), button_up(HAL::BUTTON3, GPIO_Types::SignalLevel::High),
  button_down(HAL::BUTTON2, GPIO_Types::SignalLevel::High), up{HAL::up}, down{HAL::down}, left{HAL::left}, right{HAL::right}
{
}

BSP & BSP::get()
{
    static BSP instance;
    return instance;
}

// bool & BSP::up{HAL::up};
// bool & BSP::down{HAL::down};
// bool & BSP::left{HAL::left};
// bool & BSP::right{HAL::right};

void BSP::init()
{
    display.init();
}
