/**
 * APP.cpp
 *
 *  Created on: 03-03-2019
 *  @author: Paweł Warzecha
 */

#include <exception>

#include <os_abstraction.hpp>

#include <BSP/BSP.hpp>
// #include <HAL/HAL.hpp>

#include <GUI.hpp>
#include <sys/types.h>

#include "BSP/Clock.hpp"
#include "DataContainer.hpp"

#include "APP.hpp"

namespace
{
void gui_task(void *)
{
    constexpr static uint8_t sleep_time_ms{20};

    for (;;)
    {
        DataContainer::get().stateMachine.update();
        OsAbstraction::delay_ms(sleep_time_ms);
    }
    // BSP::display.draw();
}

void system_interface_task(void *)
{
    constexpr static uint8_t sleep_time_ms{20};

    for (;;)
    {
        // std::cout << "System interface task started" << std::endl;
        BSP::get().button_up.update();
        BSP::get().button_down.update();
        BSP::get().button_left.update();
        BSP::get().button_right.update();
        BSP2::Clock::update();
        BSP::get().magnetometer.update();
        BSP::get().accelerometer.update();
        BSP::get().thermometer.update();

        if (BSP::get().communication_interface.is_message_available())
        {
            auto message = BSP::get().communication_interface.get_message();

            if (message.length == 1)
            {
                switch (message.data[0])
                {
                    case 'u':
                        BSP::get().up = true;
                        break;
                    case 'd':
                        BSP::get().down = true;
                        break;
                    case 'l':
                        BSP::get().left = true;
                        break;
                    case 'r':
                        BSP::get().right = true;
                        break;
                    default:
                        break;
                }
            }
        }

        if (BSP::get().button_up.was_released() || BSP::get().up)
        {
            DataContainer::get().stateMachine.signal_callback(Signal::BUTTON_UP);
            BSP::get().up = false;
        }
        if (BSP::get().button_down.was_released() || BSP::get().down)
        {
            DataContainer::get().stateMachine.signal_callback(Signal::BUTTON_DOWN);
            BSP::get().down = false;
        }
        if (BSP::get().button_left.was_released() || BSP::get().left)
        {
            DataContainer::get().stateMachine.signal_callback(Signal::BUTTON_LEFT);
            BSP::get().left = false;
        }
        if (BSP::get().button_right.was_released() || BSP::get().right)
        {
            DataContainer::get().stateMachine.signal_callback(Signal::BUTTON_RIGHT);
            BSP::get().right = false;
        }

        // if (HAL::reset)
        // {
        //     // flash();
        // }
        OsAbstraction::delay_ms(sleep_time_ms);
    }
}

}  // namespace

void app_init()
{
    constexpr static uint32_t gui_task_stack_depth{10000};
    constexpr static uint32_t system_interface_task_stack_depth{1024};

    constexpr static uint32_t gui_task_priority{2};
    constexpr static uint32_t system_interface_task_priority{1};

    BSP::get().display.set_frame_buffer({DataContainer::get().stateMachine.getFrameBuffer(), BSP::DISPLAY_HEIGHT * BSP::DISPLAY_WIDTH});
    BSP::get().display.set_display_redrawn_callback([&]() { DataContainer::get().stateMachine.swap_framebuffers(); });

    OsAbstraction::create_task("gui_task", gui_task_stack_depth, gui_task_priority, gui_task);
    OsAbstraction::create_task("system_interface_task", system_interface_task_stack_depth, system_interface_task_priority, system_interface_task);

    OsAbstraction::start_scheduler();
}
