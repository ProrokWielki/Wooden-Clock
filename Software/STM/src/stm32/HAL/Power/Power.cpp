/**
 * @file Clock.cpp
 * @author Pawel Warzecha
 * @brief
 * @version 0.1
 * @date 2025-10-19
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <cassert>

#include <HAL/Power.hpp>
#include <HAL/Register.hpp>
#include <HAL/types.hpp>

#include "cmsis_bridge/cmsis_bridge.hpp"

Power::Power() : CR1(to_address(Power_Types::Register::CR1))
{
}

void Power::set_backup_domain_write_protection_state(Power_Types::WriteProtectionState state)
{
    static constexpr uint8_t WRITE_PROTECTION_BIT_POSITION{8};

    CR1.set_bit_value(to_value(state), WRITE_PROTECTION_BIT_POSITION);
}