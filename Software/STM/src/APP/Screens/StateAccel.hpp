/**
 * StataAccel.hpp
 *
 *  Created on: 02-05-2020
 *  @author: Paweł Warzecha
 */

#ifndef APP_STATEMACHINE_STATES_STATEACCEL_HPP_
#define APP_STATEMACHINE_STATES_STATEACCEL_HPP_

#include <Canvas.hpp>

#include <BSP/Accelerometer.hpp>

#include <BSP/BSP.hpp>
#include <cstdint>
#include <limits>

class StateAccel: public Canvas
{
public:
    explicit StateAccel(BSP2::Accelerometer & accel) : accel_(accel), magnet(32, 32, empty_frame_buffer.data())
    {
    }

    void init() override
    {
        add(&magnet);
        // validate();
    }

    void up_date() override
    {
        memset(empty_frame_buffer.data(), 0, get_height() * get_width());

        const auto [x, y, z] = accel_.get_linear_accelerations();

        const double scaled_x = (-x * 16.0) + 15.0;
        const double scaled_y = (y * 16.0) + 15.0;

        const auto display_x = static_cast<uint8_t>(scaled_x);
        const auto display_y = static_cast<uint8_t>(scaled_y);

        empty_frame_buffer[std::min(display_y, max_y_index()) * BSP::DISPLAY_WIDTH + std::min(display_x, max_x_index())] = std::numeric_limits<uint8_t>::max();

        // validate();
    }

private:
    BSP2::Accelerometer & accel_;
    std::array<uint8_t, BSP::DISPLAY_HEIGHT*BSP::DISPLAY_WIDTH> empty_frame_buffer{};
    Image magnet;
};

#endif /* APP_STATEMACHINE_STATES_STATENORTH_HPP_ */
