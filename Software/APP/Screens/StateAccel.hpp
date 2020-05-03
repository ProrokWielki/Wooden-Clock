/**
 * StataAccel.hpp
 *
 *  Created on: 02-05-2020
 *  @author: Paweł Warzecha
 */

#ifndef APP_STATEMACHINE_STATES_STATEACCEL_HPP_
#define APP_STATEMACHINE_STATES_STATEACCEL_HPP_

#include <Canvas.hpp>

#include "LSM9DS1/LSM9DS1.hpp"

#include "BSP.hpp"

class StateAccel: public Canvas
{
public:
    explicit StateAccel(LSM9DS1 & accel) : accel_(accel), magnet(32, 32, &empty_frame_buffer[0][0])
    {
    }

    void init() override
    {
        add(&magnet);
        validate();
    }

    virtual void up_date() override
    {
        static uint8_t old_x = 0;
        static uint8_t old_y = 0;

        int16_t x = accel_.get_linear_acceleration(Axis::X);
        int16_t y = accel_.get_linear_acceleration(Axis::Y);

        x = ((-x * 16) >> 14) + 16;
        y = ((y * 16) >> 14) + 16;

        x = x > 31 ? 31 : x;
        y = y > 31 ? 31 : y;

        x = x < 0 ? 0 : x;
        y = y < 0 ? 0 : y;

        empty_frame_buffer[old_y][old_x] = 0;

        old_x = x;
        old_y = y;

        empty_frame_buffer[y][x] = 255;

        validate();
    }

private:
    LSM9DS1 & accel_;
    uint8_t empty_frame_buffer[32][32] = {0};
    Image magnet;
};

#endif /* APP_STATEMACHINE_STATES_STATENORTH_HPP_ */
