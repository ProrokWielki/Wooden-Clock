/**
 * APP.cpp
 *
 *  Created on: 03-03-2019
 *  @author: Paweł Warzecha
 */

#include <FreeRTOS.h>
#include <task.h>

#include "BSP.hpp"

#include <GUI.hpp>

#include "DataContainer.hpp"

[[noreturn]] void display_task(void * pvParameters)
{
    (void)(pvParameters);

    const TickType_t xDelay = 20 / portTICK_PERIOD_MS;

    for (;;)
    {

        DataContainer::stateMachine.update();

        vTaskDelay(xDelay);
    }
}

[[noreturn]] void system_interface_task(void * pvParameters)
{
    (void)(pvParameters);

    const TickType_t xDelay = 20 / portTICK_PERIOD_MS;

    for (;;)
    {
        BSP::buton1.update();
        BSP::buton2.update();
        BSP::buton3.update();
        BSP::buton4.update();

        if (BSP::buton1.wasPressed() || HAL::up)
        {
            DataContainer::stateMachine.signal_callback(Signal::BUTTON1);
            HAL::up = false;
        }
        if (BSP::buton2.wasPressed() || HAL::down)
        {
            DataContainer::stateMachine.signal_callback(Signal::BUTTON2);
            HAL::down = false;
        }
        if (BSP::buton3.wasPressed() || HAL::left)
        {
            DataContainer::stateMachine.signal_callback(Signal::BUTTON3);
            HAL::left = false;
        }
        if (BSP::buton4.wasPressed() || HAL::right)
        {
            DataContainer::stateMachine.signal_callback(Signal::BUTTON4);
            HAL::right = false;
        }
        vTaskDelay(xDelay);
    }
}

void APP_init()
{

    BSP::display.set_frame_buffer(DataContainer::stateMachine.getFrameBuffer());
    BSP::display.set_dispaly_redrawn_callback([&]() { DataContainer::stateMachine.swap_framebuffers(); });

    xTaskCreate(display_task, "dispaly_task", 2048, NULL, 2, NULL);
    xTaskCreate(system_interface_task, "system_interface_task", 64, NULL, 1, NULL);

    vTaskStartScheduler();
}
