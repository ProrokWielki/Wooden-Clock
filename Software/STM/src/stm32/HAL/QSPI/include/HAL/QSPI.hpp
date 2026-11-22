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

    QSPI(Clock & clock, GPIO & IO1, GPIO & IO2, GPIO & IO3, GPIO & IO4, GPIO & SCK, GPIO & CS, uint32_t frequency, uint32_t flash_size);

    void enable_memory_mapped_mode(uint8_t instruction);
    void disable_memory_mapped_mode();
    std::span<uint8_t> read_data_from_register(Mode mode, uint8_t instruction, const std::span<uint8_t> read_data_buffer);
    void send_command(Mode mode, uint8_t instruction);
    void send_command(Mode mode, uint8_t instruction, uint32_t address);
    void write_data(Mode mode, uint8_t instruction, const std::span<const uint8_t> data_to_write);
    void write_data(Mode mode, uint8_t instruction, uint32_t address, const std::span<const uint8_t> data_to_write);
    void enable();
    void disable();

private:
    void set_flash_size(uint32_t flash_size);

    void set_num_of_address_lines(Register<uint32_t> & ccr, QSPI_types::AddressLines num_of_address_lines);
    void set_address_size(Register<uint32_t> & ccr, QSPI_types::AddressSize address_size);
    void set_num_of_instruction_lines(Register<uint32_t> & ccr, QSPI_types::InstructionLines num_of_instruction_lines);
    void set_num_of_data_lines(Register<uint32_t> & ccr, QSPI_types::DataLines num_of_data_lines);
    void set_alternate_bytes(Register<uint32_t> & ccr, QSPI_types::AlternateBytes alternate_bytes);
    void set_mode(Register<uint32_t> & ccr, QSPI_types::Mode mode);
    void set_num_of_dummy_cycles(Register<uint32_t> & ccr, uint8_t num_of_dummy_cycles);
    void set_instruction(Register<uint32_t> & ccr, uint8_t instruction);

    [[nodiscard]] bool is_busy() const;

    Register<uint32_t> CR;
    Register<uint32_t> DCR;
    Register<uint32_t> CCR;
    Register<uint32_t> SR;
    Register<uint32_t> DLR;
    Register<uint32_t> DR;
    Register<uint32_t> FCR;
    Register<uint32_t> AR;
};
