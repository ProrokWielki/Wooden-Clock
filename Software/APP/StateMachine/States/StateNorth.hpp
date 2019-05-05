/**
 * StateNorth.hpp
 *
 *  Created on: 02-05-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_STATEMACHINE_STATES_STATENORTH_HPP_
#define APP_STATEMACHINE_STATES_STATENORTH_HPP_

#include "../State.hpp"

#include "LSM9DS1/LSM9DS1.hpp"

#include "BSP.hpp"

class StateNorth: public State
{
public:
    explicit StateNorth(LSM9DS1 & magneto) : magneto_(magneto)
    {
    }

    virtual void execute() override
    {

        int16_t x = magneto_.get_magnetic_field(Axis::X);
        int16_t y = magneto_.get_magnetic_field(Axis::Y);

        x = -x * 16 / 3200 + 16;
        y = -y * 16 / 3200 + 16;

        x = x > 31 ? 31 : x;
        y = y > 31 ? 31 : y;

        x = x < 0 ? 0 : x;
        y = y < 0 ? 0 : y;

        empty_frame_buffer[y][x] = 255;
        BSP::display.set_frame_buffer(&empty_frame_buffer[0][0]);
    }

private:
    uint8_t empty_frame_buffer[32][32] = {0};
    LSM9DS1 & magneto_;
};

#endif /* APP_STATEMACHINE_STATES_STATENORTH_HPP_ */
