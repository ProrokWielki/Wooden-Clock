#include "include/Screens/StateAccel.hpp"

StateAccel::StateAccel(BSP2::Accelerometer & accel) : accel_(accel), magnet(get_width(), get_height(), empty_frame_buffer.data())
{
}

void StateAccel::init()
{

    static const WidgetAndPositions mag{.x = 0, .y = 0, .widget = magnet};
    static const std::array<const std::reference_wrapper<const WidgetAndPositions>, 1> widgets{mag};

    add(widgets);
    // validate();
}

void StateAccel::up_date()
{
    memset(empty_frame_buffer.data(), 0, get_height() * get_width());

    const auto [x, y, z] = accel_.get_linear_accelerations();

    const float scaled_x = (-x * 16.0f) + 15.0f;
    const float scaled_y = (y * 16.0f) + 15.0f;

    const auto display_x = static_cast<uint8_t>(scaled_x);
    const auto display_y = static_cast<uint8_t>(scaled_y);

    empty_frame_buffer.at(std::min(display_y, max_y_index()) * get_width() + std::min(display_x, max_x_index())) = std::numeric_limits<uint8_t>::max();

    // validate();
}