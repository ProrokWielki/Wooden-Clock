/**
 * SPI.cpp
 *
 *  Created on: 04-02-2025
 *  @author: Paweł Warzecha
 */

#include <cassert>
#include <cstdint>
#include <span>

#include <cmsis_bridge/cmsis_bridge.hpp>

#include <HAL/Clock.hpp>
#include <HAL/GPIO.hpp>
#include <HAL/Register.hpp>
#include <HAL/SPI.hpp>
#include <HAL/types.hpp>

SPI::SPI(Clock & clock, SPI_types::SPI_Number spi, GPIO & MOSI, GPIO & MISO, GPIO & SCK, SPI_types::SPIMode mode, SPI_types::SPIDataSize data_size,
         SPI_types::SPIPolarity polarity, SPI_types::SPIPhase phase, SPI_types::SPIForamt format, SPI_types::BaudRatePrescaller baudrate_prescaller)
: CR1(to_address(spi, SPI_types::Register::CR1)), CR2(to_address(spi, SPI_types::Register::CR2)), SR(to_address(spi, SPI_types::Register::SR)),
  DR(to_address(spi, SPI_types::Register::DR)), CRCPR(to_address(spi, SPI_types::Register::CRCPR)), RXCRCR(to_address(spi, SPI_types::Register::RXCRCR)),
  TXCRCR(to_address(spi, SPI_types::Register::TXCRCR))
{
    clock.enable_clock_for(Peripheral::SPI_1);  // TODO:  use to_peripheral

    MISO.set_as_spi_pin(GPIO_Types::AlternateFunction::AF5);  // TODO: Make it generic
    MOSI.set_as_spi_pin(GPIO_Types::AlternateFunction::AF5);
    SCK.set_as_spi_pin(GPIO_Types::AlternateFunction::AF5);

    configure(mode, data_size, polarity, phase, format, baudrate_prescaller);
    enable();
}

void SPI::enable()
{
    constexpr static uint8_t ENABLE_BIT_POSITION{6};
    CR1.set_bit(ENABLE_BIT_POSITION);
}

void SPI::disable()
{
    constexpr static uint8_t ENABLE_BIT_POSITION{6};
    CR1.clear_bit(ENABLE_BIT_POSITION);
}

void SPI::configure(SPI_types::SPIMode mode, SPI_types::SPIDataSize data_size, SPI_types::SPIPolarity polarity, SPI_types::SPIPhase phase,
                    SPI_types::SPIForamt format, SPI_types::BaudRatePrescaller baud_rate_prescaller)
{
    set_mode(mode);
    set_polarity(polarity);
    set_phase(phase);
    set_format(format);
    set_baudrate(baud_rate_prescaller);

    constexpr static uint8_t SSI_BIT_POSITION{8};
    CR1.set_bit(SSI_BIT_POSITION);

    set_data_size(data_size);

    constexpr static uint8_t SS_OUTPUT_ENABLE_BIT_POSITION{2};
    CR2.set_bit(SS_OUTPUT_ENABLE_BIT_POSITION);

    constexpr static uint8_t RX_FIFO_THRESHOLD_BIT_POSITION{12};
    CR2.set_bit(RX_FIFO_THRESHOLD_BIT_POSITION);
}

void SPI::set_mode(SPI_types::SPIMode mode)
{
    constexpr static uint8_t MODE_BIT_POSITION{2};
    CR1.set_bit_value(static_cast<uint8_t>(mode), MODE_BIT_POSITION);
}

void SPI::set_polarity(SPI_types::SPIPolarity polarity)
{
    constexpr static uint8_t POLARITY_BIT_POSITION{1};
    CR1.set_bit_value(static_cast<uint8_t>(polarity), POLARITY_BIT_POSITION);
}

