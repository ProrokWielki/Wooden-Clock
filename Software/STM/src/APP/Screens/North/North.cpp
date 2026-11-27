#include "include/Screens/StateNorth.hpp"

StateNorth::StateNorth(BSP2::Magnetometer & magneto) : magneto_(magneto), magnet(get_width(), get_height(), empty_frame_buffer.data())
{
}

void StateNorth::init()
{
    static const WidgetAndPositions mag{.x = 0, .y = 0, .widget = magnet};
    static const std::array<const std::reference_wrapper<const WidgetAndPositions>, 1> widgets{mag};

    add(widgets);
}

void StateNorth::up_date()
{
    const BSP2::MagneticField magnetic_field{magneto_.get_magnetic_filed()};

    int16_t x{magnetic_field.x};
    int16_t y{magnetic_field.y};

    const static int8_t INDEX_HALF_SCREEN{static_cast<int8_t>(get_width() / 2U)};

    x = static_cast<int16_t>(-x * INDEX_HALF_SCREEN / std::numeric_limits<int16_t>::max() + INDEX_HALF_SCREEN);
    y = static_cast<int16_t>(-y * INDEX_HALF_SCREEN / std::numeric_limits<int16_t>::max() + INDEX_HALF_SCREEN);

    x = std::clamp(x, static_cast<int16_t>(0), static_cast<int16_t>(get_width() - 1));
    y = std::clamp(y, static_cast<int16_t>(0), static_cast<int16_t>(get_width() - 1));

    empty_frame_buffer.at(y * get_width() + x) = std::numeric_limits<uint8_t>::max();

    // validate();
}