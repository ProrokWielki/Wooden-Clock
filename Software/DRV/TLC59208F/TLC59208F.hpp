/**
 * TLC59208F.hpp
 *
 *  Created on: 27-02-2019
 *  @author: Paweł Warzecha
 */

#ifndef DRV_TLC59208F_TLC59208F_HPP_
#define DRV_TLC59208F_TLC59208F_HPP_

#include <stdint.h>
#include <string.h>

#include "HAL.hpp"

class TLC59208F
{
public:
    TLC59208F(I2C & i2c, const uint8_t deviceAddress, GPIO & resetPin)
    : i2c_(i2c), deviceAddress_(deviceAddress), resetPin_(resetPin), ledValues_{0x82}, cashedLedValues_{0x82}
    {
    }

    void init()
    {
        resetPin_.set_mode(eOutput);
        resetPin_.set_speed(eVeryHighSpeed);

        resetPin_.set_output_low();
        i2c_.set_slave_address(deviceAddress_ >> 1, e7bitAddress);
        resetPin_.set_output_high();
    }

    void set_register_value(uint8_t registerAddress, uint8_t valueToBeSet)
    {
        uint8_t dataToBeSend[2];

        dataToBeSend[0] = registerAddress;
        dataToBeSend[1] = valueToBeSet;

        i2c_.write_data(dataToBeSend, 2);
    }

    void set_registers_values(const uint8_t registerStartAddress, const uint8_t * const valuesToBeSet, const uint8_t numberOfValues)
    {

        uint8_t dataToBeSend[16];

        dataToBeSend[0] = registerStartAddress | 0x80;
        memcpy(&(dataToBeSend[1]), valuesToBeSet, (numberOfValues + 1) * sizeof(uint8_t));

        i2c_.write_data(dataToBeSend, numberOfValues + 1);
    }

    void set_all_leds_values(uint8_t * allLedsValues)
    {
        memcpy(&(ledValues_[1]), allLedsValues, 8 * sizeof(uint8_t));

        i2c_.write_data_DMA(ledValues_, 9);
    }

    void cashe_all_leds_values(uint8_t * allLedsValues)
    {
        memcpy(&(cashedLedValues_[1]), allLedsValues, 8 * sizeof(uint8_t));
    }

    void send_cashed_leds_values()
    {
        i2c_.write_data_DMA(cashedLedValues_, 9);
    }

    void set_transfer_complete_callback(std::function<void()> callback)
    {
        i2c_.get_DMA()->set_transfer_complete_callback(std::move(callback));
        i2c_.get_DMA()->enable_interrupt(eTransferCompleted);
    }

    void set_half_transfer_callback(std::function<void()> callback)
    {
        i2c_.get_DMA()->set_half_transfer_callback(std::move(callback));
        i2c_.get_DMA()->enable_interrupt(eHalfTransfer);
    }

protected:
private:
    I2C & i2c_;
    const uint8_t deviceAddress_;
    GPIO & resetPin_;

    uint8_t ledValues_[9];
    uint8_t cashedLedValues_[9];
};

#endif /* DRV_TLC59208F_TLC59208F_HPP_ */
