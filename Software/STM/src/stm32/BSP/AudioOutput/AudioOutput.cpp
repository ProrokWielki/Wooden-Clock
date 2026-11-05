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

#include <HAL/HAL.hpp>

AudioOutput::AudioOutput()
{
    HAL::get().DAC1.get_dma()->set_transfer_complete_callback([&]() { sound_playing_complete(); });
    HAL::get().DAC1.get_dma()->enable_interrupt(DMA_Types::Interrupt::TransferCompleted);
}

void AudioOutput::play(const std::span<const uint8_t> & data)
{
    if (is_playing)
    {
        return;
    }

    is_playing = true;
    HAL::get().DAC1.play_dma(data);
}

bool AudioOutput::is_sound_playing() const
{
    return is_playing;
}

void AudioOutput::sound_playing_complete()
{
    is_playing = false;
    HAL::get().DAC1.stop();
}
