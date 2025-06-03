/**
 * Counter.hpp
 *
 *  Created on: 22-09-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_SCREENS_COUNTER_HPP_
#define APP_SCREENS_COUNTER_HPP_

#include "../Assets/Text/texts.h"
#include <Canvas.hpp>
#include <widgets/Image.hpp>

class Counter: public Canvas
{
public:
    /**
     * @brief Constructor
     */
    Counter() : first{7, 10, zero}, second{7, 10, zero}, third{7, 10, zero}, forth{7, 10, zero}

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
        add(&first, 21, 0);
        add(&second, 14, 0);
        add(&third, 7, 0);
        add(&forth, 0, 0);
        // validate();
    }

    void up_date() override
    {
        constexpr static uint8_t MAX_NUMBER{9};

        first_counter++;

        if (first_counter > MAX_NUMBER)
        {
            first_counter = 0;
            second_counter++;
        }
        if (second_counter > MAX_NUMBER)
        {
            second_counter = 0;
            third_counter++;
        }
        if (third_counter > MAX_NUMBER)
        {
            third_counter = 0;
            fotrh_counter++;
        }
        if (fotrh_counter > MAX_NUMBER)
        {
            fotrh_counter = 0;
        }
        first.setPixelMap(to_text(first_counter));
        second.setPixelMap(to_text(second_counter));
        third.setPixelMap(to_text(third_counter));
        forth.setPixelMap(to_text(fotrh_counter));
        // validate();
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

#endif /* APP_SCREENS_COUNTER_HPP_ */
