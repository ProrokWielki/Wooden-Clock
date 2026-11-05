#pragma once

#include <array>
#include <cstdint>

struct DownArrow {
    constexpr static size_t WIDTH{12};
    constexpr static size_t HEIGHT{14};

    [[gnu::section(".external_flash")]] inline static const std::array<uint8_t, WIDTH * HEIGHT> DATA{
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
    0,   0,   0,   0,   255, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   255,
    255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 255, 255, 0,   0,
    0,   0,   0,   0,   0,   0,   255, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,
    0,   255, 255, 255, 255, 0,   0,   0,   0,   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,   255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 0,   0,   0,   255, 255, 255, 255, 255, 255, 255, 255, 0,   0,   0,   0,   0,   255, 255, 255, 255, 255, 255, 0,   0,   0,   0,
    0,   0,   0,   255, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 0,   0,   0,   0,   0
    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    };
};
