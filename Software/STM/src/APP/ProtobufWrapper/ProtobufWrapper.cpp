#include <pb_decode.h>

#include "debug_msg.pb.h"
#include "esp_msg.pb.h"

#include "ProtobufWrapper.hpp"

namespace ProtobufWrapper
{
time_message parse_time_message(const uint8_t * data, size_t length)
{
    time_message result{};

    pb_istream_t stream = pb_istream_from_buffer(data, length);
    EspToMcuMsg pb_time_msg{};
    if (!pb_decode(&stream, EspToMcuMsg_fields, &pb_time_msg))
    {
        // Handle decode error
        return result;
    }

    if (pb_time_msg.which_msg == EspToMcuMsg_time_tag)
    {
        result.hours = pb_time_msg.msg.time.hours;      // NOLINT(cppcoreguidelines-pro-type-union-access)
        result.minutes = pb_time_msg.msg.time.minutes;  // NOLINT(cppcoreguidelines-pro-type-union-access)
        result.seconds = pb_time_msg.msg.time.seconds;  // NOLINT(cppcoreguidelines-pro-type-union-access)
    }

    return result;
}

Mode parse_mode_message(const uint8_t * const data, const size_t length)
{
    if (length == 0 || data == nullptr)
    {
        return Mode::NORMAL;  // Default to NORMAL if no data is provided
    }

    pb_istream_t stream = pb_istream_from_buffer(data, length);
    PcToMcuDebugMsg pb_mode_msg{};
    if (!pb_decode(&stream, PcToMcuDebugMsg_fields, &pb_mode_msg))
    {
        // Handle decode error
        return Mode::NORMAL;  // Default to NORMAL on error
    }

    switch (pb_mode_msg.msg.mode)
    {
        case Mode_FLASHING:
            return Mode::FLASHING;
        case Mode_REBOOT:
            return Mode::REBOOT;
        default:
            return Mode::NORMAL;
    }
}

}  // namespace ProtobufWrapper