/**
 * DMA.cpp
 *
 *  Created on: 30-01-2025
 *  @author: Paweł Warzecha
 */

#include <cassert>
#include <cstdint>
#include <functional>

#include <HAL/Clock.hpp>
#include <HAL/DMA.hpp>
#include <HAL/Register.hpp>
#include <cmsis_bridge/cmsis_bridge.hpp>

#include "HAL/types.hpp"

namespace
{
constexpr static uint8_t MEMORY_TRANSFER_SIZE_FIELD_BIT_LENGTH = 16;
constexpr static uint8_t PERIPHERAL_ADDRESS_FIELD_BIT_LENGTH = 32;
constexpr static uint8_t MEMORY_ADDRESS_FIELD_BIT_LENGTH = 32;
constexpr static uint8_t PRIORITY_LEVEL_FIELD_BIT_LENGTH = 2;
constexpr static uint8_t PERIHERAL_SIZE_FIELD_BIT_LENGTH = 2;
constexpr static uint8_t MEMORY_SIZE_FIELD_BIT_LENGTH = 2;

constexpr uint8_t DMA_PRIORITY_START_POSITION{12};
constexpr uint8_t DMA_MEM_2_MEM_START_POSITION{14};
constexpr uint8_t DMA_MEMORY_SIZE_START_POSITION{10};
constexpr uint8_t DMA_PERIPHERAL_SIZE_START_POSITION{8};
constexpr uint8_t DMA_MEMORY_INCREMENT_START_POSITION{7};
constexpr uint8_t DMA_PERIPHERAL_INCREMENT_START_POSITION{6};
constexpr uint8_t DMA_CIRCULAR_MODE_START_POSITION{5};
constexpr uint8_t DMA_READ_DIRECTION_START_POSITION{4};
constexpr uint8_t DMA_ENABLE_START_POSITION{0};

}  // namespace

DMA::DMA(Clock & clock, DMA_Types::DmaNumber dma_number, DMA_Types::Channel dma_channel)
: IFCR(to_address(dma_number, dma_channel, DMA_Types::DmaRegister::IFCR)), ISR(to_address(dma_number, dma_channel, DMA_Types::DmaRegister::ISR)),
  CCR(to_address(dma_number, dma_channel, DMA_Types::DmaRegister::CCR)), CNDTR(to_address(dma_number, dma_channel, DMA_Types::DmaRegister::CNDTR)),
  CPAR(to_address(dma_number, dma_channel, DMA_Types::DmaRegister::CPAR)), CMAR(to_address(dma_number, dma_channel, DMA_Types::DmaRegister::CMAR)),
  CSELR(to_address(dma_number, dma_channel, DMA_Types::DmaRegister::CSELR)), channel_(dma_channel), dma_number_(dma_number)
{
    clock.enable_clock_for(to_peripheral(dma_number));
}

void DMA::set_priority(DMA_Types::Priority priority)
{
    CCR.set_value(to_value(priority), DMA_PRIORITY_START_POSITION, PRIORITY_LEVEL_FIELD_BIT_LENGTH);
}

void DMA::enable_mem2mem()
{
    CCR.set_bit(DMA_MEM_2_MEM_START_POSITION);
}

void DMA::disable_mem2mem()
{
    CCR.clear_bit(DMA_MEM_2_MEM_START_POSITION);
}

void DMA::set_memory_size(DMA_Types::DataSize memory_size)
{
    CCR.set_value(to_value(memory_size), DMA_MEMORY_SIZE_START_POSITION, MEMORY_SIZE_FIELD_BIT_LENGTH);
}

void DMA::set_peripheral_size(DMA_Types::DataSize peripheral_size)
{
    CCR.set_value(to_value(peripheral_size), DMA_PERIPHERAL_SIZE_START_POSITION, PERIHERAL_SIZE_FIELD_BIT_LENGTH);
}

void DMA::enable_memory_increment()
{
    CCR.set_bit(DMA_MEMORY_INCREMENT_START_POSITION);
}

void DMA::disable_memory_increment()
{
    CCR.clear_bit(DMA_MEMORY_INCREMENT_START_POSITION);
}

void DMA::enable_peripheral_increment()
{
    CCR.set_bit(DMA_PERIPHERAL_INCREMENT_START_POSITION);
}

void DMA::disable_peripheral_increment()
{
    CCR.clear_bit(DMA_PERIPHERAL_INCREMENT_START_POSITION);
}

void DMA::enable_circular_mode()
{
    CCR.set_bit(DMA_CIRCULAR_MODE_START_POSITION);
}

void DMA::disable_circular_mode()
{
    CCR.clear_bit(DMA_CIRCULAR_MODE_START_POSITION);
}

void DMA::set_read_direction(DMA_Types::ReadDirection read_direction)
{
    CCR.set_value(to_value(read_direction), DMA_READ_DIRECTION_START_POSITION, 1);
}

void DMA::enable_interrupt(DMA_Types::Interrupt interrupt)
{
    CCR.set_bit(to_bit_position(interrupt));
}

void DMA::disable_interrupt(DMA_Types::Interrupt interrupt)
{
    CCR.clear_bit(to_bit_position(interrupt));
}

void DMA::enable()
{
    CCR.set_bit(DMA_ENABLE_START_POSITION);
}

void DMA::disable()
{
    CCR.clear_bit(DMA_ENABLE_START_POSITION);
}

void DMA::set_transfer_size(uint16_t transfer_size)
{
    CNDTR.set_value(transfer_size, 0, MEMORY_TRANSFER_SIZE_FIELD_BIT_LENGTH);
}

void DMA::set_peripheral_address(uint32_t peripheral_address)
{
    CPAR.set_value(peripheral_address, 0, PERIPHERAL_ADDRESS_FIELD_BIT_LENGTH);
}

void DMA::set_memory_address(uint32_t memory_address)
{
    CMAR.set_value(memory_address, 0, MEMORY_ADDRESS_FIELD_BIT_LENGTH);
}

void DMA::enable_request(DMA_Types::Request request)
{
    assert(is_request_valid(dma_number_, channel_, request) && "Not a valid request");

    auto channel_position = to_start_position(channel_);
    auto request_value = to_value(dma_number_, channel_, request);

    static constexpr uint8_t REQUEST_FIELD_BIT_LENGTH{4};
    CSELR.set_value(request_value, channel_position, REQUEST_FIELD_BIT_LENGTH);
}

void DMA::set_transfer_complete_callback(std::function<void()> callback)
{
    complete_transfer_callback_ = std::move(callback);
}

void DMA::set_half_transfer_callback(std::function<void()> callback)
{
    half_transfer_callback_ = std::move(callback);
}

void DMA::transfer_complete_callback()
{
    disable();
    complete_transfer_callback_();
    clear_transfer_complete_interrupt();
}

void DMA::half_transfer_callback()
{
    disable();
    half_transfer_callback_();
    clear_half_transfer_interrupt();
}

bool DMA::is_half_transfer_interrupt()
{
    return ISR.get_bit(to_bit_position(channel_, DMA_Types::Interrupt::HalfTransfer)) != 0;
}

bool DMA::is_transfer_complete_interrupt()
{
    return ISR.get_bit(to_bit_position(channel_, DMA_Types::Interrupt::TransferCompleted)) != 0;
}

void DMA::clear_transfer_complete_interrupt()
{
    IFCR.set_bit(to_bit_position(channel_, DMA_Types::Interrupt::TransferCompleted));
}

void DMA::clear_half_transfer_interrupt()
{
    IFCR.set_bit(to_bit_position(channel_, DMA_Types::Interrupt::TransferCompleted));
}
