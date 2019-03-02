/*
 * Display.cpp
 *
 *  Created on: 30 pa? 2018
 *      Author: Proro
 */

#include <stdint.h>
#include <string.h>

#include "Display.hpp"

#include "HAL.hpp"

void Display::draw(void)
{
    static uint8_t currentLine = 0;

    HAL::ROW_MULTIPLEXER::output_enable(false);

    draw_line(currentLine);

    while (not is_line_drawn())
        ;

    for (uint8_t i = 0; i < 4; i++) {
        transferComplete[i] = false;
    }

    if (0 == currentLine) {
        HAL::ROW_MULTIPLEXER::shift_bit(eLow);
    } else
        HAL::ROW_MULTIPLEXER::shift_bit(eHigh);

    HAL::ROW_MULTIPLEXER::output_enable(true);

    currentLine++;
    currentLine %= 32;
}

void Display::draw_line(uint8_t lineNumber)
{
    HAL::COLUIMNS_1::set_all_leds_value(&(displayFrameBuffer[32 * lineNumber + 0]));
    HAL::COLUIMNS_2::set_all_leds_value(&(displayFrameBuffer[32 * lineNumber + 8]));
    HAL::COLUIMNS_3::set_all_leds_value(&(displayFrameBuffer[32 * lineNumber + 16]));
    HAL::COLUIMNS_4::set_all_leds_value(&(displayFrameBuffer[32 * lineNumber + 24]));
}

bool Display::is_line_drawn()
{
    bool return_value = true;

    for (uint8_t i = 0; i < 4; i++) {
        return_value = return_value && transferComplete[i];
    }

    return return_value;
}
