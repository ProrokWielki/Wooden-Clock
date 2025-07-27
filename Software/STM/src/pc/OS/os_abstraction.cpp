

#include <functional>
#include <thread>
#include <vector>

#include "os_abstraction.hpp"
namespace
{
std::vector<std::thread> tasks;
}

void OsAbstraction::create_task(char *, uint32_t, uint32_t, std::function<void(void *)> thread_function)
{
    tasks.emplace_back([thread_function]() { thread_function(nullptr); });
}

void OsAbstraction::start_scheduler()
{
}

void OsAbstraction::delay_ms(unsigned int) {};