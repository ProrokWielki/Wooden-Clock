#include <BSP/Clock.hpp>

#include <HAL/HAL.hpp>
#include <HAL/RTC.hpp>

BSP2::Time BSP2::Clock::time{};

BSP2::Time BSP2::Clock::get_time()
{
    return time;
}

void BSP2::Clock::set_time(BSP2::Time time)
{
    HAL::get().rtc.set_hours(time.hours);
    HAL::get().rtc.set_minutes(time.minutes);
    // HAL::get().rtc.set_seconds(time.seconds);
}

void BSP2::Clock::update()
{
    time.seconds = HAL::get().rtc.get_seconds();
    time.minutes = HAL::get().rtc.get_minutes();
    time.hours = HAL::get().rtc.get_hours();
}