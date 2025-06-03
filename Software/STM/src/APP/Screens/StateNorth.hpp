/**
 * StateNorth.hpp
 *
 *  Created on: 02-05-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_STATEMACHINE_STATES_STATENORTH_HPP_
#define APP_STATEMACHINE_STATES_STATENORTH_HPP_

#include <Canvas.hpp>

#include <DRV/LSM9DS1.hpp>

#include <BSP/BSP.hpp>
#include <array>
#include <limits>

class StateNorth: public Canvas
{
public:
    explicit StateNorth(LSM9DS1 & magneto) : magneto_(magneto), magnet(32, 32, &empty_frame_buffer[0][0])
    {
    }

    void init() override
    {
        add(&magnet);
        // validate();
    }

    void up_date() override
    {
        int16_t x = magneto_.get_magnetic_field(Axis::X);
        int16_t y = magneto_.get_magnetic_field(Axis::Y);

        constexpr static uint8_t INDEX_HALF_SCREEN{static_cast<uint8_t>(get_width()/2U)};

        x = -x * INDEX_HALF_SCREEN / std::numeric_limits<int16_t>::max() + INDEX_HALF_SCREEN;
        y = -y * INDEX_HALF_SCREEN / std::numeric_limits<int16_t>::max()  + INDEX_HALF_SCREEN;

        x = x > get_width() - 1 ? get_width() - 1 : x;
        y = y > get_height() - 1 ? get_height() - 1 : y;

        x = x < 0 ? 0 : x;
        y = y < 0 ? 0 : y;

        empty_frame_buffer[y][x] = std::numeric_limits<uint8_t>::max();

        // validate();
    }

private:
    LSM9DS1 & magneto_;
    std::array<std::array<uint8_t, get_width()>,get_height()> empty_frame_buffer{};
    Image magnet;
};

#endif /* APP_STATEMACHINE_STATES_STATENORTH_HPP_ */
