/**
 * StateButtons.hpp
 *
 *  Created on: 17-05-2020
 *  @author: Paweł Warzecha
 */

#pragma once

#include <widgets/Image.hpp>

#include "Images/Images.hpp"

class StateButtons: public Canvas
{
public:
    /**
     * @brief Constructor.
     */
    StateButtons()
    : up_arrow_(get_image(ImageType::UP_ARROW)), down_arrow_(get_image(ImageType::DOWN_ARROW)), left_arrow_(get_image(ImageType::LEFT_ARROW)),
      right_arrow_(get_image(ImageType::RIGHT_ARROW))
    {
    }

    /**
     * @brief Execution of the State action.
     */
    void init() override
    {
        constexpr uint8_t UP_ARROW_X{10};
        constexpr uint8_t UP_ARROW_Y{0};
        constexpr uint8_t DOWN_ARROW_X{10};
        constexpr uint8_t DOWN_ARROW_Y{18};
        constexpr uint8_t LEFT_ARROW_X{0};
        constexpr uint8_t LEFT_ARROW_Y{10};
        constexpr uint8_t RIGHT_ARROW_X{18};
        constexpr uint8_t RIGHT_ARROW_Y{10};

        up_arrow_.hide();
        down_arrow_.hide();
        left_arrow_.hide();
        right_arrow_.hide();

        add(&up_arrow_, UP_ARROW_X, UP_ARROW_Y);
        add(&down_arrow_, DOWN_ARROW_X, DOWN_ARROW_Y);
        add(&left_arrow_, LEFT_ARROW_X, LEFT_ARROW_Y);
        add(&right_arrow_, RIGHT_ARROW_X, RIGHT_ARROW_Y);

        // validate();
    }

    void up_date() override
    {
        up_arrow_.hide();
        down_arrow_.hide();
        left_arrow_.hide();
        right_arrow_.hide();

        if (BSP::get().button_down.is_pressed())
        {
            down_arrow_.show();
        }
        if (BSP::get().button_up.is_pressed())
        {
            up_arrow_.show();
        }
        if (BSP::get().button_left.is_pressed())
        {
            left_arrow_.show();
        }
        if (BSP::get().button_right.is_pressed())
        {
            right_arrow_.show();
        }

        // validate();
    }

private:
    Image & up_arrow_;
    Image & down_arrow_;
    Image & left_arrow_;
    Image & right_arrow_;
};
