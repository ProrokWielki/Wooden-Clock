/**
 * @file Clock.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-06-04
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include <cstdint>

namespace BSP2
{
struct Time {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
};

class Clock
{
public:
    static Time get_time();
    static void update();

private:
    static Time time;
};
}