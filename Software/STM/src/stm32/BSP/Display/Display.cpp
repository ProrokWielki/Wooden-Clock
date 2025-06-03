/**
 *  @file Display.cpp
 *
 *  Created on: 30-11-2018
 *  @author: Paweł Warzecha
 */

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <string>

#include <HAL/HAL.hpp>

#include "HAL/types.hpp"
#include "include/BSP/Display.hpp"

Display::Display(uint8_t width, uint8_t height, const uint8_t * frameBuffer)
: displayWidth(width), displayHeight(height), displayFrameBuffer(frameBuffer), transferComplete{true, true, true, true}
{
}

void Display::init()
{
    HAL::TLC59208F_1.set_transfer_complete_callback([&]() { transfer_complete(0); });
    HAL::TLC59208F_2.set_transfer_complete_callback([&]() { transfer_complete(1); });
    HAL::TLC59208F_3.set_transfer_complete_callback([&]() { transfer_complete(2); });
    HAL::TLC59208F_4.set_transfer_complete_callback([&]() { transfer_complete(3); });
}

void Display::set_dispaly_redrawn_callback(std::function<void()> callback)
{
    display_redrawn_callback = callback;
}

void Display::draw_next_line()
{

    if (true == is_line_drawn())
    {

        if (0 == currentLine_)
        {
            if (display_redrawn_callback)
                display_redrawn_callback();
        }

        std::ranges::fill(transferComplete.begin(),transferComplete.end(), false);


        const uint16_t current_line_offset = 32 * currentLine_;

        HAL::TLC59208F_1.cashe_all_leds_values(&(displayFrameBuffer[current_line_offset + 0]));
        HAL::TLC59208F_2.cashe_all_leds_values(&(displayFrameBuffer[current_line_offset + 8]));
        HAL::TLC59208F_3.cashe_all_leds_values(&(displayFrameBuffer[current_line_offset + 16]));
        HAL::TLC59208F_4.cashe_all_leds_values(&(displayFrameBuffer[current_line_offset + 24]));

        HAL::SR_74HC595_1.output_enable(false);

        HAL::TLC59208F_1.send_cashed_leds_values();
        HAL::TLC59208F_2.send_cashed_leds_values();
        HAL::TLC59208F_3.send_cashed_leds_values();
        HAL::TLC59208F_4.send_cashed_leds_values();
    }
}

bool Display::is_line_drawn()
{
    for (const volatile auto transfer_completed: transferComplete)
        if (transfer_completed == false)
            return false;

    return true;
}

void Display::transfer_complete(const uint8_t transferNumber)
{
    transferComplete[transferNumber] = true;
    if (true == is_line_drawn())
    {

        HAL::SR_74HC595_1.shift_bit(0 == currentLine_ ? GPIO_Types::SignalLevel::Low : GPIO_Types::SignalLevel::High);

        HAL::SR_74HC595_1.output_enable(true);

        currentLine_ += 1;
        currentLine_ %= 32;
    }
}
