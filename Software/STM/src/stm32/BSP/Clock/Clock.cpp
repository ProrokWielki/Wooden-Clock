#include <BSP/Clock.hpp>

#include <HAL/HAL.hpp>
#include <HAL/RTC.hpp>

BSP2::Time BSP2::Clock::time{};

BSP2::Time BSP2::Clock::get_time()
{
    return time;
}

void BSP2::Clock::update()
{
    if (HAL::parse_time == true)
    {
        const uint8_t minute = (HAL::uart_buffer[HAL::head - 2] - 48) + (HAL::uart_buffer[HAL::head - 3] - 48) * 10;
        const uint8_t hour = (HAL::uart_buffer[HAL::head - 4] - 48) + (HAL::uart_buffer[HAL::head - 5] - 48) * 10;

        HAL::rtc.set_minutes(minute);
        HAL::rtc.set_hours(hour);

        HAL::parse_time = false;
    }

    time.seconds = HAL::rtc.get_seconds();
    time.minutes = HAL::rtc.get_minutes();
    time.hours = HAL::rtc.get_hours();
}