/**
 * @file SysConfig.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-12-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <HAL/GPIO.hpp>
#include <HAL/Register.hpp>
#include <HAL/types.hpp>
#include <cstdint>

class SysConfig
{
public:
    SysConfig();

    void set_fast_mode_plus(I2C_Types::I2CNumber i2c);
    void set_fast_mode_plus(GPIO_Types::Port port, uint8_t pin_number);

private:
    [[nodiscard]] bool does_pin_needs_setting_fmp(GPIO_Types::Port port, uint8_t pin_number) const;

    Register<uint32_t> MEMRMP;
    Register<uint32_t> CFGR1;
    Register<uint32_t> EXTICR1;
    Register<uint32_t> EXTICR2;
    Register<uint32_t> EXTICR3;
    Register<uint32_t> EXTICR4;
    Register<uint32_t> SCSR;
    Register<uint32_t> CFGR2;
    Register<uint32_t> SWPR;
    Register<uint32_t> SKR;
};