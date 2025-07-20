/**
 * @file register.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include <gmock/gmock.h>

#include <HAL/types.hpp>

class Clock
{
public:
    MOCK_METHOD(void, enable_clock_for, (Peripheral));
    MOCK_METHOD(void, enable_clock_for, (PeripheralWithSelectableClockSource));
};
