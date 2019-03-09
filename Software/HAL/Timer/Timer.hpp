/**
 * Timer.hpp
 *
 *  Created on: 05-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef HAL_TIMER_TIMER_HPP_
#define HAL_TIMER_TIMER_HPP_

#include "Register/Register.hpp"

#include <stm32l4xx.h>

/**
 *  @brief Class for operations on Timers.
 *
 *  @details
 *  Class allows configuration and simple usage of any Timer.
 */
class Timer
{
public:
    /**
     * @brief Constructor.
     *
     * @param timer pointer to timer structure.
     */
    Timer(volatile TIM_TypeDef * timer) : ARR(timer->ARR), PSC(timer->PSC), CR1(timer->CR1)
    {
    }

    /**
     * @brief Sets reload value.
     *
     * @param reload reload value.
     */
    void set_relode_value(const uint32_t reload)
    {
        ARR.set_value(reload, 0, 32);
    }

    /**
     * @brief sets prescaler value.
     *
     * @param prescaler prescaler value
     */
    void set_prescaler_value(const uint16_t prescaler)
    {
        PSC.set_value(prescaler, 0, 16);
    }

    /**
     * @brief Enables the timer.
     */
    void enable()
    {
        CR1.set_bit(TIM_CR1_CEN_Pos);
    }

    /**
     * @brief Disables the timer.
     */
    void disable()
    {
        CR1.clear_bit(TIM_CR1_CEN_Pos);
    }

protected:
private:
    Register ARR;
    Register PSC;
    Register CR1;
};

#endif /* HAL_TIMER_TIMER_HPP_ */
