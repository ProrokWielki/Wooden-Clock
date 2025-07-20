/**
 * Magnetometer.hpp
 *
 *  Created on: 02-05-2019
 *  @author: Paweł Warzecha
 */

#ifndef BSP_MAGNETOMETER_MAGNETOMETER_HPP_
#define BSP_MAGNETOMETER_MAGNETOMETER_HPP_

#include <cstdint>
#include <functional>

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
}  // namespace BSP2
#endif /* BSP_MAGNETOMETER_MAGNETOMETER_HPP_ */
