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

#include <Canvas.hpp>
#include <widgets/Image.hpp>

#include <BSP/Accelerometer.hpp>
#include <BSP/BSP.hpp>

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
    Particle(float x, float y);

    bool operator==(const Particle & other) const;

    void set_position(float x, float y);

    void update(float accel_x, float accel_y);

    [[nodiscard]] bool should_move();

    void stop();
    void stop(float x, float y);
    void stop_x();
    void stop_y();
    [[nodiscard]] std::tuple<float, float> get_position() const;
    [[nodiscard]] std::tuple<float, float> get_speed() const;
    [[nodiscard]] std::tuple<int8_t, int8_t> get_position_as_int() const;

private:
    static constexpr float MAX_SPEED{0.5};
    static constexpr float REST_SPEED{0.02};
    static constexpr float FULL_RATE_SPEED{0.15};

    float x_{};
    float y_{};
    float speed_x_{};
    float speed_y_{};
    float move_progress_{};
};

template<size_t N>
class ParticleContainer
{
    constexpr static uint8_t NUM_OF_POSSIBLE_NEXT_POSITIONS{5};
    constexpr static size_t NUM_OF_SECTORS{64};
    struct Offset {
        int8_t dx;
        int8_t dy;
    };

    using Offsets = std::array<Offset, NUM_OF_POSSIBLE_NEXT_POSITIONS>;

    static const std::array<Offsets, NUM_OF_SECTORS> & direction_table()
    {
        static const auto table = [] {
            constexpr float PI{std::numbers::pi};
            constexpr float DIAGONAL_OFFSET{0.5};
            constexpr float HORIZONTAL_OFFSET{1.0};
            constexpr float deltas[NUM_OF_POSSIBLE_NEXT_POSITIONS]{0.0, -DIAGONAL_OFFSET, DIAGONAL_OFFSET, -HORIZONTAL_OFFSET, HORIZONTAL_OFFSET};

            std::array<Offsets, NUM_OF_SECTORS> t{};
            for (size_t s{0}; s < NUM_OF_SECTORS; ++s)
            {
                const float gravity_vector = -PI + (static_cast<float>(s) + 0.5f) * (2.0f * PI / NUM_OF_SECTORS);
                for (size_t k{0}; k < NUM_OF_POSSIBLE_NEXT_POSITIONS; ++k)
                {
                    t[s][k] = {static_cast<int8_t>(std::round(std::cos(gravity_vector + deltas[k]))),
                               static_cast<int8_t>(-std::round(std::sin(gravity_vector + deltas[k])))};
                }
            }
            return t;
        }();
        return table;
    }

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

    void update(float accel_x, float accel_y)
    {
        for (auto & particle : particles)
        {
            particle.update(accel_x, accel_y);
            if (!particle.should_move())
            {
                continue;
            }
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

        constexpr float PI{std::numbers::pi};
        const auto sector = std::min(static_cast<size_t>((gravity_vector + PI) * (NUM_OF_SECTORS / (2.0 * PI))), NUM_OF_SECTORS - 1);
        const auto & offsets = direction_table()[sector];

        std::array<std::tuple<int8_t, int8_t>, NUM_OF_POSSIBLE_NEXT_POSITIONS> result{};
        for (size_t i{0}; i < NUM_OF_POSSIBLE_NEXT_POSITIONS; ++i)
        {
            result[i] = {static_cast<int8_t>(particle_x + offsets[i].dx), static_cast<int8_t>(particle_y + offsets[i].dy)};
        }
        return result;
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

    [[nodiscard]] inline uint32_t fast_rand() const
    {
        static uint32_t state{2463534242u};
        state ^= state << 13;
        state ^= state >> 17;
        state ^= state << 5;
        return state;
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
        return movable_positions.at(fast_rand() % movable_positions_index);
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
    StateSand(BSP2::Accelerometer & accel);

    void init() override;

    void up_date() override;

private:
    BSP2::Accelerometer & accel_;
    std::array<uint8_t, BSP::DISPLAY_WIDTH * BSP::DISPLAY_WIDTH> empty_frame_buffer{};
    Image magnet;
    static constexpr uint8_t NUM_OF_PARTICLES{128};
    ParticleContainer<NUM_OF_PARTICLES> particles_{};
};