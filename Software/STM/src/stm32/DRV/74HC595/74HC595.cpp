/**
 * 74HC595.cpp
 *
 *  Created on: 06-02-2025
 *  @author: Paweł Warzecha
 */

#include <HAL/Register.hpp>
#include <cstdint>

#include "HAL/types.hpp"
#include "include/DRV/74HC595.hpp"

using namespace GPIO_Types;

SR_74HC595::SR_74HC595(GPIO & dataInPin, GPIO & registerClockPin, GPIO & storageClockPin, GPIO & outputEnablePin, GPIO & clearPin, uint8_t chain_length)
: dataInPin_(dataInPin), registerClockPin_(registerClockPin), storageClockPin_(storageClockPin), outputEnablePin_(outputEnablePin), clearPin_(clearPin), chain_length_{chain_length}
{
    dataInPin_.set_mode(PortMode::Output);
    dataInPin_.set_speed(PortOutputSpeed::VeryHigh);

    registerClockPin_.set_mode(PortMode::Output);
    registerClockPin_.set_speed(PortOutputSpeed::VeryHigh);

    storageClockPin_.set_mode(PortMode::Output);
    storageClockPin_.set_speed(PortOutputSpeed::VeryHigh);

    outputEnablePin_.set_mode(PortMode::Output);
    outputEnablePin_.set_speed(PortOutputSpeed::VeryHigh);

    clearPin_.set_mode(PortMode::Output);
    clearPin_.set_speed(PortOutputSpeed::VeryHigh);

    output_enable(false);
    clear();
}

void SR_74HC595::clear()
{
    clearPin_.set_output_low();
    asm("nop");
    clearPin_.set_output_high();
}

void SR_74HC595::output_enable(bool enable)
{

    outputEnablePin_.set_output_value(enable ? SignalLevel::Low : SignalLevel::High);
}

void SR_74HC595::shift_bit(SignalLevel bitValue)
{
    dataInPin_.set_output_value(bitValue);
    store_input();
    show();
}

void SR_74HC595::store_input()
{
    registerClockPin_.set_output_low();
    asm("nop");
    registerClockPin_.set_output_high();
}

void SR_74HC595::show()
{
    storageClockPin_.set_output_low();
    asm("nop");
    storageClockPin_.set_output_high();
}

void SR_74HC595::set_all_outputs_high()
{
    for (uint8_t i{0}; i< chain_length_ * NUM_OF_OUTPUTS ; ++i)
    {
        shift_bit(GPIO_Types::SignalLevel::High);
    }
}
