/**
 * Counter.hpp
 *
 *  Created on: 22-09-2019
 *  @author: Paweł Warzecha
 */

#pragma once

#include <format>
#include <string>

#include <Canvas.hpp>
#include <widgets/Text.hpp>

#include <BSP/BSP.hpp>

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
        const auto temperature{BSP::thermometer.get_temperature()};
        std::string temperature_str = std::to_string(temperature);
        temperature_text.setText(temperature_str.substr(0, temperature_str.find(".")+2) + "*C");
    }

private:
    Text temperature_text{"0*C"};
};
