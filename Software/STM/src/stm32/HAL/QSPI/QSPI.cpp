#include <cassert>
#include <cstdint>
#include <span>

#include <cmsis_bridge/cmsis_bridge.hpp>

#include <HAL/Clock.hpp>
#include <HAL/GPIO.hpp>
#include <HAL/QSPI.hpp>
#include <HAL/Register.hpp>
#include <HAL/types.hpp>

QSPI::QSPI(Clock & clock, GPIO & IO1, GPIO & IO2, GPIO & IO3, GPIO & IO4, GPIO & SCK, GPIO & CS, uint32_t frequency)
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

    enable();
}

std::span<uint8_t> QSPI::read_data_from_register(Mode mode, uint8_t instruction, std::span<uint8_t> read_data_buffer)
{
    while (is_busy())
        ;

    DLR.write(read_data_buffer.size() - 1);

    Register<uint32_t> ccr{CCR.read()};
    if (mode == Mode::SingleLine)
    {
        ccr.set_value(1, 8, 2);   // 1 line instruction
        ccr.set_value(0, 10, 2);  // no address
        ccr.set_value(1, 24, 2);  // 1 line data
        ccr.set_value(1, 26, 2);  // 1 line data
    }
    else
    {
        assert(false && "Only single line mode is supported for now");
    }

    constexpr static uint8_t INSTRUCTION_BIT_POSITION{0};
    constexpr static uint8_t INSTRUCTION_BIT_LENGTH{8};
    ccr.set_value(instruction, INSTRUCTION_BIT_POSITION, INSTRUCTION_BIT_LENGTH);  // Set the instruction

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
        ccr.set_value(1, 8, 2);   // 1 line instruction
        ccr.set_value(0, 10, 2);  // no address
        ccr.set_value(0, 24, 2);  // no data
        ccr.set_value(0, 26, 2);  // no data
    }
    else
    {
        assert(false && "Only single line mode is supported for now");
    }

    constexpr static uint8_t INSTRUCTION_BIT_POSITION{0};
    constexpr static uint8_t INSTRUCTION_BIT_LENGTH{8};
    ccr.set_value(instruction, INSTRUCTION_BIT_POSITION, INSTRUCTION_BIT_LENGTH);  // Set the instruction

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
        ccr.set_value(1, 8, 2);   // 1 line instruction
        ccr.set_value(1, 10, 2);  // 1 line address
        ccr.set_value(2, 12, 2);  // 24 bit address
        ccr.set_value(0, 24, 2);  // no data
        ccr.set_value(0, 26, 2);  // indirect write
    }
    else
    {
        assert(false && "Only single line mode is supported for now");
    }

    constexpr static uint8_t INSTRUCTION_BIT_POSITION{0};
    constexpr static uint8_t INSTRUCTION_BIT_LENGTH{8};
    ccr.set_value(instruction, INSTRUCTION_BIT_POSITION, INSTRUCTION_BIT_LENGTH);  // Set the instruction

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

    DCR.set_value(23, 16, 5);  // fsize - 24 bit address
    DCR.set_value(4, 8, 3);    // csht - 4 cycle chip select high time

    uint32_t cr_value = 0;
    Register<uint32_t> ccr{&cr_value};

    ccr.set_value(1, 8, 2);   // 1 line instruction
    ccr.set_value(1, 10, 2);  // address on 1 line
    ccr.set_value(2, 12, 2);  // 24 bit address
    ccr.set_value(0, 14, 2);  // no alternate bytes
    ccr.set_value(8, 18, 5);  // 8 dummy cycles
    ccr.set_value(3, 24, 2);  // dmode - 4 lines data
    ccr.set_value(3, 26, 2);  // memory-mapped mode

    constexpr static uint8_t INSTRUCTION_BIT_POSITION{0};
    constexpr static uint8_t INSTRUCTION_BIT_LENGTH{8};
    ccr.set_value(instruction, INSTRUCTION_BIT_POSITION, INSTRUCTION_BIT_LENGTH);  // Set the instruction

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

void QSPI::write_data(Mode mode, uint8_t instruction, const std::span<uint8_t> data_to_write)
{
    while (is_busy())
        ;

    DLR.write(data_to_write.size() - 1);

    Register<uint32_t> ccr{CCR.read()};
    if (mode == Mode::SingleLine)
    {
        ccr.set_value(1, 8, 2);   // 1 line instruction
        ccr.set_value(0, 10, 2);  // no address
        ccr.set_value(1, 24, 2);  // 1 line data
        ccr.set_value(0, 26, 2);  // 1 indirect write
    }
    else
    {
        assert(false && "Only single line mode is supported for now");
    }

    constexpr static uint8_t INSTRUCTION_BIT_POSITION{0};
    constexpr static uint8_t INSTRUCTION_BIT_LENGTH{8};
    ccr.set_value(instruction, INSTRUCTION_BIT_POSITION, INSTRUCTION_BIT_LENGTH);  // Set the instruction

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

void QSPI::write_data(Mode mode, uint8_t instruction, uint32_t address, const std::span<uint8_t> data_to_write)
{
    while (is_busy())
        ;

    DLR.write(data_to_write.size() - 1);
    AR.write(address);

    Register<uint32_t> ccr{CCR.read()};
    if (mode == Mode::QuadLine)
    {
        ccr.set_value(1, 8, 2);   // 1 line instruction
        ccr.set_value(1, 10, 2);  // no address
        ccr.set_value(2, 12, 2);  // 24-bit address
        ccr.set_value(3, 24, 2);  // 4 line data
        ccr.set_value(0, 26, 2);  // 1 indirect write
    }
    else
    {
        assert(false && "Only quad line mode is supported for now");
    }

    constexpr static uint8_t INSTRUCTION_BIT_POSITION{0};
    constexpr static uint8_t INSTRUCTION_BIT_LENGTH{8};
    ccr.set_value(instruction, INSTRUCTION_BIT_POSITION, INSTRUCTION_BIT_LENGTH);  // Set the instruction

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
