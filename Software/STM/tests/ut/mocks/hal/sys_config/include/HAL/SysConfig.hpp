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

class SysConfig
{
public:
    MOCK_METHOD(void, set_fast_mode_plus, (I2C_Types::I2CNumber));
    MOCK_METHOD(void, set_fast_mode_plus, (GPIO_Types::Port port, uint8_t pin_number));
};
