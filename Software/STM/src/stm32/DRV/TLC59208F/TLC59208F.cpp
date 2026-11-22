/**
 * TLC59208F.cpp
 *
 *  Created on: 23-02-2025
 *  @author: Paweł Warzecha
 */

#include <array>
#include <cstring>

#include <HAL/DMA.hpp>

#include "HAL/types.hpp"
#include "include/DRV/TLC59208F.hpp"

using namespace GPIO_Types;
;

TLC59208F::TLC59208F(I2C & i2c, const uint8_t deviceAddress, GPIO & resetPin)
: i2c_(i2c), deviceAddress_(deviceAddress), resetPin_(resetPin), ledValues_{0x82}, cashedLedValues_{0x82}
{
}

void TLC59208F::init()
{
    resetPin_.set_mode(PortMode::Output);
    resetPin_.set_speed(PortOutputSpeed::VeryHigh);

    resetPin_.set_output_low();
    i2c_.set_slave_address(deviceAddress_ >> 1, I2C_Types::AddressLength::bits7);
    resetPin_.set_output_high();
}

void TLC59208F::set_register_value(uint8_t registerAddress, uint8_t valueToBeSet)
{
    std::array<uint8_t, 2> dataToBeSend{};

    dataToBeSend[0] = registerAddress;
    dataToBeSend[1] = valueToBeSet;

    i2c_.write_data(dataToBeSend);
}

void TLC59208F::set_registers_values(const uint8_t registerStartAddress, const std::span<const uint8_t> data_to_send)
{
    std::array<uint8_t, 16> dataToBeSend{};

    constexpr uint8_t WRITE_BIT(0x80);
    dataToBeSend[0] = registerStartAddress | WRITE_BIT;
    memcpy(&(dataToBeSend[1]), data_to_send.data(), data_to_send.size() * sizeof(uint8_t));

    const std::span<const uint8_t> data_to_send_span{dataToBeSend.data(), data_to_send.size() + 1};

    i2c_.write_data(data_to_send_span);
}

void TLC59208F::set_all_leds_values(const std::array<const uint8_t, NUM_OF_LEDS> & allLedsValues)
{
    // ledValues_[0] is the register address, it should stay unchanged.
    memcpy(&(ledValues_[1]), allLedsValues.data(), allLedsValues.size() * sizeof(uint8_t));

    i2c_.write_data_dma(ledValues_);
}

void TLC59208F::cache_all_leds_values(std::span<uint8_t> allLedsValues)
{
    memcpy(&(cashedLedValues_[1]), allLedsValues.data(), NUM_OF_LEDS * sizeof(uint8_t));
}

void TLC59208F::send_cashed_leds_values()
{
    i2c_.write_data_dma(cashedLedValues_);
}

void TLC59208F::set_transfer_complete_callback(std::function<void()> callback)
{
    i2c_.get_dma()->set_transfer_complete_callback(std::move(callback));
    i2c_.get_dma()->enable_interrupt(DMA_Types::Interrupt::TransferCompleted);
}

void TLC59208F::set_stop_callback(std::function<void()> callback)
{
    i2c_.set_stop_callback(std::move(callback));
    i2c_.enable_interrupt(I2C_Types::Interrupt::STOPDetectedInterrupt);
}

void TLC59208F::set_half_transfer_callback(std::function<void()> callback)
{
    i2c_.get_dma()->set_half_transfer_callback(std::move(callback));
    i2c_.get_dma()->enable_interrupt(DMA_Types::Interrupt::HalfTransfer);
}

void TLC59208F::disable_low_power_mode()
{
    std::array<uint8_t, 1> read_buffer{};

    constexpr uint8_t MODE1_REGISTER_ADDRESS{0};
    auto read_value = i2c_.read_data_from_register(MODE1_REGISTER_ADDRESS, read_buffer);
    Register<uint8_t> MODE_1{std::move(read_value[0])};

    constexpr uint8_t SLEEP_MODE_BIT_POSITION{4};
    MODE_1.clear_bit(SLEEP_MODE_BIT_POSITION);

    std::array<uint8_t, 1> write_buffer{MODE_1.read()};
    set_registers_values(MODE1_REGISTER_ADDRESS, write_buffer);
}

void TLC59208F::enable_led_drivers()
{
    constexpr uint8_t LEDOUT0_REGISTER_ADDRESS{0x0C};

    uint8_t ledout0_val{0};
    uint8_t ledout1_val{0};

    Register<uint8_t> LEDOUT0{std::move(ledout0_val)};
    Register<uint8_t> LEDOUT1{std::move(ledout1_val)};

    constexpr uint8_t NUM_OF_LEDS_IN_SINGLE_REGISTER{4};
    for (uint8_t current_led{0}; current_led < NUM_OF_LEDS_IN_SINGLE_REGISTER; ++current_led)
    {
        constexpr uint8_t LED_DRIVER_ON_VALUE{2};
        constexpr uint8_t LED_DRIVER_ON_POSITION{0};
        constexpr uint8_t LED_DRIVER_ON_LENGTH{2};

        LEDOUT0.set_value(LED_DRIVER_ON_VALUE, LED_DRIVER_ON_POSITION + (LED_DRIVER_ON_LENGTH * current_led), LED_DRIVER_ON_LENGTH);
        LEDOUT1.set_value(LED_DRIVER_ON_VALUE, LED_DRIVER_ON_POSITION + (LED_DRIVER_ON_LENGTH * current_led), LED_DRIVER_ON_LENGTH);
    }

    std::array<uint8_t, 2> write_buffer{LEDOUT0.read(), LEDOUT1.read()};
    set_registers_values(LEDOUT0_REGISTER_ADDRESS, write_buffer);
}