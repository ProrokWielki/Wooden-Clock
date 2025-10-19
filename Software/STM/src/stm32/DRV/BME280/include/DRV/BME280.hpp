/**
 * @file BME280.hpp
 * @author Paweł Warzecha
 * @date 2025-02-06
 */
#ifndef DRV_BME280_BME280_HPP_
#define DRV_BME280_BME280_HPP_

#include <HAL/GPIO.hpp>
#include <HAL/SPI.hpp>

class BME280
{
public:
    BME280(SPI & spi, GPIO & chip_select);

    void init();

    uint8_t get_id();

    double get_humidity();
    double get_temperature();
    double get_pressure();

private:
    struct CalibrationData {
        uint16_t dig_T1;
        int16_t dig_T2;
        int16_t dig_T3;
        uint16_t dig_P1;
        int16_t dig_P2;
        int16_t dig_P3;
        int16_t dig_P4;
        int16_t dig_P5;
        int16_t dig_P6;
        int16_t dig_P7;
        int16_t dig_P8;
        int16_t dig_P9;
        uint8_t dig_H1;
        int16_t dig_H2;
        uint8_t dig_H3;
        int16_t dig_H4;
        int16_t dig_H5;
        int8_t dig_H6;
    };

    void get_calibration_data();

    uint32_t get_raw_humidity();
    uint32_t get_raw_temperature();
    uint32_t get_raw_pressure();

    uint8_t read_8_bits_register(uint8_t register_address);
    uint16_t read_16_bits_register(uint8_t msb_register_address, uint8_t lsb_register_address);
    uint32_t read_20_bits_register(uint8_t msb_register_address, uint8_t lsb_register_address, uint8_t xlsb_register_address);

    template<typename T>
    T read_8_bits_register_as(uint8_t register_address)
    {
        static_assert(sizeof(T) >= sizeof(uint8_t), "Wrong size.");
        return static_cast<T>(read_8_bits_register(register_address));
    }

    template<typename T>
    T read_16_bits_register_as(uint8_t msb_register_address, uint8_t lsb_register_address)
    {
        static_assert(sizeof(T) >= sizeof(uint16_t), "Wrong size.");
        return static_cast<T>(read_16_bits_register(msb_register_address, lsb_register_address));
    }

    template<typename T>
    T read_20_bits_register_as(uint8_t msb_register_address, uint8_t lsb_register_address, uint8_t xlsb_register_address)
    {
        static_assert(sizeof(T) >= sizeof(uint32_t), "Wrong size.");
        return static_cast<T>(read_20_bits_register(msb_register_address, lsb_register_address, xlsb_register_address));
    }

    uint8_t read_data(uint8_t register_address);

    void write_register(uint8_t register_address, uint8_t data);

    void write_data(uint8_t register_address, uint8_t data);

    SPI & spi_;
    GPIO & chip_select_;
    CalibrationData calibration_data{};
};

#endif /* DRV_BME280_BME280_HPP_ */
