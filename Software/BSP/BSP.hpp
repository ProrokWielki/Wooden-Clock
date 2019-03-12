/**
 * BSP.hpp
 *
 *  Created on: 06-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef BSP_BSP_HPP_
#define BSP_BSP_HPP_

#include "Button/Button.hpp"
#include "Display/Display.hpp"

class BSP
{

public:
    static void init();

    static Display display;

    static Button buton1;
    static Button buton2;
    static Button buton3;
    static Button buton4;

private:
    BSP() = delete;

    static void display_init();
};

#endif /* BSP_BSP_HPP_ */
