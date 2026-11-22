#include <cassert>
#include <cstdint>
#include <limits>
#include <span>

#include <cmsis_bridge/cmsis_bridge.hpp>

#include <HAL/Clock.hpp>
#include <HAL/GPIO.hpp>
#include <HAL/QSPI.hpp>
#include <HAL/Register.hpp>
#include <HAL/types.hpp>

QSPI::QSPI(Clock & clock, GPIO & IO1, GPIO & IO2, GPIO & IO3, GPIO & IO4, GPIO & SCK, GPIO & CS, uint32_t frequency, uint32_t flash_size)
: CR{to_address(QSPI_types::Register::CR)}, DCR{to_address(QSPI_types::Register::DCR)}, CCR{to_address(QSPI_types::Register::CCR)},
  SR{to_address(QSPI_types::Register::SR)}, DLR{to_address(QSPI_types::Register::DLR)}, DR{to_address(QSPI_types::Register::DR)},
  FCR{to_address(QSPI_types::Register::FCR)}, AR{to_address(QSPI_types::Register::AR)}
{
    clock.enable_clock_for(Peripheral::QSPI);

    IO1.set_as_spi_pin(GPIO_Types::AlternateFunction::AF10);
    IO2.set_as_spi_pin(GPIO_Types::AlternateFunction::AF10);
    IO3.set_as_spi_pin(GPIO_Types::AlternateFunction::AF10);
    IO4.set_as_spi_pin(GPIO_Types::AlternateFunction::AF10);
    SCK.set_as_spi_pin(GPIO_Types::AlternateFunction::AF10);
    CS.set_as_spi_pin(GPIO_Types::AlternateFunction::AF10);

    const auto prescaler{clock.get_clock_frequency() / frequency};
    constexpr static uint8_t PRESCALER_BIT_POSITION{24};
    constexpr static uint8_t PRESCALER_BIT_LENGTH{8};
    CR.set_value(prescaler - 1, PRESCALER_BIT_POSITION, PRESCALER_BIT_LENGTH);

    constexpr uint8_t NUM_OF_CS_HIGH_CYCLES{5};
    constexpr uint8_t NUM_OF_CS_HIGH_CYCLES_POSITION{8};
    constexpr uint8_t NUM_OF_CS_HIGH_CYCLES_LENGTH{3};
    DCR.set_value(NUM_OF_CS_HIGH_CYCLES - 1, NUM_OF_CS_HIGH_CYCLES_POSITION, NUM_OF_CS_HIGH_CYCLES_LENGTH);

    set_flash_size(flash_size);

    enable();
}

std::span<uint8_t> QSPI::read_data_from_register(Mode mode, uint8_t instruction, const std::span<uint8_t> read_data_buffer)
{
    while (is_busy())
        ;

    DLR.write(read_data_buffer.size() - 1);

    Register<uint32_t> ccr{CCR.read()};
    if (mode == Mode::SingleLine)
    {
        set_num_of_instruction_lines(ccr, QSPI_types::InstructionLines::LINES_1);
        set_num_of_address_lines(ccr, QSPI_types::AddressLines::NO_ADDRESS);
        set_num_of_data_lines(ccr, QSPI_types::DataLines::LINES_1);
        set_mode(ccr, QSPI_types::Mode::INDIRECT_READ);
    }
    else
    {
        assert(false && "Only single line mode is supported for now");
    }

    set_instruction(ccr, instruction);

    CCR.write(ccr.read());

    for (auto & byte : read_data_buffer)
    {
        while (!(SR.get_bit(2) || SR.get_bit(1)))
            ;
        byte = DR.read<uint8_t>();
    }

    return read_data_buffer;
}

void QSPI::send_command(Mode mode, uint8_t instruction)
{
    while (is_busy())
        ;

    Register<uint32_t> ccr{CCR.read()};
    if (mode == Mode::SingleLine)
    {
        set_num_of_instruction_lines(ccr, QSPI_types::InstructionLines::LINES_1);
        set_num_of_address_lines(ccr, QSPI_types::AddressLines::NO_ADDRESS);
        set_num_of_data_lines(ccr, QSPI_types::DataLines::NO_DATA);
        set_mode(ccr, QSPI_types::Mode::INDIRECT_WRITE);
    }
    else
    {
        assert(false && "Only single line mode is supported for now");
    }

    set_instruction(ccr, instruction);

    CCR.write(ccr.read());
}

