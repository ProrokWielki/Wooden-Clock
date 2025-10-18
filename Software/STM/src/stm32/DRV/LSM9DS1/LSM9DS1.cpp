/**
 * LSM9DS1.cpp
 *
 *  Created on: 05-05-2019
 *  @author: Paweł Warzecha
 */

#include "include/DRV/LSM9DS1.hpp"
#include "include/DRV/LSM9DS1_types.hpp"
#include <array>
#include <chrono>

constexpr uint8_t READ_BIT = 0x80;

LSM9DS1::LSM9DS1(SPI & spi, GPIO & gyro_cs, GPIO & magnet_cs) : spi_(spi), gyro_cs_(gyro_cs), magneto_cs_(magnet_cs)
{
    gyro_cs_.set_mode(GPIO_Types::PortMode::Output);
    gyro_cs_.set_output_high();

    magneto_cs_.set_mode(GPIO_Types::PortMode::Output);
    magneto_cs_.set_output_high();

    std::array<uint8_t, 1> data_to_write1{0x05};

    spi.write_data_to_register(gyro_cs, 0x22, {data_to_write1});
    spi.write_data_to_register(magnet_cs, 0x22, {data_to_write1});

    std::array<uint8_t, 1> data_to_write3{0x02};

    spi.write_data_to_register(gyro_cs, 0x23, {data_to_write3});

    std::array<uint8_t, 1> data_to_write1f{0b00111000};

    spi.write_data_to_register(gyro_cs, 0x1f, {data_to_write1f});

    std::array<uint8_t, 1> data_to_write2{0b11000000};

    spi.write_data_to_register(gyro_cs, 0x2E, {data_to_write2});
    // // spi.write_data_to_register(magnet_cs, 0x22, {data_to_write1});

    std::array<uint8_t, 1> data_to_write10{0xBB};
    std::array<uint8_t, 1> data_to_write20{0xA0};
    spi.write_data_to_register(gyro_cs_, 0x10, data_to_write10);  // 119 Hz, 2000 dps, 16 Hz BW
    spi.write_data_to_register(gyro_cs_, 0x20, data_to_write20);  // 119 Hz, 2g

    set_data_rate(MagnetometerDataRate::Hz_80);
    set_XY_operation_mode(MagnetometerXYOperationMode::ultra_performance);
    set_full_scale(MagnetometerFullScale::Gs_16);
    set_operation_mode(MagnetometerOperationMode::continuous_conversion);

    // set_bandwidth(BandwidthG::BW_3);
    // set_data_rate(DataRateG::Hz_952);
    // set_full_scale(FullScaleG::dps2000);
}

void LSM9DS1::set_operation_mode(MagnetometerOperationMode operation_mode)
{
    Register<uint8_t> control_register_3{read_register(MagnetometerRegister::CTRL_REG3)};
    control_register_3.set_value(static_cast<uint8_t>(operation_mode), 0, 3);

    write_register(MagnetometerRegister::CTRL_REG3, control_register_3.read());
}

void LSM9DS1::set_data_rate(DataRateG data_rate)
{
    Register<uint8_t> control_register_1{read_register(GyroscopeRegister::CTRL_REG1)};
    control_register_1.set_value(static_cast<uint8_t>(data_rate), 5, 3);

    write_register(GyroscopeRegister::CTRL_REG1, control_register_1.read());
}

void LSM9DS1::set_full_scale(FullScaleG full_scale)
{
    Register<uint8_t> control_register_1{read_register(GyroscopeRegister::CTRL_REG1)};
    control_register_1.set_value(static_cast<uint8_t>(full_scale), 3, 2);

    write_register(GyroscopeRegister::CTRL_REG1, control_register_1.read());
}

void LSM9DS1::set_bandwidth(BandwidthG bandwidth)
{
    Register<uint8_t> control_register_1{read_register(GyroscopeRegister::CTRL_REG1)};
    control_register_1.set_value(static_cast<uint8_t>(bandwidth), 0, 2);

    write_register(GyroscopeRegister::CTRL_REG1, control_register_1.read());
}

void LSM9DS1::set_XY_operation_mode(MagnetometerXYOperationMode operation_mode)
{
    Register<uint8_t> control_register_1{read_register(MagnetometerRegister::CTRL_REG1)};
    control_register_1.set_value(static_cast<uint8_t>(operation_mode), 5, 2);

    write_register(MagnetometerRegister::CTRL_REG1, control_register_1.read());
}

void LSM9DS1::set_data_rate(MagnetometerDataRate data_rate)
{
    Register<uint8_t> control_register_1{read_register(MagnetometerRegister::CTRL_REG1)};
    control_register_1.set_value(static_cast<uint8_t>(data_rate), 2, 3);

    write_register(MagnetometerRegister::CTRL_REG1, control_register_1.read());
}

