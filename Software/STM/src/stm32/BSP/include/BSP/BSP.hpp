/**
 * BSP.hpp
 *
 *  Created on: 06-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef BSP_BSP_HPP_
#define BSP_BSP_HPP_

#include <BSP/Button.hpp>
#include <BSP/Display.hpp>
#include <BSP/Magnetometer.hpp>


class BSP
{
public:
    static void init();

    static Display display;

    static Button button_right;
    static Button button_left;
    static Button button_up;
    static Button button_down;

private:
    BSP() = delete;

    static void display_init();
};

#endif /* BSP_BSP_HPP_ */
