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
#include <array>
#include <limits>
#include <stddef.h>

class Particle
{
public:
    Particle() = default;
    Particle(double x, double y) : x_{x}, y_{y}
    {
    }

    void set_position(double x, double y)
    {
        x_ = x;
        y_ = y;
    }

    void update(double accel_x, double accel_y)
    {
        constexpr double delta_t = 0.2;

        speed_x_ += accel_x * delta_t;
        speed_y_ += accel_y * delta_t;

        x_ += speed_x_ * delta_t;
        y_ += speed_y_ * delta_t;
    }

    void stop(double x, double y)
    {
        if (std::abs(x - x_) > 0.5)
        {
            speed_x_ = 0;
        }

        if (std::abs(y - y_) > 0.5)
        {
            speed_y_ = 0;
        }
        x_ = x;
        y_ = y;
    }

    [[nodiscard]] std::tuple<double, double> get_position() const
    {
        return {x_, y_};
    }
    [[nodiscard]] std::tuple<uint8_t, uint8_t> get_position_as_uint() const
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
public:
    ParticleContainer()
    {
        for (size_t i{0}; i < N; ++i)
        {
            particles[i].set_position(i % 31, i / 31);
        }
    }

    void update(double accel_x, double accel_y)
    {
        auto particles_after_update = particles;
        for (auto & particle : particles_after_update)
        {
            particle.update(accel_x, accel_y);
        }

        bool needs_updating{true};
        std::array<bool, N> particles_updated{};

        while (needs_updating)
        {
            for (size_t i{0}; i < N; ++i)
            {
                needs_updating = !particles_updated[i];
                if (needs_updating == false)
                {
                    continue;
                }

                for (size_t k{0}; k < N; ++k)
                {
                    if (k == i)
                    {
                        continue;
                    }

                    if (particles_after_update[i].get_position_as_uint() == particles[k].get_position_as_uint())
                    {
                        needs_updating = false;
                        break;
                    }
                }
                if (needs_updating)
                {
                    particles[i] = particles_after_update[i];
                    particles_updated[i] = true;
                    break;
                }
            }
        }

        for (auto & particle : particles)
        {
            auto [particle_x, particle_y] = particle.get_position();

            if (particle_x < 0 || particle_x > 31 || particle_y < 0 || particle_y > 31)
            {
                particle_x = particle_x < 0.0 ? 0.0 : particle_x > 31.0 ? 31 : particle_x;
                particle_y = particle_y < 0.0 ? 0.0 : particle_y > 31.0 ? 31 : particle_y;

                particle.stop(particle_x, particle_y);
            }
        }
        for (size_t i{0}; i < N; ++i)
        {
            if (particles_updated[i] == false)
            {
                auto [particle_x, particle_y] = particles[i].get_position();
                particles[i].stop(particle_x, particle_y);
            }
        }
    }

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
    StateSand(BSP2::Accelerometer & accel) : accel_(accel), magnet(get_width(), get_height(), empty_frame_buffer[0])
    {
    }

    void init() override
    {
        add(&magnet);
        // validate();
    }

    void up_date() override
    {
        memset(empty_frame_buffer, 0, get_width() * get_height());

        auto [x, y, z] = accel_.get_linear_accelerations();
        particles_.update(-x, y);

        auto paricless = particles_.get_particles();

        for (const auto & particle : paricless)
        {

            const auto [particle_x, particle_y] = particle.get_position();

            const auto display_x = static_cast<uint8_t>(particle_x);
            const auto display_y = static_cast<uint8_t>(particle_y);

            empty_frame_buffer[std::min(display_y,max_y_index())][std::min(display_x,max_x_index())] = std::numeric_limits<uint8_t>::max();
        }

        // validate();
    }

private:
    BSP2::Accelerometer & accel_;
    uint8_t empty_frame_buffer[32][32] = {};
    Image magnet;
    ParticleContainer<1> particles_{};
};