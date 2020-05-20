/**
 * DataContainer.cpp
 *
 *  Created on: 10-03-2019
 *  @author: Paweł Warzecha
 */

#include "DataContainer.hpp"

#include <GUI.hpp>

GUI DataContainer::stateMachine({{{&(DataContainer::Text), Signal::BUTTON1}, &(DataContainer::Mario)},
                                 {{&(DataContainer::Mario), Signal::BUTTON1}, &(DataContainer::Hourglass)},
                                 {{&(DataContainer::Hourglass), Signal::BUTTON1}, &(DataContainer::North)},
                                 {{&(DataContainer::North), Signal::BUTTON1}, &(DataContainer::Arrows)},
                                 {{&(DataContainer::Arrows), Signal::BUTTON1}, &(DataContainer::Accel)},
                                 {{&(DataContainer::Accel), Signal::BUTTON1}, &(DataContainer::CounterView)},
                                 {{&(DataContainer::CounterView), Signal::BUTTON1}, &(DataContainer::Buttons)},
                                 {{&(DataContainer::Buttons), Signal::BUTTON1}, &(DataContainer::Text)}},
                                &Text);

StateMario DataContainer::Mario;
StateArrows DataContainer::Arrows;
StateHourglass DataContainer::Hourglass;
StateText DataContainer::Text;
StateNorth DataContainer::North(HAL::LSM9DS1_1);
Counter DataContainer::CounterView;
StateAccel DataContainer::Accel(HAL::LSM9DS1_1);
StateButtons DataContainer::Buttons;

// uint8_t DataContainer::FrameBuffer1[32 * 32];
// uint8_t DataContainer::FrameBuffer2[32 * 32];
