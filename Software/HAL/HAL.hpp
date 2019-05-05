/**
 *  @file HAL.hpp
 *
 *  Created on: 21-11-2018
 *  @author: Paweł Warzecha
 */

#ifndef HAL_HAL_HPP_
#define HAL_HAL_HPP_

#include "Clock/Clock.hpp"
#include "DMA/DMA.hpp"
#include "GPIO/GPIO.hpp"
#include "I2C/I2C.hpp"
#include "SPI/SPI.hpp"
#include "Timer/Timer.hpp"

#include "74HC595/74HC595.hpp"
#include "LSM9DS1/LSM9DS1.hpp"
#include "TLC59208F/TLC59208F.hpp"

class LSM9DS1;

class HAL
{
public:
    static GPIO I2C1_SCL;
    static GPIO I2C1_SDA;

    static GPIO I2C2_SCL;
    static GPIO I2C2_SDA;

    static GPIO I2C3_SCL;
    static GPIO I2C3_SDA;

    static GPIO I2C4_SCL;
    static GPIO I2C4_SDA;

    static GPIO SPI1_MISO;
    static GPIO SPI1_MOSI;
    static GPIO SPI1_SCK;
    static GPIO SPI1_CS1;
    static GPIO SPI1_CS2;

    static GPIO TLC_RESET;

    static GPIO SR_DATAIN;
    static GPIO SR_RCLOCK;
    static GPIO SR_SCLOCK;
    static GPIO SR_OE;
    static GPIO SR_CLEAR;

    static GPIO BUTTON;
    static GPIO BUTTON2;
    static GPIO BUTTON3;
    static GPIO BUTTON4;

    static DMA DMA1_2;
    static DMA DMA1_4;
    static DMA DMA2_2;
    static DMA DMA2_7;

    static I2C I2C_1;
    static I2C I2C_2;
    static I2C I2C_3;
    static I2C I2C_4;

    static SPI SPI_1;

    static SR_74HC595 SR_74HC595_1;

    static TLC59208F TLC59208F_1;
    static TLC59208F TLC59208F_2;
    static TLC59208F TLC59208F_3;
    static TLC59208F TLC59208F_4;

    static LSM9DS1 LSM9DS1_1;

    static Timer Timer2;

    static void clock_init(void);
    static void I2C_init(void);
    static void SPI_init(void);
    static void GPIO_Init(void);
    static void DMA_init();
    static void Timer_init();
    static void NVIC_init(void);
    static void TLC59208F_init(void);
    static void SR_74HC595_init(void);
    static void LSM9DS1_init();

    static void init(void);

private:
    HAL() = delete;
};
#endif /* HAL_HAL_HPP_ */
