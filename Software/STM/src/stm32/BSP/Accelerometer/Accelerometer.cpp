
#include <HAL/HAL.hpp>

#include <DRV/LSM9DS1.hpp>

#include <BSP/Accelerometer.hpp>

BSP2::Accelerations BSP2::Accelerometer::get_linear_accelerations() const
{
    return accelerations_;
}

void BSP2::Accelerometer::update()
{
    auto accelerations = HAL::LSM9DS1_1.get_linear_acceleration();

    accelerations_.x = accelerations.x;
    accelerations_.y = accelerations.y;
    accelerations_.z = accelerations.z;
}