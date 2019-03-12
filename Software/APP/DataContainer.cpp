/**
 * DataContainer.cpp
 *
 *  Created on: 10-03-2019
 *  @author: Paweł Warzecha
 */

#include "DataContainer.hpp"

#include "StateMachine/StateMachine.hpp"

StateMachine DataContainer::stateMachine(&Hourglass);

StateMario DataContainer::Mario;
StateArrows DataContainer::Arrows;
StateHourglass DataContainer::Hourglass;
