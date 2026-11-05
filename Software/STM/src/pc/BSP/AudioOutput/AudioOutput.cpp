/**
 * @file AudioOutput.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-10-10
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "include/BSP/AudioOutput.hpp"

AudioOutput::AudioOutput()
{
}

void AudioOutput::play(const std::span<const uint8_t> &)
{
}

bool AudioOutput::is_sound_playing() const
{
    return is_playing;
}

void AudioOutput::sound_playing_complete()
{
}
