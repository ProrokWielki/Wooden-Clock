/**
 * DataContainer.cpp
 *
 *  Created on: 10-03-2019
 *  @author: Paweł Warzecha
 */

#include "DataContainer.hpp"
#include "Screens/StateSand.hpp"

#include <GUI.hpp>

#include <BSP/BSP.hpp>

std::array<Transition, 11> trainsitions{{{&DataContainer::Mario, Signal::BUTTON_UP, &DataContainer::Hourglass},
                                         {&DataContainer::Hourglass, Signal::BUTTON_UP, &DataContainer::North},
                                         {&(DataContainer::North), Signal::BUTTON_UP, &(DataContainer::text)},
                                         {&(DataContainer::text), Signal::BUTTON_UP, &(DataContainer::StateHour)},
                                         {&(DataContainer::StateHour), Signal::BUTTON_UP, &(DataContainer::Arrows)},
                                         {&(DataContainer::Arrows), Signal::BUTTON_UP, &(DataContainer::Accel)},
                                         {&(DataContainer::Accel), Signal::BUTTON_UP, &(DataContainer::CounterView)},
                                         {&(DataContainer::CounterView), Signal::BUTTON_UP, &(DataContainer::Buttons)},
                                         {&(DataContainer::Buttons), Signal::BUTTON_UP, &(DataContainer::Sand)},
                                         {&(DataContainer::Sand), Signal::BUTTON_UP, &(DataContainer::temperature)},
                                         {&(DataContainer::temperature), Signal::BUTTON_UP, &(DataContainer::Mario)}}};

GUI DataContainer::stateMachine(
{trainsitions}, &Mario, [](uint8_t * new_frame_buffer) { BSP::display.set_frame_buffer(new_frame_buffer); }, FrameBuffer1, FrameBuffer2);

StateMario DataContainer::Mario;
StateArrows DataContainer::Arrows;
StateHourglass DataContainer::Hourglass;
StateNorth DataContainer::North(BSP::magnetometer);
Counter DataContainer::CounterView;
StateAccel DataContainer::Accel(BSP::accelerometer);
StateButtons DataContainer::Buttons;
StateSand DataContainer::Sand(BSP::accelerometer);
Hour DataContainer::StateHour;
Temperature DataContainer::temperature;
TextScreen DataContainer::text;

uint8_t DataContainer::FrameBuffer1[32 * 32];
uint8_t DataContainer::FrameBuffer2[32 * 32];
