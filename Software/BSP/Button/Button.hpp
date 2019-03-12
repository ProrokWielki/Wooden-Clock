/**
 * Button.hpp
 *
 *  Created on: 12-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef BSP_BUTTON_BUTTON_HPP_
#define BSP_BUTTON_BUTTON_HPP_

#include "HAL.hpp"

class Button
{
public:
    Button(GPIO & buttonGpio, SignalLevel_t pressedLevel)
    : buttonGpio_(buttonGpio), pressedLevel_(pressedLevel), previousLevel_(pressedLevel), buttonPressed(false), buttonReleased(false)
    {
    }

    void update()
    {
        SignalLevel_t currentLevel = buttonGpio_.get_input_value();

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

    bool wasReleased()
    {
        bool returnValue = buttonReleased;
        buttonReleased = false;

        return returnValue;
    }

    bool wasPressed()
    {
        bool returnValue = buttonPressed;
        buttonPressed = false;

        return returnValue;
    }

private:
    GPIO & buttonGpio_;
    SignalLevel_t pressedLevel_;

    SignalLevel_t previousLevel_;

    bool buttonPressed;
    bool buttonReleased;
};

#endif /* BSP_BUTTON_BUTTON_HPP_ */
