/**
 * Button.hpp
 *
 *  Created on: 12-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef BSP_BUTTON_BUTTON_HPP_
#define BSP_BUTTON_BUTTON_HPP_

#include <HAL/GPIO.hpp>

class Button
{
public:
    Button(GPIO & buttonGpio, GPIO_Types::SignalLevel pressedLevel);

    void update();

    bool was_released();

    bool was_pressed();

    bool is_pressed();

private:
    GPIO & buttonGpio_;

    GPIO_Types::SignalLevel pressedLevel_;
    GPIO_Types::SignalLevel previousLevel_;

    bool buttonPressed{false};
    bool buttonReleased{false};
};

#endif /* BSP_BUTTON_BUTTON_HPP_ */
