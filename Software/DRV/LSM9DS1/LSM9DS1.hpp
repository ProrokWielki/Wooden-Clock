/**
 * LSM9DS1.hpp
 *
 *  Created on: 30-04-2019
 *  @author: Paweł Warzecha
 */

#ifndef DRV_LSM9DS1_LSM9DS1_HPP_
#define DRV_LSM9DS1_LSM9DS1_HPP_

#include <HAL.hpp>

#include "LSM9DS1_types.hpp"

class LSM9DS1
{
public:
    LSM9DS1(SPI & spi, GPIO & gyro_cs, GPIO & magnet_cs) : spi_(spi), gyro_cs_(gyro_cs), magneto_cs_(magnet_cs)
    {
    }

    void init()
    {
        gyro_cs_.set_output_high();
        magneto_cs_.set_output_high();
    }

    void set_operation_mode(MagnetometerOperationMode operation_mode)
    {
        uint8_t register_value = read_register(MagnetometerRegister::CTRL_REG3);

        register_value = ((register_value & ~(0b11)) | (static_cast<uint8_t>(operation_mode)));

        write_register(MagnetometerRegister::CTRL_REG3, register_value);
    }

    void set_data_rate(DataRateG data_rate)
    {
        uint8_t register_value = read_register(GyroscopeRegister::CTRL_REG1);

        register_value = ((register_value & ~(0b111 << 5)) | (static_cast<uint8_t>(data_rate) << 5));

        write_register(GyroscopeRegister::CTRL_REG1, register_value);
    }

    void set_full_scale(FullScaleG full_scale)
    {
        uint8_t register_value = read_register(GyroscopeRegister::CTRL_REG1);

        register_value = ((register_value & ~(0b11 << 3)) | (static_cast<uint8_t>(full_scale) << 3));

        write_register(GyroscopeRegister::CTRL_REG1, register_value);
    }

    void set_bandwidth(BandwidthG bandwidth)
    {
        uint8_t register_value = read_register(GyroscopeRegister::CTRL_REG1);

        register_value = ((register_value & ~(0b11)) | (static_cast<uint8_t>(bandwidth)));

        write_register(GyroscopeRegister::CTRL_REG1, register_value);
    }

    void set_XY_operation_mode(MagnetometerXYOperationMode operation_mode)
    {
        uint8_t register_value = read_register(MagnetometerRegister::CTRL_REG1);

        register_value = ((register_value & ~(0b11 << 5)) | (static_cast<uint8_t>(operation_mode) << 5));

        write_register(MagnetometerRegister::CTRL_REG1, register_value);
    }

    void set_data_rate(MagnetometerDataRate data_rate)
    {
        uint8_t register_value = read_register(MagnetometerRegister::CTRL_REG1);

        register_value = ((register_value & ~(0b111 << 2)) | (static_cast<uint8_t>(data_rate) << 2));

        write_register(MagnetometerRegister::CTRL_REG1, register_value);
    }

    void set_full_scale(MagnetometerFullScale full_scale)
    {
        uint8_t register_value = read_register(MagnetometerRegister::CTRL_REG2);

        register_value = ((register_value & ~(0b11 << 5)) | (static_cast<uint8_t>(full_scale) << 5));

        write_register(MagnetometerRegister::CTRL_REG2, register_value);
    }

    int16_t get_angular_velocity(Axis axis)
    {
        GyroscopeRegister data_register = static_cast<GyroscopeRegister>(GYROSCPE_DATA | static_cast<uint8_t>(axis));

        int16_t angular_velocity = static_cast<int16_t>(read_register(data_register));
        angular_velocity |= static_cast<int16_t>(read_register(++data_register)) << 8;

        return angular_velocity;
    }

    int16_t get_linear_acceleration(Axis axis)
    {
        GyroscopeRegister data_register = static_cast<GyroscopeRegister>(ACCELEROMETER_DATA | static_cast<uint8_t>(axis));

        int16_t linear_acceleration = static_cast<int16_t>(read_register(data_register));
        linear_acceleration |= static_cast<int16_t>(read_register(++data_register)) << 8;

        return linear_acceleration;
    }

    int16_t get_magnetic_field(Axis axis)
    {
        MagnetometerRegister data_register = static_cast<MagnetometerRegister>(MAGNETOMETER_DATA | static_cast<uint8_t>(axis));

        int16_t magnetic_field = static_cast<int16_t>(read_register(data_register));
        magnetic_field |= static_cast<int16_t>(read_register(++data_register)) << 8;

        return magnetic_field;
    }

private:
    uint8_t read_register(GyroscopeRegister register_address)
    {
        gyro_cs_.set_output_low();

        int8_t register_value = read_data(static_cast<uint8_t>(register_address));

        gyro_cs_.set_output_high();

        return register_value;
    }

    uint8_t read_register(MagnetometerRegister register_address)
    {
        magneto_cs_.set_output_low();

        int8_t register_value = read_data(static_cast<uint8_t>(register_address));

        magneto_cs_.set_output_high();

        return register_value;
    }

    void write_register(GyroscopeRegister register_address, uint8_t data)
    {

        gyro_cs_.set_output_low();

        write_data(static_cast<uint8_t>(register_address), data);

        gyro_cs_.set_output_high();
    }

    void write_register(MagnetometerRegister register_address, uint8_t data)
    {
        magneto_cs_.set_output_low();

        write_data(static_cast<uint8_t>(register_address), data);

        magneto_cs_.set_output_high();
    }

    void write_data(uint8_t register_address, uint8_t data)
    {
        spi_.exchange_data(register_address);
        spi_.exchange_data(data);
    }

    uint8_t read_data(uint8_t register_address)
    {
        spi_.exchange_data(0x80 | register_address);
        return spi_.exchange_data(0);
    }

    SPI & spi_;
    GPIO & gyro_cs_;
    GPIO & magneto_cs_;
};

#endif /* DRV_LSM9DS1_LSM9DS1_HPP_ */
