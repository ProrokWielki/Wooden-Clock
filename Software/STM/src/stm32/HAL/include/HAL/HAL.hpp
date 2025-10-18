/**
 *  @file HAL.hpp
 *
 *  Created on: 21-11-2018
 *  @author: Paweł Warzecha
 */

#ifndef HAL_HAL_HPP_
#define HAL_HAL_HPP_

#include <HAL/Clock.hpp>
#include <HAL/DMA.hpp>
#include <HAL/GPIO.hpp>
#include <HAL/I2C.hpp>
#include <HAL/RTC.hpp>
#include <HAL/SPI.hpp>
#include <HAL/Timer.hpp>
#include <HAL/USART.hpp>

#include <DRV/74HC595.hpp>
#include <DRV/BME280.hpp>
#include <DRV/LSM9DS1.hpp>
#include <DRV/TLC59208F.hpp>

class LSM9DS1;

class HAL
{
public:
    static HAL & get();

    Clock clock;

    GPIO I2C1_SCL;
    GPIO I2C1_SDA;

    GPIO I2C2_SCL;
    GPIO I2C2_SDA;

    GPIO I2C3_SCL;
    GPIO I2C3_SDA;

    GPIO I2C4_SCL;
    GPIO I2C4_SDA;

    GPIO SPI1_MISO;
    GPIO SPI1_MOSI;
    GPIO SPI1_SCK;
    GPIO SPI1_CS1;
    GPIO SPI1_CS2;
    GPIO SPI1_CS3;

    GPIO QSPI_IO0;
    GPIO QSPI_IO1;
    GPIO QSPI_IO2;
    GPIO QSPI_IO3;
    GPIO QSPI_CLK;
    GPIO QSPI_CS;

    GPIO UART3_TX;
    GPIO UART3_RX;

    GPIO UART4_TX;
    GPIO UART4_RX;

    GPIO TLC_RESET;

    GPIO SR_DATAIN;
    GPIO SR_RCLOCK;
    GPIO SR_SCLOCK;
    GPIO SR_OE;
    GPIO SR_CLEAR;

    GPIO BUTTON1;
    GPIO BUTTON2;
    GPIO BUTTON3;
    GPIO BUTTON4;

    DMA DMA1_2;
    DMA DMA1_4;
    DMA DMA2_2;
    DMA DMA2_4;
    DMA DMA2_7;

    I2C I2C_1;
    I2C I2C_2;
    I2C I2C_3;
    I2C I2C_4;

    SPI SPI_1;

    USART USART_3;
    USART USART_4;

    SR_74HC595 SR_74HC595_1;

    TLC59208F TLC59208F_1;
    TLC59208F TLC59208F_2;
    TLC59208F TLC59208F_3;
    TLC59208F TLC59208F_4;

    LSM9DS1 LSM9DS1_1;

    BME280 BME280_1;

    Timer Timer2;

    RTC_ rtc;

    void clock_init();
    void qspi_init();
    void i2c_init();
    // static void spi_init();
    void gpio_init();
    // static void dma_init();
    void timer_init();
    // static void rtc_init();
    void nvic_init();
    void tlc59208f_init();
    void sr_74hc595_init();
    void lsm9ds1_init();

    void init();

    bool reset;

    bool new_time_set;
    uint8_t new_hour;
    uint8_t new_minutes;
    bool parse_time;

private:
    HAL();
};

#endif /* HAL_HAL_HPP_ */
