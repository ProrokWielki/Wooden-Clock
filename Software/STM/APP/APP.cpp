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

void flash()  __attribute__((section(".flasher_section")));

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
        BSP::button_up.update();
        BSP::button_down.update();
        BSP::button_left.update();
        BSP::button_right.update();

        if (BSP::button_up.wasPressed() || HAL::up)
        {
            DataContainer::stateMachine.signal_callback(Signal::BUTTON_UP);
            HAL::up = false;
        }
        if (BSP::button_down.wasPressed() || HAL::down)
        {
            DataContainer::stateMachine.signal_callback(Signal::BUTTON_DOWN);
            HAL::down = false;
        }
        if (BSP::button_left.wasPressed() || HAL::left)
        {
            DataContainer::stateMachine.signal_callback(Signal::BUTTON_LEFT);
            HAL::left = false;
        }
        if (BSP::button_right.wasPressed() || HAL::right)
        {
            DataContainer::stateMachine.signal_callback(Signal::BUTTON_RIGHT);
            HAL::right = false;
        }
        if(HAL::reset)
        {
            flash();
        }
        vTaskDelay(xDelay);
    }
}



void flash()
{
    // disable screen and stop everything.
    HAL::SR_74HC595_1.output_enable(false);
    __disable_irq();
    vTaskSuspendAll();

    // erase 254 pages - in the 255th is this function :)


    // write recived data to the flash
    uint8_t dupa[200];
    for(uint8_t i =0; i< 200; i++)
    {
        dupa[i] = i+1;
    }

    SCB->AIRCR  = ((0x5FAUL << 16) | (1<<2));

    for(;;)
    {
        asm("nop");
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
