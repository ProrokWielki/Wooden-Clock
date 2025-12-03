/**
 * @file BME280.cpp
 * @author Paweł Warzecha
 * @date 2025-02-06
 */

#include "BME280_SensorAPI/bme280_defs.h"
#include <cstdint>

#include <BME280_SensorAPI/bme280.h>

#include <DRV/BME280.hpp>

namespace
{
bme280_uncomp_data to_bme280_uncomp_data(uint32_t temperature, uint32_t pressure, uint32_t humidity)
{
    return {.pressure = pressure, .temperature = temperature, .humidity = humidity};
}

bme280_calib_data to_bme280_calib_data(uint16_t dig_t1, int16_t dig_t2, int16_t dig_t3, uint16_t dig_p1, int16_t dig_p2, int16_t dig_p3, int16_t dig_p4,
                                       int16_t dig_p5, int16_t dig_p6, int16_t dig_p7, int16_t dig_p8, int16_t dig_p9, uint8_t dig_h1, int16_t dig_h2,
                                       uint8_t dig_h3, int16_t dig_h4, int16_t dig_h5, int8_t dig_h6

)
{
    return {.dig_t1 = dig_t1,
            .dig_t2 = dig_t2,
            .dig_t3 = dig_t3,
            .dig_p1 = dig_p1,
            .dig_p2 = dig_p2,
            .dig_p3 = dig_p3,
            .dig_p4 = dig_p4,
            .dig_p5 = dig_p5,
            .dig_p6 = dig_p6,
            .dig_p7 = dig_p7,
            .dig_p8 = dig_p8,
            .dig_p9 = dig_p9,
            .dig_h1 = dig_h1,
            .dig_h2 = dig_h2,
            .dig_h3 = dig_h3,
            .dig_h4 = dig_h4,
            .dig_h5 = dig_h5,
            .dig_h6 = dig_h6,
            .t_fine = 0};
}
}  // namespace

BME280::BME280(SPI & spi, GPIO & chip_select) : spi_(spi), chip_select_(chip_select)
{
}

void BME280::init()
{
    chip_select_.set_output_high();

    get_calibration_data();
}

uint8_t BME280::get_id()
{
    constexpr uint8_t ID_REGISTER_ADDRESS{0x0D0};
    return read_8_bits_register(ID_REGISTER_ADDRESS);
}

uint32_t BME280::get_raw_humidity()
{

    constexpr uint8_t HUMIDITY_MSB_REGISTER_ADDRESS{0xFD};
    constexpr uint8_t HUMIDITY_LSB_REGISTER_ADDRESS{0xFE};

    return read_16_bits_register_as<uint32_t>(HUMIDITY_MSB_REGISTER_ADDRESS, HUMIDITY_LSB_REGISTER_ADDRESS);
}

uint32_t BME280::get_raw_temperature()
{
    constexpr uint8_t RAW_TEMPERATURE_MSB_REGISTER_ADDRESS{0xFA};
    constexpr uint8_t RAW_TEMPERATURE_LSB_REGISTER_ADDRESS{0xFB};
    constexpr uint8_t RAW_TEMPERATURE_XLSB_REGISTER_ADDRESS{0xFC};

    return read_20_bits_register_as<uint32_t>(RAW_TEMPERATURE_MSB_REGISTER_ADDRESS, RAW_TEMPERATURE_LSB_REGISTER_ADDRESS,
                                              RAW_TEMPERATURE_XLSB_REGISTER_ADDRESS);
}

uint32_t BME280::get_raw_pressure()
{
    constexpr uint8_t RAW_PRESSURE_MSB_REGISTER_ADDRESS{0xF7};
    constexpr uint8_t RAW_PRESSURE_LSB_REGISTER_ADDRESS{0xF8};
    constexpr uint8_t RAW_PRESSURE_XLSB_REGISTER_ADDRESS{0xF9};

    return read_20_bits_register_as<uint32_t>(RAW_PRESSURE_MSB_REGISTER_ADDRESS, RAW_PRESSURE_LSB_REGISTER_ADDRESS, RAW_PRESSURE_XLSB_REGISTER_ADDRESS);
}

