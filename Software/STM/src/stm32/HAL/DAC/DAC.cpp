/**
 * @file DAC.cpp
 * @author Pawel Warzecha
 * @brief
 * @version 0.1
 * @date 2026-10-09
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "include/HAL/DAC.hpp"
#include "HAL/Clock.hpp"
#include "HAL/types.hpp"

#include <HAL/GPIO.hpp>

#include <cmsis_bridge/cmsis_bridge.hpp>

DAC::DAC(Clock & clock, DAC_Types::DacNumber dac_number, DAC_Types::DacChannel dac_channel, DAC_Types::DacTrigger dac_trigger, GPIO & dac_pin, DMA * dma)
: dac_number_(dac_number), dac_channel_(dac_channel), dma_(dma), CR{to_address(dac_number, DAC_Types::Register::CR)},
  MCR{to_address(dac_number, DAC_Types::Register::MCR)}, DHR12R1{to_address(dac_number, DAC_Types::Register::DHR12R1)},
  DHR8R1{to_address(dac_number, DAC_Types::Register::DHR8R1)}
{
    dac_pin.set_mode(GPIO_Types::PortMode::Analog);

    clock.enable_clock_for(to_peripheral(dac_number_));

    set_trigger(dac_trigger);

    // enable();
}

void DAC::set_trigger(DAC_Types::DacTrigger trigger)
{
    static constexpr uint8_t TRIGGER_ENABLE_BIT_POSTION{2};
    CR.set_bit(TRIGGER_ENABLE_BIT_POSTION);

    static constexpr uint8_t TRIGGER_TYPE_POSTION{3};
    static constexpr uint8_t TRIGGER_TYPE_LENGTH{3};

    CR.set_value(to_value(trigger), TRIGGER_TYPE_POSTION, TRIGGER_TYPE_LENGTH);
}

void DAC::enable()
{
    static constexpr uint8_t ENABLE_BIT_POSITION{0};
    CR.set_bit(ENABLE_BIT_POSITION);
}

void DAC::disable()
{
    static constexpr uint8_t ENABLE_BIT_POSITION{0};
    CR.clear_bit(ENABLE_BIT_POSITION);
}

void DAC::enable_dma()
{
    static constexpr uint8_t DMA_ENABLE_BIT_POSITION{12};
    CR.set_bit(DMA_ENABLE_BIT_POSITION);
}

void DAC::play_dma(const std::span<const uint8_t> & data)
{
    enable();

    dma_->enable_request(DMA_Types::Request::DAC_CH1);

    dma_->enable_memory_increment();

    dma_->set_memory_address(reinterpret_cast<intptr_t>(data.data()));  // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)

    dma_->set_peripheral_address(DHR8R1.get_address());
    dma_->set_read_direction(DMA_Types::ReadDirection::ReadFromMemory);
    dma_->set_memory_size(DMA_Types::DataSize::Bits8);
    dma_->set_peripheral_size(DMA_Types::DataSize::Bits8);
    dma_->set_transfer_size(data.size());

    dma_->enable();

    enable_dma();
}

void DAC::stop()
{
    disable();
}

DMA * DAC::get_dma()
{
    return dma_;
}