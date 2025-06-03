/**
 * Counter.hpp
 *
 *  Created on: 22-09-2019
 *  @author: Paweł Warzecha
 */

#pragma once

#include "../Assets/Text/texts.h"
#include <Canvas.hpp>
#include <DRV/BME280.hpp>
#include <widgets/Image.hpp>

#include <HAL/HAL.hpp>

class Temperature: public Canvas
{
public:
    /**
     * @brief Constructor
     */
    Temperature() : first{7, 10, zero}, second{7, 10, zero}, degree_{7, 10, degree}, capital_c_{9, 10, capital_C}

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
        add(&degree_, first.getWidth() + second.getWidth(), 0);
        add(&capital_c_, first.getWidth() + second.getWidth() + degree_.getWidth(), 0);
        // validate();
    }

    void up_date() override
    {

        // uint32_t time = 0;
        first.setPixelMap(to_text(static_cast<uint8_t>(HAL::BME280_1.get_temperature()) / 10));
        second.setPixelMap(to_text(static_cast<uint8_t>(HAL::BME280_1.get_temperature()) % 10));

        // validate();
    }

private:
    // BME280 & bme_;
    Image first;
    Image second;
    Image degree_;
    Image capital_c_;
};
