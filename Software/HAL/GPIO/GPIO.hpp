/*
 * GPIO.hpp
 *
 *  Created on: 13-11-2018
 *      Author: Pawe? Warzecha
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

template<const uint32_t GPIO_ADDRESS, uint8_t PIN>
class GPIO
{
public:
    /** Sets GPIO mode.
     *
     * @param ePortMode GPIO mode to be set.
     */
    static void set_mode(PortMode_t ePortMode)
    {
        MODER::set_value(ePortMode, PIN * MODER_FIELD_BIT_LENGTH, MODER_FIELD_BIT_LENGTH);
    }
    /** Sets GPIO output type.
     *
     * @param ePortOutputType GPIO output type to be set.
     */
    static void set_output_type(PortOutputType_t ePortOutputType)
    {
        OTYPER::set_value(ePortOutputType, PIN * OTYPER_FIELD_BIT_LENGTH, OTYPER_FIELD_BIT_LENGTH);
    }
    /** Sets GPIO speed.
     *
     * @param ePortOutputSpeed GPIO speed to be set.
     */
    static void set_speed(PortOutputSpeed_t ePortOutputSpeed)
    {
        OSPEEDR::set_value(ePortOutputSpeed, PIN * OSPEEDR_FIELD_BIT_LENGTH, OSPEEDR_FIELD_BIT_LENGTH);
    }
    /** Turns on and off pulling resistor.
     *
     * @param ePortPullUpPullDown Pulling resistor to be set.
     */
    static void set_pullUp_pullDown(PortPullUpPullDown_t ePortPullUpPullDown)
    {
        PUPDR::set_value(ePortPullUpPullDown, PIN * PUPDR_FIELD_BIT_LENGTH, PUPDR_FIELD_BIT_LENGTH);
    }
    /** Sets the alternate function of the GPIO.
     *
     * @param u8AlternateFunction Alternate function to be set.
     */
    static void set_alternate_function(AlteranteFunction_t u8AlternateFunction)
    {
        if (PIN >= 8) {
            AFRH::set_value(u8AlternateFunction, (PIN - AFRH_START_FIELD) * AFR_FIELD_BIT_LENGTH, AFR_FIELD_BIT_LENGTH);
        } else {
            AFRL::set_value(u8AlternateFunction, PIN * AFR_FIELD_BIT_LENGTH, AFR_FIELD_BIT_LENGTH);
        }
    }

    /** Sets the output value of the GPIO
     *
     * @param eSignalLevel Output level to be set.
     */
    static void set_output_value(SignalLevel_t eSignalLevel)
    {
        ODR::set_value(eSignalLevel, PIN * ODR_FIELD_BIT_LENGTH, ODR_FIELD_BIT_LENGTH);
    }
    /// Sets output to the high state.
    static void set_output_high(void)
    {
        BSRR::set_bit(PIN);
    }
    /// Sets output to the low state.
    static void set_output_low(void)
    {
        BRR::set_bit(PIN);
    }
    /// Toggles output level.
    static void toogle_output_value(void)
    {
        ODR::toggle_bit(PIN);
    }

    /** Gets the GPIO's output level
     *
     * @return The value of the GPIO
     */
    static SignalLevel_t get_input_value(void)
    {
        return IDR::get_value(PIN);
    }

    /** Sets the GPIO as a I2C pin
     *
     * @param u8AlternateFunction Alternate function which corresponds to the I2C.
     */
    static void set_as_I2C_pin(AlteranteFunction_t u8AlternateFunction)
    {
        set_alternate_function(u8AlternateFunction);
        set_pullUp_pullDown(ePullUp);
        set_mode(eAlternate);
        set_output_type(eOpenDrain);
        set_speed(eVeryHighSpeed);
    }

protected:
private:
    constexpr volatile static uint32_t adrMODER = (uint32_t)(&(((GPIO_TypeDef *)GPIO_ADDRESS)->MODER));
    constexpr volatile static uint32_t adrOTYPER = (uint32_t)(&(((GPIO_TypeDef *)GPIO_ADDRESS)->OTYPER));
    constexpr volatile static uint32_t adrOSPEEDR = (uint32_t)(&(((GPIO_TypeDef *)GPIO_ADDRESS)->OSPEEDR));
    constexpr volatile static uint32_t adrPUPDR = (uint32_t)(&(((GPIO_TypeDef *)GPIO_ADDRESS)->PUPDR));
    constexpr volatile static uint32_t adrAFRL = (uint32_t)(&(((GPIO_TypeDef *)GPIO_ADDRESS)->AFR[0]));
    constexpr volatile static uint32_t adrAFRH = (uint32_t)(&(((GPIO_TypeDef *)GPIO_ADDRESS)->AFR[1]));
    constexpr volatile static uint32_t adrBSRR = (uint32_t)(&(((GPIO_TypeDef *)GPIO_ADDRESS)->BSRR));
    constexpr volatile static uint32_t adrBRR = (uint32_t)(&(((GPIO_TypeDef *)GPIO_ADDRESS)->BRR));
    constexpr volatile static uint32_t adrODR = (uint32_t)(&(((GPIO_TypeDef *)GPIO_ADDRESS)->ODR));
    constexpr volatile static uint32_t adrIDR = (uint32_t)(&(((GPIO_TypeDef *)GPIO_ADDRESS)->IDR));

    typedef Register<adrMODER> MODER;
    typedef Register<adrOTYPER> OTYPER;
    typedef Register<adrOSPEEDR> OSPEEDR;
    typedef Register<adrPUPDR> PUPDR;
    typedef Register<adrAFRL> AFRL;
    typedef Register<adrAFRH> AFRH;
    typedef Register<adrBSRR> BSRR;
    typedef Register<adrBRR> BRR;
    typedef Register<adrODR> ODR;
    typedef Register<adrIDR> IDR;

    GPIO(){};
};

#endif /* HAL_GPIO_GPIO_HPP_ */
