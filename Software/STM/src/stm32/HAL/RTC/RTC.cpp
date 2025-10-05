/**
 * SPI.cpp
 *
 *  Created on: 04-02-2025
 *  @author: Paweł Warzecha
 */

#include <cstdint>

#include <HAL/Clock.hpp>
#include <HAL/RTC.hpp>
#include <HAL/Register.hpp>
#include <HAL/types.hpp>
#include <cmsis_bridge/cmsis_bridge.hpp>

#include <stm32l452xx.h>

constexpr static uint8_t TENS_OF_HOURS_POSITION{20};
constexpr static uint8_t TENS_OF_HOURS_FIELD_LENGTH{3};
constexpr static uint8_t UNITS_OF_HOURS_POSITION{16};
constexpr static uint8_t UNITS_OF_HOURS_FIELD_LENGTH{4};

constexpr static uint8_t TENS_OF_MINUTES_POSITION{12};
constexpr static uint8_t TENS_OF_MINUTES_FIELD_LENGTH{3};
constexpr static uint8_t UNITS_OF_MINUTES_POSITION{8};
constexpr static uint8_t UNITS_OF_MINUTES_FIELD_LENGTH{4};

constexpr static uint8_t TENS_OF_SECONDS_POSITION{4};
constexpr static uint8_t TENS_OF_SECONDS_FIELD_LENGTH{4};
constexpr static uint8_t UNITS_OF_SECONDS_POSITION{0};
constexpr static uint8_t UNITS_OF_SECONDS_FIELD_LENGTH{3};

constexpr static uint8_t START_INIT_BIT_POSITION{7};
constexpr static uint8_t IS_IN_INIT_MODE_BIT_POSITION{6};

