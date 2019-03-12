/**
 * DataContainer.hpp
 *
 *  Created on: 10-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_DATACONTAINER_HPP_
#define APP_DATACONTAINER_HPP_

#include "StateMachine/StateMachine.hpp"

#include "StateMachine/States/StateArrows.hpp"
#include "StateMachine/States/StateHourglass.hpp"
#include "StateMachine/States/StateMario.hpp"

class DataContainer
{
public:
    static StateMachine stateMachine;

    static StateMario Mario;
    static StateArrows Arrows;
    static StateHourglass Hourglass;
};

#endif /* APP_DATACONTAINER_HPP_ */
