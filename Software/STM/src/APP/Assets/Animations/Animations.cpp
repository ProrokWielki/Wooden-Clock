#include <cassert>

#include "Animations.hpp"
#include "Arrows/Arrows.hpp"
#include "Hourglass/Hourglass.hpp"

Animation & get_animation(AnimationType animation)
{
    switch (animation)
    {
        case AnimationType::HOURGLASS:
            return get_hourglass_animation();
        case AnimationType::ARROWS:
            return get_arrows_animation();
        default:
            assert(false && "Unknown animation");
    }
}