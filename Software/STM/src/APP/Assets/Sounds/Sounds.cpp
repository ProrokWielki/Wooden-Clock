/**
 * @file Sounds.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-10-11
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <cstdint>

#include "Sounds.hpp"
#include "TwinkleTwinkle.hpp"

const std::span<const uint8_t> & get_sound(SoundType sound_type)
{
    const static std::span<const uint8_t> twinkle_twinkle{TwinkleTwinkle::DATA.data(), TwinkleTwinkle::LENGTH};

    switch (sound_type)
    {
        case SoundType::TWINKLE_TWINKLE:
            return twinkle_twinkle;
        default:
            return twinkle_twinkle;
    };
}
