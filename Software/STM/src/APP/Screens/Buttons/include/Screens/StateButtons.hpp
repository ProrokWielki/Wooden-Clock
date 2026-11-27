/**
 * StateButtons.hpp
 *
 *  Created on: 17-05-2020
 *  @author: Paweł Warzecha
 */

#pragma once

#include <array>
#include <functional>

#include <Canvas.hpp>

#include <BSP/BSP.hpp>

#include <widgets/Image.hpp>

#include "Images/Images.hpp"
#include "Widget.hpp"

class StateButtons: public Canvas
{
public:
    /**
     * @brief Constructor.
     */
    StateButtons();

    /**
     * @brief Execution of the State action.
     */
    void init() override;

    void up_date() override;

private:
    const Image & up_arrow_;
    const Image & down_arrow_;
    const Image & left_arrow_;
    const Image & right_arrow_;
};
