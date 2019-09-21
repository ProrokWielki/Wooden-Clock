/**
 * State.hpp
 *
 *  Created on: 10-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_STATEMACHINE_STATE_HPP_
#define APP_STATEMACHINE_STATE_HPP_

class State
{
public:
    virtual ~State()
    {
    }

    virtual void execute() = 0;
};

#endif /* APP_STATEMACHINE_STATE_HPP_ */