void SPI::set_baudrate(SPI_types::BaudRatePrescaller baud_rate_prescaller)
{
    constexpr static uint8_t BAUDRATE_VALUE_POSITION{3};
    constexpr static uint8_t BAUDRATE_VALUE_LENGTH{3};

    CR1.set_value(to_value(baud_rate_prescaller), BAUDRATE_VALUE_POSITION, BAUDRATE_VALUE_LENGTH);
}

void SPI::set_phase(SPI_types::SPIPhase phase)
{
    constexpr static uint8_t PHASE_BIT_POSITION{0};
    CR1.set_bit_value(static_cast<uint8_t>(phase), PHASE_BIT_POSITION);
}

void SPI::set_format(SPI_types::SPIForamt format)
{
    constexpr static uint8_t FORMAT_BIT_POSITION{7};
    CR1.set_bit_value(static_cast<uint8_t>(format), FORMAT_BIT_POSITION);
}

void SPI::set_data_size(SPI_types::SPIDataSize data_size)
{
    constexpr static uint8_t DATA_SIZE_VALUE_POSITION{8};
    constexpr static uint8_t DATA_SIZE_VALUE_LENGTH{4};

    CR2.set_value(static_cast<uint8_t>(data_size), DATA_SIZE_VALUE_POSITION, DATA_SIZE_VALUE_LENGTH);
}

void SPI::read_data_from_register(GPIO & cs_pin, uint8_t register_address, std::span<uint8_t> & received_data, uint8_t num_of_bytes_to_read)
{
    assert(received_data.size() >= num_of_bytes_to_read && "Buffer too small.");

    while (is_data_received())
    {
        const uint8_t discard = DR.read();
        (void)discard;
    }

    cs_pin.set_output_low();

    while (not is_transmit_finished())
        ;

    while (is_busy())
        ;

    DR.write_u8(register_address);

    while (not is_transfer_finished())
        ;

    uint8_t current_byte{0};

    while (is_data_received())
    {
        const uint8_t discard = DR.read();
        (void)discard;
    }

    while (current_byte < num_of_bytes_to_read)
    {
        DR.write_u8(0);

        while (not is_transfer_finished())
            ;

        while (is_data_received())
        {
            received_data[current_byte++] = DR.read();
        }
    }

    cs_pin.set_output_high();
}

void SPI::write_data_to_register(GPIO & cs_pin, uint8_t register_address, const std::span<uint8_t> & data_to_write)
{

    while (is_data_received())
    {
        const uint8_t discard = DR.read();
        (void)discard;
    }

    cs_pin.set_output_low();

    while (not is_transmit_finished())
        ;

    while (is_busy())
        ;

    DR.write(register_address);

    while (not is_transmit_finished())
        ;

    while (is_busy())
        ;

    uint8_t current_byte{0};
    while (current_byte < data_to_write.size())
    {
        while (is_busy())
            ;
        while (not is_transmit_finished())
            ;

        DR.write(data_to_write[current_byte++]);

        while (is_data_received())
        {
            const uint8_t discard = DR.read();
            (void)discard;
        }
    }

    // disable();

    cs_pin.set_output_high();
}

bool SPI::is_transfer_finished() const
{
    const bool all_data_transmitted = is_transmit_finished();
    const bool data_received = is_data_received();
    const bool spi_busy = is_busy();

    return all_data_transmitted && data_received && not spi_busy;
}

bool SPI::is_data_received() const
{
    constexpr static uint8_t RX_NOT_EMPTY_BIT_POSITION{0};
    return SR.get_bit(RX_NOT_EMPTY_BIT_POSITION);
}

bool SPI::is_busy() const
{
    constexpr static uint8_t SPI_BUSY_BIT_POSITION{7};
    return SR.get_bit(SPI_BUSY_BIT_POSITION);
}

bool SPI::is_transmit_finished() const
{
    constexpr static uint8_t TX_EMPTY_BIT_POSITION{1};
    return SR.get_bit(TX_EMPTY_BIT_POSITION);
}