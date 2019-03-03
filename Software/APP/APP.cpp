/**
 * APP.cpp
 *
 *  Created on: 03-03-2019
 *  @author: Paweł Warzecha
 */

extern "C" {
#include <FreeRTOS.h>
#include <task.h>
}

#include "Display/Display.hpp"

#include "Assets/Images/Images.hpp"

[[noreturn]] void display_task(void * pvParameters)
{
    const TickType_t xDelay = 20 / portTICK_PERIOD_MS / 32;

    Display display(32, 32, Arrows1);

    uint32_t magicNumber = 0;

    for (;;)
    {
        display.draw();
        vTaskDelay(xDelay);
        if (magicNumber == 400)
        {
            display.set_frame_buffer(Arrows2);
        }
        else if (magicNumber == 800)
        {
            display.set_frame_buffer(Arrows1);
            magicNumber = 0;
        }

        magicNumber++;
    }
}

void APP_init()
{

    xTaskCreate(display_task, "dispaly_task", 1024, NULL, 10, NULL);

    vTaskStartScheduler();
}
