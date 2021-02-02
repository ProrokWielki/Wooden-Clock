/**
 * StateButtons.hpp
 *
 *  Created on: 17-05-2020
 *  @author: Paweł Warzecha
 */

#pragma once

#include <widgets/Image.hpp>

#include "Assets/Images/Images.hpp"

class StateButtons: public Canvas
{
public:
    /**
     * @brief Constructor.
     */
    StateButtons() : up_arrow_(12, 14, up_arrow), down_arrow_(12, 14, down_arrow), left_arrow_(14, 12, left_arrow),right_arrow_(14, 12, right_arrow)
    {
    }

    /**
     * @brief Execution of the State action.
     */
    virtual void init() override
    {
        up_arrow_.hide();
        down_arrow_.hide();
        left_arrow_.hide();
        right_arrow_.hide();

        add(&up_arrow_, 10, 0);
        add(&down_arrow_, 10, 18);
        add(&left_arrow_, 0, 10);
        add(&right_arrow_, 18, 10);

        validate();
    }

    virtual void up_date() override
    {
        up_arrow_.hide();
        down_arrow_.hide();
        left_arrow_.hide();
        right_arrow_.hide();

        if (BSP::button_down.isPressed())
        {
            down_arrow_.show();
        }
        if (BSP::button_up.isPressed())
        {
            up_arrow_.show();
        }
        if (BSP::button_left.isPressed())
        {
            left_arrow_.show();
        }
        if (BSP::button_right.isPressed())
        {
            right_arrow_.show();
        }

        validate();
    }

private:
    Image up_arrow_;
    Image down_arrow_;
    Image left_arrow_;
    Image right_arrow_;
};
