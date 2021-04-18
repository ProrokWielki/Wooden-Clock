/**
 * StateArrows.hpp
 *
 *  Created on: 10-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_STATEMACHINE_STATES_STATEARROWS_HPP_
#define APP_STATEMACHINE_STATES_STATEARROWS_HPP_

#include <Canvas.hpp>

#include "Assets/Images/Images.hpp"
#include "BSP.hpp"
#include <widgets/Animation.hpp>

class StateArrows: public Canvas
{
public:
    /**
     * @brief Constructor.
     */
    StateArrows() : arrows{32, 32, {Arrows1, Arrows2}}
    {
    }

    /**
     * @brief Execution of the State action.
     */
    virtual void init() override
    {
        add(&arrows);
        validate();
    }

    virtual void up_date() override
    {
    }

private:
    Animation<2> arrows;
};

#endif /* APP_STATEMACHINE_STATES_STATEARROWS_HPP_ */
