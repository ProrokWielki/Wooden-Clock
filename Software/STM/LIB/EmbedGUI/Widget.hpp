/**
 * Widget.hpp
 *
 *  Created on: 07-04-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_GUI_WIDGET_HPP_
#define APP_GUI_WIDGET_HPP_

#include <cstdint>

class Widget
{
public:
    Widget() = default;

    uint8_t getWidth()
    {
        return width_;
    }

    uint8_t getHeight()
    {
        return height_;
    }

    uint8_t * get_pixel_map()
    {
        return pixel_map_;
    }

    virtual void update()
    {
    }

    virtual bool is_self_updatable()
    {
        return false;
    }

    virtual ~Widget()
    {
    }

    void setPixelMap(uint8_t * width)
    {
        pixel_map_ = width;
    }

    bool is_visible()
    {
        return is_visible_;
    }

    void hide()
    {
        is_visible_ = false;
    }

    void show()
    {
        is_visible_ = true;
    }

protected:
    void setWidth(uint8_t width)
    {
        width_ = width;
    }
    void setHeight(uint8_t width)
    {
        height_ = width;
    }

    uint8_t width_{};
    uint8_t height_{};

    uint8_t * pixel_map_{};

    bool is_visible_{true};
};

#endif /* APP_GUI_WIDGET_HPP_ */
