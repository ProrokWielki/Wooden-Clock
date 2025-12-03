/**
 * StateNorth.hpp
 *
 *  Created on: 02-05-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_STATEMACHINE_STATES_STATENORTH_HPP_
#define APP_STATEMACHINE_STATES_STATENORTH_HPP_

#include <Canvas.hpp>

#include <BSP/Magnetometer.hpp>

#include <BSP/BSP.hpp>
#include <array>
#include <limits>

class StateNorth: public Canvas
{
public:
    explicit StateNorth(BSP2::Magnetometer & magneto) : magneto_(magneto), magnet(get_width(), get_height(), empty_frame_buffer.data())
    {
    }

    void init() override
    {
        add(&magnet);
        // validate();
    }

    void up_date() override
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

private:
    BSP2::Magnetometer & magneto_;
    std::array<uint8_t, get_width() * get_height()> empty_frame_buffer{};
    Image magnet;
};

#endif /* APP_STATEMACHINE_STATES_STATENORTH_HPP_ */
