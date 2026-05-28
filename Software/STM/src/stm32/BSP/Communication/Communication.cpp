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

[[nodiscard]] char Communication::get_last_received_char() const
{
    if (messages_.at(head_).length == 0)
    {
        return '\0';
    }

    auto & current_message = messages_.at(head_);
    auto last_char_position = current_message.length - 1;
    return current_message.data.at(last_char_position);
}

void Communication::discard_last_received_char()
{
    if (messages_.at(head_).length == 0)
    {
        return;
    }

    auto & current_message = messages_.at(head_);
    current_message.length--;
}

void Communication::message_end(bool add_zero_in_the_end)
{
    if (add_zero_in_the_end)
    {
        add_byte('\0');
    }
    head_ = (head_ + 1) % MAX_NUM_OF_MESSAGES;
    messages_.at(head_).length = 0;
}