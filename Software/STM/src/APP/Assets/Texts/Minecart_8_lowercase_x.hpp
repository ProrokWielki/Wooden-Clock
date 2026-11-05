#pragma once

#include <array>
#include <cstdint>

#include "texts.hpp"

struct Minecart_8_lowercase_x
{
    [[gnu::section(".external_flash")]] inline static const std::array<uint8_t, 60> DATA{
    0,   0, 0, 0, 0,   0, 0, 0,   0, 0,   0, 0, 0, 0, 0,   0, 0, 0, 0, 0,   0, 0,   0, 0, 0,   0, 0, 0, 0,   0,
    184, 0, 0, 0, 184, 0, 0, 184, 0, 184, 0, 0, 0, 0, 184, 0, 0, 0, 0, 184, 0, 184, 0, 0, 184, 0, 0, 0, 184, 0,
    };
    constexpr static std::size_t WIDTH{6};
    constexpr static std::size_t HEIGHT{10};
    constexpr static std::size_t FONT_SIZE{8};
};