/**
 *  @file GPIO.hpp
 *
 *  Created on: 13-11-2018
 *  @author: Paweł Warzecha
 */

#ifndef HAL_GPIO_GPIO_HPP_
#define HAL_GPIO_GPIO_HPP_

#include <cstdint>

#include <HAL/Register.hpp>

#include "HAL/types.hpp"

class Clock;
class SysConfig;

/**
 *  @brief Class for operations on GPIOs.
 *
 *  @details
 *  Class allows configuration and simple usage of any GPIO.
 */
class GPIO
{
public:
    /**
     * @brief Construct a new GPIO object
     *
     * @param gpio Pointer to GPIO port register
     * @param pinNumber GPIO pin number
     */
    GPIO(Clock & clock, SysConfig & sys_config, GPIO_Types::Port gpio, const uint8_t pinNumber);

    /** Sets GPIO mode.
     *
     * @param ePortMode GPIO mode to be set.
     */
    void set_mode(GPIO_Types::PortMode ePortMode);

    /** Sets GPIO output type.
     *
     * @param ePortOutputType GPIO output type to be set.
     */
    void set_output_type(GPIO_Types::PortOutputType ePortOutputType);

    /** Sets GPIO speed.
     *
     * @param ePortOutputSpeed GPIO speed to be set.
     */
    void set_speed(GPIO_Types::PortOutputSpeed ePortOutputSpeed);

    /** Turns on and off pulling resistor.
     *
     * @param PortPullUpPullDown Pulling resistor to be set.
     */
    void set_pull_up_pull_down(GPIO_Types::PortPullUpPullDown ePortPullUpPullDown);

    /** Sets the alternate function of the GPIO.
     *
     * @param u8AlternateFunction Alternate function to be set.
     */
    void set_alternate_function(GPIO_Types::AlternateFunction AlternateFunction);

    /** Sets the output value of the GPIO
     *
     * @param SignalLevel Output level to be set.
     */
    void set_output_value(GPIO_Types::SignalLevel SignalLevel);

    /// Sets output to the high state.
    void set_output_high();

    /// Sets output to the low state.
    void set_output_low();

    /// Toggles output level.
    void toggle_output_value();

    void set_fast_mode_plus();

    /** Gets the GPIO's output level
     *
     * @return The value of the GPIO
     */
    GPIO_Types::SignalLevel get_input_value();

    /** Sets the GPIO as a I2C pin
     *
     * @param AlternateFunction Alternate function which corresponds to the I2C.
     */
    void set_as_i2c_pin(GPIO_Types::AlternateFunction AlternateFunction);

    /** Sets the GPIO as a SPI pin
     *
     * @param AlternateFunction Alternate function which corresponds to the SPI.
     */
    void set_as_spi_pin(GPIO_Types::AlternateFunction AlternateFunction);

protected:
private:
    Clock & clock_;
    SysConfig & sys_config_;

    Register<uint32_t> MODER;
    Register<uint32_t> OTYPER;
    Register<uint32_t> OSPEEDR;
    Register<uint32_t> PUPDR;
    Register<uint32_t> AFRL;
    Register<uint32_t> AFRH;
    Register<uint32_t> BSRR;
    Register<uint32_t> BRR;
    Register<uint32_t> ODR;
    Register<uint32_t> IDR;

    GPIO_Types::Port port_;
    uint8_t pin_number_;
};

#endif /* HAL_GPIO_GPIO_HPP_ */
