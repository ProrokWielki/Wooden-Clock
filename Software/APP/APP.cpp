/**
 * APP.cpp
 *
 *  Created on: 03-03-2019
 *  @author: Paweł Warzecha
 */

#include <FreeRTOS.h>
#include <task.h>

#include "BSP.hpp"

#include "Assets/Images/Images.hpp"

uint8_t * frames[] = {frame_1,  frame_2,  frame_3,  frame_4,  frame_5,  frame_6,  frame_7,  frame_8,  frame_9,  frame_10, frame_11,
                      frame_12, frame_13, frame_14, frame_15, frame_16, frame_17, frame_18, frame_19, frame_20, frame_21};

[[noreturn]] void display_task(void * pvParameters)
{
    (void)(pvParameters);

    const TickType_t xDelay = 100 / portTICK_PERIOD_MS;

    uint8_t currentFrame = 0;

    for (;;)
    {
        BSP::display.set_frame_buffer(frames[currentFrame++]);
        if (currentFrame == 21)
            currentFrame = 0;
        vTaskDelay(xDelay);
    }
}

void APP_init()
{

    xTaskCreate(display_task, "dispaly_task", 2048, NULL, 1, NULL);

    vTaskStartScheduler();
}
