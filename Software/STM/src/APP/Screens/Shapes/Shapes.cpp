#include "include/Screens/Shapes.hpp"

void ShapesScreen::init()
{
    static const WidgetAndPositions filled{.x = 0, .y = 0, .widget = filled_circle_};
    static const WidgetAndPositions outlined{.x = get_width() / 2, .y = 0, .widget = outline_circle_};

    static const std::array<const std::reference_wrapper<const WidgetAndPositions>, 2> widgets{filled, outlined};

    add(widgets);
}

void ShapesScreen::up_date()
{
}