/*
 * HAL.cpp
 *
 *  Created on: 21-11-2018
 *      Author: Paweł Warzecha
 */

#include <array>

#include <stm32l4xx.h>

#include <HAL/types.hpp>

#include "HAL/Clock.hpp"
#include "HAL/Timer.hpp"
#include "HAL/types.hpp"
#include "include/HAL/HAL.hpp"

namespace
{
constexpr uint8_t I2C_1_SCL_PIN_NUMBER{9};
constexpr uint8_t I2C_1_SDA_PIN_NUMBER{10};

constexpr uint8_t I2C_2_SCL_PIN_NUMBER{10};
constexpr uint8_t I2C_2_SDA_PIN_NUMBER{11};

constexpr uint8_t I2C_3_SCL_PIN_NUMBER{0};
constexpr uint8_t I2C_3_SDA_PIN_NUMBER{1};

constexpr uint8_t I2C_4_SCL_PIN_NUMBER{6};
constexpr uint8_t I2C_4_SDA_PIN_NUMBER{7};

constexpr uint8_t SPI_1_MISO_PIN_NUMBER{11};
constexpr uint8_t SPI_1_MOSI_PIN_NUMBER{12};
constexpr uint8_t SPI_1_SCK_PIN_NUMBER{5};
constexpr uint8_t SPI_1_CS1_PIN_NUMBER{0};
constexpr uint8_t SPI_1_CS2_PIN_NUMBER{9};
constexpr uint8_t SPI_1_CS3_PIN_NUMBER{1};

constexpr uint8_t QSPI_IO0_PIN_NUMBER{1};
constexpr uint8_t QSPI_IO1_PIN_NUMBER{0};
constexpr uint8_t QSPI_IO2_PIN_NUMBER{7};
constexpr uint8_t QSPI_IO3_PIN_NUMBER{6};
constexpr uint8_t QSPI_CLK_PIN_NUMBER{3};
constexpr uint8_t QSPI_CS_PIN_NUMBER{2};

constexpr uint8_t UART_3_TX_PIN_NUMBER{10};
constexpr uint8_t UART_3_RX_PIN_NUMBER{11};

constexpr uint8_t UART_4_TX_PIN_NUMBER{0};
constexpr uint8_t UART_4_RX_PIN_NUMBER{1};

constexpr uint8_t TLC_RESET_PIN_NUMBER{9};

constexpr uint8_t SR_DATAIN_PIN_NUMBER{14};
constexpr uint8_t SR_RCLOCK_PIN_NUMBER{7};
constexpr uint8_t SR_SCLOCK_PIN_NUMBER{6};
constexpr uint8_t SR_OE_PIN_NUMBER{15};
constexpr uint8_t SR_CLEAR_PIN_NUMBER{8};
constexpr uint8_t SR_CHAIN_LENGTH{4};

constexpr uint8_t BUTTON1_PIN_NUMBER{8};
constexpr uint8_t BUTTON2_PIN_NUMBER{8};
constexpr uint8_t BUTTON3_PIN_NUMBER{2};
constexpr uint8_t BUTTON4_PIN_NUMBER{2};

constexpr uint8_t TLC59208F_4_ADDRESS{0x46};
constexpr uint8_t TLC59208F_3_ADDRESS{0x44};
constexpr uint8_t TLC59208F_2_ADDRESS{0x42};
constexpr uint8_t TLC59208F_1_ADDRESS{0x40};

constexpr float I2C_CLOCK_SPEED_1MHZ{1'000'000.0};

constexpr unsigned int ESP_UART_SPEED{500'000};
constexpr unsigned int DEBUG_UART_SPEED{115200};

}  // namespace

// bool HAL::new_time_set{false};
// uint8_t HAL::new_hour{0};
// uint8_t HAL::new_minutes{0};
// bool HAL::parse_time{false};

HAL::HAL()
: clock{}, power{}, sys_config{}, I2C1_SCL(clock, sys_config, GPIO_Types::Port::A, I2C_1_SCL_PIN_NUMBER),
  I2C1_SDA(clock, sys_config, GPIO_Types::Port::A, I2C_1_SDA_PIN_NUMBER), I2C2_SCL(clock, sys_config, GPIO_Types::Port::B, I2C_2_SCL_PIN_NUMBER),
  I2C2_SDA(clock, sys_config, GPIO_Types::Port::B, I2C_2_SDA_PIN_NUMBER), I2C3_SCL(clock, sys_config, GPIO_Types::Port::C, I2C_3_SCL_PIN_NUMBER),
  I2C3_SDA(clock, sys_config, GPIO_Types::Port::C, I2C_3_SDA_PIN_NUMBER), I2C4_SCL(clock, sys_config, GPIO_Types::Port::B, I2C_4_SCL_PIN_NUMBER),
  I2C4_SDA(clock, sys_config, GPIO_Types::Port::B, I2C_4_SDA_PIN_NUMBER), SPI1_MISO(clock, sys_config, GPIO_Types::Port::A, SPI_1_MISO_PIN_NUMBER),
  SPI1_MOSI(clock, sys_config, GPIO_Types::Port::A, SPI_1_MOSI_PIN_NUMBER), SPI1_SCK(clock, sys_config, GPIO_Types::Port::A, SPI_1_SCK_PIN_NUMBER),
  SPI1_CS1(clock, sys_config, GPIO_Types::Port::E, SPI_1_CS1_PIN_NUMBER), SPI1_CS2(clock, sys_config, GPIO_Types::Port::B, SPI_1_CS2_PIN_NUMBER),
  SPI1_CS3(clock, sys_config, GPIO_Types::Port::E, SPI_1_CS3_PIN_NUMBER), QSPI_IO0(clock, sys_config, GPIO_Types::Port::B, QSPI_IO0_PIN_NUMBER),
  QSPI_IO1(clock, sys_config, GPIO_Types::Port::B, QSPI_IO1_PIN_NUMBER), QSPI_IO2(clock, sys_config, GPIO_Types::Port::A, QSPI_IO2_PIN_NUMBER),
  QSPI_IO3(clock, sys_config, GPIO_Types::Port::A, QSPI_IO3_PIN_NUMBER), QSPI_CLK(clock, sys_config, GPIO_Types::Port::A, QSPI_CLK_PIN_NUMBER),
  QSPI_CS(clock, sys_config, GPIO_Types::Port::A, QSPI_CS_PIN_NUMBER), UART3_TX(clock, sys_config, GPIO_Types::Port::C, UART_3_TX_PIN_NUMBER),
  UART3_RX(clock, sys_config, GPIO_Types::Port::C, UART_3_RX_PIN_NUMBER), UART4_TX(clock, sys_config, GPIO_Types::Port::A, UART_4_TX_PIN_NUMBER),
  UART4_RX(clock, sys_config, GPIO_Types::Port::A, UART_4_RX_PIN_NUMBER), TLC_RESET(clock, sys_config, GPIO_Types::Port::C, TLC_RESET_PIN_NUMBER),
  SR_DATAIN(clock, sys_config, GPIO_Types::Port::B, SR_DATAIN_PIN_NUMBER), SR_RCLOCK(clock, sys_config, GPIO_Types::Port::C, SR_RCLOCK_PIN_NUMBER),
  SR_SCLOCK(clock, sys_config, GPIO_Types::Port::C, SR_SCLOCK_PIN_NUMBER), SR_OE(clock, sys_config, GPIO_Types::Port::B, SR_OE_PIN_NUMBER),
  SR_CLEAR(clock, sys_config, GPIO_Types::Port::C, SR_CLEAR_PIN_NUMBER), BUTTON1(clock, sys_config, GPIO_Types::Port::A, BUTTON1_PIN_NUMBER),
  BUTTON2(clock, sys_config, GPIO_Types::Port::B, BUTTON2_PIN_NUMBER), BUTTON3(clock, sys_config, GPIO_Types::Port::C, BUTTON3_PIN_NUMBER),
  BUTTON4(clock, sys_config, GPIO_Types::Port::E, BUTTON4_PIN_NUMBER), DMA1_2(clock, DMA_Types::DmaNumber::DMA_1, DMA_Types::Channel::Channel2),
  DMA1_4(clock, DMA_Types::DmaNumber::DMA_1, DMA_Types::Channel::Channel4), DMA2_2(clock, DMA_Types::DmaNumber::DMA_2, DMA_Types::Channel::Channel2),
  DMA2_4(clock, DMA_Types::DmaNumber::DMA_2, DMA_Types::Channel::Channel4), DMA2_7(clock, DMA_Types::DmaNumber::DMA_2, DMA_Types::Channel::Channel7),
  I2C_1(clock, sys_config, I2C_Types::I2CNumber::I2C_1, I2C1_SCL, I2C1_SDA, I2C_CLOCK_SPEED_1MHZ, &DMA2_7),
  I2C_2(clock, sys_config, I2C_Types::I2CNumber::I2C_2, I2C2_SCL, I2C2_SDA, I2C_CLOCK_SPEED_1MHZ, &DMA1_4),
  I2C_3(clock, sys_config, I2C_Types::I2CNumber::I2C_3, I2C3_SCL, I2C3_SDA, I2C_CLOCK_SPEED_1MHZ, &DMA1_2),
  I2C_4(clock, sys_config, I2C_Types::I2CNumber::I2C_4, I2C4_SCL, I2C4_SDA, I2C_CLOCK_SPEED_1MHZ, &DMA2_2),
  SPI_1(clock, SPI_types::SPI_Number::SPI_1, SPI1_MOSI, SPI1_MISO, SPI1_SCK, SPI_types::SPIMode::master, SPI_types::SPIDataSize::_8bits,
        SPI_types::SPIPolarity::idle_high, SPI_types::SPIPhase::data_on_second_edge, SPI_types::SPIForamt::MSB_first,
        SPI_types::BaudRatePrescaller::Prescaller_256),
  USART_3(clock, Usart_Types::UsartNumber::USART_3, UART3_TX, UART3_RX, ESP_UART_SPEED),
  USART_4(clock, Usart_Types::UsartNumber::UART_4, UART4_TX, UART4_RX, DEBUG_UART_SPEED),
  SR_74HC595_1(SR_DATAIN, SR_RCLOCK, SR_SCLOCK, SR_OE, SR_CLEAR, SR_CHAIN_LENGTH), TLC59208F_1(I2C_4, TLC59208F_1_ADDRESS, TLC_RESET),
  TLC59208F_2(I2C_1, TLC59208F_2_ADDRESS, TLC_RESET), TLC59208F_3(I2C_3, TLC59208F_3_ADDRESS, TLC_RESET), TLC59208F_4(I2C_2, TLC59208F_4_ADDRESS, TLC_RESET),
  LSM9DS1_1(SPI_1, SPI1_CS1, SPI1_CS2), BME280_1(SPI_1, SPI1_CS3), Timer2(timer_types::Timer_number::Timer_2), rtc{clock, power}
{
}

HAL & HAL::get()
{
    static HAL instance;
    return instance;
}

void HAL::init()
{
    clock_init();
    SystemCoreClockUpdate();

    gpio_init();

    qspi_init();

    timer_init();
    // dma_init();
    i2c_init();
    // spi_init();
    // rtc_init();

    // uint8_t who_am_i_m;
    // uint8_t who_am_i_g;

    tlc59208f_init();

    sr_74hc595_init();
    // lsm9ds1_init();

    DMA2_7.enable_request(DMA_Types::Request::I2C_1_TX);
    DMA1_4.enable_request(DMA_Types::Request::I2C_2_TX);
    DMA1_2.enable_request(DMA_Types::Request::I2C_3_TX);
    DMA2_2.enable_request(DMA_Types::Request::I2C_4_TX);

    // DMA2_4.enable_request(DMA::);

    // DMA1_CSELR->CSELR |= ((3 << 12) | (3 << 4));

    // TIM2->DIER |= (1 << 0);
    Timer2.enable_interrupt(timer_types::Interrupt::UPDATE);

    // clock.enable_clock_for(Peripheral::USART_3);

    // USART3->BRR = 0xA0;
    // USART3->CR1 = 0x2f;

    // who_am_i_m = LSM9DS1_1.get_who_am_i_m();
    // who_am_i_g = LSM9DS1_1.get_who_am_i_g();

    BME280_1.init();

    // BME280_1.get_id();

    // auto hum = BME280_1.get_humidity();
    // auto temp = BME280_1.get_temperature();
    // auto pressure = BME280_1.get_pressure();
}

void HAL::qspi_init()
{
    //     RCC->AHB3ENR = 1 << 8;  // QSPI_EN

    //     QUADSPI->CR = 255 << 24;

    //     QUADSPI->DCR |= 24 << 16;  // FSIZE = 24  -- 16MB
    //     QUADSPI->DCR |= 1 << 8;    // nCS stays high for at least 8 cycles between Flash memory commands

    //     QUADSPI->CR |= QUADSPI_CR_EN;  // Enable

    //     ///////////////////////////

    //     uint32_t ccr, sr;

    //     uint32_t tmp;

    //     /* Configure automatic polling mode to wait for memory ready */

    //     QUADSPI->DLR = 647; /* use len-1 so 20 bytes is (20-1 == 19) */

    //     /* Commands are sent through CCR */
    //     tmp = 1 << 26; /* indirect read */
    //     tmp |= 0x9F;
    //     tmp |= 1 << 8;
    //     tmp |= 1 << 24;
    //     QUADSPI->CCR = tmp;

    //     /////////////////////////////////////
    //     int len;
    //     int max_len = 648;
    //     uint32_t buf[648];

    //     uint32_t * a = buf;

    //     len = 0;
    //     /* manually transfer data from the QSPI peripheral, this
    //      * loop runs while QUADSPI_SR_BUSY is set. It pulls 1 byte
    //      * at a time.
    //      */
    //     do
    //     {
    //         sr = QUADSPI->SR;
    //         if (sr & (1 << 2))
    //         {
    //             *a = QUADSPI->DR;
    //             a++;
    //             len++;
    //             if (len >= max_len)
    //             {
    //                 break;
    //             }
    //         }
    //     } while (sr & (1 << 5));

    //     /// ///////////////////////////////

    //     //    print_status(QUADSPI_SR);
    //     //    printf("\nRead ID returned %d bytes\n", len);
    //     QUADSPI->FCR = 0x1f;

    //     /////////////////////////////////////////
    // #if 1
    //     ccr = 0x06;
    //     ccr |= 1 << 8;
    //     ccr |= 1 << 26;
    //     QUADSPI->CCR = ccr;
    //     do
    //     {
    //         sr = QUADSPI->SR;
    //     } while (sr & (1 << 5));
    //     QUADSPI->FCR = 0x1f; /* reset the flags */
    //     ///

    //     uint8_t buffer = 1;

    //     ccr = 0;
    //     /* adjusting this to 0 fixed the write issue. */
    //     ccr |= 0x02; /* write 256 bytes */
    //     /* For some reason 1-1-4 command */
    //     ccr |= 1 << 8;
    //     ccr |= 1 << 10;
    //     ccr |= 2 << 12; /* 24 bit address */
    //     ccr |= 1 << 24;
    //     QUADSPI->DLR = 255;
    //     QUADSPI->AR = 0;
    //     QUADSPI->CCR = ccr; /* go write a page */
    //     tmp = 0;
    //     do
    //     {
    //         sr = QUADSPI->SR;
    //         if (sr & (1 << 1))
    //         {
    //             break;
    //         }
    //         tmp++;
    //         QUADSPI->DR = buffer++;
    //     } while (QUADSPI->SR & (1 << 5));

    //     QUADSPI->FCR = 0x1f;
    // #else
    //     ccr = 0x06;
    //     ccr |= 1 << 8;
    //     ccr |= 1 << 26;
    //     QUADSPI->CCR = ccr;
    //     do
    //     {
    //         sr = QUADSPI->SR;
    //     } while (sr & (1 << 5));
    //     QUADSPI->FCR = 0x1f; /* reset the flags */

    //     ccr = 0xC7;
    //     ccr |= 1 << 8;
    //     ccr |= 1 << 26;
    //     QUADSPI->CCR = ccr;
    //     do
    //     {
    //         sr = QUADSPI->SR;
    //     } while (sr & (1 << 5));
    //     QUADSPI->FCR = 0x1f; /* reset the flags */
    //                          ///
    //     for (uint32_t dupa = 0; dupa < 0x3fffffff; dupa++)
    //     {
    //         (void)dupa;
    //     }
    // #endif

    //     /* Commands are sent through CCR */
    //     ccr = 0x03;
    //     ccr |= 1 << 8;
    //     ccr |= 2 << 18;
    //     ccr |= 1 << 10;
    //     ccr |= 2 << 12; /* 24 bit address */
    //     ccr |= 1 << 24;
    //     ccr |= 1 << 26;
    //     QUADSPI->DLR = 255;
    //     QUADSPI->CCR = ccr;
    //     QUADSPI->AR = 0;

    //     /////////////////////////////////////

    //     a = buf;

    //     len = 0;
    //     /* manually transfer data from the QSPI peripheral, this
    //      * loop runs while QUADSPI_SR_BUSY is set. It pulls 1 byte
    //      * at a time.
    //      */
    //     do
    //     {
    //         sr = QUADSPI->SR;
    //         if (sr & (1 << 2))
    //         {
    //             *a = QUADSPI->DR;
    //             a++;
    //             len++;
    //             if (len >= max_len)
    //             {
    //                 break;
    //             }
    //         }
    //     } while (sr & (1 << 5));

    //     /// ///////////////////////////////

    //     //    print_status(QUADSPI_SR);
    //     //    printf("\nRead ID returned %d bytes\n", len);
    //     QUADSPI->FCR = 0x1f;

    //     /* Commands are sent through CCR */
    //     ccr = 0x03;
    //     ccr |= 1 << 8;
    //     ccr |= 1 << 10;
    //     ccr |= 2 << 12; /* 24 bit address */
    //     ccr |= 2 << 18;
    //     ccr |= 1 << 24;
    //     ccr |= 3 << 26;
    //     QUADSPI->CCR = ccr;
}

void HAL::clock_init()
{
    // M = 1
    // N = 10
    // R = 2
    // P = 7
    // Q = 2

    //  while((RCC->CR & RCC_CR_PLLRDY) == 0);

    FLASH->ACR |= FLASH_ACR_LATENCY_4WS;  // Latency set to 4 wait states
    FLASH->ACR |= FLASH_ACR_PRFTEN;       // Prefetch enable
    FLASH->ACR |= FLASH_ACR_DCEN;         // Data cashe enable
    FLASH->ACR |= FLASH_ACR_ICEN;         // Instruction cashe enable

    RCC->CR |= RCC_CR_HSEON;

    while ((RCC->CR & RCC_CR_HSERDY) == 0)
        ;

    RCC->PLLCFGR = (3 << 0) | (20 << 8) | (1 << 24);

    RCC->CR |= RCC_CR_PLLON;  // HSI turned on

    while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        ;

    RCC->CSR |= 1;

    while ((RCC->CSR & 2) == 0)
        ;

    RCC->CFGR |= (3 << 0);
}

void HAL::i2c_init()
{
    // RCC->CCIPR |= RCC_CCIPR_I2C1SEL_0;
    // RCC->CCIPR |= RCC_CCIPR_I2C2SEL_0;
    // RCC->CCIPR |= RCC_CCIPR_I2C3SEL_0;
    // RCC->CCIPR2 |= RCC_CCIPR2_I2C4SEL_0;

    // /* Clock enable */
    // RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN;  // Enable clock for I2C1
    // RCC->APB1ENR1 |= RCC_APB1ENR1_I2C2EN;  // Enable clock for I2C2
    // RCC->APB1ENR1 |= RCC_APB1ENR1_I2C3EN;  // Enable clock for I2C3
    // RCC->APB1ENR2 |= RCC_APB1ENR2_I2C4EN;  // Enable clock for I2C4

    // clock.set_clock_source_for(Peripheral::I2C_1, ClockSource::PCLK);
    // clock.set_clock_source_for(Peripheral::I2C_2, ClockSource::PCLK);
    // clock.set_clock_source_for(Peripheral::I2C_3, ClockSource::PCLK);
    // clock.set_clock_source_for(Peripheral::I2C_4, ClockSource::PCLK);

    // /* Clock enable */
    // clock.enable_clock_for(Peripheral::I2C_1);
    // clock.enable_clock_for(Peripheral::I2C_2);
    // clock.enable_clock_for(Peripheral::I2C_3);
    // clock.enable_clock_for(Peripheral::I2C_4);

    /* Fast-mode Plus enable */
    // SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C1_FMP;  // Enable FM+ for I2C1
    // SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C2_FMP;  // Enable FM+ for I2C2
    // SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C3_FMP;  // Enable FM+ for I2C3
    // SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C4_FMP;  // Enable FM+ for I2C4

    // SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C_PB6_FMP |  // Enable FM+ on PB6
    //                  SYSCFG_CFGR1_I2C_PB7_FMP;   // Enable FM+ on PB7

    /* I2C set timing*/
    // I2C_1.set_timing(4, 1, 0, 3, 6);
    // I2C_2.set_timing(4, 1, 0, 3, 6);
    // I2C_3.set_timing(4, 1, 0, 3, 6);
    // I2C_4.set_timing(4, 1, 0, 3, 6);

    /* I2C periphery enable */
    // I2C_1.enable();
    // I2C_2.enable();
    // I2C_3.enable();
    // I2C_4.enable();
}

void HAL::gpio_init()
{
    /* Clock enable */
    // clock.enable_clock_for(Peripheral::GPIO_A);
    // clock.enable_clock_for(Peripheral::GPIO_B);
    // clock.enable_clock_for(Peripheral::GPIO_C);
    // clock.enable_clock_for(Peripheral::GPIO_E);

    // I2C1_SCL.set_as_I2C_pin(GPIO_Types::AlternateFunction::AF4);
    // I2C1_SDA.set_as_I2C_pin(GPIO_Types::AlternateFunction::AF4);

    // I2C2_SCL.set_as_I2C_pin(GPIO_Types::AlternateFunction::AF4);
    // I2C2_SDA.set_as_I2C_pin(GPIO_Types::AlternateFunction::AF4);

    // I2C3_SCL.set_as_I2C_pin(GPIO_Types::AlternateFunction::AF4);
    // I2C3_SDA.set_as_I2C_pin(GPIO_Types::AlternateFunction::AF4);

    // I2C4_SCL.set_as_I2C_pin(GPIO_Types::AlternateFunction::AF5);
    // I2C4_SDA.set_as_I2C_pin(GPIO_Types::AlternateFunction::AF5);

    SPI1_MISO.set_as_spi_pin(GPIO_Types::AlternateFunction::AF5);
    SPI1_MOSI.set_as_spi_pin(GPIO_Types::AlternateFunction::AF5);
    SPI1_SCK.set_as_spi_pin(GPIO_Types::AlternateFunction::AF5);

    SPI1_CS1.set_mode(GPIO_Types::PortMode::Output);
    SPI1_CS1.set_output_type(GPIO_Types::PortOutputType::PushPull);
    SPI1_CS1.set_pull_up_pull_down(GPIO_Types::PortPullUpPullDown::None);

    SPI1_CS2.set_mode(GPIO_Types::PortMode::Output);
    SPI1_CS2.set_output_type(GPIO_Types::PortOutputType::PushPull);
    SPI1_CS2.set_pull_up_pull_down(GPIO_Types::PortPullUpPullDown::None);

    SPI1_CS3.set_mode(GPIO_Types::PortMode::Output);
    SPI1_CS3.set_output_type(GPIO_Types::PortOutputType::PushPull);
    SPI1_CS3.set_pull_up_pull_down(GPIO_Types::PortPullUpPullDown::None);

    QSPI_IO0.set_as_spi_pin(GPIO_Types::AlternateFunction::AF10);
    QSPI_IO1.set_as_spi_pin(GPIO_Types::AlternateFunction::AF10);
    QSPI_IO2.set_as_spi_pin(GPIO_Types::AlternateFunction::AF10);
    QSPI_IO3.set_as_spi_pin(GPIO_Types::AlternateFunction::AF10);
    QSPI_CLK.set_as_spi_pin(GPIO_Types::AlternateFunction::AF10);
    QSPI_CS.set_as_spi_pin(GPIO_Types::AlternateFunction::AF10);

    // UART3_RX.set_as_SPI_pin(GPIO_Types::AlternateFunction::AF7);  // ToDo not spi :)
    // UART3_TX.set_as_SPI_pin(GPIO_Types::AlternateFunction::AF7);

    // UART4_RX.set_as_SPI_pin(GPIO_Types::AlternateFunction::AF7);  // ToDo not spi :)
    // UART4_TX.set_as_SPI_pin(GPIO_Types::AlternateFunction::AF7);
}

// void HAL::dma_init()
// {
//     clock.enable_clock_for(Peripheral::DMA_1);
//     clock.enable_clock_for(Peripheral::DMA_2);
// }

void HAL::timer_init()
{
    clock.enable_clock_for(Peripheral::TIMER_2);

    Timer2.set_reload_value(625);    // 625
    Timer2.set_prescaler_value(79);  // 79
    Timer2.enable();
}

void HAL::nvic_init()
{
    NVIC_EnableIRQ(DMA1_Channel2_IRQn);
    NVIC_EnableIRQ(DMA1_Channel4_IRQn);
    NVIC_EnableIRQ(DMA2_Channel7_IRQn);
    NVIC_EnableIRQ(DMA2_Channel2_IRQn);
    NVIC_EnableIRQ(TIM2_IRQn);
}

void HAL::tlc59208f_init()
{
    std::array<uint8_t, 2> first{0, 0x08};
    std::array<uint8_t, 2> second{0xAA, 0xAA};

    TLC59208F_1.init();
    TLC59208F_2.init();
    TLC59208F_3.init();
    TLC59208F_4.init();

    TLC59208F_1.set_registers_values(0x00, first.data(), first.size());
    TLC59208F_2.set_registers_values(0x00, first.data(), first.size());
    TLC59208F_3.set_registers_values(0x00, first.data(), first.size());
    TLC59208F_4.set_registers_values(0x00, first.data(), first.size());

    TLC59208F_1.set_registers_values(0x0C, second.data(), second.size());
    TLC59208F_2.set_registers_values(0x0C, second.data(), second.size());
    TLC59208F_3.set_registers_values(0x0C, second.data(), second.size());
    TLC59208F_4.set_registers_values(0x0C, second.data(), second.size());
}

void HAL::sr_74hc595_init()
{
    SR_74HC595_1.set_all_outputs_high();
}

void HAL::lsm9ds1_init()
{
    LSM9DS1_1.set_data_rate(MagnetometerDataRate::Hz_80);
    LSM9DS1_1.set_xy_operation_mode(MagnetometerXYOperationMode::ultra_performance);
    LSM9DS1_1.set_full_scale(MagnetometerFullScale::Gs_16);
    LSM9DS1_1.set_operation_mode(MagnetometerOperationMode::continuous_conversion);
}
