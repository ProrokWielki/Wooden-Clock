/**
 *  @file I2C.hpp
 *
 *  @brief Wrapper for the I2Cs.
 *
 *  Created on: 02-02-2025
 *  @author: Paweł Warzecha
 */

#include <cassert>
#include <cmath>
#include <cstdint>
#include <limits>
#include <span>

#include <stm32l4xx.h>

#include <HAL/DMA.hpp>
#include <HAL/Register.hpp>
#include <cmsis_bridge/cmsis_bridge.hpp>

#include "HAL/types.hpp"
#include <HAL/Clock.hpp>
#include <HAL/GPIO.hpp>
#include <HAL/I2C.hpp>

namespace
{
constexpr static uint8_t DIGITAL_FILTER_FIELD_BIT_LENGTH{4};
constexpr static uint8_t TRANSFER_SIZE_FIELD_BIT_LENGTH{8};
constexpr static uint8_t DATA_FIELD_BIT_LENGTH{8};
constexpr static uint8_t PRESCALER_FIELD_BIT_LENGTH{4};
constexpr static uint8_t DATA_SETUP_FIELD_BIT_LENGTH{4};
constexpr static uint8_t DATA_HOLD_FIELD_BIT_LENGTH{4};
constexpr static uint8_t SCL_HIGH_FIELD_BIT_LENGTH{8};
constexpr static uint8_t SCL_LOW_FIELD_BIT_LENGTH{8};
constexpr static uint8_t DIRECTION_BIT_LENGTH{1};

constexpr static uint8_t REGISTER_OFFSET_7BIT_ADDRESS{1};
constexpr static uint8_t REGISTER_OFFSET_10BIT_ADDRESS{0};
constexpr static uint8_t REGISTER_OFFSET_DIRECTION_ADDRESS{10};
}  // namespace

using namespace I2C_Types;

I2C::I2C(Clock & clock, I2C_Types::I2CNumber i2c, GPIO & scl, GPIO & sda, double frequency, DMA * dma)
: CR1(to_address(i2c, I2C_Types::Register::CR1)), CR2(to_address(i2c, I2C_Types::Register::CR2)), ICR(to_address(i2c, I2C_Types::Register::ICR)),
  ISR(to_address(i2c, I2C_Types::Register::ISR)), OAR1(to_address(i2c, I2C_Types::Register::OAR1)), OAR2(to_address(i2c, I2C_Types::Register::OAR2)),
  PECR(to_address(i2c, I2C_Types::Register::PECR)), RXDR(to_address(i2c, I2C_Types::Register::RXDR)), TIMEOUTR(to_address(i2c, I2C_Types::Register::TIMEOUTR)),
  TIMINGR(to_address(i2c, I2C_Types::Register::TIMINGR)), TXDR(to_address(i2c, I2C_Types::Register::TXDR)), dma_(dma)
{
    clock.enable_clock_for(to_peripheral(i2c));
    clock.set_clock_source_for(to_peripheral_with_clock_select(i2c), ClockSource::SYSTEM_CLOCK);

    if (i2c != I2C_Types::I2CNumber::I2C_4)
    {
        scl.set_as_I2C_pin(GPIO_Types::AlternateFunction::AF4);
        sda.set_as_I2C_pin(GPIO_Types::AlternateFunction::AF4);  // make it generic
    }
    else
    {
        scl.set_as_I2C_pin(GPIO_Types::AlternateFunction::AF5);
        sda.set_as_I2C_pin(GPIO_Types::AlternateFunction::AF5);  // make it generic
    }
    set_frequency(frequency);

    enable();
}

void I2C::enable()
{
    CR1.set_bit(I2C_CR1_PE_Pos);
}

void I2C::disable()
{
    CR1.clear_bit(I2C_CR1_PE_Pos);
}

void I2C::enable_interrupt(Interrupt interrupt)
{
    CR1.set_bit(to_bit_position(interrupt));
}

void I2C::disable_interrupt(Interrupt interrupt)
{
    CR1.clear_bit(to_bit_position(interrupt));
}

