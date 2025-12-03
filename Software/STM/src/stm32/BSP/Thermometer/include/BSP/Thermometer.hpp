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
    [[nodiscard]] double get_temperature() const;
    void update();

private:
    double temperature_{};
};

}  // namespace BSP2