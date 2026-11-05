/**
 * @file AudioOutput.hpp
 * @author Pawel Warzecha (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-10-10
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <cstdint>
#include <span>

class AudioOutput
{
public:
    AudioOutput();

    void play(const std::span<const uint8_t> & data);
    [[nodiscard]] bool is_sound_playing() const;

private:
    void sound_playing_complete();

    bool is_playing{false};
};