/**
 *  @file Register.hpp
 *
 *  @brief Wrapper for the Registers.
 *
 *  Created on: 16-11-2018
 *  @author: Paweł Warzecha
 */

#ifndef HAL_REGISTER_REGISTER_HPP_
#define HAL_REGISTER_REGISTER_HPP_

#include <stdint.h>

/**
 *  @brief Static class for operations on registers.
 *
 *  @details
 *  Class allows for the basic operations on the registers,
 *  such as changing value of field, getting its value and toggling
 *  bit in register.
 *
 */
class Register
{
public:
    /** Sets given values to register, without changing other values.
     *
     * @param u32Value Value to be written to the register
     * @param u8FielStartPosition Position in register from where to start writing the value
     * @param u8FieldBitLength Length in bits of the field to which the value is written.
     */
    void set_value(uint32_t u32Value, uint8_t u8FielStartPosition, uint8_t u8FieldBitLength = 1)
    {
        u32Register = ((u32Register & ~(get_mask(u8FieldBitLength) << (u8FielStartPosition))) | (u32Value << (u8FielStartPosition)));
    }

    /** Reads value from the register.
     *
     * @param u8FielStartPosition Position in register from where to start reading the value
     * @param u8FieldBitLength Length in bits of the field from which the value is read.
     *
     * @return Value of wanted field in register.
     */
    uint32_t get_value(uint8_t u8FielStartPosition, uint8_t u8FieldBitLength = 1)
    {
        return (u32Register & (get_mask(u8FieldBitLength) << (u8FielStartPosition)));
    }

    /** Toggles single bit in register.
     *
     * @param u8Position Position of bit to be toggled.
     */
    void toggle_bit(uint8_t u8Position)
    {
        u32Register ^= (1U << u8Position);
    }

    /** Sets single bit in register.
     *
     * @param u8Position Position of the bit to be toggled
     */
    void set_bit(uint8_t u8Position)
    {
        u32Register |= (1U << u8Position);
    }

    /** Clears sing;e bit in register.
     *
     * @param u8Position Position of the bit to be toggled
     */
    void clear_bit(uint8_t u8Position)
    {
        u32Register &= ~(1U << u8Position);
    }

    /**
     * @brief Writes data to register
     * @param value: value to be writen to register
     */
    void write(uint32_t value)
    {
        *reinterpret_cast<volatile uint32_t *>(&u32Register) = value;
    }

    /**
     * @brief Writes data to register
     * @param value: value to be writen to register
     */
    void write(uint16_t value)
    {
        *reinterpret_cast<volatile uint16_t *>(&u32Register) = value;
    }

    /**
     * @brief Writes data to register
     * @param value: value to be writen to register
     */
    void write(uint8_t value)
    {
        *reinterpret_cast<volatile uint8_t *>(&u32Register) = value;
    }

    /**
     * @brief Reads data from the register.
     * @return Register value.
     */
    uint32_t read(void)
    {
        return u32Register;
    }

    /// Constructor.
    explicit Register(volatile uint32_t & registerValue) : u32Register(registerValue)
    {
    }

protected:
private:
    /** Generates a bit mask.
     *
     * @param u8FieldBitLength length of the mask to be generated.
     *
     * @return mask of length @param u8FieldBitLength starting form LSB.
     */
    static uint32_t get_mask(uint8_t u8FieldBitLength)
    {
        uint32_t u32Mask = 0;

        while (u8FieldBitLength--)
            u32Mask = ((u32Mask << 1U) | 1U);

        return u32Mask;
    }

    /// Reference to register value.
    volatile uint32_t & u32Register;
};
#endif /* HAL_REGISTER_REGISTER_HPP_ */
