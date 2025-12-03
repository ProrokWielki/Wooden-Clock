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

StateMario DataContainer::Mario{};
StateArrows DataContainer::Arrows{};
StateHourglass DataContainer::Hourglass{};
StateNorth DataContainer::North{BSP::get().magnetometer};
Counter DataContainer::CounterView{};
StateAccel DataContainer::Accel{BSP::get().accelerometer};
StateButtons DataContainer::Buttons{};
StateSand DataContainer::Sand{BSP::get().accelerometer};
Hour DataContainer::StateHour{};
Temperature DataContainer::temperature{};
TextScreen DataContainer::text{};
ShapesScreen DataContainer::Shapes{};

namespace
{
constexpr static uint8_t NUM_OF_TRANSITIONS{12};

constexpr static std::array<Transition, NUM_OF_TRANSITIONS> transitions{
{{.source_canvas = &DataContainer::Mario, .trigger = Signal::BUTTON_UP, .target_canvas = &DataContainer::Shapes},
 {.source_canvas = &DataContainer::Shapes, .trigger = Signal::BUTTON_UP, .target_canvas = &DataContainer::Hourglass},
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

}  // namespace


DataContainer::DataContainer()
: stateMachine{BSP::get().frame_buffer1.data(), BSP::get().frame_buffer2.data(), {transitions}, &DataContainer::Mario, [](uint8_t * new_frame_buffer) {
                   BSP::get().display.set_frame_buffer({new_frame_buffer, BSP::DISPLAY_HEIGHT * BSP::DISPLAY_WIDTH});
               }}
{
}

DataContainer & DataContainer::get()
{
    static DataContainer instance;
    return instance;
}
