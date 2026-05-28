#include "DebugMessagesHandler.hpp"

#include <algorithm>
#include <cstring>
#include <ranges>

#include <bootloader.hpp>

void DebugMessagesHandler::handle_debug_message(Message message)
{
    std::array<uint8_t, 6> reset_message{"reset"};
    if (std::ranges::equal(message.data.data(), message.data.data() + message.length, reset_message.data(), reset_message.data() + reset_message.size()))
    {
        flash();
    }
}