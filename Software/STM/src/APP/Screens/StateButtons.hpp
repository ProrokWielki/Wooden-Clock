/**
 * StateButtons.hpp
 *
 *  Created on: 17-05-2020
 *  @author: Paweł Warzecha
 */

#pragma once

#include <array>
#include <functional>
#include <widgets/Image.hpp>

#include "Images/Images.hpp"
#include "Widget.hpp"

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

        static const WidgetAndPositions up{.x = UP_ARROW_X, .y = UP_ARROW_Y, .widget = up_arrow_};
        static const WidgetAndPositions down{.x = DOWN_ARROW_X, .y = DOWN_ARROW_Y, .widget = down_arrow_};
        static const WidgetAndPositions left{.x = LEFT_ARROW_X, .y = LEFT_ARROW_Y, .widget = left_arrow_};
        static const WidgetAndPositions right{.x = RIGHT_ARROW_X, .y = RIGHT_ARROW_Y, .widget = right_arrow_};

        static const std::array<const std::reference_wrapper<const WidgetAndPositions>, 4> widgets{up, down, left, right};

        add(widgets);
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
    const Image & up_arrow_;
    const Image & down_arrow_;
    const Image & left_arrow_;
    const Image & right_arrow_;
};
