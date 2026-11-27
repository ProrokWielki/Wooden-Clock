#include "include/Screens/Temperature.hpp"

/**
 * @brief Execution of the State action.
 */
void Temperature::init()
{
    static const WidgetAndPositions temp{.x = 0, .y = 0, .widget = temperature_text};
    static const std::array<const std::reference_wrapper<const WidgetAndPositions>, 1> widgets{temp};

    add(widgets);
}

void Temperature::up_date()
{
    const auto temperature{BSP::get().thermometer.get_temperature()};
    const std::string temperature_str{std::to_string(temperature)};
    temperature_text.setText(temperature_str.substr(0, temperature_str.find(".") + 2) + "*C");
}