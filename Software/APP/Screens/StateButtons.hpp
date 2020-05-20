/**
 * StateButtons.hpp
 *
 *  Created on: 17-05-2020
 *  @author: Paweł Warzecha
 */

#pragma once

#include <Canvas.hpp>

#include "Assets/Images/Images.hpp"

class StateButtons: public Canvas
{
public:
    /**
     * @brief Constructor.
     */
    StateButtons() : up_arrow_(12, 16, up_arrow), down_arrow_(12, 16, down_arrow)
    {
    }

    /**
     * @brief Execution of the State action.
     */
    virtual void init() override
    {
        up_arrow_.hide();
        down_arrow_.hide();

        add(&up_arrow_, 10, 0);
        add(&down_arrow_, 10, 16);

        validate();
    }

    virtual void up_date() override
    {
        up_arrow_.hide();
        down_arrow_.hide();

        if (BSP::buton2.isPressed())
        {
            down_arrow_.show();
        }
        if (BSP::buton3.isPressed())
        {
            up_arrow_.show();
        }

        validate();
    }

private:
    Image up_arrow_;
    Image down_arrow_;
};
