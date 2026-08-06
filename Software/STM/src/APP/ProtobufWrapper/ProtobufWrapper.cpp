#include <pb_decode.h>

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

    result.hours = pb_time_msg.msg.time.hours;
    result.minutes = pb_time_msg.msg.time.minutes;
    result.seconds = pb_time_msg.msg.time.seconds;

    return result;
}
}  // namespace ProtobufWrapper