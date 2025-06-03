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
    HAL();

    static Clock clock;

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
    static GPIO SPI1_CS3;

    static GPIO QSPI_IO0;
    static GPIO QSPI_IO1;
    static GPIO QSPI_IO2;
    static GPIO QSPI_IO3;
    static GPIO QSPI_CLK;
    static GPIO QSPI_CS;

    static GPIO UART3_TX;
    static GPIO UART3_RX;

    static GPIO UART4_TX;
    static GPIO UART4_RX;

    static GPIO TLC_RESET;

    static GPIO SR_DATAIN;
    static GPIO SR_RCLOCK;
    static GPIO SR_SCLOCK;
    static GPIO SR_OE;
    static GPIO SR_CLEAR;

    static GPIO BUTTON1;
    static GPIO BUTTON2;
    static GPIO BUTTON3;
    static GPIO BUTTON4;

    static DMA DMA1_2;
    static DMA DMA1_4;
    static DMA DMA2_2;
    static DMA DMA2_7;
    static DMA DMA2_4;

    static I2C I2C_1;
    static I2C I2C_2;
    static I2C I2C_3;
    static I2C I2C_4;

    static SPI SPI_1;

    static USART USART_3;
    static USART USART_4;

    static SR_74HC595 SR_74HC595_1;

    static TLC59208F TLC59208F_1;
    static TLC59208F TLC59208F_2;
    static TLC59208F TLC59208F_3;
    static TLC59208F TLC59208F_4;

    static LSM9DS1 LSM9DS1_1;

    static BME280 BME280_1;

    static Timer Timer2;

    static RTC_ rtc;

    static void clock_init();
    static void qspi_init();
    static void i2c_init();
    // static void spi_init();
    static void gpio_init();
    // static void dma_init();
    static void timer_init();
    // static void rtc_init();
    static void nvic_init();
    static void tlc59208f_init();
    static void sr_74hc595_init();
    static void lsm9ds1_init();

    static void init();

    static volatile bool up;
    static volatile bool down;
    static volatile bool left;
    static volatile bool right;
    static volatile bool reset;

    static constexpr uint8_t UART_BUFFER_SIZE{50};

    static std::array<volatile uint8_t, UART_BUFFER_SIZE> uart_buffer;
    static volatile uint8_t head;
    static uint8_t tail;
    static bool new_time_set;
    static uint8_t new_hour;
    static uint8_t new_minutes;
    static bool parse_time;
};

#endif /* HAL_HAL_HPP_ */
