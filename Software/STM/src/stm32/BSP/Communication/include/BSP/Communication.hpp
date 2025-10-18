/**
 * @file Communication.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-10-17
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include <array>
#include <cstdint>
#include <span>

struct Message {
    static constexpr uint8_t MAX_MESSAGE_LENGTH{100};

    std::array<uint8_t, MAX_MESSAGE_LENGTH> data{};
    uint8_t length{};
};

class Communication
{
public:
    [[nodiscard]] bool is_message_available() const;
    Message get_message();

    void add_byte(uint8_t byte);
    void message_end();

private:
    static constexpr uint8_t MAX_NUM_OF_MESSAGES{10};

    std::array<Message, MAX_NUM_OF_MESSAGES> messages_{};

    uint8_t head_{0};
    uint8_t tail_{0};
};
