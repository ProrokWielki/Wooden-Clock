#pragma once

#include <string>

#include <widgets/Animation.hpp>

enum class AnimationType
{
    HOURGLASS,
    ARROWS
};

Animation & get_animation(AnimationType animation);