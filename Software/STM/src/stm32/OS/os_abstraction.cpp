#include <FreeRTOS.h>
#include <task.h>

#include "os_abstraction.hpp"
#include <array>

struct TaskArguments {
    std::function<void()> task_function;
    uint32_t loop_time;
};

std::vector<TaskArguments> arguments{};
std::vector<TaskFunction_t> tasks_pointers{};

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