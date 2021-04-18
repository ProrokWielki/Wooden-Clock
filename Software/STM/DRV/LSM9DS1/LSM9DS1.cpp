/**
 * LSM9DS1.cpp
 *
 *  Created on: 05-05-2019
 *  @author: Paweł Warzecha
 */

#include "LSM9DS1.hpp"
#include "LSM9DS1_types.hpp"

GyroscopeRegister & operator++(GyroscopeRegister & a)
{
    a = static_cast<GyroscopeRegister>(static_cast<int>(a) + 1);
    return a;
}

MagnetometerRegister & operator++(MagnetometerRegister & a)
{
    a = static_cast<MagnetometerRegister>(static_cast<int>(a) + 1);
    return a;
}
