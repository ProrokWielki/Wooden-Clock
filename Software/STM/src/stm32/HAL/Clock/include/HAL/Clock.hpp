/**
 * @file Clock.hpp
 * @author Pawel Warzecha
 * @brief
 * @version 0.1
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <HAL/Register.hpp>
#include <HAL/types.hpp>
#include <cstdint>

class Clock
{
public:
    Clock();

    void enable_clock_for(Peripheral peripheral);
    void set_clock_source_for(PeripheralWithSelectableClockSource peripheral, ClockSource clock_source);

    [[nodiscard]] uint32_t get_clock_frequency() const;

private:
    friend class ClockTestAhb1_EnableClock_Test;
    friend class ClockTestAhb2_EnableClock_Test;
    friend class ClockTestAhb3_EnableClock_Test;
    friend class ClockTestApb1_1_EnableClock_Test;
    friend class ClockTestApb1_2_EnableClock_Test;
    friend class ClockTestApb2_EnableClock_Test;
    friend class ClockTestCciprValidClockSource_SetClockSource_Test;
    friend class ClockTestCcipr2ValidClockSource_SetClockSource_Test;

    Register<uint32_t> & get_peripheral_clock_register(Peripheral peripheral);
    Register<uint32_t> & get_peripheral_clock_source_register(PeripheralWithSelectableClockSource peripheral);

    Register<uint32_t> AHB1;
    Register<uint32_t> AHB2;
    Register<uint32_t> AHB3;
    Register<uint32_t> APB1_1;
    Register<uint32_t> APB1_2;
    Register<uint32_t> APB2;
    Register<uint32_t> PLL_CONFIG;
    Register<uint32_t> CCIPR;
    Register<uint32_t> CCIPR2;
};