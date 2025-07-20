#include <BSP/Clock.hpp>

BSP2::Time BSP2::Clock::time{};

BSP2::Time BSP2::Clock::get_time()
{
    return time;
}

void BSP2::Clock::update()
{
    time.seconds = 12;
    time.minutes = 11;
    time.hours = 10;
}