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
#include "Animations.hpp"
#include "Widget.hpp"
#include <BSP/BSP.hpp>
#include <array>
#include <functional>

class StateArrows: public Canvas
{
public:
    /**
     * @brief Constructor.
     */
    StateArrows();

    /**
     * @brief Execution of the State action.
     */
    void init() override;

    void up_date() override;

private:
    Animation & arrows;
};

#endif /* APP_STATEMACHINE_STATES_STATEARROWS_HPP_ */
