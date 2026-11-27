#include "include/Screens/StateSand.hpp"

Particle::Particle(float x, float y) : x_{x}, y_{y}
{
}

bool Particle::operator==(const Particle & other) const
{
    return x_ == other.x_ && y_ == other.y_;
}

void Particle::set_position(float x, float y)
{
    x_ = x;
    y_ = y;
}

void Particle::update(float accel_x, float accel_y)
{
    constexpr float delta_t = 0.015;
    constexpr float max_speed = 0.5;
    constexpr float min_speed = -max_speed;

    constexpr float dead_zone = 0.01f;
    constexpr float friction = 0.99f;

    if (std::fabs(accel_x) < dead_zone)
    {
        accel_x = 0.0f;
    }
    if (std::fabs(accel_y) < dead_zone)
    {
        accel_y = 0.0f;
    }

    speed_x_ += accel_x * delta_t;
    speed_y_ += accel_y * delta_t;

    speed_x_ = std::clamp((speed_x_ + accel_x * delta_t) * friction, min_speed, max_speed);
    speed_y_ = std::clamp((speed_y_ + accel_y * delta_t) * friction, min_speed, max_speed);
}

[[nodiscard]] bool Particle::should_move()
{
    const float speed = std::max(std::fabs(speed_x_), std::fabs(speed_y_));
    if (speed < REST_SPEED)
    {
        move_progress_ = 0.0;
        return false;
    }

    move_progress_ += std::min(speed / FULL_RATE_SPEED, 1.0f);
    if (move_progress_ < 1.0)
    {
        return false;
    }
    move_progress_ -= 1.0;
    return true;
}

void Particle::stop()
{
    speed_x_ = 0;
    speed_y_ = 0;
}

void Particle::stop(float x, float y)
{
    speed_x_ = 0;
    speed_y_ = 0;

    x_ = x;
    y_ = y;
}

void Particle::stop_x()
{
    speed_x_ = 0;
}

void Particle::stop_y()
{
    speed_y_ = 0;
}

[[nodiscard]] std::tuple<float, float> Particle::get_position() const
{
    return {x_, y_};
}
[[nodiscard]] std::tuple<float, float> Particle::get_speed() const
{
    return {speed_x_, speed_y_};
}
[[nodiscard]] std::tuple<int8_t, int8_t> Particle::get_position_as_int() const
{
    return {x_, y_};
}

StateSand::StateSand(BSP2::Accelerometer & accel) : accel_(accel), magnet(get_width(), get_height(), empty_frame_buffer.data())
{
}

void StateSand::init()
{
    static const WidgetAndPositions mag{.x = 0, .y = 0, .widget = magnet};
    static const std::array<const std::reference_wrapper<const WidgetAndPositions>, 1> widgets{mag};

    add(widgets);
}

void StateSand::up_date()
{
    memset(empty_frame_buffer.data(), 0, get_width() * get_height());

    auto [x, y, z] = accel_.get_linear_accelerations();
    particles_.update(-x, y);

    const auto & paricless = particles_.get_particles();

    for (const auto & particle : paricless)
    {

        const auto [particle_x, particle_y] = particle.get_position();

        const auto display_x = static_cast<uint8_t>(particle_x);
        const auto display_y = static_cast<uint8_t>(particle_y);

        empty_frame_buffer.at(std::min(display_y, max_y_index()) * BSP::DISPLAY_WIDTH + std::min(display_x, max_x_index())) =
        std::numeric_limits<uint8_t>::max();
    }
}
