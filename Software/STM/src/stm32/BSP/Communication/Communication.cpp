#include <cassert>

#include <BSP/Communication.hpp>

bool Communication::is_message_available() const
{
    return head_ != tail_;
}

Message Communication::get_message()
{
    assert(is_message_available() && "No massages available.");
    auto oldest_message = messages_.at(tail_);

    tail_ = (tail_ + 1) % MAX_NUM_OF_MESSAGES;

    return oldest_message;
}

void Communication::add_byte(uint8_t byte)
{
    auto & current_message = messages_.at(head_);

    current_message.data.at(current_message.length++) = byte;
}

void Communication::message_end()
{
    head_ = (head_ + 1) % MAX_NUM_OF_MESSAGES;
    messages_.at(head_).length = 0;
}