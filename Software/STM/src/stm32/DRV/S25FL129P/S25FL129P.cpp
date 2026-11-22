#include "include/DRV/S25FL129P.hpp"
#include <array>
#include <cstdint>
#include <limits>

S25FL129P::S25FL129P(QSPI & qspi) : qspi_(qspi)
{
}

uint64_t S25FL129P::get_manufacturer_id()
{
    constexpr uint8_t MANUFACTURER_ID_LENGTH{5};
    std::array<uint8_t, MANUFACTURER_ID_LENGTH> id_buffer{};

    constexpr uint8_t READ_IDENTIFICATION_INSTRUCTION{0x9F};
    auto id = qspi_.read_data_from_register(QSPI::Mode::SingleLine, READ_IDENTIFICATION_INSTRUCTION, id_buffer);

    uint64_t manufacturer_id{};
    for (uint8_t current_byte_index{0}; current_byte_index < MANUFACTURER_ID_LENGTH; ++current_byte_index)
    {
        const uint8_t last_byte_index{MANUFACTURER_ID_LENGTH - 1};
        const uint8_t current_offset = (last_byte_index - current_byte_index) * std::numeric_limits<uint8_t>::digits;
        manufacturer_id |= (id[current_byte_index] << (current_offset));
    }

    return manufacturer_id;
}

void S25FL129P::erase_256kb_sector(uint8_t sector)
{
    enable_erase();

    if (!is_erase_enabled())
    {
        return;
    }

    constexpr uint32_t SECTOR_SIZE{0x40000};  // 256kB
    constexpr uint8_t ERASE_COMMAND{0xD8};

    const uint32_t address = sector * SECTOR_SIZE;
    qspi_.send_command(QSPI::Mode::SingleLine, ERASE_COMMAND, address);

    while (is_erase_in_progress())
        ;
}

void S25FL129P::erase_chip()
{
    enable_erase();

    if (!is_erase_enabled())
    {
        return;
    }

    qspi_.send_command(QSPI::Mode::SingleLine, 0xC7);

    while (is_erase_in_progress())
        ;
}

void S25FL129P::write_data(uint32_t address, std::span<uint8_t> data)
{
    switch_to_quad_mode();

    enable_write();

    constexpr uint8_t QUAD_WRITE_INSTRUCTION{0x32};
    qspi_.write_data(QSPI::Mode::QuadLine, QUAD_WRITE_INSTRUCTION, address, data);

    while (is_write_in_progress())
        ;
}

void S25FL129P::switch_to_memory_mapped_mode()
{
    switch_to_quad_mode();

    constexpr uint8_t QUAD_READ_INSTRUCTION{0x6B};
    qspi_.enable_memory_mapped_mode(QUAD_READ_INSTRUCTION);
}

bool S25FL129P::is_erase_in_progress() const
{
    return is_write_in_progress();
}

bool S25FL129P::is_erase_enabled() const
{
    return is_write_enabled();
}

void S25FL129P::enable_erase()
{
    enable_write();
}

bool S25FL129P::is_write_in_progress() const
{
    auto status = get_status_register_value();
    return (status & 0x01) != 0;
}

bool S25FL129P::is_write_enabled() const
{
    auto status = get_status_register_value();
    return (status & 0x02) != 0;
}

uint8_t S25FL129P::get_status_register_value() const
{
    std::array<uint8_t, 1> status_buffer{};

    constexpr uint8_t READ_STATUS_REGISTER_INSTRUCTION{0x05};
    auto status = qspi_.read_data_from_register(QSPI::Mode::SingleLine, READ_STATUS_REGISTER_INSTRUCTION, status_buffer);

    return status[0];
}

uint8_t S25FL129P::get_configuration_register_value() const
{
    std::array<uint8_t, 1> configuration_buffer{};

    constexpr uint8_t READ_CONFIGURATION_REGISTER_INSTRUCTION{0x35};
    auto configuration = qspi_.read_data_from_register(QSPI::Mode::SingleLine, READ_CONFIGURATION_REGISTER_INSTRUCTION, configuration_buffer);

    return configuration[0];
}

void S25FL129P::write_register(const std::span<const uint8_t> data)
{
    constexpr uint8_t WRITE_REGISTER_INSTRUCTION{0x01};
    qspi_.write_data(QSPI::Mode::SingleLine, WRITE_REGISTER_INSTRUCTION, data);
}

void S25FL129P::switch_to_quad_mode()
{
    while (is_write_in_progress())
        ;

    auto sr_value = get_status_register_value();
    auto cr_value = get_configuration_register_value();

    std::array<uint8_t, 2> data_to_send{sr_value, static_cast<uint8_t>(cr_value | 0x02)};

    enable_write();

    write_register(data_to_send);

    while (is_write_in_progress())
        ;
}

void S25FL129P::enable_write()
{
    qspi_.send_command(QSPI::Mode::SingleLine, 0x06);
}