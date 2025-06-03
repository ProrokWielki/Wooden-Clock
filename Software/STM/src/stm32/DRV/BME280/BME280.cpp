/**
 * @file BME280.cpp
 * @author Paweł Warzecha
 * @date 2025-02-06
 */

#include "include/DRV/BME280.hpp"

BME280::BME280(SPI & spi, GPIO & chip_select) : spi_(spi), chip_select_(chip_select)
{
}

void BME280::init()
{
    chip_select_.set_output_high();

    get_calibration_data();

    write_register(0x72, 0xff);
    write_register(0x74, 0xff);
}

uint8_t BME280::get_id()
{

    return read_register(0xD0);
    ;
}

float BME280::get_humidity()
{

    uint8_t hum_lsb = read_register(0xFE);
    uint8_t hum_msb = read_register(0xFD);

    int32_t value = static_cast<int32_t>(hum_lsb);
    value |= static_cast<int32_t>(hum_msb) << 8;

    return convert_to_RH(value);
}

float BME280::get_temperature()
{

    return ((get_t_fine() * 5 + 128) >> 8) / 100.0;
}

float BME280::get_pressure()
{
    const uint8_t press_lsb = read_register(0xF8);
    const uint8_t press_msb = read_register(0xF7);
    const uint8_t press_xlsb = read_register(0xF9);

    int32_t value = static_cast<int32_t>(press_lsb) << 4;
    value |= static_cast<int32_t>(press_msb) << 12;
    value |= static_cast<int32_t>(press_xlsb) >> 4;

    return convert_to_Pa(value);
}

void BME280::get_calibration_data()
{
    calibration_data.dig_T1 = static_cast<uint16_t>(read_register(0x88)) | static_cast<uint16_t>(read_register(0x89)) << 8;
    calibration_data.dig_T2 = static_cast<int16_t>(read_register(0x8A)) | static_cast<int16_t>(read_register(0x8B)) << 8;
    calibration_data.dig_T3 = static_cast<int16_t>(read_register(0x8C)) | static_cast<int16_t>(read_register(0x8D)) << 8;
    calibration_data.dig_P1 = static_cast<uint16_t>(read_register(0x8E)) | static_cast<uint16_t>(read_register(0x8F)) << 8;
    calibration_data.dig_P2 = static_cast<int16_t>(read_register(0x90)) | static_cast<int16_t>(read_register(0x91)) << 8;
    calibration_data.dig_P3 = static_cast<int16_t>(read_register(0x92)) | static_cast<int16_t>(read_register(0x93)) << 8;
    calibration_data.dig_P4 = static_cast<int16_t>(read_register(0x94)) | static_cast<int16_t>(read_register(0x95)) << 8;
    calibration_data.dig_P5 = static_cast<int16_t>(read_register(0x96)) | static_cast<int16_t>(read_register(0x97)) << 8;
    calibration_data.dig_P6 = static_cast<int16_t>(read_register(0x98)) | static_cast<int16_t>(read_register(0x99)) << 8;
    calibration_data.dig_P7 = static_cast<int16_t>(read_register(0x9A)) | static_cast<int16_t>(read_register(0x9B)) << 8;
    calibration_data.dig_P8 = static_cast<int16_t>(read_register(0x9C)) | static_cast<int16_t>(read_register(0x9D)) << 8;
    calibration_data.dig_P9 = static_cast<int16_t>(read_register(0x9E)) | static_cast<int16_t>(read_register(0x9F)) << 8;
    calibration_data.dig_H1 = static_cast<uint8_t>(read_register(0xA1));
    calibration_data.dig_H2 = static_cast<int16_t>(read_register(0xE1)) | static_cast<int16_t>(read_register(0xE2)) << 8;
    calibration_data.dig_H3 = static_cast<uint8_t>(read_register(0xE3));
    calibration_data.dig_H4 = static_cast<int16_t>(read_register(0xE4)) << 4 | (static_cast<int16_t>(read_register(0xE5)) & 0x0F);
    calibration_data.dig_H5 = (static_cast<int16_t>(read_register(0xE5)) & 0x0F) | (static_cast<int16_t>(read_register(0xE6)) << 4);
    calibration_data.dig_H3 = static_cast<int8_t>(read_register(0xE7));
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

    const uint8_t hum_lsb = read_register(0xFB);
    const uint8_t hum_msb = read_register(0xFA);
    const uint8_t hum_xlsb = read_register(0xFC);

    int32_t value = static_cast<int32_t>(hum_lsb) << 4;
    value |= static_cast<int32_t>(hum_msb) << 12;
    value |= static_cast<int32_t>(hum_xlsb) >> 4;

    return value;
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
    int32_t raw_temperature = get_raw_temperature();

    auto var1 = ((((raw_temperature >> 3) - (static_cast<int32_t>(calibration_data.dig_T1) << 1))) * (static_cast<int32_t>(calibration_data.dig_T2))) >> 11;
    auto var2 =
    (((((raw_temperature >> 4) - static_cast<int32_t>(calibration_data.dig_T1)) * ((raw_temperature >> 4) - static_cast<int32_t>(calibration_data.dig_T1))) >>
      12) *
     (static_cast<int32_t>(calibration_data.dig_T3))) >>
    14;
    return var1 + var2;
}

uint8_t BME280::read_register(uint8_t register_address)
{
    return read_data(static_cast<uint8_t>(register_address));
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
    write_data(static_cast<uint8_t>(register_address), data);
}

void BME280::write_data(uint8_t register_address, uint8_t data)
{
    spi_.write_data_to_register(chip_select_, register_address, std::span<uint8_t>{&data, 1});
}
