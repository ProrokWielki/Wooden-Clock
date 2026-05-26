#pragma once

#include <cstdint>
#include <span>

#include <HAL/Register.hpp>
#include <HAL/types.hpp>

class Clock;
class GPIO;

class QSPI
{
public:
    enum class Mode
    {
        SingleLine,
        DualLine,
        QuadLine
    };

    QSPI(Clock & clock, GPIO & IO1, GPIO & IO2, GPIO & IO3, GPIO & IO4, GPIO & SCK, GPIO & CS, uint32_t frequency);

    void enable_memory_mapped_mode(uint8_t instruction);
    std::span<uint8_t> read_data_from_register(Mode mode, uint8_t instruction, uint8_t data_to_receive_length);
    void send_command(Mode mode, uint8_t instruction);
    void write_data(Mode mode, uint8_t instruction, const std::span<uint8_t> data_to_write);
    void write_data(Mode mode, uint8_t instruction, uint32_t address, const std::span<uint8_t> data_to_write);
    void enable();

private:
    [[nodiscard]] bool is_busy() const;

    Register<uint32_t> CR;
    Register<uint32_t> CCR;
    Register<uint32_t> SR;
    Register<uint32_t> DLR;
    Register<uint32_t> DR;
    Register<uint32_t> FCR;
    Register<uint32_t> AR;
};
