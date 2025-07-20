/**
 * DMA.hpp
 *
 *  Created on: 13-11-2018
 *  @author: Paweł Warzecha
 */

#ifndef HAL_DMA_DMA_HPP_
#define HAL_DMA_DMA_HPP_

#include <cstdint>
#include <functional>

#include <HAL/Register.hpp>

#include "HAL/types.hpp"

class Clock;

/**
 *  @brief Static class for operations on DMAs.
 *
 *  @details
 *  Class allows configuration and simple usage of the DMA.
 *
 */
class DMA
{
public:
    DMA(Clock & clock, DMA_Types::DmaNumber dma_number, DMA_Types::Channel dma_channel);

    /**
     * @brief Sets priority for the DMA channel.
     *
     * @param priority priority to be set.
     */
    void set_priority(DMA_Types::Priority priority);

    /**
     * @brief Enables memory-to-memory DMA transfer.
     */
    void enable_mem2mem();

    /**
     * @brief Disables memory-to-memory DMA transfer.
     */
    void disable_mem2mem();

    /**
     * @brief Sets size of the memory data.
     *
     * @param memory_size size of the data
     */
    void set_memory_size(DMA_Types::DataSize memory_size);

    /**
     * @brief Sets size of the peripheral data.
     *
     * @param peripheral_size size of the data
     */
    void set_peripheral_size(DMA_Types::DataSize peripheral_size);

    /**
     * @brief Enables automatic memory increment.
     */
    void enable_memory_increment();

    /**
     * @brief Disables automatic memory increment.
     */
    void disable_memory_increment();

    /**
     * @brief Enables automatic peripheral increment.
     */
    void enable_peripheral_increment();

    /**
     * @brief Disables automatic peripheral increment.
     */
    void disable_peripheral_incremen();

    /**
     * @brief Enables circular mode.
     */
    void enable_circular_mode();

    /**
     * @brief Disables circular mode.
     */
    void disable_circular_mode();

    /**
     * @brief Sets from where the data is read.
     * @param read_direction direction of read.
     */
    void set_read_direction(DMA_Types::ReadDirection read_direction);

    /**
     * @brief Enables interrupt.
     *
     * @param interrupt interrupt to be enabled.
     */
    void enable_interrupt(DMA_Types::Interrupt interrupt);

    /**
     * @brief Disables interrupt.
     *
     * @param DMAInterrupt interrupt to be disabled.
     */
    void disable_interrupt(DMA_Types::Interrupt interrupt);

    /**
     * @brief Enables DMA channel.
     */
    void enable();

    /**
     * @brief Disables DMA channel.
     */
    void disable();

    /**
     * @brief Sets the number of transfers.
     *
     * @param TransferSize number of transfer to be made.
     */
    void set_transfer_size(uint16_t TransferSize);

    /**
     * @brief Sets address of the peripheral.
     *
     * @param PeripheralAddress peripheral address.
     */
    void set_periphearl_address(uint32_t PeripheralAddress);

    /**
     * @brief Sets address of the memory.
     *
     * @param MemoryAddress memory address.
     */
    void set_memory_address(uint32_t MemoryAddress);

    /**
     * @brief Sets DMA request.
     *
     * @param DMARequest DMA request to be enabled.
     */
    void set_request(DMA_Types::Request request);

    /**
     * @brief Sets callback function to be called when interrupt is received. Can be set only once!
     *
     * @param callback function to be called when interrupt is received.
     */
    void set_transfer_complete_callback(std::function<void()> callback);  // TODO: make it possible to change the callback.

    /**
     * @brief Sets callback function to be called when interrupt is received. Can be set only once!
     *
     * @param callback function to be called when interrupt is received.
     */
    void set_half_transfer_callback(std::function<void()> callback);  // TODO: make it possible to change the callback.

    /**
     * @brief function to be called to when interrupt is received. Has to be put to the IRQ handler!
     */
    void transfer_complete_callback();

    /**
     * @brief function to be called to when interrupt is received. Has to be put to the IRQ handler!
     */
    void half_transfer_callback();

    bool is_half_transfer_interrupt();

    bool is_transfer_complete_interrupt();

private:
    void clear_transfer_complete_interrupt();

    void clear_half_transfer_interrupt();

    Register<uint32_t> IFCR;
    Register<uint32_t> ISR;

    Register<uint32_t> CCR;
    Register<uint32_t> CNDTR;
    Register<uint32_t> CPAR;
    Register<uint32_t> CMAR;

    Register<uint32_t> CSELR;

    DMA_Types::Channel channel;

    std::function<void()> complete_transfer_callback_;
    std::function<void()> half_transfer_callback_;
};

#endif /* HAL_DMA_DMA_HPP_ */
