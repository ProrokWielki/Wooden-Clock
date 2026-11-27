/**
 * @file ButtonStateMachine.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-11-26
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "include/ButtonHandler/detail/ButtonStateMachine.hpp"
#include <algorithm>

void ButtonStateMachine::update(bool is_button_pressed)
{
    ++current_wait_cycles;

    const auto found_transition = std::ranges::find_if(transitions_, [this, is_button_pressed](Transition transition) {
        return transition.origin == this->state_ && transition.is_button_pressed == is_button_pressed && this->current_wait_cycles > transition.wait_cycles;
    });

    if (found_transition != transitions_.end())
    {
        current_wait_cycles = 0;
        state_ = found_transition->target;
    }
}

ButtonStateMachine::State ButtonStateMachine::get_state() const
{
    return state_;
}