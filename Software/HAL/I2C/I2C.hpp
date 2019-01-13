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

#include "I2C_types.hpp"

constexpr static uint8_t DIGITAL_FILTER_FIELD_BIT_LENGTH = 4;
constexpr static uint8_t TRANSFER_SIZE_FIELD_BIT_LENGTH = 8;
constexpr static uint8_t DATA_FIELD_BIT_LENGTH = 8;

constexpr static uint8_t REGISTER_OFFSET_7BIT_ADDRESS = 1;
constexpr static uint8_t REGISTER_OFFSET_10BIT_ADDRESS = 0;

/**
 *  @brief Static class for operations on I2Cs.
 *
 *  @details
 *  Class allows configuration and simple usage of the I2C.
 *
 *  The class is static, it has a private constructor and can't be instantiated.
 *
 *  @tparam I2C_ADDRESS address of the I2C.
 */
template<const uint32_t I2C_ADDRESS>
class I2C
{
public:
  ///Enables the I2C.
  static void enable(void)
  {
    CR1::set_value(eEnable, I2C_CR1_PE_Pos);
  }
  ///Disables the I2C.
  static void disable(void)
  {
    CR1::set_value(eDisable, I2C_CR1_PE_Pos);
  }

  /** Enables given interrupt.
   *
   * @param eI2CInterrupt The interrupt to be enabled.
   */
  static void enable_interrupt(I2CInterrupts_t eI2CInterrupt)
  {
    CR1::set_value(eEnable, eI2CInterrupt);
  }
  /** Disables given interrupt.
   *
   * @param eI2CInterrupt The interrupt to be disabled.
   */
  static void disable_interrupt(I2CInterrupts_t eI2CInterrupt)
  {
    CR1::set_value(eDisable, eI2CInterrupt);
  }

  /** Configures the digital filter.
   *
   * @param eI2CDigitalFilter Digital filter configuration.
   */
  static void set_digital_filter(I2CDigitalFilter_t eI2CDigitalFilter)
  {
    CR1::set_value(eI2CDigitalFilter, I2C_CR1_DNF_Pos, DIGITAL_FILTER_FIELD_BIT_LENGTH);
  }

  /// enables analog filter.
  static void enable_analog_filter(void)
  {
	  CR1::set_value(eAnalogFilterEnable, I2C_CR1_ANFOFF_Pos);
  }
  /// disables analog filter.
  static void disable_analog_filter(void)
  {
    CR1::set_value(eAnalogFilterDisable, I2C_CR1_ANFOFF_Pos);
  }

  /** Enables given DMA request.
   *
   * @param eI2CDMARequest DMA request type.
   */
  static void enable_DMA_request(I2CDMARequest_t eI2CDMARequest)
    {
      CR1::set_value(eEnable, eI2CDMARequest);
    }
  /** Disables given DMA request.
   *
   * @param eI2CDMARequest DMA request type.
   */
  static void disable_DMA_request(I2CDMARequest_t eI2CDMARequest)
    {
      CR1::set_value(eDisable, eI2CDMARequest);
    }

  /** Sets the slave address.
   *
   * @param u16SlaveAddress The slave address.
   * @param eI2CAdressLength Lenggth of the slave address.
   */
  static void set_slave_address(uint16_t  u16SlaveAddress, I2CAddressLength eI2CAdressLength)
  {
    if(eI2CAdressLength == e7bitAddress)
      {
        CR2::set_value(u16SlaveAddress,  REGISTER_OFFSET_7BIT_ADDRESS, eI2CAdressLength);
        CR2::set_value(eDisable, I2C_CR2_ADD10_Pos);
      }
    else
      {
       CR2::set_value(u16SlaveAddress,  REGISTER_OFFSET_10BIT_ADDRESS, eI2CAdressLength);
       CR2::set_value(eEnable, I2C_CR2_ADD10_Pos);
      }
  }

