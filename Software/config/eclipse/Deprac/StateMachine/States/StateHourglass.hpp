/**
 * StateHourglass.hpp
 *
 *  Created on: 10-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_STATEMACHINE_STATES_STATEHOURGLASS_HPP_
#define APP_STATEMACHINE_STATES_STATEHOURGLASS_HPP_

#include "BSP.hpp"

#include "StateMachine/State.hpp"

#include "Assets/Images/Images.hpp"

class StateHourglass: public State
{
public:
    /**
     * @brief Constructor
     */
    StateHourglass()
    : frames{frame_1,  frame_2,  frame_3,  frame_4,  frame_5,  frame_6,  frame_7,  frame_8,  frame_9,  frame_10, frame_11,
             frame_12, frame_13, frame_14, frame_15, frame_16, frame_17, frame_18, frame_19, frame_20, frame_21}

    {
    }

    /**
     * @brief Execution of the State action.
     */
    virtual void execute() override
    {
        static uint8_t currentFrame = 0;

        BSP::display.set_frame_buffer(frames[currentFrame++]);
        if (currentFrame == 21)
            currentFrame = 0;
    }

private:
    uint8_t * frames[21];
};

#endif /* APP_STATEMACHINE_STATES_STATEHOURGLASS_HPP_ */
