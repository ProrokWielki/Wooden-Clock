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
        DataContainer::stateMachine.update();
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
        BSP::button_up.update();
        BSP::button_down.update();
        BSP::button_left.update();
        BSP::button_right.update();
        BSP2::Clock::update();
        BSP::magnetometer.update();
        BSP::accelerometer.update();
        BSP::thermometer.update();

        if (BSP::button_up.wasReleased() || BSP::up)
        {
            DataContainer::stateMachine.signal_callback(Signal::BUTTON_UP);
            BSP::up = false;
        }
        if (BSP::button_down.wasReleased() || BSP::down)
        {
            DataContainer::stateMachine.signal_callback(Signal::BUTTON_DOWN);
            BSP::down = false;
        }
        if (BSP::button_left.wasReleased() || BSP::left)
        {
            DataContainer::stateMachine.signal_callback(Signal::BUTTON_LEFT);
            BSP::left = false;
        }
        if (BSP::button_right.wasReleased() || BSP::right)
        {
            DataContainer::stateMachine.signal_callback(Signal::BUTTON_RIGHT);
            BSP::right = false;
        }

        // if (HAL::reset)
        // {
        //     // flash();
        // }
        OsAbstraction::delay_ms(sleep_time_ms);
    }
}

}  // namespace

void APP_init()
{

    BSP::display.set_frame_buffer(DataContainer::stateMachine.getFrameBuffer());
    BSP::display.set_dispaly_redrawn_callback([&]() { DataContainer::stateMachine.swap_framebuffers(); });

    // char dispaly_task[] = "dispaly_task";
    char guui_task[] = "gui_task";
    char systeam_interface_task[] = "system_interface_task";

    OsAbstraction::create_task(guui_task, 10000, 2, gui_task);
    OsAbstraction::create_task(systeam_interface_task, 1024, 1, system_interface_task);

    OsAbstraction::start_scheduler();
}
