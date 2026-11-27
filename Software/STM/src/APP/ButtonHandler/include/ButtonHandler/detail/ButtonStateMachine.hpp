/**
 * @file ButtonStateMachine.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-11-26
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <array>
#include <cstdint>

class ButtonStateMachine
{
public:
    enum class State : uint8_t
    {
        IDLE,
        PRESSED,
        LONG_PRESSED,
        RELEASED,
        DOUBLE_PRESSED,
        WAIT_FOR_RELEASE
    };

    void update(bool is_button_pressed);
    [[nodiscard]] State get_state() const;

private:
    struct Transition {
        State origin{State::IDLE};
        bool is_button_pressed{false};
        State target{State::IDLE};
        uint8_t wait_cycles{0};
    };

    uint8_t current_wait_cycles{0};

    State state_{State::IDLE};

    static constexpr std::array transitions_{
    Transition{.origin = State::IDLE, .is_button_pressed = true, .target = State::PRESSED, .wait_cycles = 0},

    Transition{.origin = State::PRESSED, .is_button_pressed = true, .target = State::LONG_PRESSED, .wait_cycles = 50},
    Transition{.origin = State::PRESSED, .is_button_pressed = false, .target = State::RELEASED, .wait_cycles = 0},

    Transition{.origin = State::RELEASED, .is_button_pressed = true, .target = State::DOUBLE_PRESSED, .wait_cycles = 0},
    Transition{.origin = State::RELEASED, .is_button_pressed = false, .target = State::IDLE, .wait_cycles = 15},

    Transition{.origin = State::LONG_PRESSED, .is_button_pressed = true, .target = State::WAIT_FOR_RELEASE, .wait_cycles = 0},
    Transition{.origin = State::LONG_PRESSED, .is_button_pressed = false, .target = State::IDLE, .wait_cycles = 0},

    Transition{.origin = State::DOUBLE_PRESSED, .is_button_pressed = true, .target = State::WAIT_FOR_RELEASE, .wait_cycles = 0},
    Transition{.origin = State::DOUBLE_PRESSED, .is_button_pressed = false, .target = State::IDLE, .wait_cycles = 0},

    Transition{.origin = State::WAIT_FOR_RELEASE, .is_button_pressed = false, .target = State::IDLE, .wait_cycles = 0},

    };
};