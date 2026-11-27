#include "include/Screens/Counter.hpp"

void Counter::init()
{
    static constexpr uint8_t TEXT_FIELD_HEIGHT{11};

    static const WidgetAndPositions ct_1{.x = 0, .y = 0, .widget = counter_text};
    static const WidgetAndPositions ct_2{.x = 0, .y = TEXT_FIELD_HEIGHT, .widget = counter_text2};
    static const WidgetAndPositions ct_3{.x = 0, .y = 2 * TEXT_FIELD_HEIGHT, .widget = counter_text3};

    static std::array<const std::reference_wrapper<const WidgetAndPositions>, 3> widgets{ct_1, ct_2, ct_3};

    add(widgets);
}

void Counter::up_date()
{
    constexpr static uint16_t MAX_NUMBER{1000};

    if (++counter_value > MAX_NUMBER)
    {
        counter_value = 0;
    }

    counter_text.setText(std::to_string(counter_value), TextAlignment::RIGHT);
    counter_text2.setText(std::to_string(counter_value * 2), TextAlignment::CENTER);
    counter_text3.setText(std::to_string(MAX_NUMBER - counter_value), TextAlignment::LEFT);
}