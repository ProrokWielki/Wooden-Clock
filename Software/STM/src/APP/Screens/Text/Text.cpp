#include "include/Screens/Text.hpp"

void TextScreen::init()
{
    static const WidgetAndPositions ct1{.x = 0, .y = 0, .widget = counter_text1};
    static const WidgetAndPositions ct2{.x = 0, .y = counter_text1.getHeight(), .widget = counter_text2};
    static const WidgetAndPositions ct3{.x = 0, .y = static_cast<uint8_t>(counter_text1.getHeight() + counter_text2.getHeight()), .widget = counter_text3};

    static const std::array<const std::reference_wrapper<const WidgetAndPositions>, 3> widgets{ct1, ct2, ct3};

    add(widgets);
}