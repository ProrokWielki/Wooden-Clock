/**
 * LSM9DS1_registers.hpp
 *
 *  Created on: 30-04-2019
 *  @author: Paweł Warzecha
 */

#ifndef DRV_LSM9DS1_LSM9DS1_TYPES_HPP_
#define DRV_LSM9DS1_LSM9DS1_TYPES_HPP_

#include <cstdint>

constexpr uint8_t GYROSCPE_DATA = 0x10;
constexpr uint8_t ACCELEROMETER_DATA = 0x20;
constexpr uint8_t MAGNETOMETER_DATA = 0x20;

enum class Axis
{
    X = 0x08,
    Y = 0x0A,
    Z = 0x0C
};

enum class GyroscopeRegister : uint8_t
{
    CTRL_REG1 = 0x10,
    CTRL_REG4 = 0x1E,

    WHO_AM_I = 0x0F,

    OUT_X_G_L = 0x18,
    OUT_X_G_H = 0x19,
    OUT_Y_G_L = 0x1A,
    OUT_Y_G_H = 0x1B,
    OUT_Z_G_L = 0x1C,
    OUT_Z_G_H = 0x1D,

};

enum class MagnetometerRegister : uint8_t
{
    CTRL_REG1 = 0x20,
    CTRL_REG2 = 0x21,
    CTRL_REG3 = 0x22,

    WHO_AM_I = 0x0F,

    OUT_X_L_M = 0x28,
    OUT_X_H_M = 0x29,
    OUT_Y_L_M = 0x2A,
    OUT_Y_H_M = 0x2B,
    OUT_Z_L_M = 0x2C,
    OUT_Z_H_M = 0x2D

};

enum class DataRateG : uint8_t
{
    Hz_14_9 = 1,
    Hz_59_5 = 2,
    Hz_119 = 3,
    Hz_238 = 4,
    Hz_476 = 5,
    Hz_952 = 6
};

enum class FullScaleG : uint8_t
{
    dps_245 = 0,
    dps500 = 1,
    dps2000 = 3
};

enum class BandwidthG : uint8_t
{
    BW_0 = 0,
    BW_1 = 1,
    BW_2 = 2,
    BW_3 = 3
};

enum class MagnetometerXYOperationMode : uint8_t
{
    medium_performance = 1,
    high_performance = 2,
    ultra_performance = 3
};

enum class MagnetometerDataRate : uint8_t
{
    Hz_0_625 = 0,
    Hz_1_25 = 1,
    Hz_2_5 = 2,
    Hz_5 = 3,
    Hz_10 = 4,
    Hz_20 = 5,
    Hz_40 = 6,
    Hz_80 = 7
};

enum class MagnetometerFullScale : uint8_t
{
    Gs_4 = 0,
    Gs_8 = 1,
    Gs_12 = 2,
    Gs_16 = 3
};

enum class MagnetometerOperationMode : uint8_t
{
    continuous_conversion = 0,
    single_conversion = 1,
    power_down = 2
};

GyroscopeRegister & operator++(GyroscopeRegister & a);

MagnetometerRegister & operator++(MagnetometerRegister & a);

#endif /* DRV_LSM9DS1_LSM9DS1_TYPES_HPP_ */
