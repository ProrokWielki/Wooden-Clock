/**
 * Button.cpp
 *
 *  Created on: 23-02-2025
 *  @author: Paweł Warzecha
 */

#include "include/BSP/Button.hpp"

#include "HAL/types.hpp"

Button::Button(GPIO & buttonGpio, GPIO_Types::SignalLevel pressedLevel)
: buttonGpio_(buttonGpio), pressedLevel_(pressedLevel), previousLevel_(pressedLevel)
{
    buttonGpio_.set_mode(GPIO_Types::PortMode::Input);
    buttonGpio_.set_pullUp_pullDown(GPIO_Types::PortPullUpPullDown::None);
}

void Button::update()
{
    const GPIO_Types::SignalLevel currentLevel = buttonGpio_.get_input_value();

    if (currentLevel == pressedLevel_ and previousLevel_ != currentLevel)
    {
        buttonPressed = true;
    }
    else if (currentLevel != pressedLevel_ and previousLevel_ != currentLevel)
    {
        buttonReleased = true;
    }

    previousLevel_ = currentLevel;
}

bool Button::wasReleased()
{
    const bool returnValue = buttonReleased;
    buttonReleased = false;

    return returnValue;
}

bool Button::wasPressed()
{
    const bool returnValue = buttonPressed;
    buttonPressed = false;

    return returnValue;
}

bool Button::isPressed()
{
    auto currentLevel = buttonGpio_.get_input_value();

    return currentLevel == pressedLevel_;
}
