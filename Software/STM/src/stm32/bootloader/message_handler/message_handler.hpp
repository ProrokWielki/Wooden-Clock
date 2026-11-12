#pragma once

#include <cstdint>
#include <span>

#include "peripherals/uart.hpp"

#include "pb_decode.h"
#include "pb_encode.h"

#include "flashing_command.pb.h"
#include "flashing_msg.pb.h"
#include "flashing_start.pb.h"
#include "write_data.pb.h"

namespace MessageHandler
{

enum class Message
{
    FLASHING_START,
    FLASHING_COMMAND,
    PAGE_DATA,
};

constexpr size_t get_length(Message message)
{
    switch (message)
    {
        case Message::FLASHING_START:
            return 14;
        case Message::FLASHING_COMMAND:
            return 2;
        case Message::PAGE_DATA:
            return 2064;
        default:
            return 0;
    }
}

__attribute__((section(".flasher_section"), noinline)) static std::span<uint8_t> get_buffer()
{
    static std::array<uint8_t, 2100> buffer;
    return buffer;
}

__attribute__((section(".flasher_section"), noinline)) static std::span<uint8_t> get_buffer(size_t length)
{
    return get_buffer().first(length);
}

__attribute__((section(".flasher_section"), noinline)) static FlashingStart get_flashing_start_message()
{
    PcToMcuFlashingMsg message;

    auto buffer = get_buffer(get_length(Message::FLASHING_START));
    auto read_data = UART::get_data(buffer);
    auto in_stream = pb_istream_from_buffer(read_data.data(), read_data.size());

    pb_decode(&in_stream, PcToMcuFlashingMsg_fields, &message);

    return message.msg.flashing_start;
}

__attribute__((section(".flasher_section"), noinline)) static FlashingCommand get_flashing_command_message()
{
    PcToMcuFlashingMsg message;

    auto buffer = get_buffer(get_length(Message::FLASHING_COMMAND));
    auto read_data = UART::get_data(buffer);
    auto in_stream = pb_istream_from_buffer(read_data.data(), read_data.size());

    pb_decode(&in_stream, PcToMcuFlashingMsg_fields, &message);

    return message.msg.flashing_command;
}

__attribute__((section(".flasher_section"), noinline)) static WriteData get_write_data_message()
{
    PcToMcuFlashingMsg message;

    auto buffer = get_buffer(get_length(Message::PAGE_DATA));
    auto read_data = UART::get_data(buffer);
    auto in_stream = pb_istream_from_buffer(read_data.data(), read_data.size());

    pb_decode(&in_stream, PcToMcuFlashingMsg_fields, &message);

    return message.msg.write_data;
}

__attribute__((section(".flasher_section"), noinline)) static void send_state_message(FlashingState state)
{
    McuToPcFlashingMsg flashing_msg{};
    flashing_msg.which_msg = McuToPcFlashingMsg_flashing_state_tag;
    flashing_msg.msg.flashing_state = state;

    auto buffer = get_buffer();
    pb_ostream_t stream = pb_ostream_from_buffer(buffer.data(), buffer.size());

    pb_encode(&stream, McuToPcFlashingMsg_fields, &flashing_msg);
    UART::send_data(buffer.first(stream.bytes_written));
}

}  // namespace MessageHandler