/**
 * StateHourglass.hpp
 *
 *  Created on: 10-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_STATEMACHINE_STATES_STATEHOURGLASS_HPP_
#define APP_STATEMACHINE_STATES_STATEHOURGLASS_HPP_

#include <BSP/BSP.hpp>

#include <Canvas.hpp>
#include <widgets/Animation.hpp>

#include "Animations/Animations.hpp"

class StateHourglass: public Canvas
{
public:
    /**
     * @brief Constructor
     */
    StateHourglass() : hourglass{get_animation(AnimationType::HOURGLASS)}
    {
    }

    /**
     * @brief Execution of the State action.
     */
    void init() override
    {
        static const WidgetAndPositions hour{.x = 0, .y = 0, .widget = hourglass};
        static const std::array<const std::reference_wrapper<const WidgetAndPositions>, 1> widgets{hour};

        add(widgets);
    }

    void up_date() override
    {
    }

private:
    Animation & hourglass;
};

#endif /* APP_STATEMACHINE_STATES_STATEHOURGLASS_HPP_ */
