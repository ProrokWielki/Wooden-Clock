/**
 * Counter.hpp
 *
 *  Created on: 22-09-2019
 *  @author: Paweł Warzecha
 */

#pragma once

#include "../Assets/Text/texts.hpp"

#include <Canvas.hpp>

#include <string>
#include <widgets/Text.hpp>

class Temperature: public Canvas
{
public:
    /**
     * @brief Constructor
     */
    Temperature() = default;

    /**
     * @brief Execution of the State action.
     */
    void init() override
    {
        add(&temperature_text, 0, 0);
    }

    void up_date() override
    {

        // uint32_t time = 0;
        // auto temperature = HAL::BME280_1.get_temperature();
        auto temperature = 13;
        temperature_text.setText(std::to_string(temperature) + "*C");

        // validate();
    }

private:
    Text temperature_text{"0*C"};
};
