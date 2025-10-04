#pragma once

#include <array>
#include <cstdint>

struct LeftArrow {
    constexpr static uint8_t WIDTH{14};
    constexpr static uint8_t HEIGHT{12};

    constexpr static std::array<uint8_t, static_cast<size_t>(WIDTH * HEIGHT)> DATA{
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
    0,   0,   0,   0,   0,   255, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,
    0,   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    0,   0,   255, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 0,   0,   0,   0,   0,   0,   0,   0,
    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    };
};