double BME280::get_temperature()
{
    auto calibration = to_bme280_calib_data(
    calibration_data.dig_T1, calibration_data.dig_T2, calibration_data.dig_T3, calibration_data.dig_P1, calibration_data.dig_P2, calibration_data.dig_P3,
    calibration_data.dig_P4, calibration_data.dig_P5, calibration_data.dig_P6, calibration_data.dig_P7, calibration_data.dig_P8, calibration_data.dig_P9,
    calibration_data.dig_H1, calibration_data.dig_H2, calibration_data.dig_H3, calibration_data.dig_H4, calibration_data.dig_H5, calibration_data.dig_H6);

    auto raw_temperature = get_raw_temperature();

    auto uncompensated_data = to_bme280_uncomp_data(raw_temperature, 0, 0);

    bme280_data compensated_data{};

    bme280_compensate_data(BME280_TEMP, &uncompensated_data, &compensated_data, &calibration);

    return compensated_data.temperature;
}

double BME280::get_pressure()
{

    auto calibration = to_bme280_calib_data(
    calibration_data.dig_T1, calibration_data.dig_T2, calibration_data.dig_T3, calibration_data.dig_P1, calibration_data.dig_P2, calibration_data.dig_P3,
    calibration_data.dig_P4, calibration_data.dig_P5, calibration_data.dig_P6, calibration_data.dig_P7, calibration_data.dig_P8, calibration_data.dig_P9,
    calibration_data.dig_H1, calibration_data.dig_H2, calibration_data.dig_H3, calibration_data.dig_H4, calibration_data.dig_H5, calibration_data.dig_H6);

    auto raw_temperature = get_raw_temperature();
    auto raw_pressure = get_raw_pressure();

    auto uncompensated_data = to_bme280_uncomp_data(raw_temperature, raw_pressure, 0);

    bme280_data compensated_data{};

    bme280_compensate_data(BME280_PRESS, &uncompensated_data, &compensated_data, &calibration);

    return compensated_data.pressure;
}

double BME280::get_humidity()
{
    auto calibration = to_bme280_calib_data(
    calibration_data.dig_T1, calibration_data.dig_T2, calibration_data.dig_T3, calibration_data.dig_P1, calibration_data.dig_P2, calibration_data.dig_P3,
    calibration_data.dig_P4, calibration_data.dig_P5, calibration_data.dig_P6, calibration_data.dig_P7, calibration_data.dig_P8, calibration_data.dig_P9,
    calibration_data.dig_H1, calibration_data.dig_H2, calibration_data.dig_H3, calibration_data.dig_H4, calibration_data.dig_H5, calibration_data.dig_H6);

    auto raw_temperature = get_raw_temperature();
    auto raw_humidity = get_raw_humidity();

    auto uncompensated_data = to_bme280_uncomp_data(raw_temperature, 0, raw_humidity);

    bme280_data compensated_data{};

    bme280_compensate_data(BME280_HUM, &uncompensated_data, &compensated_data, &calibration);

    return compensated_data.humidity;
}

