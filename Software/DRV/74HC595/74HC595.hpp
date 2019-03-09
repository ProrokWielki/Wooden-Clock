/**
 * 74HC595.hpp
 *
 *  Created on: 27-02-2019
 *  @author: Paweł Warzecha
 */

#ifndef DRV_74HC595_74HC595_HPP_
#define DRV_74HC595_74HC595_HPP_

#include <stdint.h>

#include "HAL.hpp"

class SR_74HC595
{
public:
    SR_74HC595(GPIO & dataInPin, GPIO & registerClockPin, GPIO & storageClockPin, GPIO & outputEnablePin, GPIO & clearPin)
    : dataInPin_(dataInPin), registerClockPin_(registerClockPin), storageClockPin_(storageClockPin), outputEnablePin_(outputEnablePin), clearPin_(clearPin)
    {
    }

    void init()
    {
        dataInPin_.set_mode(eOutput);
        dataInPin_.set_speed(eVeryHighSpeed);

        registerClockPin_.set_mode(eOutput);
        registerClockPin_.set_speed(eVeryHighSpeed);

        storageClockPin_.set_mode(eOutput);
        storageClockPin_.set_speed(eVeryHighSpeed);

        outputEnablePin_.set_mode(eOutput);
        outputEnablePin_.set_speed(eVeryHighSpeed);

        clearPin_.set_mode(eOutput);
        clearPin_.set_speed(eVeryHighSpeed);

        output_enable(false);
        clear();
    }

    void clear(void)
    {
        clearPin_.set_output_low();
        asm("nop");
        clearPin_.set_output_high();
    }

    void output_enable(bool enable)
    {

        outputEnablePin_.set_output_value(enable ? eLow : eHigh);
    }

    void shift_bit(SignalLevel_t bitValue)
    {
        dataInPin_.set_output_value(bitValue);
        store_input();
        show();
    }

private:
    void store_input()
    {
        registerClockPin_.set_output_low();
        asm("nop");
        registerClockPin_.set_output_high();
    }

    void show()
    {
        storageClockPin_.set_output_low();
        asm("nop");
        storageClockPin_.set_output_high();
    }

    GPIO dataInPin_;
    GPIO registerClockPin_;
    GPIO storageClockPin_;
    GPIO outputEnablePin_;
    GPIO clearPin_;
};

#endif /* DRV_74HC595_74HC595_HPP_ */
