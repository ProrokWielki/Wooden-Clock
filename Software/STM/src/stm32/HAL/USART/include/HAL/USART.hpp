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
#include <functional>

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

    [[nodiscard]] uint8_t get_received_data();

    void handle_interrupts();

    void set_buffer_not_empty_callback(std::function<void(uint8_t)>);
    void set_idle_callback(std::function<void()>);

private:
    void set_baud_rate(uint32_t baud_rate);

    [[nodiscard]] bool is_read_buffer_not_empty() const;
    void handle_read_buffer_not_empty();

    [[nodiscard]] bool is_idle_interrupt() const;
    void handle_idle_interrupt();
    void clear_idle_interrupt();

    std::function<void(uint8_t)> buffer_not_empty_callback_{};
    std::function<void()> idle_callback_{};

    Clock & clock_;
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