#pragma once

#include <functional>
#include <cstdint>

class OsAbstraction
{
public:
    static void create_task(char* name, uint32_t stack_depth, uint32_t priority, std::function<void(void*)> task_function);
    static void start_scheduler();
    static void delay_ms(unsigned int ms);
};