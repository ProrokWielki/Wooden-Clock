/**
 * SPI.hpp
 *
 *  Created on: 28-04-2019
 *  @author: Paweł Warzecha
 */

#ifndef HAL_SPI_SPI_HPP_
#define HAL_SPI_SPI_HPP_

#include <stdint.h>
#include <stm32l4xx.h>

#include "../Register/Register.hpp"

#include "SPI_types.hpp"

class SPI
{
public:
    explicit SPI(SPI_TypeDef * spi) : CR1(spi->CR1), CR2(spi->CR2), SR(spi->SR), DR(spi->DR), CRCPR(spi->CRCPR), RXCRCR(spi->RXCRCR), TXCRCR(spi->TXCRCR)
    {
    }

    void enable()
    {
        CR1.set_bit(SPI_CR1_SPE_Pos);
    }

    void disable()
    {
        CR1.clear_bit(SPI_CR1_SPE_Pos);
    }

    void set_prescaler(SPIPprescaler prescaler)
    {
        CR1.set_value(static_cast<uint8_t>(prescaler), SPI_CR1_BR_Pos, 3);
    }

    void configure(SPIMode mode, SPIDataSize data_size, SPIPolarity polarity, SPIPhase phase, SPIForamt format)
    {
        set_mode(mode);
        set_polarity(polarity);
        set_phase(phase);
        set_format(format);
        CR1.set_value(7, SPI_CR1_BR_Pos, 3);
        CR1.set_bit(SPI_CR1_SSI_Pos);

        set_data_size(data_size);
        CR2.set_bit(SPI_CR2_SSOE_Pos);
        CR2.set_bit(SPI_CR2_FRXTH_Pos);
    }

    void set_mode(SPIMode mode)
    {
        CR1.set_value(static_cast<uint8_t>(mode), SPI_CR1_MSTR_Pos);
    }

    void set_polarity(SPIPolarity polarity)
    {
        CR1.set_value(static_cast<uint8_t>(polarity), SPI_CR1_CPOL_Pos);
    }

    void set_phase(SPIPhase phase)
    {
        CR1.set_value(static_cast<uint8_t>(phase), SPI_CR1_CPHA_Pos);
    }

    void set_format(SPIForamt format)
    {
        CR1.set_value(static_cast<uint8_t>(format), SPI_CR1_LSBFIRST_Pos);
    }

    void set_data_size(SPIDataSize data_size)
    {
        CR2.set_value(static_cast<uint8_t>(data_size), SPI_CR2_DS_Pos, 4);
    }

    uint8_t exchange_data(uint8_t value_to_send)
    {
        enable();

        while (not SR.get_value(SPI_SR_TXE_Pos, 1))
            ;

        DR.write(value_to_send);

        while (not SR.get_value(SPI_SR_RXNE_Pos, 1))
            ;

        while (SR.get_value(SPI_SR_BSY_Pos, 1))
            ;
        disable();

        return DR.read();
    }

private:
    Register CR1;
    Register CR2;
    Register SR;
    Register DR;
    Register CRCPR;
    Register RXCRCR;
    Register TXCRCR;
};

#endif /* HAL_SPI_SPI_HPP_ */
