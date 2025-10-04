/**
 * TLC59208F.hpp
 *
 *  Created on: 27-02-2019
 *  @author: Paweł Warzecha
 */

#ifndef DRV_TLC59208F_TLC59208F_HPP_
#define DRV_TLC59208F_TLC59208F_HPP_

#include <cstdint>
#include <functional>

#include <HAL/GPIO.hpp>
#include <HAL/I2C.hpp>

class TLC59208F
{
public:
    TLC59208F(I2C & i2c, const uint8_t deviceAddress, GPIO & resetPin);

    void init();

    void set_register_value(uint8_t registerAddress, uint8_t valueToBeSet);

    void set_registers_values(const uint8_t registerStartAddress, const uint8_t * const valuesToBeSet, const uint8_t numberOfValues);

    void set_all_leds_values(const uint8_t * allLedsValues);

    void cache_all_leds_values(const uint8_t * allLedsValues);

    void send_cashed_leds_values();

    void set_transfer_complete_callback(std::function<void()> callback);

    void set_half_transfer_callback(std::function<void()> callback);

private:
    I2C & i2c_;
    const uint8_t deviceAddress_;
    GPIO & resetPin_;

    uint8_t ledValues_[9];
    uint8_t cashedLedValues_[9];
};

#endif /* DRV_TLC59208F_TLC59208F_HPP_ */
