/**
 * SPI_types.hpp
 *
 *  Created on: 28-04-2019
 *  @author: Paweł Warzecha
 */

#ifndef HAL_SPI_SPI_TYPES_HPP_
#define HAL_SPI_SPI_TYPES_HPP_

enum class SPIPprescaler : uint8_t
{
    _2 = 0,
    _4 = 1,
    _8 = 2,
    _16 = 3,
    _32 = 4,
    _64 = 5,
    _128 = 6,
    _256 = 7
};

enum class SPIForamt : uint8_t
{
    MSB_first,
    LSB_first
};

enum class SPIMode : uint8_t
{
    slave,
    master
};

enum class SPIPolarity : uint8_t
{
    idle_low,
    idle_high
};

enum class SPIPhase : uint8_t
{
    data_on_first_edge,
    data_on_second_edge
};

enum class SPIDataSize : uint8_t
{
    _4bits = 3,
    _5bits = 4,
    _6bits = 5,
    _7bits = 6,
    _8bits = 7,
    _9bits = 8,
    _10bits = 9,
    _11bits = 10,
    _12bits = 11,
    _13bits = 12,
    _14bits = 13,
    _15bits = 14,
    _16bits = 15
};

#endif /* HAL_SPI_SPI_TYPES_HPP_ */
