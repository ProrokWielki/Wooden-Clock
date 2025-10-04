#pragma once

#include <functional>
#include <cstdint>

class OsAbstraction
{
public:
    static void create_task(const char* name, uint32_t stack_depth, uint32_t priority, void (*task_function)(void*));
    static void start_scheduler();
    static void delay_ms(unsigned int ms);
};