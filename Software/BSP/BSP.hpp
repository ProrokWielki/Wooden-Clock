/**
 * BSP.hpp
 *
 *  Created on: 06-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef BSP_BSP_HPP_
#define BSP_BSP_HPP_

#include "Display/Display.hpp"

class BSP
{

public:
    static void init();

    static Display display;

private:
    BSP() = delete;

    static void display_init();
};

#endif /* BSP_BSP_HPP_ */
