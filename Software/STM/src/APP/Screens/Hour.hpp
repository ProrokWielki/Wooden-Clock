/**
 * Counter.hpp
 *
 *  Created on: 22-09-2019
 *  @author: Paweł Warzecha
 */

#pragma once

#include "Widget.hpp"
#include <Canvas.hpp>
#include <array>
#include <functional>

#include <widgets/Text.hpp>

#include <BSP/Clock.hpp>

#include "Texts/texts.hpp"

class Hour: public Canvas
{
public:
    /**
     * @brief Constructor
     */
    Hour() = default;

    /**
     * @brief Execution of the State action.
     */
    void init() override
    {
        static const WidgetAndPositions time{.x = 0, .y = 0, .widget = time_text};
        static const std::array<const std::reference_wrapper<const WidgetAndPositions>, 1> widgets{time};
        add(widgets);
    }

    void up_date() override
    {
        constexpr uint8_t MAX_SINGLE_DIDGET_MINUTE{9};

        const BSP2::Time time = BSP2::Clock::get_time();

        time_text.setText(std::to_string(time.hours) + ":" +
                          (time.minutes <= MAX_SINGLE_DIDGET_MINUTE ? "0" + std::to_string(time.minutes) : std::to_string(time.minutes)));
    }

private:
    Text time_text{"00:00", TextFactory::to_image, get_width()};
};
