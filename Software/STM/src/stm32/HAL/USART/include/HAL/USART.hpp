/**
 * @file USART.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-06-01
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <cstdint>

#include <HAL/GPIO.hpp>
#include <HAL/Register.hpp>
#include <HAL/types.hpp>

class USART
{
public:
    /**
     * @brief Construct a new USART object
     *
     * @param usart_number USART number to be used
     * @param tx_pin GPIO pin for TX
     * @param rx_pin GPIO pin for RX
     * @param baud_rate Baud rate for USART communication
     */
    USART(Clock & clock, Usart_Types::UsartNumber usart_number, GPIO & tx_pin, GPIO & rx_pin, uint32_t baud_rate);

private:
    void set_baud_rate(uint32_t baud_rate);

    Clock& clock_;
    Register<uint32_t> CR1;
    Register<uint32_t> CR2;
    Register<uint32_t> CR3;
    Register<uint32_t> BRR;
    Register<uint16_t> GTPR;
    Register<uint32_t> RTOR;
    Register<uint32_t> ISR;
    Register<uint32_t> ICR;
    Register<uint16_t> RDR;
    Register<uint16_t> TDR;
};