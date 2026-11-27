/**
 * @file ButtonHandler.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-11-26
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <cstdint>

#include <BSP/Button.hpp>

#include "detail/ButtonStateMachine.hpp"

enum class ButtonState : uint8_t
{
    NONE,
    PRESSED,
    LONG_PRESSED,
    DOUBLE_PRESSED,
    RELEASED,
};

class ButtonHandler
{
public:
    ButtonHandler(Button button);

    void update();

    bool is_pressed();
    bool was_released();
    bool was_double_pressed();
    bool was_long_pressed();

private:
    ButtonState determine_button_state();

    Button button_;

    ButtonStateMachine::State previous_state_{ButtonStateMachine::State::IDLE};
    ButtonStateMachine::State current_state_{ButtonStateMachine::State::IDLE};

    ButtonState button_state_{ButtonState::NONE};

    ButtonStateMachine button_state_machine_;
};