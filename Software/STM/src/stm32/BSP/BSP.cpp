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
: display(DISPLAY_WIDTH, DISPLAY_HEIGHT, frame_buffer1.data()), button_right(HAL::get().BUTTON1, GPIO_Types::SignalLevel::High),
  button_left(HAL::get().BUTTON4, GPIO_Types::SignalLevel::High), button_up(HAL::get().BUTTON3, GPIO_Types::SignalLevel::High),
  button_down(HAL::get().BUTTON2, GPIO_Types::SignalLevel::High)
{
    HAL::get().USART_3.set_buffer_not_empty_callback([this](uint8_t data) { communication_interface.add_byte(data); });
    HAL::get().USART_3.set_idle_callback([this]() { communication_interface.message_end(); });
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