void I2C::set_digital_filter(DigitalFilter digital_filter)
{
    CR1.set_value(to_value(digital_filter), I2C_CR1_DNF_Pos, DIGITAL_FILTER_FIELD_BIT_LENGTH);
}

void I2C::enable_analog_filter()
{
    CR1.set_bit(I2C_CR1_ANFOFF_Pos);
}

void I2C::disable_analog_filter()
{
    CR1.clear_bit(I2C_CR1_ANFOFF_Pos);
}

void I2C::enable_DMA_request(DMARequest dma_request)
{
    CR1.set_bit(to_bit_position(dma_request));
}

void I2C::disable_DMA_request(DMARequest dma_request)
{
    CR1.clear_bit(to_bit_position(dma_request));
}

void I2C::set_slave_address(uint16_t slave_address, AddressLength address_length)
{
    if (address_length == AddressLength::bits7)
    {
        constexpr static uint8_t I2C_7_BIT_ADDRESS_VALUE_LENGTH{10};

        CR2.set_value(slave_address, REGISTER_OFFSET_7BIT_ADDRESS, I2C_7_BIT_ADDRESS_VALUE_LENGTH);
        CR2.clear_bit(I2C_CR2_ADD10_Pos);
    }
    else
    {
        constexpr static uint8_t I2C_10_BIT_ADDRESS_VALUE_LENGTH{10};

        CR2.set_value(slave_address, REGISTER_OFFSET_10BIT_ADDRESS, I2C_10_BIT_ADDRESS_VALUE_LENGTH);
        CR2.set_bit(I2C_CR2_ADD10_Pos);
    }
}

void I2C::write_data(std::span<uint8_t> data)
{
    uint8_t u8TransferSize{};
    size_t bytes_to_send{data.size()};
    size_t current_byte{0};

    set_transfer_direction(I2C_Types::TransferDirection::WRITE);

    while (bytes_to_send > 0)
    {
        if (bytes_to_send > std::numeric_limits<uint8_t>::max())
        {
            u8TransferSize = std::numeric_limits<uint8_t>::max();
            enable_option(Option::Reload);
        }
        else
        {
            u8TransferSize = bytes_to_send;
            disable_option(Option::Reload);
        }

        bytes_to_send -= u8TransferSize;

        set_transfer_size(u8TransferSize);
        enable_option(Option::AutoEnd);

        start_transfer();

        while (u8TransferSize-- > 0)
        {
            set_data_to_be_send(data[current_byte++]);
            while (false == is_transfer_completed())
                ;
        }
    }
}

void I2C::write_data_DMA(uint8_t * data, uint16_t numberOfBytes)
{
    dma_->enable_memory_increment();
    dma_->set_memory_address(reinterpret_cast<uint32_t>(data));  // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
    dma_->set_peripheral_address(TXDR.get_address());
    dma_->set_read_direction(DMA_Types::ReadDirection::ReadFromMemory);
    dma_->set_memory_size(DMA_Types::DataSize::Bits8);
    dma_->set_peripheral_size(DMA_Types::DataSize::Bits8);
    dma_->set_transfer_size(numberOfBytes);

    set_transfer_size(numberOfBytes);
    start_transfer();

    enable_DMA_request(DMARequest::Transmit);
    dma_->enable();
}

void I2C::set_transfer_direction(TransferDirection direction)
{
    CR2.set_value(to_value(direction), REGISTER_OFFSET_DIRECTION_ADDRESS, DIRECTION_BIT_LENGTH);
}

void I2C::read_data(std::span<uint8_t> & received_data, uint16_t num_of_bytes_to_read)
{
    assert(received_data.size() >= num_of_bytes_to_read && "Received data won't fit into the buffer");

    uint8_t u8TransferSize{};
    size_t bytes_to_read{num_of_bytes_to_read};
    size_t current_byte{0};

    set_transfer_direction(I2C_Types::TransferDirection::READ);

    while (bytes_to_read > 0)
    {
        if (bytes_to_read > std::numeric_limits<uint8_t>::max())
        {
            u8TransferSize = std::numeric_limits<uint8_t>::max();
            enable_option(Option::Reload);
        }
        else
        {
            u8TransferSize = bytes_to_read;
            disable_option(Option::Reload);
        }

        bytes_to_read -= u8TransferSize;

        set_transfer_size(u8TransferSize);
        enable_option(Option::AutoEnd);

        start_transfer();

        while (u8TransferSize-- > 0)
        {
            while (false == is_data_received())
                ;
            received_data[current_byte++] = RXDR.get_value(0, std::numeric_limits<uint8_t>::digits);
        }
    }
}

