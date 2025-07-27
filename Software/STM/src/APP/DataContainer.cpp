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

std::array<Transition, 11> trainsitions{
{{.source_canvas = &DataContainer::Mario, .trigger = Signal::BUTTON_UP, .target_canvas = &DataContainer::Hourglass},
 {.source_canvas = &DataContainer::Hourglass, .trigger = Signal::BUTTON_UP, .target_canvas = &DataContainer::North},
 {.source_canvas = &(DataContainer::North), .trigger = Signal::BUTTON_UP, .target_canvas = &(DataContainer::text)},
 {.source_canvas = &(DataContainer::text), .trigger = Signal::BUTTON_UP, .target_canvas = &(DataContainer::StateHour)},
 {.source_canvas = &(DataContainer::StateHour), .trigger = Signal::BUTTON_UP, .target_canvas = &(DataContainer::Arrows)},
 {.source_canvas = &(DataContainer::Arrows), .trigger = Signal::BUTTON_UP, .target_canvas = &(DataContainer::Accel)},
 {.source_canvas = &(DataContainer::Accel), .trigger = Signal::BUTTON_UP, .target_canvas = &(DataContainer::CounterView)},
 {.source_canvas = &(DataContainer::CounterView), .trigger = Signal::BUTTON_UP, .target_canvas = &(DataContainer::Buttons)},
 {.source_canvas = &(DataContainer::Buttons), .trigger = Signal::BUTTON_UP, .target_canvas = &(DataContainer::Sand)},
 {.source_canvas = &(DataContainer::Sand), .trigger = Signal::BUTTON_UP, .target_canvas = &(DataContainer::temperature)},
 {.source_canvas = &(DataContainer::temperature), .trigger = Signal::BUTTON_UP, .target_canvas = &(DataContainer::Mario)}}};

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
