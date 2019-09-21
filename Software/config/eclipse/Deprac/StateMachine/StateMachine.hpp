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

enum class Signal;

typedef std::map<std::pair<State *, Signal>, State *> TransitionMatrix;

class StateMachine
{
public:
    explicit StateMachine(TransitionMatrix transitionMatrix, State * startState);

    void update(void)
    {
        if (updateNedded)
        {
            currentState_ = transiton(recieved_);
            updateNedded = false;
        }
        currentState_->execute();
    }

    void signal_callback(const Signal & signal)
    {
        recieved_ = signal;
        updateNedded = true;
    }

private:
    TransitionMatrix transitionMatrix_;

    State * transiton(Signal signal)
    {

        State * state_to_retrun;
        try
        {
            state_to_retrun = transitionMatrix_.at(std::make_pair(currentState_, signal));
        } catch (...)
        {
            state_to_retrun = currentState_;
        }

        return state_to_retrun;
    }

    Signal recieved_{};

    bool updateNedded{false};

    State * currentState_;
};

#endif /* APP_STATEMACHINE_STATEMACHINE_HPP_ */
