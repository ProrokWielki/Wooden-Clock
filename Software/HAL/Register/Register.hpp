/**
  *  @file Register.hpp
  *
  *  @brief Wrapper for the Registers.
  *
  *  Created on: 16-11-2018
  *  @author: Paweł Warzecha
  */

/**
 *  @brief Static class for operations on registers.
 *
 *  @details
 *  Class allows for the basic operations on the registers,
 *  such as changing value of field, getting its value and toggling
 *  bit in register.
 *
 *  The class is static, it has a private constructor and can't be instantiated.
 *
 *  @tparam REGISTER_ADDRESS address of the register
 */

#ifndef HAL_REGISTER_REGISTER_HPP_
#define HAL_REGISTER_REGISTER_HPP_

#include <stdint.h>

template<const uint32_t REGISTER_ADDRESS>
  class Register
  {
  public:

    /** Sets given values to register, without changing other values.
     *
     * @param u32Value Value to be written to the register
     * @param u8FielStartPosition Position in register from where to start writing the value
     * @param u8FieldBitLength Length in bits of the field to which the value is written.
     */
    static void set_value(uint32_t u32Value, uint8_t u8FielStartPosition, uint8_t u8FieldBitLength = 1)
    {
      u32Register = ( ( u32Register & ~( get_mask(u8FieldBitLength) << ( u8FielStartPosition) ) )
                    | ( u32Value << ( u8FielStartPosition) ) );
    }

    /** Reads value from the register.
     *
     * @param u8FielStartPosition Position in register from where to start reading the value
     * @param u8FieldBitLength Length in bits of the field from which the value is read.
     *
     * @return Value of wanted field in register.
     */
    static uint32_t get_value(uint8_t u8FielStartPosition, uint8_t u8FieldBitLength = 1)
    {
      return ( u32Register & ( get_mask(u8FieldBitLength) << ( u8FielStartPosition) ) );
    }

    /** Toggles single bit in register.
     *
     * @param u8Position Position of bit to be toggled.
     */
    static void toggle_bit(uint8_t u8Position)
    {
      u32Register ^= ( 1U << u8Position );
    }

    static void set_bit(uint8_t u8Position)
    {
      u32Register |= ( 1U << u8Position );
    }

    static void clear_bit(uint8_t u8Position)
    {
      u32Register &= ~( 1U << u8Position );
    }

  protected:

  private:

    /// Constructor, it is private so the class can't be instantiated.
    Register(){}

    /** Generates a bit mask.
     *
     * @param u8FieldBitLength length of the mask to be generated.
     *
     * @return mask of length @param u8FieldBitLength starting form LSB.
     */
    static uint32_t get_mask(uint8_t u8FieldBitLength)
    {
      uint32_t u32Mask = 0;

      while(u8FieldBitLength--)
        u32Mask = ( ( u32Mask << 1U ) | 1U );

      return u32Mask;
    }

    /// Reference to register value.
    static uint32_t & u32Register;

  };

template<const uint32_t REGISTER_ADDRESS>
  uint32_t & Register<REGISTER_ADDRESS>::u32Register = *( (uint32_t *)REGISTER_ADDRESS );

#endif /* HAL_REGISTER_REGISTER_HPP_ */
