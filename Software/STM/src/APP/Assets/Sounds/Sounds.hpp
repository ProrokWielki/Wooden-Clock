/**
 * @file Sounds.hpp
 * @author Pawel Warzecha (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-10-11
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <cstdint>
#include <span>

enum class SoundType
{
    TWINKLE_TWINKLE
};

const std::span<const uint8_t> & get_sound(SoundType sound);