/**
 * Timer.hpp
 *
 *  Created on: 04-02-2025
 *  @author: Paweł Warzecha
 */

#include <HAL/Register.hpp>
#include <HAL/Timer.hpp>
#include <HAL/types.hpp>

#include <cassert>
#include <cmsis_bridge/cmsis_bridge.hpp>
#include <cstdint>
#include <limits>

Timer::Timer(Clock & clock, timer_types::Timer_number timer, uint32_t frequency, timer_types::MasterMode master_mode)
: ARR(to_address(timer, timer_types::Register::ARR)), PSC(to_address(timer, timer_types::Register::PSC)), CR1(to_address(timer, timer_types::Register::CR1)),
  CR2(to_address(timer, timer_types::Register::CR2)), SR(to_address(timer, timer_types::Register::SR)), DIER(to_address(timer, timer_types::Register::DIER))
{
    clock.enable_clock_for(to_peripheral(timer));

    set_frequency(frequency);

    set_master_mode(master_mode);

    enable();
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

void Timer::set_master_mode(timer_types::MasterMode master_mode)
{
    static constexpr uint8_t MASTER_MODE_POSITION{4};
    static constexpr uint8_t MASTER_MODE_LENGTH{3};

    CR2.set_value(to_value(master_mode), MASTER_MODE_POSITION, MASTER_MODE_LENGTH);
}

void Timer::set_frequency(uint32_t frequency)
{
    static constexpr uint16_t MAX_PRESCALLER{std::numeric_limits<uint16_t>::max()};
    static constexpr uint32_t MAX_RELOAD{std::numeric_limits<uint32_t>::max()};

    static constexpr uint32_t CLOCK_FREQUENCY{80'000'000};  // TODO: fix

    for (uint16_t prescaller = 1; prescaller < MAX_PRESCALLER; ++prescaller)
    {
        const uint32_t RELOAD_VALUE{(CLOCK_FREQUENCY / prescaller) / frequency};
        if (RELOAD_VALUE < MAX_RELOAD)
        {
            set_prescaler_value(prescaller - 1);
            set_reload_value(RELOAD_VALUE - 1);

            return;
        }
    }

    assert(false && "could not set frequency");
}