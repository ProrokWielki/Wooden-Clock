/**
 * StateArrows.hpp
 *
 *  Created on: 10-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_STATEMACHINE_STATES_STATETEXT_HPP_
#define APP_STATEMACHINE_STATES_STATETEXT_HPP_

#include <Canvas.hpp>

#include "Assets/Text/texts.h"

class StateText: public Canvas
{
public:
    /**
     * @brief Constructor.
     */
    StateText() : text(32, 10, hour_13_57)
    {
    }

    /**
     * @brief Execution of the State action.
     */
    virtual void init() override
    {
        add(&text);
        validate();
    }

    virtual void up_date() override
    {
    }

private:
    Image text;
};

#endif /* APP_STATEMACHINE_STATES_STATETEXT_HPP_ */
