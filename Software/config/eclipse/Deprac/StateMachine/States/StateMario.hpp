/**
 * StateMario.hpp
 *
 *  Created on: 10-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_STATEMACHINE_STATES_STATEMARIO_HPP_
#define APP_STATEMACHINE_STATES_STATEMARIO_HPP_

#include "../State.hpp"

#include "Assets/Images/Images.hpp"
#include "BSP.hpp"

class StateMario: public State
{
public:
    virtual void execute() override
    {
        BSP::display.set_frame_buffer(Mario_pixel_map);
    }

private:
};

#endif /* APP_STATEMACHINE_STATES_STATEMARIO_HPP_ */
