

#include "os_abstraction.hpp"
#include <thread>
#include <vector>

#include <iostream>

std::vector<std::thread> tasks;
void OsAbstraction::create_task(char *, uint32_t, uint32_t, std::function<void(void*)> && thread_function)
{

    tasks.push_back(std::thread([thread_function]() {
            // std::cout << "Thread started" << std::endl;
            thread_function(nullptr);
    }));
}

void OsAbstraction::start_scheduler()
{
}

void OsAbstraction::delay_ms(unsigned int) {};