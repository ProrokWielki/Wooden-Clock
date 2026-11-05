#pragma once

namespace ProtobufWrapper
{
struct time_message {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
};

enum class Mode
{
    FLASHING,
    REBOOT,
    NORMAL
};

time_message parse_time_message(const uint8_t * data, size_t length);
Mode parse_mode_message(const uint8_t * const data, const size_t length);

}  // namespace ProtobufWrapper
