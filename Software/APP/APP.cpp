/**
 * APP.cpp
 *
 *  Created on: 03-03-2019
 *  @author: Paweł Warzecha
 */

#include <FreeRTOS.h>
#include <task.h>

#include "BSP.hpp"

#include "DataContainer.hpp"

[[noreturn]] void display_task(void * pvParameters)
{
    (void)(pvParameters);

    const TickType_t xDelay = 20 / portTICK_PERIOD_MS;

    for (;;)
    {

        BSP::buton1.update();
        BSP::buton2.update();
        BSP::buton3.update();
        BSP::buton4.update();

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
        DataContainer::stateMachine.update();
        vTaskDelay(xDelay);
    }
}

void APP_init()
{

    xTaskCreate(display_task, "dispaly_task", 2048, NULL, 2, NULL);

    vTaskStartScheduler();
}
