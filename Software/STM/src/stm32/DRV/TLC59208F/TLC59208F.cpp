/**
 * TLC59208F.cpp
 *
 *  Created on: 23-02-2025
 *  @author: Paweł Warzecha
 */

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
    uint8_t dataToBeSend[2];

    dataToBeSend[0] = registerAddress;
    dataToBeSend[1] = valueToBeSet;

    i2c_.write_data({dataToBeSend, 2});
}

void TLC59208F::set_registers_values(const uint8_t registerStartAddress, uint8_t const * const valuesToBeSet, const uint8_t numberOfValues)
{

    uint8_t dataToBeSend[16];

    dataToBeSend[0] = registerStartAddress | 0x80;
    memcpy(&(dataToBeSend[1]), valuesToBeSet, (numberOfValues + 1) * sizeof(uint8_t));

    i2c_.write_data({dataToBeSend, numberOfValues + 1U});
}

void TLC59208F::set_all_leds_values(uint8_t const * const allLedsValues)
{
    memcpy(&(ledValues_[1]), allLedsValues, 8 * sizeof(uint8_t));

    i2c_.write_data_DMA(ledValues_, 9);
}

void TLC59208F::cashe_all_leds_values(uint8_t const * const allLedsValues)
{
    memcpy(&(cashedLedValues_[1]), allLedsValues, 8 * sizeof(uint8_t));
}

void TLC59208F::send_cashed_leds_values()
{
    i2c_.write_data_DMA(cashedLedValues_, 9);
}

void TLC59208F::set_transfer_complete_callback(std::function<void()> callback)
{
    i2c_.get_DMA()->set_transfer_complete_callback(std::move(callback));
    i2c_.get_DMA()->enable_interrupt(DMA_Types::Interrupt::TransferCompleted);
}

void TLC59208F::set_half_transfer_callback(std::function<void()> callback)
{
    i2c_.get_DMA()->set_half_transfer_callback(std::move(callback));
    i2c_.get_DMA()->enable_interrupt(DMA_Types::Interrupt::HalfTransfer);
}
