/**
 * @file RTC.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include <cstdint>

#include <HAL/Register.hpp>
#include <HAL/Clock.hpp>
#include <HAL/types.hpp>


class RTC_
{
public:
    RTC_(Clock& clock);

    uint8_t get_hours();
    uint8_t get_minutes();
    uint8_t get_seconds();

    void set_hours(uint8_t hour);
    void set_minutes(uint8_t minute);

    bool is_24hrs();
    bool is_am();

private:
    Clock& clock_;

    Register<uint32_t> TR;
    Register<uint32_t> DR;
    Register<uint32_t> SSR;
    Register<uint32_t> ICSR;
    Register<uint32_t> PRER;
    Register<uint32_t> WUTR;
    Register<uint32_t> CR;
    Register<uint32_t> WPR;
    Register<uint32_t> CALR;
    Register<uint32_t> SHIFTR;
    Register<uint32_t> TSTR;
    Register<uint32_t> TSDR;
    Register<uint32_t> TSSSR;
    Register<uint32_t> ALRMAR;
    Register<uint32_t> ALRMASSR;
    Register<uint32_t> ALARMBR;
    Register<uint32_t> ALRMBSSR;
    Register<uint32_t> ISR;

    void unlock_registers();
    void enter_init_mode();
    void lock_registers();

    [[nodiscard]] bool is_synchronized() const;
    [[nodiscard]] bool can_time_be_set() const;

};
