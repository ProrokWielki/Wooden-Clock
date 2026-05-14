#include <pb_decode.h>

#include "time_msg.pb.h"

#include "ProtobufWrapper.hpp"

namespace ProtobufWrapper
{
time_message parse_time_message(const uint8_t * data, size_t length)
{
    time_message result{};

    pb_istream_t stream = pb_istream_from_buffer(data, length);
    time_msg pb_time_msg{};
    if (!pb_decode(&stream, time_msg_fields, &pb_time_msg))
    {
        // Handle decode error
        return result;
    }

    result.hours = pb_time_msg.hours;
    result.minutes = pb_time_msg.minutes;
    result.seconds = pb_time_msg.seconds;

    return result;
}
}  // namespace ProtobufWrapper