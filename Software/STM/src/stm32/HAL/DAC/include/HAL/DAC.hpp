/**
 * @file DAC.hpp
 * @author Pawel Warzecha
 * @brief
 * @version 0.1
 * @date 2026-10-09
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <cstdint>
#include <span>

#include <HAL/Clock.hpp>
#include <HAL/DMA.hpp>
#include <HAL/GPIO.hpp>
#include <HAL/Register.hpp>
#include <HAL/types.hpp>

class DAC
{
public:
    DAC(Clock & clock, DAC_Types::DacNumber dac_number, DAC_Types::DacChannel dac_channel, DAC_Types::DacTrigger dac_trigger, GPIO & dac_pin,
        DMA * dma = nullptr);

    void play_dma(const std::span<const uint8_t> & data);

    void stop();

    DMA * get_dma();

private:
    void set_trigger(DAC_Types::DacTrigger trigger);

    void enable();
    void disable();
    void enable_dma();

    DAC_Types::DacNumber dac_number_;
    DAC_Types::DacChannel dac_channel_;

    DMA * dma_;

    Register<uint32_t> CR;
    Register<uint32_t> MCR;
    Register<uint32_t> DHR12R1;
    Register<uint32_t> DHR8R1;
    // Register<uint32_t> DATA_HOLDING_8BIT;
    // Register<uint32_t> DATA_HOLDING_12BIT;
};