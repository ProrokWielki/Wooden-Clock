/**
  *  @file GPIO_types.hpp
  *
  *  @brief Types used with GPIO
  *
  *  Stores enumerators allowing easier configuration of GPIOs
  *
  *  Created on: 13-11-2018
  *  @author: Paweł Warzecha
  */

#ifndef HAL_GPIO_GPIO_TYPES_HPP_
#define HAL_GPIO_GPIO_TYPES_HPP_


/// Stores possible modes of any GPIO
typedef enum
{
	eInput = 0,    //!< Input
	eOutput = 1,   //!< Output
	eAlternate = 2,//!< Alternate
	eAnalog = 3    //!< Analog

}PortMode_t;


/// Stores possible output types of any GPIO
typedef enum
{
	ePushPull = 0,//!< Push-Pull output
	eOpenDrain = 1//!< Open drain output

}PortOutputType_t;

/// Stores possible output speeds of any GPIO
typedef enum
{
	eLowSpeed = 0,    //!< Low speed
	eMediumSpeed = 1, //!< Medium speed
	eHighSpeed = 2,   //!< High speed
	eVeryHighSpeed = 3//!<  Very high speed

}PortOutputSpeed_t;

/// Stores possible pulling resistors configuration of any GPIO
typedef enum
{
	eNone = 0,   //!< No pulling resistor
	ePullUp = 1, //!< Pull up resistor
	ePullDown = 2//!< Pull down resistor

}PortPullUpPullDown_t;

/// Stores possible alternate functions of any GPIO
typedef enum
{
	eAF0, //!< Alternate function 0
	eAF1, //!< Alternate function 1
	eAF2, //!< Alternate function 2
	eAF3, //!< Alternate function 3
	eAF4, //!< Alternate function 4
	eAF5, //!< Alternate function 5
	eAF6, //!< Alternate function 6
	eAF7, //!< Alternate function 7
	eAF8, //!< Alternate function 8
	eAF9, //!< Alternate function 9
	eAF10,//!< Alternate function 10
	eAF11,//!< Alternate function 11
	eAF12,//!< Alternate function 12
	eAF13,//!< Alternate function 13
	eAF14,//!< Alternate function 14
	eAF15 //!< Alternate function 15

}AlteranteFunction_t;

/// Stores possible logical states of any GPIO
typedef enum
{
	eLow = 0,//!< Low state
	eHigh = 1//!< High state
}SignalLevel_t;


#endif /* HAL_GPIO_GPIO_TYPES_HPP_ */
