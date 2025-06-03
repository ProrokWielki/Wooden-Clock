/**
 * SPI.hpp
 *
 *  Created on: 28-04-2019
 *  @author: Paweł Warzecha
 */

#ifndef HAL_SPI_SPI_HPP_
#define HAL_SPI_SPI_HPP_

#include <cstdint>
#include <span>

#include <HAL/Register.hpp>
#include <HAL/types.hpp>

class Clock;
class GPIO;

class SPI
{
public:
    SPI(Clock & clock, SPI_types::SPI_Number spi, GPIO & MOSI, GPIO & MISO, GPIO & SCK, SPI_types::SPIMode mode, SPI_types::SPIDataSize data_size,
        SPI_types::SPIPolarity polarity, SPI_types::SPIPhase phase, SPI_types::SPIForamt format,SPI_types::BaudRatePrescaller baudrate_prescaller);

    void enable();

    void disable();

    void configure(SPI_types::SPIMode mode, SPI_types::SPIDataSize data_size, SPI_types::SPIPolarity polarity, SPI_types::SPIPhase phase,
                   SPI_types::SPIForamt format, SPI_types::BaudRatePrescaller baud_rate_prescaller);

    void set_mode(SPI_types::SPIMode mode);

    void set_polarity(SPI_types::SPIPolarity polarity);

    void set_phase(SPI_types::SPIPhase phase);

    void set_format(SPI_types::SPIForamt format);

    void set_data_size(SPI_types::SPIDataSize data_size);

    void set_baudrate(SPI_types::BaudRatePrescaller baud_rate_prescaller);

    // uint8_t exchange_data(uint8_t value_to_send);

    void read_data_from_register(GPIO & cs_pin, uint8_t register_address, std::span<uint8_t> & received_data, uint8_t num_of_bytes_to_read);
    void write_data_to_register(GPIO & cs_pin, uint8_t register_address, const std::span<uint8_t> & data_to_write);

private:
    Register<uint32_t> CR1;
    Register<uint32_t> CR2;
    Register<uint32_t> SR;
    Register<uint32_t> DR;
    Register<uint32_t> CRCPR;
    Register<uint32_t> RXCRCR;
    Register<uint32_t> TXCRCR;

    [[nodiscard]] bool is_transfer_finished() const;

    [[nodiscard]] bool is_busy() const;
    [[nodiscard]] bool is_data_received() const;
    [[nodiscard]] bool is_transmit_finished() const;
};

#endif /* HAL_SPI_SPI_HPP_ */