void QSPI::send_command(Mode mode, uint8_t instruction, uint32_t address)
{
    while (is_busy())
        ;

    AR.write(address);
    Register<uint32_t> ccr{CCR.read()};
    if (mode == Mode::SingleLine)
    {
        set_num_of_instruction_lines(ccr, QSPI_types::InstructionLines::LINES_1);
        set_num_of_address_lines(ccr, QSPI_types::AddressLines::LINES_1);
        set_address_size(ccr, QSPI_types::AddressSize::BITS_24);
        set_num_of_data_lines(ccr, QSPI_types::DataLines::NO_DATA);
        set_mode(ccr, QSPI_types::Mode::INDIRECT_WRITE);
    }
    else
    {
        assert(false && "Only single line mode is supported for now");
    }

    set_instruction(ccr, instruction);

    CCR.write(ccr.read());
}

void QSPI::enable()
{
    CR.set_bit(0);
}

void QSPI::disable()
{
    CR.clear_bit(0);
}

bool QSPI::is_busy() const
{
    constexpr static uint8_t BUSY_BIT_POSITION{5};
    return SR.get_bit(BUSY_BIT_POSITION);
}

void QSPI::enable_memory_mapped_mode(uint8_t instruction)
{
    while (is_busy())
        ;

    Register<uint32_t> ccr{CCR.read()};

    set_num_of_instruction_lines(ccr, QSPI_types::InstructionLines::LINES_1);
    set_num_of_address_lines(ccr, QSPI_types::AddressLines::LINES_1);
    set_address_size(ccr, QSPI_types::AddressSize::BITS_24);
    set_alternate_bytes(ccr, QSPI_types::AlternateBytes::NO_ALTERNATE_BYTES);
    set_num_of_data_lines(ccr, QSPI_types::DataLines::LINES_4);
    set_mode(ccr, QSPI_types::Mode::MEMORY_MAPPED);

    constexpr uint8_t NUM_OF_DUMMY_CYCLES{8};
    set_num_of_dummy_cycles(ccr, NUM_OF_DUMMY_CYCLES);

    set_instruction(ccr, instruction);
    CCR.write(ccr.read());

    while (is_busy())
        ;
}

void QSPI::disable_memory_mapped_mode()
{
    constexpr uint8_t ABORT_BIT_POSITION{1};

    CR.set_bit(ABORT_BIT_POSITION);

    while (CR.get_bit(ABORT_BIT_POSITION))
        ;

    constexpr uint8_t FMODE_POSTION{26};
    constexpr uint8_t FMODE_LENGTH{2};
    constexpr uint8_t INDIRECT_WRITE_MODE_VALUE{0};

    CCR.set_value(INDIRECT_WRITE_MODE_VALUE, FMODE_POSTION, FMODE_LENGTH);
}

void QSPI::write_data(Mode mode, uint8_t instruction, const std::span<const uint8_t> data_to_write)
{
    while (is_busy())
        ;

    DLR.write(data_to_write.size() - 1);

    Register<uint32_t> ccr{CCR.read()};
    if (mode == Mode::SingleLine)
    {
        set_num_of_instruction_lines(ccr, QSPI_types::InstructionLines::LINES_1);
        set_num_of_address_lines(ccr, QSPI_types::AddressLines::NO_ADDRESS);
        set_num_of_data_lines(ccr, QSPI_types::DataLines::LINES_1);
        set_mode(ccr, QSPI_types::Mode::INDIRECT_WRITE);
    }
    else
    {
        assert(false && "Only single line mode is supported for now");
    }

    set_instruction(ccr, instruction);

    CCR.write(ccr.read());

    for (const auto & byte : data_to_write)
    {
        while (!(SR.get_bit(2) || SR.get_bit(1)))
            ;
        DR.write<uint8_t>(byte);
    }

    while (!SR.get_bit(1))
        ;
}

void QSPI::write_data(Mode mode, uint8_t instruction, uint32_t address, const std::span<const uint8_t> data_to_write)
{
    while (is_busy())
        ;

    DLR.write(data_to_write.size() - 1);
    AR.write(address);

    Register<uint32_t> ccr{CCR.read()};
    if (mode == Mode::QuadLine)
    {
        set_num_of_instruction_lines(ccr, QSPI_types::InstructionLines::LINES_1);
        set_num_of_address_lines(ccr, QSPI_types::AddressLines::LINES_1);
        set_address_size(ccr, QSPI_types::AddressSize::BITS_24);
        set_num_of_data_lines(ccr, QSPI_types::DataLines::LINES_4);
        set_mode(ccr, QSPI_types::Mode::INDIRECT_WRITE);
    }
    else
    {
        assert(false && "Only quad line mode is supported for now");
    }

    set_instruction(ccr, instruction);

    CCR.write(ccr.read());

    for (const auto & byte : data_to_write)
    {
        while (!(SR.get_bit(2) || SR.get_bit(1)))
            ;
        DR.write<uint8_t>(byte);
    }

    while (!(SR.get_bit(2) || SR.get_bit(1)))
        ;
}

