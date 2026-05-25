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
        static const WidgetAndPositions temp{.x = 0, .y = 0, .widget = temperature_text};
        static const std::array<const std::reference_wrapper<const WidgetAndPositions>, 1> widgets{temp};

        add(widgets);
    }

    void up_date() override
    {
        const auto temperature{BSP::get().thermometer.get_temperature()};
        const std::string temperature_str{std::to_string(temperature)};
        temperature_text.setText(temperature_str.substr(0, temperature_str.find(".") + 2) + "*C");
    }

private:
    Text temperature_text{"0*C", TextFactory::to_image, get_width()};
};
