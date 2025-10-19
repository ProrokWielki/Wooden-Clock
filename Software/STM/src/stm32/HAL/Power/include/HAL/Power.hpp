/**
 * @file Clock.hpp
 * @author Pawel Warzecha
 * @brief
 * @version 0.1
 * @date 2025-10-19
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <cstdint>

#include <HAL/Register.hpp>
#include <HAL/types.hpp>

class Power
{
public:
    Power();

    void set_backup_domain_write_protection_state(Power_Types::WriteProtectionState state);

private:
    Register<uint32_t> CR1;
};