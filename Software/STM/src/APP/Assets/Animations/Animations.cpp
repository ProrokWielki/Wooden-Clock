#include <cassert>

#include "Animations.hpp"
#include "Arrows/Arrows.hpp"
#include "Hourglass/Hourglass.hpp"

Animation & getAnimation(AnimationType animation)
{
    switch (animation)
    {
        case AnimationType::HOURGLASS:
            return getHourglassAnimation();
        case AnimationType::ARROWS:
            return getArrowsAnimation();
        default:
            assert(false && "Unknown animation");
    }
}