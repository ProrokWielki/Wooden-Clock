/**
 * BSP.cpp
 *
 *  Created on: 06-03-2019
 *  @author: Paweł Warzecha
 */

#include "include/BSP/BSP.hpp"

#include <HAL/HAL.hpp>
#include <array>

#include "Assets/Images/Images.hpp"

namespace ISR
{
extern "C" void Dispaly_Redrawn(void);
}

constexpr static uint32_t DISPLAY_WIDTH{32};
constexpr static uint32_t DISPLAY_HEIGHT{32};

std::array<uint8_t, DISPLAY_WIDTH * DISPLAY_HEIGHT> frame_buffer1{};
std::array<uint8_t, DISPLAY_WIDTH * DISPLAY_HEIGHT> frame_buffer2{};

Display BSP::display(DISPLAY_WIDTH, DISPLAY_HEIGHT, Arrows1);

Button BSP::button_right(HAL::BUTTON1, GPIO_Types::SignalLevel::High);
Button BSP::button_down(HAL::BUTTON2, GPIO_Types::SignalLevel::High);
Button BSP::button_up(HAL::BUTTON3, GPIO_Types::SignalLevel::High);
Button BSP::button_left(HAL::BUTTON4, GPIO_Types::SignalLevel::High);

void BSP::init()
{
    display.init();
}
