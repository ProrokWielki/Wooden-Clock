/**
 * @file BME280.cpp
 * @author Paweł Warzecha
 * @date 2025-02-06
 */

#include "include/DRV/BME280.hpp"
#include <cstdint>

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

float BME280::get_humidity()
{

    constexpr uint8_t HUMIDITY_MSB_REGISTER_ADDRESS{0xFD};
    constexpr uint8_t HUMIDITY_LSB_REGISTER_ADDRESS{0xFE};

    auto hum_lsb = read_16_bits_register_as<int32_t>(HUMIDITY_MSB_REGISTER_ADDRESS, HUMIDITY_LSB_REGISTER_ADDRESS);

    return convert_to_RH(hum_lsb);
}

float BME280::get_temperature()
{

    return ((get_t_fine() * 5 + 128) >> 8) / 100.0;
}

float BME280::get_pressure()
{
    constexpr uint8_t RAW_PRESSURE_MSB_REGISTER_ADDRESS{0xF7};
    constexpr uint8_t RAW_PRESSURE_LSB_REGISTER_ADDRESS{0xF8};
    constexpr uint8_t RAW_PRESSURE_XLSB_REGISTER_ADDRESS{0xF9};

    const auto pressure =
    read_20_bits_register_as<int32_t>(RAW_PRESSURE_MSB_REGISTER_ADDRESS, RAW_PRESSURE_LSB_REGISTER_ADDRESS, RAW_PRESSURE_XLSB_REGISTER_ADDRESS);

    return convert_to_Pa(pressure);
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

float BME280::convert_to_RH(int32_t register_value)
{
    int32_t v_x1_u32r{};
    v_x1_u32r = (get_t_fine() - (static_cast<int32_t>(76800)));
    v_x1_u32r =
    (((((register_value << 14) - ((static_cast<int32_t>(calibration_data.dig_H4)) << 20) - ((static_cast<int32_t>(calibration_data.dig_H5)) * v_x1_u32r)) +
       (static_cast<int32_t>(16384))) >>
      15) *
     (((((((v_x1_u32r * (static_cast<int32_t>(calibration_data.dig_H6))) >> 10) *
          (((v_x1_u32r * (static_cast<int32_t>(calibration_data.dig_H3))) >> 11) + (static_cast<int32_t>(32768)))) >>
         10) +
        (static_cast<int32_t>(2097152))) *
       (static_cast<int32_t>(calibration_data.dig_H2)) +
       8192) >>
      14));

    v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * (static_cast<int32_t>(calibration_data.dig_H1))) >> 4));
    v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
    v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
    return static_cast<uint32_t>(v_x1_u32r >> 12) / 1024.0;
}

int32_t BME280::get_raw_temperature()
{
    constexpr uint8_t RAW_TEMPERATURE_MSB_REGISTER_ADDRESS{0xFA};
    constexpr uint8_t RAW_TEMPERATURE_LSB_REGISTER_ADDRESS{0xFB};
    constexpr uint8_t RAW_TEMPERATURE_XLSB_REGISTER_ADDRESS{0xFC};

    const auto temperature =
    read_20_bits_register_as<int32_t>(RAW_TEMPERATURE_MSB_REGISTER_ADDRESS, RAW_TEMPERATURE_LSB_REGISTER_ADDRESS, RAW_TEMPERATURE_XLSB_REGISTER_ADDRESS);

    return temperature;
}

float BME280::convert_to_Pa(int32_t raw_pressure)
{
    int64_t var1{}, var2{}, p{};
    var1 = get_t_fine() - 128000;
    var2 = var1 * var1 * static_cast<int64_t>(calibration_data.dig_P6);
    var2 = var2 + ((var1 * static_cast<int64_t>(calibration_data.dig_P5)) << 17);
    var2 = var2 + (static_cast<int64_t>(calibration_data.dig_P4) << 35);
    var1 = ((var1 * var1 * static_cast<int64_t>(calibration_data.dig_P3)) >> 8) + ((var1 * static_cast<int64_t>(calibration_data.dig_P2)) << 12);
    var1 = ((((static_cast<int64_t>(1)) << 47) + var1)) * static_cast<int64_t>(calibration_data.dig_P1) >> 33;
    if (var1 == 0)
    {
        return 0;  // avoid exception caused by division by zero
    }
    p = 1048576 - raw_pressure;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = ((static_cast<int64_t>(calibration_data.dig_P9)) * (p >> 13) * (p >> 13)) >> 25;
    var2 = ((static_cast<int64_t>(calibration_data.dig_P8)) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + ((static_cast<int64_t>(calibration_data.dig_P7)) << 4);
    return p / 256.0;
}

int32_t BME280::get_t_fine()
{
    const int32_t raw_temperature = get_raw_temperature();

    auto var1 = ((((raw_temperature >> 3) - (static_cast<int32_t>(calibration_data.dig_T1) << 1))) * (static_cast<int32_t>(calibration_data.dig_T2))) >> 11;
    auto var2 =
    (((((raw_temperature >> 4) - static_cast<int32_t>(calibration_data.dig_T1)) * ((raw_temperature >> 4) - static_cast<int32_t>(calibration_data.dig_T1))) >>
      12) *
     (static_cast<int32_t>(calibration_data.dig_T3))) >>
    14;
    return var1 + var2;
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
    spi_.read_data_from_register(chip_select_, 0x80 | register_address, received_data_buffer, 1);
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
