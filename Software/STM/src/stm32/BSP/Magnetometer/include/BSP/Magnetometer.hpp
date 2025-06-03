/**
 * Magnetometer.hpp
 *
 *  Created on: 02-05-2019
 *  @author: Paweł Warzecha
 */

#ifndef BSP_MAGNETOMETER_MAGNETOMETER_HPP_
#define BSP_MAGNETOMETER_MAGNETOMETER_HPP_

#include <cstdint>
#include <functional>

class Magnetometer
{
public:
    Magnetometer(std::function<int16_t()> get_x, std::function<int16_t()> get_y);

    void update();

    int16_t get_x();

    int16_t get_y();

private:
    int16_t x_{0};
    int16_t y_{0};

    std::function<int16_t()> get_x_;
    std::function<int16_t()> get_y_;
};

#endif /* BSP_MAGNETOMETER_MAGNETOMETER_HPP_ */
