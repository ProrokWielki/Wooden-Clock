/**
 *  @file I2C.hpp
 *
 *  @brief Wrapper for the I2Cs.
 *
 *  Created on: 12-11-2018
 *  @author: Paweł Warzecha
 */

#ifndef HAL_I2C_I2C_HPP_
#define HAL_I2C_I2C_HPP_

#include <stdint.h>
#include <stm32l4xx.h>

#include "../Register/Register.hpp"

#include "../DMA/DMA.hpp"

#include "I2C_types.hpp"

constexpr static uint8_t DIGITAL_FILTER_FIELD_BIT_LENGTH = 4;
constexpr static uint8_t TRANSFER_SIZE_FIELD_BIT_LENGTH = 8;
constexpr static uint8_t DATA_FIELD_BIT_LENGTH = 8;
constexpr static uint8_t PRESCALER_FIELD_BIT_LENGTH = 4;
constexpr static uint8_t DATA_SETUP_FIELD_BIT_LENGTH = 4;
constexpr static uint8_t DATA_HOLD_FIELD_BIT_LENGT = 4;
constexpr static uint8_t SCL_HIGH_FIELD_BIT_LENGT = 8;
constexpr static uint8_t SCL_LOW_FIELD_BIT_LENGT = 8;

constexpr static uint8_t REGISTER_OFFSET_7BIT_ADDRESS = 1;
constexpr static uint8_t REGISTER_OFFSET_10BIT_ADDRESS = 0;

/**
 *  @brief Class for operations on I2Cs.
 *
 *  @details
 *  Class allows configuration and simple usage of the I2C.
 */
class I2C
{
public:
    /// Enables the I2C.
    void enable(void)
    {
        CR1.set_value(eEnable, I2C_CR1_PE_Pos);
    }
    /// Disables the I2C.
    void disable(void)
    {
        CR1.set_value(eDisable, I2C_CR1_PE_Pos);
    }

    /** Enables given interrupt.
     *
     * @param eI2CInterrupt The interrupt to be enabled.
     */
    void enable_interrupt(I2CInterrupts_t eI2CInterrupt)
    {
        CR1.set_value(eEnable, eI2CInterrupt);
    }
    /** Disables given interrupt.
     *
     * @param eI2CInterrupt The interrupt to be disabled.
     */
    void disable_interrupt(I2CInterrupts_t eI2CInterrupt)
    {
        CR1.set_value(eDisable, eI2CInterrupt);
    }

    /** Configures the digital filter.
     *
     * @param eI2CDigitalFilter Digital filter configuration.
     */
    void set_digital_filter(I2CDigitalFilter_t eI2CDigitalFilter)
    {
        CR1.set_value(eI2CDigitalFilter, I2C_CR1_DNF_Pos, DIGITAL_FILTER_FIELD_BIT_LENGTH);
    }

    /// enables analog filter.
    void enable_analog_filter(void)
    {
        CR1.set_value(eAnalogFilterEnable, I2C_CR1_ANFOFF_Pos);
    }
    /// disables analog filter.
    void disable_analog_filter(void)
    {
        CR1.set_value(eAnalogFilterDisable, I2C_CR1_ANFOFF_Pos);
    }

    /** Enables given DMA request.
     *
     * @param eI2CDMARequest DMA request type.
     */
    void enable_DMA_request(I2CDMARequest_t eI2CDMARequest)
    {
        CR1.set_value(eEnable, eI2CDMARequest);
    }
    /** Disables given DMA request.
     *
     * @param eI2CDMARequest DMA request type.
     */
    void disable_DMA_request(I2CDMARequest_t eI2CDMARequest)
    {
        CR1.set_value(eDisable, eI2CDMARequest);
    }

    /** Sets the slave address.
     *
     * @param u16SlaveAddress The slave address.
     * @param eI2CAdressLength Lenggth of the slave address.
     */
    void set_slave_address(uint16_t u16SlaveAddress, I2CAddressLength eI2CAdressLength)
    {
        if (eI2CAdressLength == e7bitAddress)
        {
            CR2.set_value(u16SlaveAddress, REGISTER_OFFSET_7BIT_ADDRESS, eI2CAdressLength);
            CR2.set_value(eDisable, I2C_CR2_ADD10_Pos);
        }
        else
        {
            CR2.set_value(u16SlaveAddress, REGISTER_OFFSET_10BIT_ADDRESS, eI2CAdressLength);
            CR2.set_value(eEnable, I2C_CR2_ADD10_Pos);
        }
    }

