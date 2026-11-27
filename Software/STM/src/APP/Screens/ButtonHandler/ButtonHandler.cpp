#include "include/Screens/StateButtonHandler.hpp"

StateButtonHandler::StateButtonHandler() : button_handler_{BSP::get().button_right}
{
}

void StateButtonHandler::init()
{
    static const WidgetAndPositions up{.x = 0, .y = 0, .widget = text};

    static const std::array<const std::reference_wrapper<const WidgetAndPositions>, 1> widgets{up};

    add(widgets);
}

void StateButtonHandler::up_date()
{
    button_handler_.update();

    if (button_handler_.was_released())
    {
        text.setText("Released");
    }
    else if (button_handler_.was_double_pressed())
    {
        text.setText("Double pressed");
    }
    else if (button_handler_.was_long_pressed())
    {
        text.setText("Long press");
    }
}