/**
 * @file ButtonHandler.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-11-26
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <BSP/Button.hpp>

#include "include/ButtonHandler/ButtonHandler.hpp"

ButtonHandler::ButtonHandler(Button button) : button_(button)
{
}

void ButtonHandler::update()
{
    button_.update();

    button_state_machine_.update(button_.is_pressed());

    previous_state_ = current_state_;
    current_state_ = button_state_machine_.get_state();

    auto new_button_state = determine_button_state();

    if (new_button_state != ButtonState::NONE)
    {
        button_state_ = new_button_state;
    }
}

bool ButtonHandler::is_pressed()
{
    return button_.is_pressed();
}

bool ButtonHandler::was_released()
{
    if (button_state_ == ButtonState::RELEASED)
    {
        button_state_ = ButtonState::NONE;
        return true;
    }
    return false;
}

bool ButtonHandler::was_double_pressed()
{
    if (button_state_ == ButtonState::DOUBLE_PRESSED)
    {
        button_state_ = ButtonState::NONE;
        return true;
    }
    return false;
}

bool ButtonHandler::was_long_pressed()
{
    if (button_state_ == ButtonState::LONG_PRESSED)
    {
        button_state_ = ButtonState::NONE;
        return true;
    }
    return false;
}

ButtonState ButtonHandler::determine_button_state()
{
    if (current_state_ != ButtonStateMachine::State::IDLE and current_state_ != ButtonStateMachine::State::WAIT_FOR_RELEASE)
    {
        return ButtonState::NONE;
    }

    switch (previous_state_)
    {
        case ButtonStateMachine::State::RELEASED:
            return ButtonState::RELEASED;
        case ButtonStateMachine::State::DOUBLE_PRESSED:
            return ButtonState::DOUBLE_PRESSED;
        case ButtonStateMachine::State::LONG_PRESSED:
            return ButtonState::LONG_PRESSED;
        case ButtonStateMachine::State::IDLE:
        case ButtonStateMachine::State::PRESSED:
        case ButtonStateMachine::State::WAIT_FOR_RELEASE:
        default:
            return ButtonState::NONE;
    }
}