void BME280::get_calibration_data()
{

    // TEMPERATURE CALIBRATION DATA
    constexpr uint8_t CALIBRATION_T1_MSB_REGISTER_ADDRESS{0x89};
    constexpr uint8_t CALIBRATION_T1_LSB_REGISTER_ADDRESS{0x88};
    calibration_data.dig_T1 = read_16_bits_register_as<uint16_t>(CALIBRATION_T1_MSB_REGISTER_ADDRESS, CALIBRATION_T1_LSB_REGISTER_ADDRESS);

    constexpr uint8_t CALIBRATION_T2_MSB_REGISTER_ADDRESS{0x8B};
    constexpr uint8_t CALIBRATION_T2_LSB_REGISTER_ADDRESS{0x8A};
    calibration_data.dig_T2 = read_16_bits_register_as<int16_t>(CALIBRATION_T2_MSB_REGISTER_ADDRESS, CALIBRATION_T2_LSB_REGISTER_ADDRESS);

    constexpr uint8_t CALIBRATION_T3_MSB_REGISTER_ADDRESS{0x8D};
    constexpr uint8_t CALIBRATION_T3_LSB_REGISTER_ADDRESS{0x8C};
    calibration_data.dig_T3 = read_16_bits_register_as<int16_t>(CALIBRATION_T3_MSB_REGISTER_ADDRESS, CALIBRATION_T3_LSB_REGISTER_ADDRESS);

    // PRESSURE CALIBRATION DATA
    constexpr uint8_t CALIBRATION_P1_MSB_REGISTER_ADDRESS{0x8F};
    constexpr uint8_t CALIBRATION_P1_LSB_REGISTER_ADDRESS{0x8E};
    calibration_data.dig_P1 = read_16_bits_register_as<uint16_t>(CALIBRATION_P1_MSB_REGISTER_ADDRESS, CALIBRATION_P1_LSB_REGISTER_ADDRESS);

    constexpr uint8_t CALIBRATION_P2_MSB_REGISTER_ADDRESS{0x91};
    constexpr uint8_t CALIBRATION_P2_LSB_REGISTER_ADDRESS{0x90};
    calibration_data.dig_P2 = read_16_bits_register_as<int16_t>(CALIBRATION_P2_MSB_REGISTER_ADDRESS, CALIBRATION_P2_LSB_REGISTER_ADDRESS);

    constexpr uint8_t CALIBRATION_P3_MSB_REGISTER_ADDRESS{0x93};
    constexpr uint8_t CALIBRATION_P3_LSB_REGISTER_ADDRESS{0x92};
    calibration_data.dig_P3 = read_16_bits_register_as<int16_t>(CALIBRATION_P3_MSB_REGISTER_ADDRESS, CALIBRATION_P3_LSB_REGISTER_ADDRESS);

    constexpr uint8_t CALIBRATION_P4_MSB_REGISTER_ADDRESS{0x95};
    constexpr uint8_t CALIBRATION_P4_LSB_REGISTER_ADDRESS{0x94};
    calibration_data.dig_P4 = read_16_bits_register_as<int16_t>(CALIBRATION_P4_MSB_REGISTER_ADDRESS, CALIBRATION_P4_LSB_REGISTER_ADDRESS);

    constexpr uint8_t CALIBRATION_P5_MSB_REGISTER_ADDRESS{0x97};
    constexpr uint8_t CALIBRATION_P5_LSB_REGISTER_ADDRESS{0x96};
    calibration_data.dig_P5 = read_16_bits_register_as<int16_t>(CALIBRATION_P5_MSB_REGISTER_ADDRESS, CALIBRATION_P5_LSB_REGISTER_ADDRESS);

    constexpr uint8_t CALIBRATION_P6_MSB_REGISTER_ADDRESS{0x99};
    constexpr uint8_t CALIBRATION_P6_LSB_REGISTER_ADDRESS{0x98};
    calibration_data.dig_P6 = read_16_bits_register_as<int16_t>(CALIBRATION_P6_MSB_REGISTER_ADDRESS, CALIBRATION_P6_LSB_REGISTER_ADDRESS);

    constexpr uint8_t CALIBRATION_P7_MSB_REGISTER_ADDRESS{0x9B};
    constexpr uint8_t CALIBRATION_P7_LSB_REGISTER_ADDRESS{0x9A};
    calibration_data.dig_P7 = read_16_bits_register_as<int16_t>(CALIBRATION_P7_MSB_REGISTER_ADDRESS, CALIBRATION_P7_LSB_REGISTER_ADDRESS);

    constexpr uint8_t CALIBRATION_P8_MSB_REGISTER_ADDRESS{0x9D};
    constexpr uint8_t CALIBRATION_P8_LSB_REGISTER_ADDRESS{0x9C};
    calibration_data.dig_P8 = read_16_bits_register_as<int16_t>(CALIBRATION_P8_MSB_REGISTER_ADDRESS, CALIBRATION_P8_LSB_REGISTER_ADDRESS);

    constexpr uint8_t CALIBRATION_P9_MSB_REGISTER_ADDRESS{0x9F};
    constexpr uint8_t CALIBRATION_P9_LSB_REGISTER_ADDRESS{0x9E};
    calibration_data.dig_P9 = read_16_bits_register_as<int16_t>(CALIBRATION_P9_MSB_REGISTER_ADDRESS, CALIBRATION_P9_LSB_REGISTER_ADDRESS);

    // HUMIDITY CALIBRATION DATA
    constexpr uint8_t CALIBRATION_H1_REGISTER_ADDRESS{0xA1};
    calibration_data.dig_H1 = read_8_bits_register_as<uint8_t>(CALIBRATION_H1_REGISTER_ADDRESS);

    constexpr uint8_t CALIBRATION_H2_MSB_REGISTER_ADDRESS{0xE2};
    constexpr uint8_t CALIBRATION_H2_LSB_REGISTER_ADDRESS{0xE1};
    calibration_data.dig_H2 = read_16_bits_register_as<int16_t>(CALIBRATION_H2_MSB_REGISTER_ADDRESS, CALIBRATION_H2_LSB_REGISTER_ADDRESS);

    constexpr uint8_t CALIBRATION_H3_REGISTER_ADDRESS{0xE3};
    calibration_data.dig_H3 = read_8_bits_register_as<uint8_t>(CALIBRATION_H3_REGISTER_ADDRESS);

    constexpr uint8_t CALIBRATION_H4_MSB_REGISTER_ADDRESS{0xE4};
    constexpr uint8_t CALIBRATION_H4_LSB_REGISTER_ADDRESS{0xE5};
    constexpr uint8_t CALIBRATION_H4_LSB_MASK{0x0F};
    const auto h4_8_bits_msb_value = static_cast<int16_t>(read_8_bits_register_as<int16_t>(CALIBRATION_H4_MSB_REGISTER_ADDRESS) << 4);
    const auto h4_4_bits_lsb_value = static_cast<int16_t>(read_8_bits_register_as<int16_t>(CALIBRATION_H4_LSB_REGISTER_ADDRESS) & CALIBRATION_H4_LSB_MASK);
    calibration_data.dig_H4 = static_cast<int16_t>(h4_8_bits_msb_value | h4_4_bits_lsb_value);

    constexpr uint8_t CALIBRATION_H5_MSB_REGISTER_ADDRESS{0xE6};
    constexpr uint8_t CALIBRATION_H5_LSB_REGISTER_ADDRESS{0xE5};
    const auto h5_8_bits_msb_value = static_cast<int16_t>(read_8_bits_register_as<int16_t>(CALIBRATION_H5_MSB_REGISTER_ADDRESS) << 4);
    const auto h5_4_bits_lsb_value = static_cast<int16_t>(read_8_bits_register_as<int16_t>(CALIBRATION_H5_LSB_REGISTER_ADDRESS) >> 4);
    calibration_data.dig_H5 = static_cast<int16_t>(h5_8_bits_msb_value | h5_4_bits_lsb_value);

    constexpr uint8_t CALIBRATION_H6_REGISTER_ADDRESS{0xE7};
    calibration_data.dig_H6 = read_8_bits_register_as<int8_t>(CALIBRATION_H6_REGISTER_ADDRESS);
}

