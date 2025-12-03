/**
 * Counter.hpp
 *
 *  Created on: 22-09-2019
 *  @author: Paweł Warzecha
 */

#pragma once

#include <Canvas.hpp>
#include <widgets/Text.hpp>

#include <BSP/Clock.hpp>

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
        add(&time_text, 0, 0);
    }

    void up_date() override
    {
        constexpr uint8_t MAX_SINGLE_DIDGET_MINUTE{9};

        const BSP2::Time time = BSP2::Clock::get_time();

        time_text.setText(std::to_string(time.hours) + ":" +
                          (time.minutes <= MAX_SINGLE_DIDGET_MINUTE ? "0" + std::to_string(time.minutes) : std::to_string(time.minutes)));
    }

private:
    Text time_text{"00:00", get_width()};
};
