/**
 * Thermometer.hpp
 *
 *  Created on: 26-07-2025
 *  @author: Paweł Warzecha
 */

#pragma once

namespace BSP2
{

class Thermometer
{
public:
    [[nodiscard]] float get_temperature() const;
    void update();

private:
    float temperature_{};
};

}  // namespace BSP2