  /** Writes the data to the slave.
   *
   * @param pu8Data Pointer to the data to be sent.
   * @param u16NumberOfBytes Number of the bytes to be sent
   */
  static void write_data(uint8_t * pu8Data, uint16_t u16NumberOfBytes)
  {
    uint8_t u8TransferSize;

    while(u16NumberOfBytes > 0)
    {
      if(u16NumberOfBytes > 255)
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
        while(false == is_transfer_completed());
        set_data_to_be_send(*(pu8Data++));
      }
    }
  }

  void read_data(uint8_t * pu8Data, uint16_t u8NumOfBytes);  //TODO: implement

  void set_timing(uint8_t u8Prescaler, uint8_t u8DataSetup, uint8_t u8DataHold, uint8_t u8SCLHigh, uint8_t u8SCLLow); //TODO: implement

protected:

private:

  /// Constructor, it is private so the class can't be instantiated.
  I2C(){}

  static bool is_transfer_completed(void)
  {
    return ISR::get_value(I2C_ISR_TXIS_Pos);
  }

  static void set_transfer_size(uint8_t u8TransferSize)
  {
    CR2::set_value(u8TransferSize, I2C_CR2_NBYTES_Pos, TRANSFER_SIZE_FIELD_BIT_LENGTH);
  }

  static void set_data_to_be_send(uint8_t u8DataToSend)
  {
    TXDR::set_value(u8DataToSend, I2C_TXDR_TXDATA_Pos, DATA_FIELD_BIT_LENGTH);
  }

  static void enable_option(I2COptions eI2COption)
  {
    CR2::set_value(eEnable, eI2COption);
  }
  static void disable_option(I2COptions eI2COption)
  {
    CR2::set_value(eDisable, eI2COption);
  }

  static void start_transfer()
  {
    CR2::set_bit(I2C_CR2_START_Pos);
  }
  static void stop_transfer()
  {
    CR2::set_bit(I2C_CR2_START_Pos);
  }

	constexpr volatile static uint32_t adrCR1      = (uint32_t)(&(((I2C_TypeDef *) I2C_ADDRESS)->CR1));
	constexpr volatile static uint32_t adrCR2      = (uint32_t)(&(((I2C_TypeDef *) I2C_ADDRESS)->CR2));
	constexpr volatile static uint32_t adrICR      = (uint32_t)(&(((I2C_TypeDef *) I2C_ADDRESS)->ICR));
	constexpr volatile static uint32_t adrISR      = (uint32_t)(&(((I2C_TypeDef *) I2C_ADDRESS)->ISR));
	constexpr volatile static uint32_t adrOAR1     = (uint32_t)(&(((I2C_TypeDef *) I2C_ADDRESS)->OAR1));
	constexpr volatile static uint32_t adrOAR2     = (uint32_t)(&(((I2C_TypeDef *) I2C_ADDRESS)->OAR2));
	constexpr volatile static uint32_t adrPECR     = (uint32_t)(&(((I2C_TypeDef *) I2C_ADDRESS)->PECR));
	constexpr volatile static uint32_t adrRXDR     = (uint32_t)(&(((I2C_TypeDef *) I2C_ADDRESS)->RXDR));
	constexpr volatile static uint32_t adrTIMEOUTR = (uint32_t)(&(((I2C_TypeDef *) I2C_ADDRESS)->TIMEOUTR));
	constexpr volatile static uint32_t adrTIMINGR  = (uint32_t)(&(((I2C_TypeDef *) I2C_ADDRESS)->TIMINGR));
	constexpr volatile static uint32_t adrTXDR     = (uint32_t)(&(((I2C_TypeDef *) I2C_ADDRESS)->TXDR));

	typedef Register<adrCR1>      CR1;
	typedef Register<adrCR2>      CR2;
	typedef Register<adrICR>      ICR;
	typedef Register<adrISR>      ISR;
	typedef Register<adrOAR1>     OAR1;
	typedef Register<adrOAR2>     OAR2;
	typedef Register<adrPECR>     PECR;
	typedef Register<adrRXDR>     RXDR;
	typedef Register<adrTIMEOUTR> TIMEOUTR;
	typedef Register<adrTIMINGR>  TIMINGR;
	typedef Register<adrTXDR>     TXDR;
};


#endif /* HAL_I2C_I2C_HPP_ */
