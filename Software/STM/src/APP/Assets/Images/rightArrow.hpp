#pragma once

#include <array>
#include <cstdint>

struct RightArrow {
    constexpr static size_t WIDTH{14};
    constexpr static size_t HEIGHT{12};

    [[gnu::section(".external_flash")]] inline static const std::array<uint8_t, WIDTH * HEIGHT> DATA{
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
    0,   0,   0,   0,   0,   0,   0,   0,   255, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 255, 255, 0,   0,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,
    0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 255, 0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 0,   0,   0,   0,   0,
    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    };
};