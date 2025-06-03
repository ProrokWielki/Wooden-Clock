/**
 * Timer.hpp
 *
 *  Created on: 05-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef HAL_TIMER_TIMER_HPP_
#define HAL_TIMER_TIMER_HPP_

#include <HAL/Register.hpp>
#include <HAL/types.hpp>

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
    explicit Timer(timer_types::Timer_number timer);

    /**
     * @brief Sets reload value.
     *
     * @param reload reload value.
     */
    void set_reload_value(const uint32_t reload);

    /**
     * @brief sets prescaler value.
     *
     * @param prescaler prescaler value
     */
    void set_prescaler_value(const uint16_t prescaler);

    /**
     * @brief clears interrupt flag
     *
     * @param interrupt interrupt flag to be cleared
     */
    void clear_interrupt_flag(timer_types::Interrupt interrupt);

    /**
     * @brief Enables interrupt
     *
     * @param interrupt interrupt to be enabled
     */
    void enable_interrupt(timer_types::Interrupt interrupt);

    /**
     * @brief Enables the timer.
     */
    void enable();

    /**
     * @brief Disables the timer.
     */
    void disable();

private:
    Register<uint32_t> ARR;
    Register<uint32_t> PSC;
    Register<uint32_t> CR1;
    Register<uint32_t> SR;
    Register<uint32_t> DIER;
};

#endif /* HAL_TIMER_TIMER_HPP_ */
