/**
 * @file StateSand.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-29
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "Canvas.hpp"

#include <BSP/Accelerometer.hpp>
#include <algorithm>
#include <array>
#include <cerrno>
#include <cstdint>
#include <cstdlib>
#include <limits>
#include <optional>
#include <random>
#include <stddef.h>
#include <tuple>

class Particle
{
public:
    Particle() = default;
    Particle(double x, double y) : x_{x}, y_{y}
    {
    }

    bool operator==(const Particle & other) const
    {
        return x_ == other.x_ && y_ == other.y_;
    }

    void set_position(double x, double y)
    {
        x_ = x;
        y_ = y;
    }

    void update(double accel_x, double accel_y)
    {
        constexpr double delta_t = 0.2;
        constexpr double max_speed = 0.5;
        constexpr double min_speed = -max_speed;

        speed_x_ += accel_x * delta_t;
        speed_y_ += accel_y * delta_t;

        speed_x_ = std::clamp(speed_x_, min_speed, max_speed);
        speed_y_ = std::clamp(speed_y_, min_speed, max_speed);
    }

    void stop()
    {
        speed_x_ = 0;
        speed_y_ = 0;
    }

    void stop(double x, double y)
    {
        speed_x_ = 0;
        speed_y_ = 0;

        x_ = x;
        y_ = y;
    }

    void stop_x()
    {
        speed_x_ = 0;
    }

    void stop_y()
    {
        speed_y_ = 0;
    }

    [[nodiscard]] std::tuple<double, double> get_position() const
    {
        return {x_, y_};
    }
    [[nodiscard]] std::tuple<double, double> get_speed() const
    {
        return {speed_x_, speed_y_};
    }
    [[nodiscard]] std::tuple<int8_t, int8_t> get_position_as_int() const
    {
        return {x_, y_};
    }

private:
    double x_{};
    double y_{};
    double speed_x_{};
    double speed_y_{};
};

template<size_t N>
class ParticleContainer
{
    constexpr static uint8_t NUM_OF_POSSIBLE_NEXT_POSITIONS{5};

public:
    ParticleContainer()
    {
        std::array<std::tuple<int8_t, int8_t>, N> initial_positions{};
        for (size_t i{0}; i < N; ++i)
        {

            while (true)
            {
                auto next_position =
                std::make_tuple<int8_t, int8_t>(static_cast<int8_t>(rand() % BSP::DISPLAY_WIDTH), static_cast<int8_t>(rand() % BSP::DISPLAY_HEIGHT));
                const std::span<std::tuple<int8_t, int8_t>> populated_indices(initial_positions.data(), i);
                if (std::ranges::find(populated_indices, next_position) != populated_indices.end())
                {
                    continue;
                }
                initial_positions.at(i) = next_position;
                particles.at(i) = Particle(std::get<0>(next_position), std::get<1>(next_position));
                break;
            }
        }
    }

    void update(double accel_x, double accel_y)
    {
        for (auto & particle : particles)
        {
            particle.update(accel_x, accel_y);
            auto maybe_next_position = get_first_movable_positions(particle);
            if (maybe_next_position.has_value())
            {
                auto [next_x, next_y] = maybe_next_position.value();
                particle.set_position(next_x, next_y);
                if (next_x == 0 or next_x == BSP::DISPLAY_WIDTH - 1)
                {
                    particle.stop_x();
                }
                if (next_y == 0 or next_y == BSP::DISPLAY_HEIGHT - 1)
                {
                    particle.stop_y();
                }
            }
            else
            {
                particle.stop();
            }
        }
    }

    [[nodiscard]] std::array<std::tuple<int8_t, int8_t>, NUM_OF_POSSIBLE_NEXT_POSITIONS> get_all_possible_next_positions(const Particle & particle) const
    {
        auto [acceleration_x, acceleration_y] = particle.get_speed();
        auto gravity_vector = atan2(-acceleration_y, acceleration_x);

        auto [particle_x, particle_y] = particle.get_position_as_int();

        static constexpr double DIAGONAL_OFFSET{0.5};
        static constexpr double HORIZONTAL_OFFSET{1.0};

        return {{
        {particle_x + std::round(std::cos(gravity_vector)), particle_y - std::round(std::sin(gravity_vector))},
        {particle_x + std::round(std::cos(gravity_vector - DIAGONAL_OFFSET)), particle_y - std::round(std::sin(gravity_vector - DIAGONAL_OFFSET))},
        {particle_x + std::round(std::cos(gravity_vector + DIAGONAL_OFFSET)), particle_y - std::round(std::sin(gravity_vector + DIAGONAL_OFFSET))},
        {particle_x + std::round(std::cos(gravity_vector - HORIZONTAL_OFFSET)), particle_y - std::round(std::sin(gravity_vector - HORIZONTAL_OFFSET))},
        {particle_x + std::round(std::cos(gravity_vector + HORIZONTAL_OFFSET)), particle_y - std::round(std::sin(gravity_vector + HORIZONTAL_OFFSET))},
        }};
    }

    [[nodiscard]] std::span<std::tuple<int8_t, int8_t>> get_valid_next_positions(const Particle & particle) const
    {
        auto all_possible_next_positions = get_all_possible_next_positions(particle);
        static std::array<std::tuple<int8_t, int8_t>, NUM_OF_POSSIBLE_NEXT_POSITIONS> valid_next_positions{};
        uint8_t valid_next_positions_index{0};

        for (const auto & position : all_possible_next_positions)
        {
            if (std::get<0>(position) < 0 || std::get<0>(position) >= static_cast<int8_t>(BSP::DISPLAY_WIDTH) || std::get<1>(position) < 0 ||
                std::get<1>(position) >= static_cast<int8_t>(BSP::DISPLAY_HEIGHT))
            {
                continue;
            }
            valid_next_positions.at(valid_next_positions_index++) = position;
        }
        return {valid_next_positions.data(), valid_next_positions_index};
    }

    [[nodiscard]] std::optional<std::tuple<int8_t, int8_t>> get_first_movable_positions(const Particle & particle) const
    {
        std::array<std::tuple<int8_t, int8_t>, NUM_OF_POSSIBLE_NEXT_POSITIONS> movable_positions{};
        uint8_t movable_positions_index{0};
        auto valid_positions = get_valid_next_positions(particle);

        for (const auto & valid_position : valid_positions)
        {
            bool is_valid_position{true};
            for (const auto & other_particle : particles)
            {
                if (other_particle == particle)
                {
                    continue;
                }
                if (other_particle.get_position_as_int() == valid_position)
                {
                    is_valid_position = false;
                    break;
                }
            }
            if (is_valid_position)
            {
                movable_positions.at(movable_positions_index++) = valid_position;
            }
        }
        if (movable_positions_index == 0)
        {
            return std::nullopt;
        }
        return movable_positions.at(rand() % movable_positions_index);
    }

    // for (size_t i{0}; i < N; ++i)
    // {
    //     if (particles_updated[i] == false)
    //     {
    //         auto [particle_x, particle_y] = particles[i].get_position();
    //         particles[i].stop(particle_x, particle_y);
    //     }
    // }
    // }

    [[nodiscard]] const std::array<Particle, N> & get_particles() const
    {
        return particles;
    }

private:
    std::array<Particle, N> particles{};
};

class StateSand: public Canvas
{
public:
    StateSand(BSP2::Accelerometer & accel) : accel_(accel), magnet(get_width(), get_height(), empty_frame_buffer.data())
    {
    }

    void init() override
    {
        add(&magnet);
        // validate();
    }

    void up_date() override
    {
        memset(empty_frame_buffer.data(), 0, get_width() * get_height());

        auto [x, y, z] = accel_.get_linear_accelerations();
        particles_.update(-x, y);

        auto paricless = particles_.get_particles();

        for (const auto & particle : paricless)
        {

            const auto [particle_x, particle_y] = particle.get_position();

            const auto display_x = static_cast<uint8_t>(particle_x);
            const auto display_y = static_cast<uint8_t>(particle_y);

            empty_frame_buffer.at(std::min(display_y, max_y_index()) * BSP::DISPLAY_WIDTH + std::min(display_x, max_x_index())) =
            std::numeric_limits<uint8_t>::max();
        }

        // validate();
    }

private:
    BSP2::Accelerometer & accel_;
    std::array<uint8_t, BSP::DISPLAY_WIDTH * BSP::DISPLAY_WIDTH> empty_frame_buffer{};
    Image magnet;
    static constexpr uint8_t NUM_OF_PARTICLES{128};
    ParticleContainer<NUM_OF_PARTICLES> particles_{};
};