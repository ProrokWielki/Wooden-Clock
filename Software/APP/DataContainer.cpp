/**
 * DataContainer.cpp
 *
 *  Created on: 10-03-2019
 *  @author: Paweł Warzecha
 */

#include "DataContainer.hpp"

#include "StateMachine/StateMachine.hpp"

StateMachine DataContainer::stateMachine({{{&(DataContainer::Arrows), Signal::BUTTON1}, &(DataContainer::Mario)},
                                          {{&(DataContainer::Mario), Signal::BUTTON1}, &(DataContainer::Hourglass)},
                                          {{&(DataContainer::Hourglass), Signal::BUTTON1}, &(DataContainer::North)},
                                          {{&(DataContainer::North), Signal::BUTTON1}, &(DataContainer::Arrows)}},
                                         &Hourglass);

StateMario DataContainer::Mario;
StateArrows DataContainer::Arrows;
StateHourglass DataContainer::Hourglass;
StateNorth DataContainer::North(HAL::LSM9DS1_1);
