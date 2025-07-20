/**
 * Magnetometer.cpp
 *
 *  Created on: 23-02-2025
 *  @author: Paweł Warzecha
 */

#include <DRV/LSM9DS1.hpp>
#include <HAL/HAL.hpp>

#include <BSP/Magnetometer.hpp>

BSP2::MagneticField BSP2::Magnetometer::get_magnetic_filed() const
{
    return magnetic_filed_;
}

void BSP2::Magnetometer::update()
{
    magnetic_filed_.x = HAL::LSM9DS1_1.get_magnetic_field(Axis::X); 
    magnetic_filed_.y = HAL::LSM9DS1_1.get_magnetic_field(Axis::Y);   
    magnetic_filed_.z = HAL::LSM9DS1_1.get_magnetic_field(Axis::Z);   
}