void LSM9DS1::set_full_scale(MagnetometerFullScale full_scale)
{
    uint8_t register_value = read_register(MagnetometerRegister::CTRL_REG2);

    register_value = ((register_value & ~(0b11 << 5)) | (static_cast<uint8_t>(full_scale) << 5));

    write_register(MagnetometerRegister::CTRL_REG2, register_value);
}

int16_t LSM9DS1::get_angular_velocity(Axis axis)
{

    const auto angular_velocity_register_l = static_cast<GyroscopeRegister>(GYROSCPE_DATA | static_cast<uint8_t>(axis));
    const auto angular_velocity_register_h = static_cast<GyroscopeRegister>((GYROSCPE_DATA | static_cast<uint8_t>(axis)) + 1U);

    const uint16_t angular_velocity_l{read_register(angular_velocity_register_l)};
    const uint16_t angular_velocity_h{read_register(angular_velocity_register_h)};

    return static_cast<int16_t>((angular_velocity_h << 8) | angular_velocity_l);
}

Accelerations LSM9DS1::get_linear_acceleration()
{
    std::array<uint8_t, 6> accel_data{};

    std::array<uint8_t, 10> single_byte_data{};
    std::span<uint8_t> accel_buffer{single_byte_data};

    constexpr double MAX_G{2.0};  // TODO: make it right

    spi_.read_data_from_register(gyro_cs_, 0x2C | READ_BIT, {accel_buffer}, 1);
    accel_data[4] = single_byte_data[0];
    spi_.read_data_from_register(gyro_cs_, 0x2D | READ_BIT, {accel_buffer}, 1);
    accel_data[5] = single_byte_data[0];
    spi_.read_data_from_register(gyro_cs_, 0x28 | READ_BIT, {accel_buffer}, 1);
    accel_data[0] = single_byte_data[0];
    spi_.read_data_from_register(gyro_cs_, 0x29 | READ_BIT, {accel_buffer}, 1);
    accel_data[1] = single_byte_data[0];
    spi_.read_data_from_register(gyro_cs_, 0x2A | READ_BIT, {accel_buffer}, 1);
    accel_data[2] = single_byte_data[0];
    spi_.read_data_from_register(gyro_cs_, 0x2B | READ_BIT, {accel_buffer}, 1);
    accel_data[3] = single_byte_data[0];

    const uint16_t unsigned_x = (static_cast<uint16_t>(accel_data[1]) << 8) | static_cast<uint16_t>(accel_data[0]);
    const uint16_t unsigned_y = (static_cast<uint16_t>(accel_data[3]) << 8) | static_cast<uint16_t>(accel_data[2]);
    const uint16_t unsigned_z = (static_cast<uint16_t>(accel_data[5]) << 8) | static_cast<uint16_t>(accel_data[4]);

    const double x = static_cast<double>(static_cast<int16_t>(unsigned_x)) / 32768.0 * MAX_G;
    const double y = static_cast<double>(static_cast<int16_t>(unsigned_y)) / 32768.0 * MAX_G;
    const double z = static_cast<double>(static_cast<int16_t>(unsigned_z)) / 32768.0 * MAX_G;

    return {.x = x, .y = y, .z = z};
}

int16_t LSM9DS1::get_magnetic_field(Axis axis)
{
    const auto magnetic_field_register_l = static_cast<MagnetometerRegister>(MAGNETOMETER_DATA | static_cast<uint8_t>(axis));
    const auto magnetic_field_acceleration_register_h = static_cast<MagnetometerRegister>((MAGNETOMETER_DATA | static_cast<uint8_t>(axis)) + 1U);

    const uint16_t magnetic_field_l{read_register(magnetic_field_register_l)};
    const uint16_t magnetic_field_h{read_register(magnetic_field_acceleration_register_h)};

    return static_cast<int16_t>((magnetic_field_h << 8) | magnetic_field_l);
}

uint8_t LSM9DS1::read_register(GyroscopeRegister register_address)
{
    std::array<uint8_t, 2> data_buffer{};
    std::span<uint8_t> received_data{data_buffer};

    spi_.read_data_from_register(gyro_cs_, static_cast<uint8_t>(register_address) | READ_BIT, received_data, 1);

    return received_data[0];
}

uint8_t LSM9DS1::read_register(MagnetometerRegister register_address)
{
    uint8_t data_buffer{};
    std::span<uint8_t> received_data{&data_buffer, 1};

    spi_.read_data_from_register(magneto_cs_, static_cast<uint8_t>(register_address) | READ_BIT, received_data, 1);

    return received_data[0];
}

void LSM9DS1::write_register(GyroscopeRegister register_address, uint8_t data)
{

    spi_.write_data_to_register(gyro_cs_, static_cast<uint8_t>(register_address), std::span<uint8_t>{&data, 1});
}

void LSM9DS1::write_register(MagnetometerRegister register_address, uint8_t data)
{

    spi_.write_data_to_register(magneto_cs_, static_cast<uint8_t>(register_address), std::span<uint8_t>{&data, 1});
}