void I2C::read_data_from_register(uint8_t register_address, std::span<uint8_t> & received_data, uint16_t num_of_bytes_to_read)
{
    write_data({&register_address, 1});
    read_data(received_data, num_of_bytes_to_read);
}

void I2C::set_timing(uint8_t u8Prescaler, uint8_t u8DataSetup, uint8_t u8DataHold, uint8_t u8SCLHigh, uint8_t u8SCLLow)
{
    TIMINGR.set_value(u8Prescaler, I2C_TIMINGR_PRESC_Pos, PRESCALER_FIELD_BIT_LENGTH);
    TIMINGR.set_value(u8DataSetup, I2C_TIMINGR_SCLDEL_Pos, DATA_SETUP_FIELD_BIT_LENGTH);
    TIMINGR.set_value(u8DataHold, I2C_TIMINGR_SDADEL_Pos, DATA_HOLD_FIELD_BIT_LENGTH);
    TIMINGR.set_value(u8SCLHigh, I2C_TIMINGR_SCLH_Pos, SCL_HIGH_FIELD_BIT_LENGTH);
    TIMINGR.set_value(u8SCLLow, I2C_TIMINGR_SCLL_Pos, SCL_LOW_FIELD_BIT_LENGTH);
}

DMA * I2C::get_DMA()
{
    return dma_;
}

bool I2C::is_transfer_completed()
{
    return ISR.get_bit(I2C_ISR_TXE_Pos) == 1;
}

bool I2C::is_data_received()
{
    return ISR.get_bit(I2C_ISR_RXNE_Pos) == 1;
}

void I2C::set_transfer_size(uint8_t u8TransferSize)
{
    CR2.set_value(u8TransferSize, I2C_CR2_NBYTES_Pos, TRANSFER_SIZE_FIELD_BIT_LENGTH);
}

void I2C::set_data_to_be_send(uint8_t u8DataToSend)
{
    TXDR.set_value(u8DataToSend, I2C_TXDR_TXDATA_Pos, DATA_FIELD_BIT_LENGTH);
}

void I2C::enable_option(Option option)
{
    CR2.set_bit(to_bit_position(option));
}
void I2C::disable_option(Option option)
{
    CR2.clear_bit(to_bit_position(option));
}

void I2C::start_transfer()
{
    CR2.set_bit(I2C_CR2_START_Pos);
}
void I2C::stop_transfer()
{
    CR2.set_bit(I2C_CR2_STOP_Pos);
}

void I2C::set_frequency(double frequency)
{

    constexpr uint8_t max_prescaler = 16;
    constexpr uint8_t max_num_of_ticks = 255;

    const double scl_low_period = 1.f / frequency / 2.f;
    const double clock_period = 1.f / 80'000'000.f;  // clock_frequency

    uint8_t found_prescaller = std::numeric_limits<uint8_t>::max();
    uint8_t found_num_of_ticks = std::numeric_limits<uint8_t>::max();
    double error = std::numeric_limits<double>::max();

    for (uint8_t prescaller{1}; prescaller <= max_prescaler; ++prescaller)
    {
        const double prescaled_clock_low_period = clock_period * prescaller;
        const double num_of_ticks = int(scl_low_period / prescaled_clock_low_period);

        if (num_of_ticks <= max_num_of_ticks and num_of_ticks > 0)
        {
            const double current_error = std::abs((prescaled_clock_low_period * int(num_of_ticks)) - scl_low_period);

            if (current_error < error)
            {
                error = current_error;
                found_prescaller = prescaller;
                found_num_of_ticks = int(num_of_ticks);
            }
        }
    }
    set_timing(found_prescaller - 1, 2, 2, found_num_of_ticks - 1, found_num_of_ticks - 1);
}