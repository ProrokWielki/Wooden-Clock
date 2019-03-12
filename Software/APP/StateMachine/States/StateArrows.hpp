/**
 * StateArrows.hpp
 *
 *  Created on: 10-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_STATEMACHINE_STATES_STATEARROWS_HPP_
#define APP_STATEMACHINE_STATES_STATEARROWS_HPP_

#include "../State.hpp"

#include "Assets/Images/Images.hpp"
#include "BSP.hpp"

class StateArrows: public State
{
public:
    StateArrows() : frames{Arrows1, Arrows2}
    {
    }

    virtual void execute() override
    {
        static uint8_t currentFrame = 0;

        BSP::display.set_frame_buffer(frames[currentFrame++]);

        currentFrame %= 2;
    }

private:
    uint8_t * frames[2];
};

#endif /* APP_STATEMACHINE_STATES_STATEARROWS_HPP_ */
