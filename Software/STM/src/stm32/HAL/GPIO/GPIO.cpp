/**
 *  @file GPIO.cpp
 *
 *  Created on: 02-02-2025
 *  @author: Paweł Warzecha
 */

#include <cstdint>

#include <HAL/Clock.hpp>
#include <HAL/Register.hpp>
#include <HAL/SysConfig.hpp>
#include <HAL/types.hpp>

#include "include/HAL/GPIO.hpp"

#include <cmsis_bridge/cmsis_bridge.hpp>

namespace
{
constexpr static uint8_t MODER_FIELD_BIT_LENGTH = 2;
constexpr static uint8_t OTYPER_FIELD_BIT_LENGTH = 1;
constexpr static uint8_t OSPEEDR_FIELD_BIT_LENGTH = 2;
constexpr static uint8_t PUPDR_FIELD_BIT_LENGTH = 2;
constexpr static uint8_t ODR_FIELD_BIT_LENGTH = 1;
constexpr static uint8_t AFR_FIELD_BIT_LENGTH = 4;

constexpr static uint8_t AFRH_START_FIELD = 8;
}  // namespace

using namespace GPIO_Types;

GPIO::GPIO(Clock & clock, SysConfig & sys_config, Port port, const uint8_t pin_number)
: clock_{clock}, sys_config_(sys_config), MODER(to_address(port, PortRegister::MODER)), OTYPER(to_address(port, PortRegister::OTYPER)),
  OSPEEDR(to_address(port, PortRegister::OSPEEDR)), PUPDR(to_address(port, PortRegister::PUPDR)), AFRL(to_address(port, PortRegister::AFRL)),
  AFRH(to_address(port, PortRegister::AFRH)), BSRR(to_address(port, PortRegister::BSRR)), BRR(to_address(port, PortRegister::BRR)),
  ODR(to_address(port, PortRegister::ODR)), IDR(to_address(port, PortRegister::IDR)), port_{port}, pin_number_(pin_number)
{
    clock_.enable_clock_for(to_peripheral(port));
};

void GPIO::set_mode(PortMode PortMode)
{
    MODER.set_value(to_register_value(PortMode), pin_number_ * MODER_FIELD_BIT_LENGTH, MODER_FIELD_BIT_LENGTH);
}

void GPIO::set_output_type(PortOutputType portOutputType)
{
    OTYPER.set_value(to_register_value(portOutputType), pin_number_ * OTYPER_FIELD_BIT_LENGTH, OTYPER_FIELD_BIT_LENGTH);
}

void GPIO::set_speed(PortOutputSpeed portOutputSpeed)
{
    OSPEEDR.set_value(to_register_value(portOutputSpeed), pin_number_ * OSPEEDR_FIELD_BIT_LENGTH, OSPEEDR_FIELD_BIT_LENGTH);
}

void GPIO::set_pull_up_pull_down(PortPullUpPullDown PortPullUpPullDown)
{
    PUPDR.set_value(to_register_value(PortPullUpPullDown), pin_number_ * PUPDR_FIELD_BIT_LENGTH, PUPDR_FIELD_BIT_LENGTH);
}

void GPIO::set_alternate_function(AlternateFunction alternateFunction)
{
    constexpr uint8_t AFRH_START_PIN_NUMBER{8};
    if (pin_number_ >= AFRH_START_PIN_NUMBER)
    {
        AFRH.set_value(to_register_value(alternateFunction), (pin_number_ - AFRH_START_FIELD) * AFR_FIELD_BIT_LENGTH, AFR_FIELD_BIT_LENGTH);
    }
    else
    {
        AFRL.set_value(to_register_value(alternateFunction), pin_number_ * AFR_FIELD_BIT_LENGTH, AFR_FIELD_BIT_LENGTH);
    }
}

void GPIO::set_output_value(SignalLevel signalLevel)
{
    ODR.set_value(to_register_value(signalLevel), pin_number_ * ODR_FIELD_BIT_LENGTH, ODR_FIELD_BIT_LENGTH);
}

void GPIO::set_output_high()
{
    ODR.set_bit(pin_number_);
}

void GPIO::set_output_low()
{
    ODR.clear_bit(pin_number_);
}

void GPIO::toggle_output_value()
{
    ODR.toggle_bit(pin_number_);
}

SignalLevel GPIO::get_input_value()
{
    return IDR.get_bit(pin_number_) == 1 ? SignalLevel::High : SignalLevel::Low;
}

void GPIO::set_as_i2c_pin(AlternateFunction AlternateFunction)
{
    set_alternate_function(AlternateFunction);
    set_pull_up_pull_down(PortPullUpPullDown::PullUp);
    set_mode(PortMode::Alternate);
    set_output_type(PortOutputType::OpenDrain);
    set_speed(PortOutputSpeed::VeryHigh);
}

void GPIO::set_as_spi_pin(AlternateFunction AlternateFunction)
{
    set_alternate_function(AlternateFunction);
    set_mode(PortMode::Alternate);
    set_output_type(PortOutputType::PushPull);
    set_pull_up_pull_down(PortPullUpPullDown::None);
    set_speed(PortOutputSpeed::VeryHigh);
}

void GPIO::set_fast_mode_plus()
{
    sys_config_.set_fast_mode_plus(port_, pin_number_);
}