    /** Writes the data to the slave.
     *
     * @param pu8Data Pointer to the data to be sent.
     * @param u16NumberOfBytes Number of the bytes to be sent
     */
    void write_data(uint8_t * pu8Data, uint16_t u16NumberOfBytes)
    {
        uint8_t u8TransferSize;

        while (u16NumberOfBytes > 0)
        {
            if (u16NumberOfBytes > 255)
            {
                u8TransferSize = 255;
                enable_option(eReload);
            }
            else
            {
                u8TransferSize = u16NumberOfBytes;
                disable_option(eReload);
            }

            u16NumberOfBytes -= u8TransferSize;

            set_transfer_size(u8TransferSize);
            enable_option(eAutoEnd);

            set_data_to_be_send(*(pu8Data++));
            u8TransferSize--;

            start_transfer();

            while (u8TransferSize-- > 0)
            {
                while (false == is_transfer_completed())
                    ;
                set_data_to_be_send(*(pu8Data++));
            }
        }
    }

    /**
     * @brief  Writes the data to the slave, using DMA.
     *
     * @param pu8Data Pointer to the data to be sent.
     * @param u16NumberOfBytes Number of the bytes to be sent.
     */
    void write_data_DMA(uint8_t * data, uint16_t numberOfBytes)
    {
        dma_->enable_memory_increment();
        dma_->set_memory_address(reinterpret_cast<uint32_t>(data));
        dma_->set_periphearl_address(addressTXDR);
        dma_->set_read_direction(eReadFromMemory);
        dma_->set_memory_size(e8Bits);
        dma_->set_peripheral_size(e8Bits);
        dma_->set_transfer_size(numberOfBytes);

        set_transfer_size(numberOfBytes);
        start_transfer();

        enable_DMA_request(eDMATransmitRequest);
        dma_->enable();
    }

    void read_data(uint8_t * pu8Data, uint16_t u8NumOfBytes);  // TODO: implement

    /**
     * @brief Sets I2C timing.
     *
     * @param u8Prescaler Clock prescaler.
     * @param u8DataSetup
     * @param u8DataHold
     * @param u8SCLHigh
     * @param u8SCLLow
     */
    void set_timing(uint8_t u8Prescaler, uint8_t u8DataSetup, uint8_t u8DataHold, uint8_t u8SCLHigh, uint8_t u8SCLLow)
    {
        TIMINGR.set_value(u8Prescaler, I2C_TIMINGR_PRESC_Pos, PRESCALER_FIELD_BIT_LENGTH);
        TIMINGR.set_value(u8DataSetup, I2C_TIMINGR_SCLDEL_Pos, DATA_SETUP_FIELD_BIT_LENGTH);
        TIMINGR.set_value(u8DataHold, I2C_TIMINGR_SDADEL_Pos, DATA_HOLD_FIELD_BIT_LENGT);
        TIMINGR.set_value(u8SCLHigh, I2C_TIMINGR_SCLH_Pos, SCL_HIGH_FIELD_BIT_LENGT);
        TIMINGR.set_value(u8SCLLow, I2C_TIMINGR_SCLL_Pos, SCL_LOW_FIELD_BIT_LENGT);
    }

    DMA * get_DMA(void)
    {
        return dma_;
    }

    /// Constructor.
    I2C(I2C_TypeDef * i2c, DMA * dma = nullptr)
    : CR1(i2c->CR1), CR2(i2c->CR2), ICR(i2c->ICR), ISR(i2c->ISR), OAR1(i2c->OAR1), OAR2(i2c->OAR2), PECR(i2c->PECR), RXDR(i2c->RXDR), TIMEOUTR(i2c->TIMEOUTR),
      TIMINGR(i2c->TIMINGR), TXDR(i2c->TXDR), dma_(dma), addressTXDR(reinterpret_cast<uint32_t>(&(i2c->TXDR)))
    {
    }

protected:
private:
    bool is_transfer_completed(void)
    {
        return ISR.get_value(I2C_ISR_TXIS_Pos);
    }

    void set_transfer_size(uint8_t u8TransferSize)
    {
        CR2.set_value(u8TransferSize, I2C_CR2_NBYTES_Pos, TRANSFER_SIZE_FIELD_BIT_LENGTH);
    }

    void set_data_to_be_send(uint8_t u8DataToSend)
    {
        TXDR.set_value(u8DataToSend, I2C_TXDR_TXDATA_Pos, DATA_FIELD_BIT_LENGTH);
    }

    void enable_option(I2COptions eI2COption)
    {
        CR2.set_value(eEnable, eI2COption);
    }
    void disable_option(I2COptions eI2COption)
    {
        CR2.set_value(eDisable, eI2COption);
    }

    void start_transfer()
    {
        CR2.set_bit(I2C_CR2_START_Pos);
    }
    void stop_transfer()
    {
        CR2.set_bit(I2C_CR2_STOP_Pos);
    }

    Register CR1;
    Register CR2;
    Register ICR;
    Register ISR;
    Register OAR1;
    Register OAR2;
    Register PECR;
    Register RXDR;
    Register TIMEOUTR;
    Register TIMINGR;
    Register TXDR;

    DMA * dma_;

    uint32_t addressTXDR;
};

#endif /* HAL_I2C_I2C_HPP_ */
