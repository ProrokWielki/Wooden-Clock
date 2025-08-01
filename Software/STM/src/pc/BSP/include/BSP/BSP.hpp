/**
 * BSP.hpp
 *
 *  Created on: 06-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef BSP_BSP_HPP_
#define BSP_BSP_HPP_

#include <BSP/Button.hpp>
#include <BSP/Accelerometer.hpp>
#include <BSP/Clock.hpp>
#include <BSP/Display.hpp>
#include <BSP/Magnetometer.hpp>
#include <BSP/Thermometer.hpp>

class BSP
{
public:
    BSP() = delete;

    static void init();

    static Display display;
    static BSP2::Magnetometer magnetometer;
    static BSP2::Accelerometer accelerometer;
    static BSP2::Clock clock;
    static BSP2::Thermometer thermometer;

    static Button button_right;
    static Button button_left;
    static Button button_up;
    static Button button_down;

    static bool up;
    static bool down;
    static bool left;
    static bool right;

private:
    static void display_init();
};

#endif /* BSP_BSP_HPP_ */
