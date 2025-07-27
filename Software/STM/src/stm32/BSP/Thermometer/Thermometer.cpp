
#include <DRV/BME280.hpp>
#include <HAL/HAL.hpp>

#include <BSP/Thermometer.hpp>

float BSP2::Thermometer::get_temperature() const
{
    return temperature_;
}

void BSP2::Thermometer::update()
{
    temperature_ = HAL::BME280_1.get_temperature();
}