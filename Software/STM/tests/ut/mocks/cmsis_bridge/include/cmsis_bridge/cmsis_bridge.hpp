/**
 * @file cmsis_bridge.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include <cstdint>

class CmsisBridgeMock
{
public:
    MOCK_METHOD(volatile uint32_t *, to_address, (GPIO_Types::Port, GPIO_Types::PortRegister));
    MOCK_METHOD(volatile uint32_t *, to_address, (ClockRegister));
};

static CmsisBridgeMock cmsis_bridge_mock;

volatile uint32_t * to_address(GPIO_Types::Port port, GPIO_Types::PortRegister portRegister)
{
    return cmsis_bridge_mock.to_address(port, portRegister);
}

volatile uint32_t * to_address(ClockRegister clock_register)
{
    return cmsis_bridge_mock.to_address(clock_register);
}
