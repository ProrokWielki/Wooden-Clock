/**
 * @file cmsis_bridge.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <cassert>
#include <cstdint>

#include <stm32l452xx.h>

#include <HAL/types.hpp>

#include <cmsis_bridge/cmsis_bridge.hpp>

namespace
{
static DMA_Channel_TypeDef * to_dma_channel_register(DMA_Types::DmaNumber dma, DMA_Types::Channel channel)
{
    switch (dma)
    {
        case DMA_Types::DmaNumber::DMA_1:
            switch (channel)
            {
                case DMA_Types::Channel::Channel1:
                    return DMA1_Channel1;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
                case DMA_Types::Channel::Channel2:
                    return DMA1_Channel2;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
                case DMA_Types::Channel::Channel3:
                    return DMA1_Channel3;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
                case DMA_Types::Channel::Channel4:
                    return DMA1_Channel4;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
                case DMA_Types::Channel::Channel5:
                    return DMA1_Channel5;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
                case DMA_Types::Channel::Channel6:
                    return DMA1_Channel6;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
                case DMA_Types::Channel::Channel7:
                    return DMA1_Channel7;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
                default:
                    assert(false && "invalid channel");
                    return nullptr;
            };
        case DMA_Types::DmaNumber::DMA_2:
            switch (channel)
            {
                case DMA_Types::Channel::Channel1:
                    return DMA2_Channel1;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
                case DMA_Types::Channel::Channel2:
                    return DMA2_Channel2;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
                case DMA_Types::Channel::Channel3:
                    return DMA2_Channel3;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
                case DMA_Types::Channel::Channel4:
                    return DMA2_Channel4;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
                case DMA_Types::Channel::Channel5:
                    return DMA2_Channel5;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
                case DMA_Types::Channel::Channel6:
                    return DMA2_Channel6;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
                case DMA_Types::Channel::Channel7:
                    return DMA2_Channel7;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
                default:
                    assert(false && "invalid channel");
                    return nullptr;
            };
        default:
            assert(false && "invalid dma");
            return nullptr;
    };
}

static DMA_Request_TypeDef * to_dma_request_register(DMA_Types::DmaNumber dma)
{
    switch (dma)
    {
        case DMA_Types::DmaNumber::DMA_1:
            return DMA1_CSELR;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case DMA_Types::DmaNumber::DMA_2:
            return DMA2_CSELR;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        default:
            assert(false && "invalid dma");
            return nullptr;
    };
}

static DMA_TypeDef * to_dma_register(DMA_Types::DmaNumber dma)
{
    switch (dma)
    {
        case DMA_Types::DmaNumber::DMA_1:
            return DMA1;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case DMA_Types::DmaNumber::DMA_2:
            return DMA2;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        default:
            assert(false && "invalid dma");
            return nullptr;
    };
}
}  // namespace

volatile uint32_t * to_address(GPIO_Types::Port port, GPIO_Types::PortRegister portRegister)
{
    GPIO_TypeDef * gpioAddress{};

    switch (port)
    {
        case GPIO_Types::Port::A:
            gpioAddress = GPIOA;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case GPIO_Types::Port::B:
            gpioAddress = GPIOB;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case GPIO_Types::Port::C:
            gpioAddress = GPIOC;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case GPIO_Types::Port::D:
            gpioAddress = GPIOD;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case GPIO_Types::Port::E:
            gpioAddress = GPIOE;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        default:
            assert(false && "wrong port");
            return nullptr;
    }

    switch (portRegister)
    {
        case GPIO_Types::PortRegister::AFRL:
            return &(gpioAddress->AFR[0]);
        case GPIO_Types::PortRegister::AFRH:
            return &(gpioAddress->AFR[1]);
        case GPIO_Types::PortRegister::BRR:
            return &(gpioAddress->BRR);
        case GPIO_Types::PortRegister::BSRR:
            return &(gpioAddress->BSRR);
        case GPIO_Types::PortRegister::IDR:
            return &(gpioAddress->IDR);
        case GPIO_Types::PortRegister::MODER:
            return &(gpioAddress->MODER);
        case GPIO_Types::PortRegister::ODR:
            return &(gpioAddress->ODR);
        case GPIO_Types::PortRegister::OSPEEDR:
            return &(gpioAddress->OSPEEDR);
        case GPIO_Types::PortRegister::OTYPER:
            return &(gpioAddress->OTYPER);
        case GPIO_Types::PortRegister::PUPDR:
            return &(gpioAddress->PUPDR);
        default:
            assert(false && "wrong port register");
            return nullptr;
    }
}

volatile uint32_t * to_address(ClockRegister clock_register)
{
    switch (clock_register)
    {
        case ClockRegister::AHB1:
            return &(RCC->AHB1ENR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case ClockRegister::AHB2:
            return &(RCC->AHB2ENR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case ClockRegister::AHB3:
            return &(RCC->AHB3ENR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case ClockRegister::APB1_1:
            return &(RCC->APB1ENR1);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case ClockRegister::APB1_2:
            return &(RCC->APB1ENR2);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case ClockRegister::APB2:
            return &(RCC->APB2ENR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case ClockRegister::PLL_CONFIG:
            return &(RCC->PLLCFGR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case ClockRegister::CCIPR:
            return &(RCC->CCIPR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case ClockRegister::CCIPR2:
            return &(RCC->CCIPR2);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case ClockRegister::BDCR:
            return &(RCC->BDCR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case ClockRegister::CR:
            return &(RCC->CR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        default:
            assert(false && "invalid clock register");
            return nullptr;
    };
}

volatile uint32_t * to_address(Power_Types::Register power_register)
{
    switch (power_register)
    {
        case Power_Types::Register::CR1:
            return &(PWR->CR1);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        default:
            assert(false && "invalid power register");
            return nullptr;
    }
}

volatile uint32_t * to_address(I2C_Types::I2CNumber port, I2C_Types::Register i2c_register)
{
    I2C_TypeDef * i2c_address{};

    switch (port)
    {
        case I2C_Types::I2CNumber::I2C_1:
            i2c_address = I2C1;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case I2C_Types::I2CNumber::I2C_2:
            i2c_address = I2C2;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case I2C_Types::I2CNumber::I2C_3:
            i2c_address = I2C3;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case I2C_Types::I2CNumber::I2C_4:
            i2c_address = I2C4;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;

        default:
            assert(false && "invalid i2c number");
    }

    switch (i2c_register)
    {
        case I2C_Types::Register::CR1:
            return &(i2c_address->CR1);
        case I2C_Types::Register::CR2:
            return &(i2c_address->CR2);
        case I2C_Types::Register::OAR1:
            return &(i2c_address->OAR1);
        case I2C_Types::Register::OAR2:
            return &(i2c_address->OAR2);
        case I2C_Types::Register::TIMINGR:
            return &(i2c_address->TIMINGR);
        case I2C_Types::Register::TIMEOUTR:
            return &(i2c_address->TIMEOUTR);
        case I2C_Types::Register::ISR:
            return &(i2c_address->ISR);
        case I2C_Types::Register::ICR:
            return &(i2c_address->ICR);
        case I2C_Types::Register::PECR:
            return &(i2c_address->PECR);
        case I2C_Types::Register::RXDR:
            return &(i2c_address->RXDR);
        case I2C_Types::Register::TXDR:
            return &(i2c_address->TXDR);
        default:
            assert(false && "invalid register");
            return nullptr;
    }
}

volatile uint32_t * to_address(DMA_Types::DmaNumber dma, DMA_Types::Channel channel, DMA_Types::DmaRegister dma_register)
{
    switch (dma_register)
    {
        case DMA_Types::DmaRegister::ISR:
            return &(to_dma_register(dma)->ISR);
        case DMA_Types::DmaRegister::IFCR:
            return &(to_dma_register(dma)->IFCR);
        case DMA_Types::DmaRegister::CCR:
            return &(to_dma_channel_register(dma, channel)->CCR);
        case DMA_Types::DmaRegister::CNDTR:
            return &(to_dma_channel_register(dma, channel)->CNDTR);
        case DMA_Types::DmaRegister::CPAR:
            return &(to_dma_channel_register(dma, channel)->CPAR);
        case DMA_Types::DmaRegister::CMAR:
            return &(to_dma_channel_register(dma, channel)->CMAR);
        case DMA_Types::DmaRegister::CSELR:
            return &(to_dma_request_register(dma)->CSELR);
        default:
            assert(false && "invalid dma register");
            return nullptr;
    };
}

volatile uint32_t * to_address(SPI_types::SPI_Number spi, SPI_types::Register spi_register)
{
    SPI_TypeDef * spi_address{};

    switch (spi)
    {
        case SPI_types::SPI_Number::SPI_1:
            spi_address = SPI1;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case SPI_types::SPI_Number::SPI_2:
            spi_address = SPI2;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case SPI_types::SPI_Number::SPI_3:
            spi_address = SPI3;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        default:
            assert(false && "invalid spi number");
    }

    switch (spi_register)
    {
        case SPI_types::Register::CR1:
            return &(spi_address->CR1);
        case SPI_types::Register::CR2:
            return &(spi_address->CR2);
        case SPI_types::Register::CRCPR:
            return &(spi_address->CRCPR);
        case SPI_types::Register::DR:
            return &(spi_address->DR);
        case SPI_types::Register::SR:
            return &(spi_address->SR);
        case SPI_types::Register::RXCRCR:
            return &(spi_address->RXCRCR);
        case SPI_types::Register::TXCRCR:
            return &(spi_address->TXCRCR);
        default:
            assert(false && "invalid register");
            return nullptr;
    }
}

volatile uint32_t * to_address(RTC_types::Register rtc_register)
{
    switch (rtc_register)
    {
        case RTC_types::Register::TR:
            return &(RTC->TR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case RTC_types::Register::DR:
            return &(RTC->DR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case RTC_types::Register::SSR:
            return &(RTC->SSR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case RTC_types::Register::ICSR:
            return &(RTC->ISR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case RTC_types::Register::PRER:
            return &(RTC->PRER);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case RTC_types::Register::WUTR:
            return &(RTC->WUTR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case RTC_types::Register::CR:
            return &(RTC->CR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case RTC_types::Register::WPR:
            return &(RTC->WPR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case RTC_types::Register::CALR:
            return &(RTC->CALR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case RTC_types::Register::SHIFTR:
            return &(RTC->SHIFTR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case RTC_types::Register::TSTR:
            return &(RTC->TSTR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case RTC_types::Register::TSDR:
            return &(RTC->TSDR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case RTC_types::Register::TSSSR:
            return &(RTC->TSSSR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case RTC_types::Register::ALRMAR:
            return &(RTC->ALRMAR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case RTC_types::Register::ALRMASSR:
            return &(RTC->ALRMASSR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case RTC_types::Register::ALARMBR:
            return &(RTC->ALRMBR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case RTC_types::Register::ALRMBSSR:
            return &(RTC->ALRMBSSR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        case RTC_types::Register::ISR:
            return &(RTC->ISR);  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
        default:
            assert(false && "invalid register");
            return nullptr;
    }
}

volatile uint32_t * to_address(timer_types::Timer_number timer, timer_types::Register timer_register)
{
    TIM_TypeDef * timer_address{};

    switch (timer)
    {
        case timer_types::Timer_number::Timer_1:
            timer_address = TIM1;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case timer_types::Timer_number::Timer_2:
            timer_address = TIM2;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case timer_types::Timer_number::Timer_3:
            timer_address = TIM3;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case timer_types::Timer_number::Timer_6:
            timer_address = TIM6;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case timer_types::Timer_number::Timer_15:
            timer_address = TIM15;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case timer_types::Timer_number::Timer_16:
            timer_address = TIM16;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        default:
            assert(false && "invalid timer number");
            return nullptr;
    }

    switch (timer_register)
    {
        case timer_types::Register::ARR:
            return &(timer_address->ARR);
        case timer_types::Register::PSC:
            return &(timer_address->PSC);
        case timer_types::Register::CR1:
            return &(timer_address->CR1);
        case timer_types::Register::SR:
            return &(timer_address->SR);
        case timer_types::Register::DIER:
            return &(timer_address->DIER);
        default:
            assert(false && "invalid register");
            return nullptr;
    }
}

volatile uint32_t * to_address(Usart_Types::UsartNumber usart, Usart_Types::Register usart_register)
{
    USART_TypeDef * usart_address{};

    switch (usart)
    {
        case Usart_Types::UsartNumber::USART_1:
            usart_address = USART1;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case Usart_Types::UsartNumber::USART_2:
            usart_address = USART2;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case Usart_Types::UsartNumber::USART_3:
            usart_address = USART3;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case Usart_Types::UsartNumber::UART_4:
            usart_address = UART4;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case Usart_Types::UsartNumber::LOW_POWER_UART_1:
            usart_address = LPUART1;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        default:
            assert(false && "invalid usart number");
            return nullptr;
    }

    switch (usart_register)
    {
        case Usart_Types::Register::CR1:
            return &(usart_address->CR1);
        case Usart_Types::Register::CR2:
            return &(usart_address->CR2);
        case Usart_Types::Register::CR3:
            return &(usart_address->CR3);
        case Usart_Types::Register::BRR:
            return &(usart_address->BRR);
        // case Usart_Types::Register::GTPR:
        // return &(usart_address->GTPR);
        case Usart_Types::Register::RTOR:
            return &(usart_address->RTOR);
        case Usart_Types::Register::ISR:
            return &(usart_address->ISR);
        case Usart_Types::Register::ICR:
            return &(usart_address->ICR);
        // case Usart_Types::Register::RDR:
        // return &(usart_address->RDR);
        // case Usart_Types::Register::TDR:
        // return &(usart_address->TDR);
        default:
            assert(false && "invalid register");
            return nullptr;
    };
}

volatile uint16_t * to_16bit_register_address(Usart_Types::UsartNumber usart, Usart_Types::Register usart_register)
{
    USART_TypeDef * usart_address{};

    switch (usart)
    {
        case Usart_Types::UsartNumber::USART_1:
            usart_address = USART1;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case Usart_Types::UsartNumber::USART_2:
            usart_address = USART2;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case Usart_Types::UsartNumber::USART_3:
            usart_address = USART3;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case Usart_Types::UsartNumber::UART_4:
            usart_address = UART4;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        case Usart_Types::UsartNumber::LOW_POWER_UART_1:
            usart_address = LPUART1;  // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
            break;
        default:
            assert(false && "invalid usart number");
            return nullptr;
    }

    switch (usart_register)
    {
        case Usart_Types::Register::GTPR:
            return &(usart_address->GTPR);
        case Usart_Types::Register::RDR:
            return &(usart_address->RDR);
        case Usart_Types::Register::TDR:
            return &(usart_address->TDR);
        default:
            assert(false && "invalid register");
            return nullptr;
    };
}