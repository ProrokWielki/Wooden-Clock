/**
 * Counter.hpp
 *
 *  Created on: 22-09-2019
 *  @author: Paweł Warzecha
 */

#pragma once

#include "../Assets/Text/texts.h"
#include <Canvas.hpp>
#include <widgets/Image.hpp>

#include <HAL/HAL.hpp>

class Hour: public Canvas
{
public:
    /**
     * @brief Constructor
     */
    Hour() : first{7, 10, zero}, second{7, 10, zero}, colon_{4, 10, colon}, third{7, 10, zero}, forth{7, 10, zero}

    {
    }

    const uint8_t * to_text(uint8_t value)
    {
        switch (value)
        {
            case 0:
                return zero;
            case 1:
                return one;
            case 2:
                return two;
            case 3:
                return three;
            case 4:
                return four;
            case 5:
                return five;
            case 6:
                return six;
            case 7:
                return seven;
            case 8:
                return eight;
            case 9:
                return nine;
            default:
                return nullptr;
        }
    }

    /**
     * @brief Execution of the State action.
     */
    void init() override
    {
        add(&first, 0, 0);
        add(&second, first.getWidth(), 0);
        add(&colon_, first.getWidth() + second.getWidth(), 0);
        add(&third, first.getWidth() + second.getWidth() + colon_.getWidth(), 0);
        add(&forth, first.getWidth() + second.getWidth() + colon_.getWidth() + third.getWidth(), 0);
        // validate();
    }

    void up_date() override
    {
        first.setPixelMap(to_text(HAL::rtc.get_hours() / 10));
        second.setPixelMap(to_text(HAL::rtc.get_hours() % 10));
        if (HAL::rtc.get_seconds() % 2)
        {
            colon_.hide();
        }
        else
        {
            colon_.show();
        }
        third.setPixelMap(to_text(HAL::rtc.get_minutes() / 10));
        forth.setPixelMap(to_text(HAL::rtc.get_minutes() % 10));
    }

private:
    Image first;
    Image second;
    Image colon_;
    Image third;
    Image forth;
};