void QSPI::set_num_of_address_lines(Register<uint32_t> & ccr, QSPI_types::AddressLines num_of_address_lines)
{
    constexpr uint8_t NUM_OF_ADDRESS_LINES_POSITION{10};
    constexpr uint8_t NUM_OF_ADDRESS_LINES_LENGTH{2};

    ccr.set_value(to_value(num_of_address_lines), NUM_OF_ADDRESS_LINES_POSITION, NUM_OF_ADDRESS_LINES_LENGTH);
}

void QSPI::set_address_size(Register<uint32_t> & ccr, QSPI_types::AddressSize address_size)
{
    constexpr uint8_t ADDRESS_SIZE_POSITION{12};
    constexpr uint8_t ADDRESS_SIZE_LENGTH{2};

    ccr.set_value(to_value(address_size), ADDRESS_SIZE_POSITION, ADDRESS_SIZE_LENGTH);
}

void QSPI::set_num_of_instruction_lines(Register<uint32_t> & ccr, QSPI_types::InstructionLines num_of_instruction_lines)
{

    constexpr uint8_t NUM_OF_INSTRUCTION_LINES_POSITION{8};
    constexpr uint8_t NUM_OF_INSTRUCTION_LINES_LENGTH{2};

    ccr.set_value(to_value(num_of_instruction_lines), NUM_OF_INSTRUCTION_LINES_POSITION, NUM_OF_INSTRUCTION_LINES_LENGTH);
}

void QSPI::set_num_of_data_lines(Register<uint32_t> & ccr, QSPI_types::DataLines num_of_data_lines)
{
    constexpr uint8_t NUM_OF_DATA_LINES_POSITION{24};
    constexpr uint8_t NUM_OF_DATA_LINES_LENGTH{2};

    ccr.set_value(to_value(num_of_data_lines), NUM_OF_DATA_LINES_POSITION, NUM_OF_DATA_LINES_LENGTH);
}

void QSPI::set_alternate_bytes(Register<uint32_t> & ccr, QSPI_types::AlternateBytes alternate_bytes)
{
    constexpr uint8_t ALTERNATE_BYTES_POSITION{16};
    constexpr uint8_t ALTERNATE_BYTES_LENGTH{2};

    ccr.set_value(to_value(alternate_bytes), ALTERNATE_BYTES_POSITION, ALTERNATE_BYTES_LENGTH);
}

void QSPI::set_mode(Register<uint32_t> & ccr, QSPI_types::Mode mode)
{
    constexpr uint8_t MODE_POSITION{26};
    constexpr uint8_t MODE_LENGTH{2};

    ccr.set_value(to_value(mode), MODE_POSITION, MODE_LENGTH);
}

void QSPI::set_flash_size(uint32_t flash_size)
{
    constexpr uint8_t FLASH_SIZE_FIELD_LENGTH{5};
    constexpr uint8_t FLASH_SIZE_POSITION{16};

    uint8_t flash_size_value{0};

    // find the postion of the last(MSB) bit in the size - basically of flash_size = 2^current_bit
    for (uint8_t current_bit{std::numeric_limits<uint32_t>::digits - 1}; current_bit > 0; --current_bit)
    {
        if ((flash_size & (1 << current_bit)) != 0)
        {
            flash_size_value = current_bit;  // number of bytes in flash memory = 2^[FSIZE+1]
            break;
        }
    }

    DCR.set_value(flash_size_value, FLASH_SIZE_POSITION, FLASH_SIZE_FIELD_LENGTH);  // fsize - 24 bit address
}

void QSPI::set_num_of_dummy_cycles(Register<uint32_t> & ccr, uint8_t num_of_dummy_cycles)
{
    constexpr static uint8_t NUM_OF_DUMMY_CYCLES_POSITION{18};
    constexpr static uint8_t NUM_OF_DUMMY_CYCLES_LENGTH{5};
    ccr.set_value(num_of_dummy_cycles, NUM_OF_DUMMY_CYCLES_POSITION, NUM_OF_DUMMY_CYCLES_LENGTH);
}

void QSPI::set_instruction(Register<uint32_t> & ccr, uint8_t instruction)
{
    constexpr static uint8_t INSTRUCTION_BIT_POSITION{0};
    constexpr static uint8_t INSTRUCTION_BIT_LENGTH{8};
    ccr.set_value(instruction, INSTRUCTION_BIT_POSITION, INSTRUCTION_BIT_LENGTH);
}
