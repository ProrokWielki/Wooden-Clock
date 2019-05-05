/**
 * StateMachine.hpp
 *
 *  Created on: 09-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_STATEMACHINE_STATEMACHINE_HPP_
#define APP_STATEMACHINE_STATEMACHINE_HPP_

#include <map>
#include <stdint.h>

#include "BSP.hpp"
#include "State.hpp"

enum signal
{
    BUTTON1,
    BUTTON2,
    BUTTON3,
    BUTTON4,
    NONE
};

class StateMachine
{
public:
    explicit StateMachine(State * startState);

    void update(void)
    {
        if (BSP::buton1.wasReleased())
        {
            recieved_ = BUTTON1;
        }

        if (recieved_ != NONE)
        {
            currentState_ = transiton(currentState_, recieved_);
            recieved_ = NONE;
        }
        currentState_->execute();
    }

private:
    typedef std::pair<State *, signal> Input;

    std::map<Input, State *> TransitionMatrix_;

    State * transiton(State * current, signal signal)
    {
        return TransitionMatrix_.at(std::make_pair(current, signal));
    }

    signal recieved_{NONE};

    State * currentState_;
};

#endif /* APP_STATEMACHINE_STATEMACHINE_HPP_ */
