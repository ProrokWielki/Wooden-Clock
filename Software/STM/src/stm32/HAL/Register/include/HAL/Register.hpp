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

#include <cstdint>
#include <utility>

/**
 *  @brief Static class for operations on registers.
 *
 *  @details
 *  Class allows for the basic operations on the registers,
 *  such as changing value of field, getting its value and toggling
 *  bit in register.
 *
 */
template<typename T>
class Register
{
public:
    /// Constructor.
    explicit Register(volatile T * const register_address) : register_{register_address}
    {
    }

    explicit Register(T && register_value) : register_value_{std::move(register_value)}, register_{&register_value_}
    {
    }

    /** Sets given values to register, without changing other values.
     *
     * @param u32Value Value to be written to the register
     * @param u8FielStartPosition Position in register from where to start writing the value
     * @param u8FieldBitLength Length in bits of the field to which the value is written.
     */
    void set_value(T value, uint8_t u8FielStartPosition, uint8_t u8FieldBitLength)
    {
        const uint32_t masked_value = value & get_mask(u8FieldBitLength);
        const uint32_t register_value_with_cleared_bits_to_set = (*register_) & ~(get_mask(u8FieldBitLength) << u8FielStartPosition);
        *register_ = register_value_with_cleared_bits_to_set | (masked_value << u8FielStartPosition);
    }

    /** Reads value from the register.
     *
     * @param u8FielStartPosition Position in register from where to start reading the value
     * @param u8FieldBitLength Length in bits of the field from which the value is read.
     *
     * @return Value of wanted field in register.
     */
    [[nodiscard]] T get_value(uint8_t u8FielStartPosition, uint8_t u8FieldBitLength) const
    {
        const T register_value = *register_;
        const T value_mask = get_mask(u8FieldBitLength) << u8FielStartPosition;

        return (register_value & value_mask) >> u8FielStartPosition;
    }

    /** Toggles single bit in register.
     *
     * @param u8Position Position of bit to be toggled.
     */
    void toggle_bit(uint8_t u8Position)
    {
        *register_ ^= (1U << u8Position);
    }

    /** Sets single bit in register.
     *
     * @param u8Position Position of the bit to be set
     */
    void set_bit(uint8_t u8Position)
    {
        *register_ |= (1U << u8Position);
    }

    /** Clears single bit in register.
     *
     * @param u8Position Position of the bit to be cleared
     */
    void clear_bit(uint8_t u8Position)
    {
        *register_ &= ~(1U << u8Position);
    }

    /** Sets value of the single bit in the register.
     *
     * @param position Position of the bit to be changed
     * @param value Value to be set.
     */
    void set_bit_value(bool value, uint8_t position)
    {
        if (value)
        {
            set_bit(position);
        }
        else
        {
            clear_bit(position);
        }
    }

    /**
     * @brief Get bit from the register
     *
     * @param u8Position bit position
     * @return bit value
     */
    [[nodiscard]] uint8_t get_bit(uint8_t u8Position) const
    {
        return ((*register_ & (1 << u8Position)) >> u8Position);
    }

    /**
     * @brief Writes data to register
     * @param value: value to be written to register
     */
    void write(T value)
    {
        *register_ = value;
    }

    /**
     * @brief Writes data to register
     * @param value: value to be written to register
     */
    void write_u8(uint8_t value)
    {
        *(volatile uint8_t * const)register_ = value;
    }

    /**
     * @brief Reads data from the register.
     * @return Register value.
     */
    [[nodiscard]] T read() const
    {
        return *register_;
    }

    [[nodiscard]] uintptr_t get_address() const
    {
        return reinterpret_cast<uintptr_t>(register_);  // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
    }

private:
    /** Generates a bit mask.
     *
     * @param u8FieldBitLength length of the mask to be generated.
     *
     * @return mask of length @param u8FieldBitLength starting form LSB.
     */
    static T get_mask(uint8_t u8FieldBitLength)
    {
        // ex. length == 2 -->  1<<2 = 0b100 --> 0b100-1 = 0b011 NICE!
        return (1UL << u8FieldBitLength) - 1UL;
    }

    /// register value, only used if rvalue refenence constructor is used.
    T register_value_{};

    /// Pointer to register value.
    volatile T * const register_{};
};
#endif /* HAL_REGISTER_REGISTER_HPP_ */
