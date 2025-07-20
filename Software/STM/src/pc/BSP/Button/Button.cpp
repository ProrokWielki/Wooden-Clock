/**
 * Button.cpp
 *
 *  Created on: 23-02-2025
 *  @author: Paweł Warzecha
 */

#include <BSP/Button.hpp>

Button::Button(std::string name) : name_(std::move(name))

{
}

void Button::update()
{
}

void Button::setPressed()
{
    pressed_ = true;
}

void Button::setReleased()
{
    if (pressed_)
    {
        released_ = true;
        pressed_ = false;
    }
}

bool Button::wasReleased()
{
    if (released_)
    {
        released_ = false;  // Reset the state after it has been read
        return true;        // Indicate that the button was released
    }
    return false;
}

bool Button::wasPressed()
{
    // if (state_)
    // {
    //     state_ = false;  // Reset the state after it has been read
    //     return true;     // Indicate that the button was released
    // }
    // return false;
    return false;
}

bool Button::isPressed()
{
    return pressed_;
}
