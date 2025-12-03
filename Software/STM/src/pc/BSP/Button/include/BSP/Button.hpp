/**
 * Button.hpp
 *
 *  Created on: 12-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef BSP_BUTTON_BUTTON_HPP_
#define BSP_BUTTON_BUTTON_HPP_

#include <string>

class Button
{
public:
    Button(std::string name);

    void update();

    bool was_released();

    bool was_pressed();

    bool is_pressed();

    void set_pressed();

    void set_released();

private:
    // GPIO & buttonGpio_;

    // GPIO_Types::SignalLevel pressedLevel_;
    // GPIO_Types::SignalLevel previousLevel_;

    // bool buttonPressed{false};
    // bool buttonReleased{false};
    std::string name_;
    bool pressed_{false};   // Current state of the button
    bool released_{false};  // Previous state of the button
};

#endif /* BSP_BUTTON_BUTTON_HPP_ */