RTC_::RTC_(Clock & clock)
: clock_{clock}, TR(to_address(RTC_types::Register::TR)), DR(to_address(RTC_types::Register::DR)), SSR(to_address(RTC_types::Register::SSR)),
  ICSR(to_address(RTC_types::Register::ICSR)), PRER(to_address(RTC_types::Register::PRER)), WUTR(to_address(RTC_types::Register::WUTR)),
  CR(to_address(RTC_types::Register::CR)), WPR(to_address(RTC_types::Register::WPR)), CALR(to_address(RTC_types::Register::CALR)),
  SHIFTR(to_address(RTC_types::Register::SHIFTR)), TSTR(to_address(RTC_types::Register::TSTR)), TSDR(to_address(RTC_types::Register::TSDR)),
  TSSSR(to_address(RTC_types::Register::TSSSR)), ALRMAR(to_address(RTC_types::Register::ALRMAR)), ALRMASSR(to_address(RTC_types::Register::ALRMASSR)),
  ALARMBR(to_address(RTC_types::Register::ALARMBR)), ALRMBSSR(to_address(RTC_types::Register::ALRMBSSR)),ISR(to_address(RTC_types::Register::ISR)) 
{
    clock_.enable_clock_for(Peripheral::POWER_INTERFACE);

    // Enable access to RTC and Backup registers
    PWR->CR1 |= PWR_CR1_DBP;


    // Resets Backup Domain Config
    RCC->BDCR |= RCC_BDCR_BDRST;
    RCC->BDCR &= ~RCC_BDCR_BDRST;

    // Set driving capability to medium high
    RCC->BDCR &= ~RCC_BDCR_LSEDRV_Msk;
    RCC->BDCR |= (0x02 << RCC_BDCR_LSEDRV_Pos);

    // Start LSE clock
    RCC->BDCR |= RCC_BDCR_LSEON;

    // Wait until LSE is ready
    while ((RCC->BDCR & RCC_BDCR_LSERDY) != RCC_BDCR_LSERDY)
        ;

    clock.set_clock_source_for(PeripheralWithSelectableClockSource::RTC_1, ClockSource::LSE);
    clock.enable_clock_for(Peripheral::RTC_1);

    unlock_registers();

    // Enter Init
    ISR.set_bit(START_INIT_BIT_POSITION);
    while (ISR.get_bit(IS_IN_INIT_MODE_BIT_POSITION) == 0)
        ;

    // Setup prescalers for 1s RTC clock
    constexpr uint32_t PRESCLAER_VALUE{0x007F'00FF}; // TODO: Make it right
    PRER.write(PRESCLAER_VALUE);

    // Exit Init
    ISR.clear_bit(START_INIT_BIT_POSITION);

    lock_registers();
}

uint8_t RTC_::get_hours()
{
    const uint8_t hours_tens = TR.get_value(TENS_OF_HOURS_POSITION, TENS_OF_HOURS_FIELD_LENGTH);
    const uint8_t hours_ones = TR.get_value(UNITS_OF_HOURS_POSITION, UNITS_OF_HOURS_FIELD_LENGTH);

    const uint8_t hours = hours_tens * 10 + hours_ones;
    return hours;
}

uint8_t RTC_::get_minutes()
{
    const uint8_t minutes_tens = TR.get_value(TENS_OF_MINUTES_POSITION, TENS_OF_MINUTES_FIELD_LENGTH);
    const uint8_t minutes_ones = TR.get_value(UNITS_OF_MINUTES_POSITION, UNITS_OF_MINUTES_FIELD_LENGTH);

    const uint8_t minutes = minutes_tens * 10 + minutes_ones;
    return minutes;
}

uint8_t RTC_::get_seconds()
{
    const uint8_t seconds_tens = TR.get_value(TENS_OF_SECONDS_POSITION, TENS_OF_SECONDS_FIELD_LENGTH);
    const uint8_t seconds_ones = TR.get_value(UNITS_OF_SECONDS_POSITION, UNITS_OF_SECONDS_FIELD_LENGTH);

    const uint8_t seconds = seconds_tens * 10U + seconds_ones;
    return seconds;
}

bool RTC_::is_24hrs()
{
    constexpr static uint8_t FORMAT_24H_BIT_POSITION{6};

    return CR.get_bit(FORMAT_24H_BIT_POSITION) == 0;
}

bool RTC_::is_am()
{
    constexpr static uint8_t AM_BIT_POSITION{22};

    return TR.get_bit(AM_BIT_POSITION) == 0;
}

void RTC_::set_hours(uint8_t hour)
{

    unlock_registers();

    Register<uint32_t> time_register{TR.read()};

    const uint8_t tens_of_minutes = hour / 10;
    const uint8_t units_of_minutes = hour % 10;

    time_register.set_value(units_of_minutes, UNITS_OF_HOURS_POSITION, UNITS_OF_HOURS_FIELD_LENGTH);
    time_register.set_value(tens_of_minutes, TENS_OF_HOURS_POSITION, TENS_OF_HOURS_FIELD_LENGTH);

    TR.write(time_register.read());

    lock_registers();

    while (not is_synchronized())
        ;
}
void RTC_::set_minutes(uint8_t minute)
{

    unlock_registers();

    Register<uint32_t> time_register{TR.read()};

    const uint8_t tens_of_minutes = minute / 10;
    const uint8_t units_of_minutes = minute % 10;

    time_register.set_value(tens_of_minutes, TENS_OF_MINUTES_POSITION, TENS_OF_MINUTES_FIELD_LENGTH);
    time_register.set_value(units_of_minutes, UNITS_OF_MINUTES_POSITION, UNITS_OF_MINUTES_FIELD_LENGTH);

    TR.write(time_register.read());

    lock_registers();

    while (not is_synchronized())
        ;
}

bool RTC_::is_synchronized() const
{
    constexpr static uint8_t SYNCHRONIZATION_BIT_POSITION{5};
    return ICSR.get_bit(SYNCHRONIZATION_BIT_POSITION) == 1;
}

bool RTC_::can_time_be_set() const
{
    constexpr static uint8_t INITIALIZED_BIT_POSITION{6};
    return ICSR.get_bit(INITIALIZED_BIT_POSITION) == 1;
}

void RTC_::enter_init_mode()
{
    constexpr static uint8_t ENTER_INIT_MODE_BIT_POSITION{7};
    ICSR.set_bit(ENTER_INIT_MODE_BIT_POSITION);
}

void RTC_::unlock_registers()
{
    constexpr static uint8_t WRITE_PROTECTION_DISABLE_1ST_VALUE{0xCA};
    constexpr static uint8_t WRITE_PROTECTION_DISABLE_2ND_VALUE{0x53};

    PWR->CR1 |= 1 << 8;

    WPR.write(WRITE_PROTECTION_DISABLE_1ST_VALUE);
    WPR.write(WRITE_PROTECTION_DISABLE_2ND_VALUE);

    enter_init_mode();

    while (not can_time_be_set())
        ;
}

void RTC_::lock_registers()
{
    PWR->CR1 &= ~(1 << 8);

    constexpr static uint8_t WRITE_PROTECTION_ENABLE_1ST_VALUE{0xFE};
    constexpr static uint8_t WRITE_PROTECTION_ENABLE_2ND_VALUE{0x64};

    WPR.write(WRITE_PROTECTION_ENABLE_1ST_VALUE);
    WPR.write(WRITE_PROTECTION_ENABLE_2ND_VALUE);
}
