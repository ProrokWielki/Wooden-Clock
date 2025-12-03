/**
 * StateArrows.hpp
 *
 *  Created on: 10-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_STATEMACHINE_STATES_STATEARROWS_HPP_
#define APP_STATEMACHINE_STATES_STATEARROWS_HPP_

#include <Canvas.hpp>

#include "../Assets/Images/Images.hpp"
#include "Assets/Animations/Animations.hpp"
#include <BSP/BSP.hpp>
#include <widgets/Animation.hpp>

class StateArrows: public Canvas
{
public:
    /**
     * @brief Constructor.
     */
    StateArrows() : arrows{get_animation(AnimationType::ARROWS)}
    {
    }

    /**
     * @brief Execution of the State action.
     */
    void init() override
    {
        add(&arrows);
        // validate();
    }

    void up_date() override
    {
    }

private:
    Animation & arrows;
};

#endif /* APP_STATEMACHINE_STATES_STATEARROWS_HPP_ */
