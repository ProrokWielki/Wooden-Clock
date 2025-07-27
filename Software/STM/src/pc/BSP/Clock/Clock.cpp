#include <BSP/Clock.hpp>

#include <ctime>

BSP2::Time BSP2::Clock::time{};

BSP2::Time BSP2::Clock::get_time()
{
    return time;
}

void BSP2::Clock::update()
{
    const time_t now{std::time(nullptr)};
    const tm * local_time{localtime(&now)};
    time.seconds = local_time->tm_sec;
    time.minutes = local_time->tm_min;
    time.hours = local_time->tm_hour;
}