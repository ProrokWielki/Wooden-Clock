/*
 * GPIO_types.hpp
 *
 *  Created on: 13-11-2018
 *      Author: Pawe³ Warzecha
 */

#ifndef HAL_GPIO_GPIO_TYPES_HPP_
#define HAL_GPIO_GPIO_TYPES_HPP_


typedef enum
{
	eInput = 0,
	eOutput = 1,
	eAlternate = 2,
	eAnalog = 3

}PortMode_t;

typedef enum
{
	ePushPull = 0,
	eOpenDrain = 1

}PortOutputType_t;

typedef enum
{
	eLowSpeed = 0,
	eMediumSpeed = 1,
	eHighSpeed = 2,
	eVeryHighSpeed = 3

}PortOutputSpeed_t;

typedef enum
{
	eNone = 0,
	ePullUp = 1,
	ePullDown = 2

}PortPullUpPullDown_t;


typedef enum
{
	eAF0,
	eAF1,
	eAF2,
	eAF3,
	eAF4,
	eAF5,
	eAF6,
	eAF7,
	eAF8,
	eAF9,
	eAF10,
	eAF11,
	eAF12,
	eAF13,
	eAF14,
	eAF15

}AlteranteFunction_t;

typedef enum
{
	eLow = 0,
	eHigh = 1
}SignalLevel_t;


#endif /* HAL_GPIO_GPIO_TYPES_HPP_ */
