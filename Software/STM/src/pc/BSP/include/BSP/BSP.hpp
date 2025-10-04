/**
 * BSP.hpp
 *
 *  Created on: 06-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef BSP_BSP_HPP_
#define BSP_BSP_HPP_

#include <BSP/Accelerometer.hpp>
#include <BSP/Button.hpp>
#include <BSP/Clock.hpp>
#include <BSP/Display.hpp>
#include <BSP/Magnetometer.hpp>
#include <BSP/Thermometer.hpp>

class BSP
{
public:
    static BSP & get();

    constexpr static uint32_t DISPLAY_WIDTH{32};
    constexpr static uint32_t DISPLAY_HEIGHT{32};

    static void init();

    std::array<uint8_t, DISPLAY_WIDTH * DISPLAY_HEIGHT> frame_buffer1{};
    std::array<uint8_t, DISPLAY_WIDTH * DISPLAY_HEIGHT> frame_buffer2{};

    Display display;

    BSP2::Magnetometer magnetometer{};
    BSP2::Accelerometer accelerometer{};
    BSP2::Clock clock{};
    BSP2::Thermometer thermometer{};

    Button button_right;
    Button button_left;
    Button button_up;
    Button button_down;

    bool up{false};
    bool down{false};
    bool left{false};
    bool right{false};

private:
    BSP();

    static void display_init();
};

#endif /* BSP_BSP_HPP_ */
