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
SoundScreen DataContainer::sound{};

namespace
{

constexpr static std::array transitions{
Transition{.source_canvas = &DataContainer::Mario, .trigger = Signal::BUTTON_UP, .target_canvas = &DataContainer::Shapes},
Transition{.source_canvas = &DataContainer::Shapes, .trigger = Signal::BUTTON_UP, .target_canvas = &DataContainer::Hourglass},
Transition{.source_canvas = &DataContainer::Hourglass, .trigger = Signal::BUTTON_UP, .target_canvas = &DataContainer::North},
Transition{.source_canvas = &(DataContainer::North), .trigger = Signal::BUTTON_UP, .target_canvas = &(DataContainer::text)},
Transition{.source_canvas = &(DataContainer::text), .trigger = Signal::BUTTON_UP, .target_canvas = &(DataContainer::sound)},
Transition{.source_canvas = &(DataContainer::sound), .trigger = Signal::BUTTON_UP, .target_canvas = &(DataContainer::StateHour)},
Transition{.source_canvas = &(DataContainer::StateHour), .trigger = Signal::BUTTON_UP, .target_canvas = &(DataContainer::Arrows)},
Transition{.source_canvas = &(DataContainer::Arrows), .trigger = Signal::BUTTON_UP, .target_canvas = &(DataContainer::Accel)},
Transition{.source_canvas = &(DataContainer::Accel), .trigger = Signal::BUTTON_UP, .target_canvas = &(DataContainer::CounterView)},
Transition{.source_canvas = &(DataContainer::CounterView), .trigger = Signal::BUTTON_UP, .target_canvas = &(DataContainer::Buttons)},
Transition{.source_canvas = &(DataContainer::Buttons), .trigger = Signal::BUTTON_UP, .target_canvas = &(DataContainer::Sand)},
Transition{.source_canvas = &(DataContainer::Sand), .trigger = Signal::BUTTON_UP, .target_canvas = &(DataContainer::temperature)},
Transition{.source_canvas = &(DataContainer::temperature), .trigger = Signal::BUTTON_UP, .target_canvas = &(DataContainer::Mario)}};

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
