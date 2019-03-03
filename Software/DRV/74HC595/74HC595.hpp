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

template<typename DATA_IN_PIN, typename REGISTER_CLOCK_PIN, typename STORAGE_CLOCK_PIN, typename OUTPUT_ENABLE_PIN, typename CLEAR_PIN, uint8_t BIT_LENGTH>
class SR_74HC595
{
public:
    static void init()
    {
        DATA_IN_PIN::set_mode(eOutput);
        DATA_IN_PIN::set_speed(eVeryHighSpeed);

        REGISTER_CLOCK_PIN::set_mode(eOutput);
        REGISTER_CLOCK_PIN::set_speed(eVeryHighSpeed);

        STORAGE_CLOCK_PIN::set_mode(eOutput);
        STORAGE_CLOCK_PIN::set_speed(eVeryHighSpeed);

        OUTPUT_ENABLE_PIN::set_mode(eOutput);
        OUTPUT_ENABLE_PIN::set_speed(eVeryHighSpeed);

        CLEAR_PIN::set_mode(eOutput);
        CLEAR_PIN::set_speed(eVeryHighSpeed);

        output_enable(false);
        clear();
    }

    static void clear(void)
    {
        CLEAR_PIN::set_output_low();
        asm("nop");
        CLEAR_PIN::set_output_high();
    }

    static void output_enable(bool enable)
    {
        SignalLevel_t outputValue = enable ? eLow : eHigh;

        OUTPUT_ENABLE_PIN::set_output_value(outputValue);
    }

    static void shift_bit(SignalLevel_t bitValue)
    {
        DATA_IN_PIN::set_output_value(bitValue);
        store_input();
        show();
    }

    static void set_all_outputs_value(SignalLevel_t outputsValue)
    {
        for (uint8_t i = 0; i < BIT_LENGTH; i++)
        {
            DATA_IN_PIN::set_output_value(outputsValue);
            store_input();
        }
        show();
    }

private:
    SR_74HC595()
    {
    }

    static void store_input()
    {
        REGISTER_CLOCK_PIN::set_output_low();
        asm("nop");
        REGISTER_CLOCK_PIN::set_output_high();
    }

    static void show()
    {
        STORAGE_CLOCK_PIN::set_output_low();
        asm("nop");
        STORAGE_CLOCK_PIN::set_output_high();
    }
};

#endif /* DRV_74HC595_74HC595_HPP_ */
