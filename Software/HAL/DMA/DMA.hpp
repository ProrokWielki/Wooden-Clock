/**
 * DMA.hpp
 *
 *  Created on: 13-11-2018
 *  @author: Paweł Warzecha
 */

#ifndef HAL_DMA_DMA_HPP_
#define HAL_DMA_DMA_HPP_

#include <functional>
#include <stdint.h>

#include <stm32l4xx.h>

#include "../Register/Register.hpp"

#include "DMA_types.hpp"

constexpr static uint8_t MEMORY_TRANSFER_SIZE_FIELD_BIT_LENGTH = 16;
constexpr static uint8_t PERIPHERAL_ADDRESS_FIELD_BIT_LENGTH = 32;
constexpr static uint8_t MEMORY_ADDRESS_FIELD_BIT_LENGTH = 32;
constexpr static uint8_t PRIORITY_LEVEL_FIELD_BIT_LENGTH = 2;
constexpr static uint8_t PERIHERAL_SIZE_FIELD_BIT_LENGTH = 2;
constexpr static uint8_t MEMORY_SIZE_FIELD_BIT_LENGTH = 2;

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
    /**
     * @brief Sets priority for the DMA channel.
     *
     * @param eDMAPriority priority to be set.
     */
    void set_priority(DMAPriority_t eDMAPriority)
    {
        CCR.set_value(eDMAPriority, DMA_CCR_PL_Pos, PRIORITY_LEVEL_FIELD_BIT_LENGTH);
    }

    /**
     * @brief Enables memory-to-memory DMA transfer.
     */
    void enable_mem2mem()
    {
        CCR.set_bit(DMA_CCR_MEM2MEM_Pos);
    }
    /**
     * @brief Disables memory-to-memory DMA transfer.
     */
    void disable_mem2mem()
    {
        CCR.clear_bit(DMA_CCR_MEM2MEM_Pos);
    }

    /**
     * @brief Sets size of the memory data.
     *
     * @param eDMAMemorySize size of the data
     */
    void set_memory_size(DMASize_t eDMAMemorySize)
    {
        CCR.set_value(eDMAMemorySize, DMA_CCR_MSIZE_Pos, MEMORY_SIZE_FIELD_BIT_LENGTH);
    }

    /**
     * @brief Sets size of the peripheral data.
     *
     * @param eDMAPeripheralSize size of the data
     */
    void set_peripheral_size(DMASize_t eDMAPeripheralSize)
    {
        CCR.set_value(eDMAPeripheralSize, DMA_CCR_PSIZE_Pos, PERIHERAL_SIZE_FIELD_BIT_LENGTH);
    }

    /**
     * @brief Enables automatic memory increment.
     */
    void enable_memory_increment()
    {
        CCR.set_bit(DMA_CCR_MINC_Pos);
    }
    /**
     * @brief Disables automatic memory increment.
     */
    void disable__memory_incremen()
    {
        CCR.clear_bit(DMA_CCR_MINC_Pos);
    }

    /**
     * @brief Enables automatic peripheral increment.
     */
    void enable_peripheral_increment()
    {
        CCR.set_bit(DMA_CCR_PINC_Pos);
    }
    /**
     * @brief Disables automatic peripheral increment.
     */
    void disable_peripheral_incremen()
    {
        CCR.clear_bit(DMA_CCR_PINC_Pos);
    }

    /**
     * @brief Enables circular mode.
     */
    void enable_circular_mode()
    {
        CCR.set_bit(DMA_CCR_CIRC_Pos);
    }
    /**
     * @brief Disables circular mode.
     */
    void disable_circular_mode()
    {
        CCR.clear_bit(DMA_CCR_CIRC_Pos);
    }

    /**
     * @brief Sets from where the data is read.
     * @param eDMAReadDirection direction of read.
     */
    void set_read_direction(DMAReadDirection_t eDMAReadDirection)
    {
        CCR.set_value(eDMAReadDirection, DMA_CCR_DIR_Pos);
    }

    /**
     * @brief Enables interrupt.
     *
     * @param DMAInterrupt interrupt to be enabled.
     */
    void enable_interrupt(DMAInterrupts_t DMAInterrupt)
    {
        CCR.set_bit(DMAInterrupt);
    }
    /**
     * @brief Disables interrupt.
     *
     * @param DMAInterrupt interrupt to be disabled.
     */
    void disable_interrupt(DMAInterrupts_t DMAInterrupt)
    {
        CCR.clear_bit(DMAInterrupt);
    }

    /**
     * @brief Enables DMA channel.
     */
    void enable()
    {
        CCR.set_bit(DMA_CCR_EN_Pos);
    }
    /**
     * @brief Disables DMA channel.
     */
    void disable()
    {
        CCR.clear_bit(DMA_CCR_EN_Pos);
    }

    /**
     * @brief Sets the number of transfers.
     *
     * @param TransferSize number of transfer to be made.
     */
    void set_transfer_size(uint16_t TransferSize)
    {
        CNDTR.set_value(TransferSize, DMA_CNDTR_NDT_Pos, MEMORY_TRANSFER_SIZE_FIELD_BIT_LENGTH);
    }

    /**
     * @brief Sets address of the peripheral.
     *
     * @param PeripheralAddress peripheral address.
     */
    void set_periphearl_address(uint32_t PeripheralAddress)
    {
        CPAR.set_value(PeripheralAddress, DMA_CPAR_PA_Pos, PERIPHERAL_ADDRESS_FIELD_BIT_LENGTH);
    }

    /**
     * @brief Sets address of the memory.
     *
     * @param MemoryAddress memory address.
     */
    void set_memory_address(uint32_t MemoryAddress)
    {
        CMAR.set_value(MemoryAddress, DMA_CMAR_MA_Pos, MEMORY_ADDRESS_FIELD_BIT_LENGTH);
    }

    /**
     * @brief Sets DMA request.
     *
     * @param DMARequest DMA request to be enabled.
     */
    void set_request(DMARequest_t DMARequest)
    {
        CMAR.set_value(DMARequest, DMA_CMAR_MA_Pos, MEMORY_ADDRESS_FIELD_BIT_LENGTH);
    }

    /**
     * @brief Sets callback function to be called when interrupt is received. Can be set only once!
     *
     * @param callback function to be called when interrupt is received.
     * @return return the callback function.
     */
    void set_transfer_complete_callback(std::function<void()> callback)  // TODO: make it possible to change the callback.
    {
        callback_ = std::move(callback);
    }

    /**
     * @brief function to be called to when interrupt is received. Has to be put to the IRQ handler!
     */
    void transfer_complete_callback(void)
    {
        disable();
        callback_();
        clear_transfer_complete_interrupt();
    }

    DMA(DMA_TypeDef * dma, DMA_Channel_TypeDef * dmaChannel, const uint8_t channelNumber)
    : IFCR(dma->IFCR), CCR(dmaChannel->CCR), CNDTR(dmaChannel->CNDTR), CPAR(dmaChannel->CPAR), CMAR(dmaChannel->CMAR), channelNumber_(channelNumber){};

protected:
private:
    void clear_transfer_complete_interrupt()
    {
        IFCR.set_bit((channelNumber_ - 1) * 4 + 1);  // TODO: Magic numbers
    }

    Register IFCR;

    Register CCR;
    Register CNDTR;
    Register CPAR;
    Register CMAR;

    const uint8_t channelNumber_;

    std::function<void()> callback_;
};

#endif /* HAL_DMA_DMA_HPP_ */
