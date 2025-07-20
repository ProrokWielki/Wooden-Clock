/**
 * @file Magnetometer.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-06-04
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include <cstdint>

namespace BSP2
{

struct MagneticField {
    int16_t x;
    int16_t y;
    int16_t z;
};

class Magnetometer
{
public:
    [[nodiscard]] MagneticField get_magnetic_filed() const;
    void update();

private:
    MagneticField magnetic_filed_{};
};
}