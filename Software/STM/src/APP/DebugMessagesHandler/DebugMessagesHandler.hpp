#pragma once

#include <BSP/Communication.hpp>

#include "ProtobufWrapper.hpp"

class DebugMessagesHandler
{
public:
    void handle_debug_message(ProtobufWrapper::Mode message);
};