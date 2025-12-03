/**
 *  @file Display.cpp
 *
 *  Created on: 30-11-2018
 *  @author: Paweł Warzecha
 */

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <string>

#include <HAL/HAL.hpp>
#include <utility>

#include "HAL/types.hpp"
#include "include/BSP/Display.hpp"

enum class Transfer : uint8_t
{
    TLC59208F_1_Transfer = 0,
    TLC59208F_2_Transfer = 1,
    TLC59208F_3_Transfer = 2,
    TLC59208F_4_Transfer = 3
};

Display::Display(uint8_t width, uint8_t height, std::span<uint8_t> frameBuffer)
: displayWidth(width), displayHeight(height), displayFrameBuffer(frameBuffer), transferComplete{true, true, true, true}
{
}

void Display::init()
{
    HAL::get().TLC59208F_1.set_transfer_complete_callback([&]() { transfer_complete(Transfer::TLC59208F_1_Transfer); });
    HAL::get().TLC59208F_2.set_transfer_complete_callback([&]() { transfer_complete(Transfer::TLC59208F_2_Transfer); });
    HAL::get().TLC59208F_3.set_transfer_complete_callback([&]() { transfer_complete(Transfer::TLC59208F_3_Transfer); });
    HAL::get().TLC59208F_4.set_transfer_complete_callback([&]() { transfer_complete(Transfer::TLC59208F_4_Transfer); });
}

void Display::set_display_redrawn_callback(std::function<void()> callback)
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

        std::ranges::fill(transferComplete.begin(), transferComplete.end(), false);

        const uint16_t current_line_offset = displayWidth * currentLine_;

        constexpr uint8_t NUM_OF_LEDS{8};
        constexpr uint8_t TLC59208F_1_LED_OFFSET{0};
        constexpr uint8_t TLC59208F_2_LED_OFFSET{TLC59208F_1_LED_OFFSET + NUM_OF_LEDS};
        constexpr uint8_t TLC59208F_3_LED_OFFSET{TLC59208F_2_LED_OFFSET + NUM_OF_LEDS};
        constexpr uint8_t TLC59208F_4_LED_OFFSET{TLC59208F_3_LED_OFFSET + NUM_OF_LEDS};

        HAL::get().TLC59208F_1.cache_all_leds_values(displayFrameBuffer.subspan(current_line_offset + TLC59208F_1_LED_OFFSET, NUM_OF_LEDS));
        HAL::get().TLC59208F_2.cache_all_leds_values(displayFrameBuffer.subspan(current_line_offset + TLC59208F_2_LED_OFFSET, NUM_OF_LEDS));
        HAL::get().TLC59208F_3.cache_all_leds_values(displayFrameBuffer.subspan(current_line_offset + TLC59208F_3_LED_OFFSET, NUM_OF_LEDS));
        HAL::get().TLC59208F_4.cache_all_leds_values(displayFrameBuffer.subspan(current_line_offset + TLC59208F_4_LED_OFFSET, NUM_OF_LEDS));

        HAL::get().SR_74HC595_1.output_enable(false);

        HAL::get().TLC59208F_1.send_cashed_leds_values();
        HAL::get().TLC59208F_2.send_cashed_leds_values();
        HAL::get().TLC59208F_3.send_cashed_leds_values();
        HAL::get().TLC59208F_4.send_cashed_leds_values();
    }
}

bool Display::is_line_drawn()
{
    for (const volatile auto transfer_completed : transferComplete)
        if (transfer_completed == false)
            return false;

    return true;
}

void Display::transfer_complete(const Transfer transferNumber)
{
    set_subtransfer_complete(transferNumber);

    if (true == is_line_drawn())
    {
        move_to_next_line();
    }
}

void Display::move_to_next_line()
{
    HAL::get().SR_74HC595_1.shift_bit(0 == currentLine_ ? GPIO_Types::SignalLevel::Low : GPIO_Types::SignalLevel::High);
    HAL::get().SR_74HC595_1.output_enable(true);

    currentLine_ += 1;
    currentLine_ %= displayHeight;
}

void Display::set_subtransfer_complete(const Transfer transferNumber)
{
    switch (transferNumber)
    {
        case Transfer::TLC59208F_1_Transfer:
            transferComplete[0] = true;
            break;
        case Transfer::TLC59208F_2_Transfer:
            transferComplete[1] = true;
            break;
        case Transfer::TLC59208F_3_Transfer:
            transferComplete[2] = true;
            break;
        case Transfer::TLC59208F_4_Transfer:
            transferComplete[3] = true;
            break;
        default:
            assert(false && "Unknown transfer number");
            break;  // do nothing
    }
}