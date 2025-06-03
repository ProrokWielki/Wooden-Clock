/**
 * DataContainer.cpp
 *
 *  Created on: 10-03-2019
 *  @author: Paweł Warzecha
 */

#include "DataContainer.hpp"
#include "Screens/StateSand.hpp"

#include <GUI.hpp>

#include <HAL/HAL.hpp>

std::array<Transition, 10> trainsitions{{{&DataContainer::Mario, Signal::BUTTON_UP, &DataContainer::Hourglass},
                                         {&DataContainer::Hourglass, Signal::BUTTON_UP, &DataContainer::StateHour},
                                         {&(DataContainer::StateHour), Signal::BUTTON_UP, &(DataContainer::North)},
                                         {&(DataContainer::North), Signal::BUTTON_UP, &(DataContainer::Arrows)},
                                         {&(DataContainer::Arrows), Signal::BUTTON_UP, &(DataContainer::Accel)},
                                         {&(DataContainer::Accel), Signal::BUTTON_UP, &(DataContainer::CounterView)},
                                         {&(DataContainer::CounterView), Signal::BUTTON_UP, &(DataContainer::Buttons)},
                                         {&(DataContainer::Buttons), Signal::BUTTON_UP, &(DataContainer::Sand)},
                                         {&(DataContainer::Sand), Signal::BUTTON_UP, &(DataContainer::temperature)},
                                         {&(DataContainer::temperature), Signal::BUTTON_UP, &(DataContainer::Mario)}}};

GUI DataContainer::stateMachine({trainsitions}, &Mario);

StateMario DataContainer::Mario;
StateArrows DataContainer::Arrows;
StateHourglass DataContainer::Hourglass;
StateText DataContainer::Text;
StateNorth DataContainer::North(HAL::LSM9DS1_1);
Counter DataContainer::CounterView;
StateAccel DataContainer::Accel(HAL::LSM9DS1_1);
StateButtons DataContainer::Buttons;
StateSand DataContainer::Sand(HAL::LSM9DS1_1);
Hour DataContainer::StateHour;
Temperature DataContainer::temperature;

// uint8_t DataContainer::FrameBuffer1[32 * 32];
// uint8_t DataContainer::FrameBuffer2[32 * 32];
