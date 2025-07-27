/**
  * Thermometer.hpp
  *
  *  Created on: 26-07-2025
  *  @author: Paweł Warzecha
  */

#pragma once

#include "BSP/Thermometer.hpp"

namespace BSP2{

class Thermometer
{
public:
    [[nodiscard]] float get_temperature() const;
    void update();

private:
    float temperature_{};
};

}