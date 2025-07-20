
#include "include/BSP/Accelerometer.hpp"
#include <BSP/Accelerometer.hpp>

BSP2::Accelerations BSP2::Accelerometer::get_linear_accelerations() const
{
    return accelerations_;
}

void BSP2::Accelerometer::update()
{
    accelerations_.x = 0.0f;  // Replace with actual accelerometer reading
    accelerations_.y = 0.0f;  // Replace with actual accelerometer reading
    accelerations_.z = 0.0f;  // Replace with actual accelerometer reading
}