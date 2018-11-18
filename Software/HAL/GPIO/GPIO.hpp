/*
 * GPIO.hpp
 *
 *  Created on: 13-11-2018
 *      Author: Pawe³ Warzecha
 */

#ifndef HAL_GPIO_GPIO_HPP_
#define HAL_GPIO_GPIO_HPP_

#include <stdint.h>

#include <stm32l4xx.h>


#include "../Register/Register.hpp"
#include "GPIO_types.hpp"


constexpr static uint8_t MODER_FIELD_BIT_LENGTH   = 2;
constexpr static uint8_t OTYPER_FIELD_BIT_LENGTH  = 1;
constexpr static uint8_t OSPEEDR_FIELD_BIT_LENGTH = 2;
constexpr static uint8_t PUPDR_FIELD_BIT_LENGTH   = 2;
constexpr static uint8_t IDR_FIELD_BIT_LENGTH     = 1;
constexpr static uint8_t ODR_FIELD_BIT_LENGTH     = 1;
constexpr static uint8_t AFR_FIELD_BIT_LENGTH     = 4;

constexpr static uint8_t AFRH_START_FIELD = 8;


template<const uint32_t PORT, uint8_t PIN>
class GPIO
{
public:
	static void set_mode(PortMode_t ePortMode)
	{
		MODER::set_value(ePortMode, PIN);
	}
	static void set_output_type(PortOutputType_t ePortOutputType)
	{
		OTYPER::set_value(ePortOutputType, PIN);
	}
	static void set_speed(PortOutputSpeed_t ePortOutputSpeed)
	{
		OSPEEDR::set_value(ePortOutputSpeed, PIN);
	}
	static void set_pullUp_pullDown(PortPullUpPullDown_t ePortPullUpPullDown)
	{
		PUPDR::set_value(ePortPullUpPullDown, PIN);
	}
	static void set_alternate_function(AlteranteFunction_t u8AlternateFunction)
	{
		if(PIN >= 8)
		{
			AFRH::set_value(u8AlternateFunction, PIN - AFRH_START_FIELD);
		}
		else
		{
			AFRL::set_value(u8AlternateFunction, PIN);
		}
	}

	static void set_output_value(SignalLevel_t eSignalLevel)
	{
		ODR::set_value(eSignalLevel, PIN);
	}
	static void toogle_output_value(void)
	{
		ODR::toggle_bit(PIN);
	}

	static SignalLevel_t get_input_value()
	{
		return IDR::get_value(PIN);
	}

protected:

private:

	constexpr volatile static uint32_t up32MODER   = (uint32_t)(&(((GPIO_TypeDef *) PORT)->MODER));
	constexpr volatile static uint32_t up32OTYPER  = (uint32_t)(&(((GPIO_TypeDef *) PORT)->OTYPER));
	constexpr volatile static uint32_t up32OSPEEDR = (uint32_t)(&(((GPIO_TypeDef *) PORT)->OSPEEDR));
	constexpr volatile static uint32_t up32PUPDR   = (uint32_t)(&(((GPIO_TypeDef *) PORT)->PUPDR));
	constexpr volatile static uint32_t up32AFRL    = (uint32_t)(&(((GPIO_TypeDef *) PORT)->AFR[0]));
	constexpr volatile static uint32_t up32AFRH    = (uint32_t)(&(((GPIO_TypeDef *) PORT)->AFR[1]));
	constexpr volatile static uint32_t up32ODR     = (uint32_t)(&(((GPIO_TypeDef *) PORT)->ODR));
	constexpr volatile static uint32_t up32IDR     = (uint32_t)(&(((GPIO_TypeDef *) PORT)->IDR));

	typedef Register<up32MODER,   MODER_FIELD_BIT_LENGTH>   MODER;
	typedef Register<up32OTYPER,  OTYPER_FIELD_BIT_LENGTH>  OTYPER;
	typedef Register<up32OSPEEDR, OSPEEDR_FIELD_BIT_LENGTH> OSPEEDR;
	typedef Register<up32PUPDR,   PUPDR_FIELD_BIT_LENGTH>   PUPDR;
	typedef Register<up32AFRL,    AFR_FIELD_BIT_LENGTH>     AFRL;
	typedef Register<up32AFRH,    AFR_FIELD_BIT_LENGTH>     AFRH;
	typedef Register<up32ODR,     ODR_FIELD_BIT_LENGTH>     ODR;
	typedef Register<up32IDR,     IDR_FIELD_BIT_LENGTH>     IDR;

	GPIO();
};


#endif /* HAL_GPIO_GPIO_HPP_ */
