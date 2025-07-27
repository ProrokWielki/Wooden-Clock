/**
 * @file Thermometer.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-07-26
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

namespace BSP2
{

class Thermometer
{
public:
    static float get_temperature();
    static void update();

private:
    static float temperature;
};
}  // namespace BSP2