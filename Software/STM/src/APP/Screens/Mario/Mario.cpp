#include "include/Screens/StateMario.hpp"

StateMario::StateMario() : mario(get_image(ImageType::MARIO))

{
}
void StateMario::init()
{
    static const WidgetAndPositions im{.x = 0, .y = 0, .widget = mario};
    static const std::array<const std::reference_wrapper<const WidgetAndPositions>, 1> widgets{im};

    add(widgets);
}

void StateMario::up_date()
{
}