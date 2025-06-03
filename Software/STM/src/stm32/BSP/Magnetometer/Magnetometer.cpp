/**
 * Magnetometer.cpp
 *
 *  Created on: 23-02-2025
 *  @author: Paweł Warzecha
 */

#include <cstdint>
#include <functional>

#include "include/BSP/Magnetometer.hpp"

Magnetometer::Magnetometer(std::function<int16_t()> get_x, std::function<int16_t()> get_y) : get_x_(std::move(get_x)), get_y_(std::move(get_y))
{
}

void Magnetometer::update()
{
    x_ = get_x_();
    y_ = get_y_();
}

int16_t Magnetometer::get_x()
{
    return x_;
}

int16_t Magnetometer::get_y()
{
    return y_;
}
