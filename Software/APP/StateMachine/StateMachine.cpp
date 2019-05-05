/**
 * StateMachine.cpp
 *
 *  Created on: 10-03-2019
 *  @author: Paweł Warzecha
 */

#include "StateMachine.hpp"
#include "DataContainer.hpp"

StateMachine::StateMachine(State * startState) : currentState_(startState)
{
    TransitionMatrix_ = {{{&(DataContainer::Arrows), BUTTON1}, &(DataContainer::Mario)},
                         {{&(DataContainer::Mario), BUTTON1}, &(DataContainer::Hourglass)},
                         {{&(DataContainer::Hourglass), BUTTON1}, &(DataContainer::North)},
                         {{&(DataContainer::North), BUTTON1}, &(DataContainer::Arrows)}};
}
