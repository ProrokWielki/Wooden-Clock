#include "include/Screens/StateArrows.hpp"

#include <widgets/Animation.hpp>

StateArrows::StateArrows() : arrows{get_animation(AnimationType::ARROWS)}
{
}

void StateArrows::init()
{
    static const WidgetAndPositions arr{.x = 0, .y = 0, .widget = arrows};
    static const std::array<const std::reference_wrapper<const WidgetAndPositions>, 1> widgets{arr};
    add(widgets);
    // validate();
}

void StateArrows::up_date()
{
}