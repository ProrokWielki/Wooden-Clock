/*
 * Register.hpp
 *
 *  Created on: 16-11-2018
 *      Author: Pawe³ Warzecha
 */

#ifndef HAL_REGISTER_REGISTER_HPP_
#define HAL_REGISTER_REGISTER_HPP_

#include <stdint.h>

template<const uint32_t REGISTER_ADDRESS, uint8_t FIELD_BIT_LENGTH>
class Register
{
public:
	static void set_value(uint32_t u32Value, uint8_t u8FieldNumber)
	{
		u32Register = ( (u32Register & ~(get_mask() << (u8FieldNumber * FIELD_BIT_LENGTH))) | (u32Value << (u8FieldNumber * FIELD_BIT_LENGTH)) );
	}

	static uint32_t get_value(uint8_t u8FieldNumber)
	{
		return (u32Register & (get_mask() << (u8FieldNumber * FIELD_BIT_LENGTH)));
	}

	static void toggle_bit(uint32_t u8Position)
	{
		u32Register ^= (1U << u8Position);
	}
protected:

private:
	Register(){}

	static uint32_t get_mask()
	{
		uint32_t u32Mask = 0;
		uint8_t iterator = FIELD_BIT_LENGTH;

		while(iterator--)
			u32Mask = ((u32Mask << 1U) | 1U);

		return u32Mask;
	}

	static uint32_t & u32Register;

};

template<const uint32_t REGISTER_ADDRESS, uint8_t FIELD_BIT_LENGTH>
	uint32_t & Register<REGISTER_ADDRESS, FIELD_BIT_LENGTH>::u32Register = *((uint32_t *)REGISTER_ADDRESS);

#endif /* HAL_REGISTER_REGISTER_HPP_ */
