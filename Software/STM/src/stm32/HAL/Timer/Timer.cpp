/**
 * Timer.hpp
 *
 *  Created on: 04-02-2025
 *  @author: Paweł Warzecha
 */

#include <HAL/Register.hpp>
#include <HAL/Timer.hpp>
#include <HAL/types.hpp>

#include <cmsis_bridge/cmsis_bridge.hpp>

Timer::Timer(timer_types::Timer_number timer)
: ARR(to_address(timer, timer_types::Register::ARR)), PSC(to_address(timer, timer_types::Register::PSC)), CR1(to_address(timer, timer_types::Register::CR1)),
  SR(to_address(timer, timer_types::Register::SR)), DIER(to_address(timer, timer_types::Register::DIER))
{
}

void Timer::set_reload_value(const uint32_t reload)
{
    constexpr static uint8_t RELOAD_FILED_LENGTH{32};
    ARR.set_value(reload, 0, RELOAD_FILED_LENGTH);
}

void Timer::set_prescaler_value(const uint16_t prescaler)
{
    constexpr static uint8_t PRESCALER_FILED_LENGTH{16};
    PSC.set_value(prescaler, 0, PRESCALER_FILED_LENGTH);
}

void Timer::enable()
{
    constexpr static uint8_t ENABLE_BIT_POSITION{0};
    CR1.set_bit(ENABLE_BIT_POSITION);
}

void Timer::disable()
{
    constexpr static uint8_t ENABLE_BIT_POSITION{0};
    CR1.clear_bit(ENABLE_BIT_POSITION);
}

void Timer::clear_interrupt_flag(timer_types::Interrupt interrupt)
{
    SR.clear_bit(to_bit_position(interrupt));
}

void Timer::enable_interrupt(timer_types::Interrupt interrupt)
{
    DIER.set_bit(to_bit_position(interrupt));
}