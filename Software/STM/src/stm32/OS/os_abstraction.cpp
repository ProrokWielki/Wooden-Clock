#include <FreeRTOS.h>
#include <task.h>

#include "os_abstraction.hpp"

void OsAbstraction::create_task(char * name, uint32_t stack_depth, uint32_t priority, void (*task_function)(void*) )
{
    xTaskCreate(task_function, name, stack_depth, nullptr, priority, nullptr);
}

void OsAbstraction::start_scheduler()
{
    vTaskStartScheduler();
}

void OsAbstraction::delay_ms(unsigned int ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}