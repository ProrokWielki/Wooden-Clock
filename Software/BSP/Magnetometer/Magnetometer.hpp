/**
 * Magnetometer.hpp
 *
 *  Created on: 02-05-2019
 *  @author: Paweł Warzecha
 */

#ifndef BSP_MAGNETOMETER_MAGNETOMETER_HPP_
#define BSP_MAGNETOMETER_MAGNETOMETER_HPP_

#include <functional>
#include <stdint.h>

class Magnetometer
{
public:
    Magnetometer(std::function<int16_t()> get_x, std::function<int16_t()> get_y) : get_x_(get_x), get_y_(get_y)
    {
    }

    void update()
    {
        x_ = get_x_();
        y_ = get_y_();
    }

    int16_t get_x()
    {
        return x_;
    }

    int16_t get_y()
    {
        return y_;
    }

private:
    int16_t x_{0};
    int16_t y_{0};

    std::function<int16_t()> get_x_;
    std::function<int16_t()> get_y_;
};

#endif /* BSP_MAGNETOMETER_MAGNETOMETER_HPP_ */
