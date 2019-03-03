/*
 * Display.cpp
 *
 *  Created on: 30 pa? 2018
 *      Author: Proro
 */

#include <stdint.h>
#include <string.h>

#include "HAL.hpp"

#include "Display.hpp"

Display::Display(uint8_t width, uint8_t height, uint8_t * fameBuffer)
: displayWidth(width), displayHeight(height), displayFrameBuffer(fameBuffer), transferComplete()
{
    HAL::COLUIMNS_1::init();
    HAL::COLUIMNS_2::init();
    HAL::COLUIMNS_3::init();
    HAL::COLUIMNS_4::init();

    HAL::COLUIMNS_1::set_transfer_complete_callback([this](void) { transferComplete[0] = true; });
    HAL::COLUIMNS_2::set_transfer_complete_callback([this](void) { transferComplete[1] = true; });
    HAL::COLUIMNS_3::set_transfer_complete_callback([this](void) { transferComplete[2] = true; });
    HAL::COLUIMNS_4::set_transfer_complete_callback([this](void) { transferComplete[3] = true; });

    uint8_t first[] = {0, 0x08};
    uint8_t second[] = {0xAA, 0xAA};

    HAL::COLUIMNS_1::set_registers_values(0x00, first, 2);
    HAL::COLUIMNS_2::set_registers_values(0x00, first, 2);
    HAL::COLUIMNS_3::set_registers_values(0x00, first, 2);
    HAL::COLUIMNS_4::set_registers_values(0x00, first, 2);

    HAL::COLUIMNS_1::set_registers_values(0x0C, second, 2);
    HAL::COLUIMNS_2::set_registers_values(0x0C, second, 2);
    HAL::COLUIMNS_3::set_registers_values(0x0C, second, 2);
    HAL::COLUIMNS_4::set_registers_values(0x0C, second, 2);

    HAL::ROW_MULTIPLEXER::init();
    HAL::ROW_MULTIPLEXER::set_all_outputs_value(eHigh);
}

void Display::draw(void)
{
    static uint8_t currentLine = 0;

    HAL::ROW_MULTIPLEXER::output_enable(false);

    draw_line(currentLine);

    while (not is_line_drawn())
        ;

    for (uint8_t i = 0; i < 4; i++)
    {
        transferComplete[i] = false;
    }

    if (0 == currentLine)
    {
        HAL::ROW_MULTIPLEXER::shift_bit(eLow);
    }
    else
    {
        HAL::ROW_MULTIPLEXER::shift_bit(eHigh);
    }

    HAL::ROW_MULTIPLEXER::output_enable(true);

    currentLine++;
    currentLine %= 32;
}

void Display::draw_line(uint8_t lineNumber)
{
    HAL::COLUIMNS_1::set_all_leds_values(&(displayFrameBuffer[32 * lineNumber + 0]));
    HAL::COLUIMNS_2::set_all_leds_values(&(displayFrameBuffer[32 * lineNumber + 8]));
    HAL::COLUIMNS_3::set_all_leds_values(&(displayFrameBuffer[32 * lineNumber + 16]));
    HAL::COLUIMNS_4::set_all_leds_values(&(displayFrameBuffer[32 * lineNumber + 24]));
}

bool Display::is_line_drawn()
{
    bool return_value = true;

    for (uint8_t i = 0; i < 4; i++)
    {
        return_value = return_value && transferComplete[i];
    }

    return return_value;
}
