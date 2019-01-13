/**
  *  @file I2C_types.hpp
  *
  *  @brief Contains enumerators for the I2C class.
  *
  *  Created on: 22-11-2018
  *  @author: Paweł Warzecha
  */

#ifndef HAL_I2C_I2C_TYPES_HPP_
#define HAL_I2C_I2C_TYPES_HPP_

#include <stm32l4xx.h>

/// Enumerator for the I2C state.
typedef enum
{
  eDisable = 0, /// I2C disabled.
  eEnable = 1   /// I2C enabled.

}I2CEnableDisable_t;

/// Enumerator for the I2C interrupts
typedef enum
{
  eTransmitInterrupt = I2C_CR1_TXIE_Pos,          ///< Transmit interrupt.
  eReceiveInterrupt  = I2C_CR1_RXIE_Pos,          ///< Receive interrupt.
  eAddressMatchInterrupt = I2C_CR1_ADDRIE_Pos,    ///< Address match interrupt.
  eNAKReceivedInterrupt = I2C_CR1_NACKIE_Pos,     ///< NAK received interrupt.
  eSTOPDetectedInterrupt = I2C_CR1_STOPIE_Pos,    ///< Stop detected interrupt.
  eTransferCompletedInterrupt = I2C_CR1_TCIE_Pos, ///< Transfer complete interrupt.
  eErrorDetectedInterrupt = I2C_CR1_ERRIE_Pos     ///< Error detected interrupt.

}I2CInterrupts_t;

typedef enum
{
  eDigitalFilterDisabled = 0, ///< Digital filter disabled
  eDigitalFilter1CLK  = 1,    ///< Digital filter set to 1 clock.
  eDigitalFilter2CLK = 2,     ///< Digital filter set to 2 clocks.
  eDigitalFilter3CLK = 3,     ///< Digital filter set to 3 clocks.
  eDigitalFilter4CLK = 4,     ///< Digital filter set to 4 clocks.
  eDigitalFilter5CLK = 5,     ///< Digital filter set to 5 clocks.
  eDigitalFilter6CLK = 6,     ///< Digital filter set to 6 clocks.
  eDigitalFilter7CLK = 7,     ///< Digital filter set to 7 clocks.
  eDigitalFilter8CLK = 8,     ///< Digital filter set to 8 clocks.
  eDigitalFilter9CLK = 9,     ///< Digital filter set to 9 clocks.
  eDigitalFilter10CLK = 10,   ///< Digital filter set to 10 clocks.
  eDigitalFilter11CLK = 11,   ///< Digital filter set to 11 clocks.
  eDigitalFilter12CLK = 12,   ///< Digital filter set to 12 clocks.
  eDigitalFilter13CLK = 13,   ///< Digital filter set to 13 clocks.
  eDigitalFilter14CLK = 14,   ///< Digital filter set to 14 clocks.
  eDigitalFilter15CLK = 15,   ///< Digital filter set to 15 clocks.

}I2CDigitalFilter_t;

/// Enumerates analog filter state.
typedef enum
{
	eAnalogFilterEnable = 0, ///< Analog filter enabled.
  eAnalogFilterDisable =1  ///< Analog filter disabled.

}I2CAnalogFilter_t;

/// Enumerates DMA requests
typedef enum
{
  eDMATransmitRequest = I2C_CR1_TXDMAEN_Pos, ///< DMA transmit request.
  eDMAReceiveRequest = I2C_CR1_RXDMAEN_Pos   ///< DMA receive request.

}I2CDMARequest_t;

/// Enumerates I2C address length
typedef enum
{
  e7bitAddress = 7,  ///< 7 bit long address
  e10bitAddress = 10 ///< 10 bit long address

}I2CAddressLength;

/// Enumerates I2C options
typedef enum
{
 eAutoEnd = I2C_CR2_AUTOEND_Pos, ///< Auto end option
 eReload = I2C_CR2_RELOAD_Pos    ///< Reload option
}I2COptions;

#endif /* HAL_I2C_I2C_TYPES_HPP_ */