uint8_t BME280::read_8_bits_register(uint8_t register_address)
{
    return read_data(register_address);
}

uint16_t BME280::read_16_bits_register(uint8_t msb_register_address, uint8_t lsb_register_address)
{
    constexpr uint8_t MSB_OFFSET{8};

    return (read_8_bits_register_as<uint16_t>(msb_register_address) << MSB_OFFSET) | read_8_bits_register_as<uint16_t>(lsb_register_address);
}

uint32_t BME280::read_20_bits_register(uint8_t msb_register_address, uint8_t lsb_register_address, uint8_t xlsb_register_address)
{
    constexpr uint8_t MSB_OFFSET{12};
    constexpr uint8_t LSB_OFFSET{4};
    constexpr uint8_t XLSB_OFFSET{4};

    return (read_8_bits_register_as<uint32_t>(msb_register_address) << MSB_OFFSET) | (read_8_bits_register_as<uint32_t>(lsb_register_address) << LSB_OFFSET) |
           (read_8_bits_register_as<uint32_t>(xlsb_register_address) >> XLSB_OFFSET);
}

uint8_t BME280::read_data(uint8_t register_address)
{
    uint8_t received_data{};
    std::span<uint8_t> received_data_buffer{&received_data, 1};

    constexpr uint8_t READ_BIT{0x80};

    spi_.read_data_from_register(chip_select_, READ_BIT | register_address, received_data_buffer, 1);
    return received_data;
}

void BME280::write_register(uint8_t register_address, uint8_t data)
{
    write_data(register_address, data);
}

void BME280::write_data(uint8_t register_address, uint8_t data)
{
    spi_.write_data_to_register(chip_select_, register_address, std::span<uint8_t>{&data, 1});
}
