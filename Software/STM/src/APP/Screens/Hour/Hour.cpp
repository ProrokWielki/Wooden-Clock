#include "include/Screens/Hour.hpp"

void Hour::init()
{
    static const WidgetAndPositions time{.x = 0, .y = 0, .widget = time_text};
    static const std::array<const std::reference_wrapper<const WidgetAndPositions>, 1> widgets{time};
    add(widgets);
}

void Hour::up_date()
{
    constexpr uint8_t MAX_SINGLE_DIDGET_MINUTE{9};

    const BSP2::Time time = BSP2::Clock::get_time();

    time_text.setText(std::to_string(time.hours) + ":" +
                      (time.minutes <= MAX_SINGLE_DIDGET_MINUTE ? "0" + std::to_string(time.minutes) : std::to_string(time.minutes)));
}