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

#include <cstdint>
#include <span>

#include <HAL/Register.hpp>
#include <HAL/types.hpp>

class DMA;
class Clock;
class GPIO;

/**
 *  @brief Class for operations on I2Cs.
 *
 *  @details
 *  Class allows configuration and simple usage of the I2C.
 */
class I2C
{
public:
    /// Constructor.
    I2C(Clock & clock, I2C_Types::I2CNumber i2c, GPIO & scl, GPIO & sda, double frequency, DMA * dma = nullptr);

    /// Enables the I2C.
    void enable();

    /// Disables the I2C.
    void disable();

    /** Enables given interrupt.
     *
     * @param interrupt The interrupt to be enabled.
     */
    void enable_interrupt(I2C_Types::Interrupt interrupt);

    /** Disables given interrupt.
     *
     * @param interrupt The interrupt to be disabled.
     */
    void disable_interrupt(I2C_Types::Interrupt interrupt);

    /** Configures the digital filter.
     *
     * @param eI2CDigitalFilter Digital filter configuration.
     */
    void set_digital_filter(I2C_Types::DigitalFilter digital_filter);

    /// enables analog filter.
    void enable_analog_filter();

    /// disables analog filter.
    void disable_analog_filter();

    /** Enables given DMA request.
     *
     * @param dma_request DMA request type.
     */
    void enable_DMA_request(I2C_Types::DMARequest dma_request);

    /** Disables given DMA request.
     *
     * @param dma_request DMA request type.
     */
    void disable_DMA_request(I2C_Types::DMARequest dma_request);

    /** Sets the slave address.
     *
     * @param slave_address The slave address.
     * @param adress_length Lenggth of the slave address.
     */
    void set_slave_address(uint16_t slave_address, I2C_Types::AddressLength adress_length);

    /** Writes the data to the slave.
     *
     * @param pu8Data Pointer to the data to be sent.
     * @param u16NumberOfBytes Number of the bytes to be sent
     */
    void write_data(std::span<uint8_t> data);

    /**
     * @brief  Writes the data to the slave, using DMA.
     *
     * @param pu8Data Pointer to the data to be sent.
     * @param u16NumberOfBytes Number of the bytes to be sent.
     */
    void write_data_DMA(uint8_t * data, uint16_t numberOfBytes);

    void read_data(std::span<uint8_t> & received_data, uint16_t num_of_bytes_to_read);

    void read_data_from_register(uint8_t register_address, std::span<uint8_t> & received_data, uint16_t num_of_bytes_to_read);

    void set_frequency(double frequency);

    DMA * get_DMA();

protected:
private:
    bool is_transfer_completed();
    bool is_data_received();

    void set_transfer_size(uint8_t u8TransferSize);

    void set_data_to_be_send(uint8_t u8DataToSend);

    void enable_option(I2C_Types::Option option);

    void disable_option(I2C_Types::Option option);

    void start_transfer();

    void stop_transfer();

    void set_transfer_direction(I2C_Types::TransferDirection direction);

    void set_timing(uint8_t u8Prescaler, uint8_t u8DataSetup, uint8_t u8DataHold, uint8_t u8SCLHigh, uint8_t u8SCLLow);

    Register<uint32_t> CR1;
    Register<uint32_t> CR2;
    Register<uint32_t> ICR;
    Register<uint32_t> ISR;
    Register<uint32_t> OAR1;
    Register<uint32_t> OAR2;
    Register<uint32_t> PECR;
    Register<uint32_t> RXDR;
    Register<uint32_t> TIMEOUTR;
    Register<uint32_t> TIMINGR;
    Register<uint32_t> TXDR;

    DMA * dma_;

    // uint32_t addressTXDR;
};

#endif /* HAL_I2C_I2C_HPP_ */
