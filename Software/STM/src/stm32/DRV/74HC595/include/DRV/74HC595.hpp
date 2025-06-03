/**
 * 74HC595.hpp
 *
 *  Created on: 27-02-2019
 *  @author: Paweł Warzecha
 */

#ifndef DRV_74HC595_74HC595_HPP_
#define DRV_74HC595_74HC595_HPP_

#include <cstdint>

#include <HAL/GPIO.hpp>

class SR_74HC595
{
public:
    SR_74HC595(GPIO & dataInPin, GPIO & registerClockPin, GPIO & storageClockPin, GPIO & outputEnablePin, GPIO & clearPin, uint8_t chain_length);

    void set_all_outputs_high();

    void clear();

    void output_enable(bool enable);

    void shift_bit(GPIO_Types::SignalLevel bitValue);


private:
    void store_input();

    void show();

    GPIO dataInPin_;
    GPIO registerClockPin_;
    GPIO storageClockPin_;
    GPIO outputEnablePin_;
    GPIO clearPin_;

    uint8_t chain_length_;
    static constexpr uint8_t NUM_OF_OUTPUTS{8};
};

#endif /* DRV_74HC595_74HC595_HPP_ */
