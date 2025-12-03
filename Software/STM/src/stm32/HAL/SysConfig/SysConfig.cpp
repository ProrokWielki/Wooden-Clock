/**
 * @file SysConfig.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-12-03
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <algorithm>
#include <array>

#include <HAL/Register.hpp>
#include <HAL/types.hpp>

#include "cmsis_bridge/cmsis_bridge.hpp"

#include "include/HAL/SysConfig.hpp"

SysConfig::SysConfig()
: MEMRMP(to_address(SysConfigRegister::MEMRMP)), CFGR1(to_address(SysConfigRegister::CFGR1)), EXTICR1(to_address(SysConfigRegister::EXTICR1)),
  EXTICR2(to_address(SysConfigRegister::EXTICR2)), EXTICR3(to_address(SysConfigRegister::EXTICR3)), EXTICR4(to_address(SysConfigRegister::EXTICR4)),
  SCSR(to_address(SysConfigRegister::SCSR)), CFGR2(to_address(SysConfigRegister::CFGR2)), SWPR(to_address(SysConfigRegister::SWPR)),
  SKR(to_address(SysConfigRegister::SKR))
{
}

void SysConfig::set_fast_mode_plus(I2C_Types::I2CNumber i2c)
{
    CFGR1.set_bit(to_bit_position(i2c, I2C_Types::Mode::FAST_PLUS));
}

void SysConfig::set_fast_mode_plus(GPIO_Types::Port port, uint8_t pin_number)
{
    if (does_pin_needs_setting_fmp(port, pin_number))
    {
        CFGR1.set_bit(to_bit_position(port, pin_number, I2C_Types::Mode::FAST_PLUS));
    }
}

bool SysConfig::does_pin_needs_setting_fmp(GPIO_Types::Port port, uint8_t pin_number) const
{
    constexpr std::array<uint8_t, 4> port_b_pins_needing_setting_fmp{6, 7, 8, 9};

    return port == GPIO_Types::Port::B and std::ranges::any_of(port_b_pins_needing_setting_fmp, [pin_number](uint8_t i) { return i == pin_number; });
}