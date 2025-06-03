/**
 * LSM9DS1.hpp
 *
 *  Created on: 30-04-2019
 *  @author: Paweł Warzecha
 */

#ifndef DRV_LSM9DS1_LSM9DS1_HPP_
#define DRV_LSM9DS1_LSM9DS1_HPP_

#include <HAL/GPIO.hpp>
#include <HAL/SPI.hpp>

#include "LSM9DS1_types.hpp"

struct Accelerations {
    double x{};
    double y{};
    double z{};
};

class LSM9DS1
{
public:
    LSM9DS1(SPI & spi, GPIO & gyro_cs, GPIO & magnet_cs);

    void set_operation_mode(MagnetometerOperationMode operation_mode);

    void set_data_rate(DataRateG data_rate);

    void set_full_scale(FullScaleG full_scale);

    void set_bandwidth(BandwidthG bandwidth);

    void set_XY_operation_mode(MagnetometerXYOperationMode operation_mode);

    void set_data_rate(MagnetometerDataRate data_rate);

    void set_full_scale(MagnetometerFullScale full_scale);

    int16_t get_angular_velocity(Axis axis);

    Accelerations get_linear_acceleration();

    int16_t get_magnetic_field(Axis axis);

private:
    uint8_t read_register(GyroscopeRegister register_address);

    uint8_t read_register(MagnetometerRegister register_address);

    void write_register(GyroscopeRegister register_address, uint8_t data);

    void write_register(MagnetometerRegister register_address, uint8_t data);

    void write_data(uint8_t register_address, uint8_t data);

    uint8_t read_data(uint8_t register_address);

    SPI & spi_;
    GPIO & gyro_cs_;
    GPIO & magneto_cs_;
};

#endif /* DRV_LSM9DS1_LSM9DS1_HPP_ */
