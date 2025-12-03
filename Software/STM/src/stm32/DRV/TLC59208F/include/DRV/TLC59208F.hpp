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
#include <span>

#include <HAL/GPIO.hpp>
#include <HAL/I2C.hpp>

class TLC59208F
{
    static constexpr uint8_t ADDRESS_LENGTH{1U};
    static constexpr uint8_t NUM_OF_LEDS{8U};
    static constexpr uint8_t BUFFER_LENGTH{ADDRESS_LENGTH + NUM_OF_LEDS};

public:
    TLC59208F(I2C & i2c, const uint8_t deviceAddress, GPIO & resetPin);

    void init();

    void set_register_value(uint8_t registerAddress, uint8_t valueToBeSet);

    void set_registers_values(const uint8_t registerStartAddress, const uint8_t * const valuesToBeSet, const uint8_t numberOfValues);

    void set_all_leds_values(const std::array<uint8_t, 8> & allLedsValues);

    void cache_all_leds_values(std::span<uint8_t> allLedsValues);

    void send_cashed_leds_values();

    void set_transfer_complete_callback(std::function<void()> callback);

    void set_half_transfer_callback(std::function<void()> callback);

private:
    I2C & i2c_;
    const uint8_t deviceAddress_;
    GPIO & resetPin_;

    std::array<uint8_t, BUFFER_LENGTH> ledValues_{};
    std::array<uint8_t, BUFFER_LENGTH> cashedLedValues_{};
};

#endif /* DRV_TLC59208F_TLC59208F_HPP_ */
