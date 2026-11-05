#include "DebugMessagesHandler.hpp"

#include <algorithm>
#include <cstring>
#include <ranges>

#include <bootloader.hpp>

void DebugMessagesHandler::handle_debug_message(ProtobufWrapper::Mode message)
{
    switch (message)
    {
        case ProtobufWrapper::Mode::FLASHING:
            flash();
            break;
        case ProtobufWrapper::Mode::REBOOT:
            // reset
            break;
        case ProtobufWrapper::Mode::NORMAL:
        default:
            break;
    }
}