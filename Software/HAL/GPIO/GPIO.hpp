/**
 *  @file GPIO.hpp
 *
 *  Created on: 13-11-2018
 *  @author: Paweł Warzecha
 */

#ifndef HAL_GPIO_GPIO_HPP_
#define HAL_GPIO_GPIO_HPP_

#include <stdint.h>

#include <stm32l4xx.h>

#include "../Register/Register.hpp"

#include "GPIO_types.hpp"

constexpr static uint8_t MODER_FIELD_BIT_LENGTH = 2;
constexpr static uint8_t OTYPER_FIELD_BIT_LENGTH = 1;
constexpr static uint8_t OSPEEDR_FIELD_BIT_LENGTH = 2;
constexpr static uint8_t PUPDR_FIELD_BIT_LENGTH = 2;
constexpr static uint8_t IDR_FIELD_BIT_LENGTH = 1;
constexpr static uint8_t ODR_FIELD_BIT_LENGTH = 1;
constexpr static uint8_t AFR_FIELD_BIT_LENGTH = 4;

constexpr static uint8_t AFRH_START_FIELD = 8;

/**
 *  @brief Class for operations on GPIOs.
 *
 *  @details
 *  Class allows configuration and simple usage of any GPIO.
 */
class GPIO
{
public:
    /** Sets GPIO mode.
     *
     * @param ePortMode GPIO mode to be set.
     */
    void set_mode(PortMode_t ePortMode)
    {
        MODER.set_value(ePortMode, pinNumber_ * MODER_FIELD_BIT_LENGTH, MODER_FIELD_BIT_LENGTH);
    }
    /** Sets GPIO output type.
     *
     * @param ePortOutputType GPIO output type to be set.
     */
    void set_output_type(PortOutputType_t ePortOutputType)
    {
        OTYPER.set_value(ePortOutputType, pinNumber_ * OTYPER_FIELD_BIT_LENGTH, OTYPER_FIELD_BIT_LENGTH);
    }
    /** Sets GPIO speed.
     *
     * @param ePortOutputSpeed GPIO speed to be set.
     */
    void set_speed(PortOutputSpeed_t ePortOutputSpeed)
    {
        OSPEEDR.set_value(ePortOutputSpeed, pinNumber_ * OSPEEDR_FIELD_BIT_LENGTH, OSPEEDR_FIELD_BIT_LENGTH);
    }
    /** Turns on and off pulling resistor.
     *
     * @param ePortPullUpPullDown Pulling resistor to be set.
     */
    void set_pullUp_pullDown(PortPullUpPullDown_t ePortPullUpPullDown)
    {
        PUPDR.set_value(ePortPullUpPullDown, pinNumber_ * PUPDR_FIELD_BIT_LENGTH, PUPDR_FIELD_BIT_LENGTH);
    }
    /** Sets the alternate function of the GPIO.
     *
     * @param u8AlternateFunction Alternate function to be set.
     */
    void set_alternate_function(AlteranteFunction_t u8AlternateFunction)
    {
        if (pinNumber_ >= 8)
        {
            AFRH.set_value(u8AlternateFunction, (pinNumber_ - AFRH_START_FIELD) * AFR_FIELD_BIT_LENGTH, AFR_FIELD_BIT_LENGTH);
        }
        else
        {
            AFRL.set_value(u8AlternateFunction, pinNumber_ * AFR_FIELD_BIT_LENGTH, AFR_FIELD_BIT_LENGTH);
        }
    }

    /** Sets the output value of the GPIO
     *
     * @param eSignalLevel Output level to be set.
     */
    void set_output_value(SignalLevel_t eSignalLevel)
    {
        ODR.set_value(eSignalLevel, pinNumber_ * ODR_FIELD_BIT_LENGTH, ODR_FIELD_BIT_LENGTH);
    }
    /// Sets output to the high state.
    void set_output_high(void)
    {
        BSRR.set_bit(pinNumber_);
    }
    /// Sets output to the low state.
    void set_output_low(void)
    {
        BRR.set_bit(pinNumber_);
    }
    /// Toggles output level.
    void toogle_output_value(void)
    {
        ODR.toggle_bit(pinNumber_);
    }

    /** Gets the GPIO's output level
     *
     * @return The value of the GPIO
     */
    SignalLevel_t get_input_value(void)
    {
        return IDR.get_value(pinNumber_) > 0 ? eHigh : eLow;
    }

    /** Sets the GPIO as a I2C pin
     *
     * @param u8AlternateFunction Alternate function which corresponds to the I2C.
     */
    void set_as_I2C_pin(AlteranteFunction_t u8AlternateFunction)
    {
        set_alternate_function(u8AlternateFunction);
        set_pullUp_pullDown(ePullUp);
        set_mode(eAlternate);
        set_output_type(eOpenDrain);
        set_speed(eVeryHighSpeed);
    }

    GPIO(GPIO_TypeDef * gpio, const uint8_t pinNumber)
    : MODER(gpio->MODER), OTYPER(gpio->OTYPER), OSPEEDR(gpio->OSPEEDR), PUPDR(gpio->PUPDR), AFRL(gpio->AFR[0]), AFRH(gpio->AFR[1]), BSRR(gpio->BSRR),
      BRR(gpio->BRR), ODR(gpio->ODR), IDR(gpio->IDR), pinNumber_(pinNumber){};

protected:
private:
    Register MODER;
    Register OTYPER;
    Register OSPEEDR;
    Register PUPDR;
    Register AFRL;
    Register AFRH;
    Register BSRR;
    Register BRR;
    Register ODR;
    Register IDR;

    const uint8_t pinNumber_;
};

#endif /* HAL_GPIO_GPIO_HPP_ */
