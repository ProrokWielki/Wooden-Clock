#pragma once

namespace ProtobufWrapper
{
struct time_message {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
};

time_message parse_time_message(const uint8_t * data, size_t length);

}  // namespace ProtobufWrapper
