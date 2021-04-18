/**
 * Counter.hpp
 *
 *  Created on: 22-09-2019
 *  @author: Paweł Warzecha
 */

#pragma once

#include "../Assets/Text/texts.h"
#include <canvas.hpp>
#include <widgets/Image.hpp>

class Hour: public Canvas
{
public:
    /**
     * @brief Constructor
     */
    Hour() : first{7, 10, zero}, second{7, 10, zero}, third{7, 10, zero}, forth{7, 10, zero}

    {
    }

    uint8_t * to_text(uint8_t value)
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
    virtual void init() override
    {
        add(&first, 0, 0);
        add(&second, 7, 0);
        add(&third, 14, 0);
        add(&forth, 21, 0);
        validate();
    }

    virtual void up_date() override
    {
        uint32_t time = RTC->TR;
        first.setPixelMap(to_text((time >> 20) & 3));
        second.setPixelMap(to_text((time >> 16) & 15));
        third.setPixelMap(to_text((time >> 12) & 15));
        forth.setPixelMap(to_text((time >> 8) & 15));
        validate();
    }

private:
    uint8_t first_counter{0};
    uint8_t second_counter{0};
    uint8_t third_counter{0};
    uint8_t fotrh_counter{0};

    Image first;
    Image second;
    Image third;
    Image forth;
};
