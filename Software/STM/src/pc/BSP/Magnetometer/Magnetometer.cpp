/**
 * @file Magnetometer.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-06-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <BSP/Magnetometer.hpp>

BSP2::MagneticField BSP2::Magnetometer::get_magnetic_filed() const
{
    return magnetic_filed_;
}

void BSP2::Magnetometer::update()
{
    magnetic_filed_.x = 0;  // Replace with actual accelerometer reading
    magnetic_filed_.y = 0;  // Replace with actual accelerometer reading
    magnetic_filed_.z = 0;  // Replace with actual accelerometer reading
}