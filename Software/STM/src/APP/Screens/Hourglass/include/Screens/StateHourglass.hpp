/**
 * StateHourglass.hpp
 *
 *  Created on: 10-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_STATEMACHINE_STATES_STATEHOURGLASS_HPP_
#define APP_STATEMACHINE_STATES_STATEHOURGLASS_HPP_

#include <BSP/BSP.hpp>

#include <Canvas.hpp>
#include <widgets/Animation.hpp>

#include "Animations/Animations.hpp"

class StateHourglass: public Canvas
{
public:
    /**
     * @brief Constructor
     */
    StateHourglass();

    /**
     * @brief Execution of the State action.
     */
    void init() override;

    void up_date() override;

private:
    Animation & hourglass;
};

#endif /* APP_STATEMACHINE_STATES_STATEHOURGLASS_HPP_ */
