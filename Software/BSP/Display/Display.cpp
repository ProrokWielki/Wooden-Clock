/**
 *  @file Display.cpp
 *
 *  Created on: 30-11-2018
 *  @author: Paweł Warzecha
 */

#include <algorithm>
#include <iterator>
#include <stdint.h>
#include <string.h>

#include "HAL.hpp"

#include "Display.hpp"

Display::Display(uint8_t width, uint8_t height, uint8_t * fameBuffer)
: displayWidth(width), displayHeight(height), displayFrameBuffer(fameBuffer), transferComplete{true, true, true, true}, currentLine_(0)
{
}

void Display::init(void)
{
    HAL::TLC59208F_1.set_transfer_complete_callback([&](void) { transfer_complete(0); });
    HAL::TLC59208F_2.set_transfer_complete_callback([&](void) { transfer_complete(1); });
    HAL::TLC59208F_3.set_transfer_complete_callback([&](void) { transfer_complete(2); });
    HAL::TLC59208F_4.set_transfer_complete_callback([&](void) { transfer_complete(3); });
}

void Display::set_dispaly_redrawn_callback(std::function<void()> callback)
{
    display_redrawn_callback = callback;
}

void Display::draw_next_line(void)
{
    __disable_irq();
    if (true == is_line_drawn())
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            transferComplete[i] = false;
        }

        HAL::SR_74HC595_1.output_enable(false);

        HAL::TLC59208F_1.set_all_leds_values(&(displayFrameBuffer[32 * currentLine_ + 0]));
        HAL::TLC59208F_2.set_all_leds_values(&(displayFrameBuffer[32 * currentLine_ + 8]));
        HAL::TLC59208F_3.set_all_leds_values(&(displayFrameBuffer[32 * currentLine_ + 16]));
        HAL::TLC59208F_4.set_all_leds_values(&(displayFrameBuffer[32 * currentLine_ + 24]));
    }
    __enable_irq();
}

bool Display::is_line_drawn()
{
    for (uint8_t i = 0; i < 4; i++)
        if (transferComplete[i] == false)
            return false;

    return true;
}

void Display::transfer_complete(const uint8_t transferNumber)
{
    transferComplete[transferNumber] = true;
    if (true == is_line_drawn())
    {

        HAL::SR_74HC595_1.shift_bit(0 == currentLine_ ? eLow : eHigh);

        HAL::SR_74HC595_1.output_enable(true);

        currentLine_++;
        currentLine_ %= 32;

        if (0 == currentLine_)
        {
            //        display_redrawn_callback();
        }
    }
}
