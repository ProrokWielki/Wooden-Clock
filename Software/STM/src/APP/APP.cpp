/**
 * APP.cpp
 *
 *  Created on: 03-03-2019
 *  @author: Paweł Warzecha
 */

#include <FreeRTOS.h>
#include <task.h>

#include <BSP/BSP.hpp>
#include <HAL/HAL.hpp>

#include <GUI.hpp>

#include "DataContainer.hpp"

void flash() __attribute__((section(".flasher_section"))) __attribute__((noinline));

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

        if (HAL::parse_time == true)
        {
            const uint8_t minute = (HAL::uart_buffer[HAL::head - 2] - 48) + (HAL::uart_buffer[HAL::head - 3] - 48) * 10;
            const uint8_t hour = (HAL::uart_buffer[HAL::head - 4] - 48) + (HAL::uart_buffer[HAL::head - 5] - 48) * 10;

            HAL::rtc.set_minutes(minute);
            HAL::rtc.set_hours(hour);

            HAL::parse_time = false;
        }
        if (HAL::reset)
        {
            flash();
        }
        vTaskDelay(xDelay);
    }
}

void flash()
{
    // // disable screen and stop everything.
    // HAL::SR_74HC595_1.output_enable(false);
    // __disable_irq();
    // vTaskSuspendAll();

    // // erase 254 pages - in the 255th is this function :)
    // /// erase
    // FLASH->KEYR = 0x45670123;
    // FLASH->KEYR = 0xCDEF89AB;

    // while (FLASH->SR & (1 << 16))
    // {
    // }

    // FLASH->SR |= (0b11 << 14) | (0b1111111 << 3) | 2;

    // FLASH->CR |= (1 << 1) | (81 << 3) | (1 << 16);

    // while (FLASH->SR & (1 << 16))
    // {
    // }

    // FLASH->CR &= ~(1 << 1);

    // // program
    // while (FLASH->SR & (1 << 16))
    // {
    // }
    // FLASH->SR |= (0b11 << 14) | (0b1111111 << 3) | 2;

    // FLASH->CR |= 1;

    // *(uint32_t *)0x8028800 = (uint32_t)0xefbeadde;
    // // while(FLASH->SR & (1<<16))
    // // {}

    // // auto sr_register = FLASH->SR;

    // *(uint32_t *)0x8028804 = (uint32_t)0xefbeadde;
    // while (FLASH->SR & (1 << 16))
    // {
    // }
    // // auto sr_register = FLASH->SR;
    // FLASH->CR &= ~(1);

    // // *(uint16_t*)0x8028802 = 0xbeef;

    // // while(FLASH->SR & (1<<16))
    // // {}

    // // FLASH->CR &= ~(1);

    // // write recived data to the flash

    // SCB->AIRCR = ((0x5FAUL << 16) | (1 << 2));

    // for (;;)
    // {
    //     asm("nop");
    // }
}

void APP_init()
{

    BSP::display.set_frame_buffer(DataContainer::stateMachine.getFrameBuffer());
    BSP::display.set_dispaly_redrawn_callback([&]() { DataContainer::stateMachine.swap_framebuffers(); });

    xTaskCreate(display_task, "dispaly_task", 2048, nullptr, 2, nullptr);
    xTaskCreate(system_interface_task, "system_interface_task", 64, nullptr, 1, nullptr);

    vTaskStartScheduler();
}
