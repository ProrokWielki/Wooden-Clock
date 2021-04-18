/**
 * DataContainer.cpp
 *
 *  Created on: 10-03-2019
 *  @author: Paweł Warzecha
 */

#include "DataContainer.hpp"

#include <GUI.hpp>

GUI DataContainer::stateMachine({{{&(DataContainer::Text), Signal::BUTTON_UP}, &(DataContainer::Mario)},
                                 {{&(DataContainer::Mario), Signal::BUTTON_UP}, &(DataContainer::Hourglass)},
                                 {{&(DataContainer::Hourglass), Signal::BUTTON_UP}, &(DataContainer::StateHour)},
                                 {{&(DataContainer::StateHour), Signal::BUTTON_UP}, &(DataContainer::North)},
                                 {{&(DataContainer::North), Signal::BUTTON_UP}, &(DataContainer::Arrows)},
                                 {{&(DataContainer::Arrows), Signal::BUTTON_UP}, &(DataContainer::Accel)},
                                 {{&(DataContainer::Accel), Signal::BUTTON_UP}, &(DataContainer::CounterView)},
                                 {{&(DataContainer::CounterView), Signal::BUTTON_UP}, &(DataContainer::Buttons)},
                                 {{&(DataContainer::Buttons), Signal::BUTTON_UP}, &(DataContainer::Text)}},
                                &Text);

StateMario DataContainer::Mario;
StateArrows DataContainer::Arrows;
StateHourglass DataContainer::Hourglass;
StateText DataContainer::Text;
StateNorth DataContainer::North(HAL::LSM9DS1_1);
Counter DataContainer::CounterView;
StateAccel DataContainer::Accel(HAL::LSM9DS1_1);
StateButtons DataContainer::Buttons;
Hour DataContainer::StateHour;

// uint8_t DataContainer::FrameBuffer1[32 * 32];
// uint8_t DataContainer::FrameBuffer2[32 * 32];
