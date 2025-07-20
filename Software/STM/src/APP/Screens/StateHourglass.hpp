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

#include "../Assets/Images/Images.hpp"

class StateHourglass: public Canvas
{
public:
    /**
     * @brief Constructor
     */
    StateHourglass()
    : hourglass{32, 32, {frame_1,  frame_2,  frame_3,  frame_4,  frame_5,  frame_6,  frame_7,  frame_8,  frame_9,  frame_10, frame_11,
                         frame_12, frame_13, frame_14, frame_15, frame_16, frame_17, frame_18, frame_19, frame_20, frame_21}}

    {
    }

    /**
     * @brief Execution of the State action.
     */
    void init() override
    {
        add(&hourglass);
        // validate();
    }

    void up_date() override
    {
    }

private:
    Animation<21> hourglass;
};

#endif /* APP_STATEMACHINE_STATES_STATEHOURGLASS_HPP_ */
