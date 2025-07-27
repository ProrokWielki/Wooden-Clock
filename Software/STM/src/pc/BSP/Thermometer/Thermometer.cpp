#include <cstdint>

#include <BSP/Thermometer.hpp>


float BSP2::Thermometer::temperature{0};

float BSP2::Thermometer::get_temperature()
{
    return temperature;
}

void BSP2::Thermometer::update()
{
   const float DUMMY_TEMPERATURE{13.f};
   temperature = DUMMY_TEMPERATURE;
}