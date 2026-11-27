
#include "include/Screens/StateHourglass.hpp"

StateHourglass::StateHourglass() : hourglass{get_animation(AnimationType::HOURGLASS)}
{
}

void StateHourglass::init()
{
    static const WidgetAndPositions hour{.x = 0, .y = 0, .widget = hourglass};
    static const std::array<const std::reference_wrapper<const WidgetAndPositions>, 1> widgets{hour};

    add(widgets);
}

void StateHourglass::up_date()
{
}
