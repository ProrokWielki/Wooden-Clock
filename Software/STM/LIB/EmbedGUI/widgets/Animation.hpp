/**
 * Animation.hpp
 *
 *  Created on: 02-04-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_GUI_WIDGETS_ANIMATION_HPP_
#define APP_GUI_WIDGETS_ANIMATION_HPP_

#include <array>
#include <stdint.h>

#include "../Widget.hpp"

template<uint8_t NUM_OF_FRAMES>
class Animation: public Widget
{
public:
    Animation(uint8_t width, uint8_t height, std::array<uint8_t *, NUM_OF_FRAMES> frames) : frames_{frames}
    {
        setWidth(width);
        setHeight(height);
        setPixelMap((frames_[current_frame]));
    }

    void update() override
    {
        current_frame++;
        current_frame = current_frame >= NUM_OF_FRAMES ? 0 : current_frame;

        setPixelMap((frames_[current_frame]));
    }

    bool is_self_updatable() override
    {
        return true;
    }

private:
    uint8_t current_frame{0};
    std::array<uint8_t *, NUM_OF_FRAMES> frames_;
};

#endif /* APP_GUI_WIDGETS_ANIMATION_HPP_ */
