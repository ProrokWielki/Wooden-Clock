#include "include/DRV/S25FL129P.hpp"
#include <array>

S25FL129P::S25FL129P(QSPI & qspi) : qspi_(qspi)
{
}

uint64_t S25FL129P::get_manufacturer_id()
{
    constexpr uint8_t MANUFACTURER_ID_LENGTH{5};

    std::array<uint8_t, MANUFACTURER_ID_LENGTH> id_buffer{};
    auto id = qspi_.read_data_from_register(QSPI::Mode::SingleLine, 0x9F, id_buffer);

    return (static_cast<uint64_t>(id[0]) << 32) | (static_cast<uint64_t>(id[1]) << 24) | (static_cast<uint64_t>(id[2]) << 16) |
           (static_cast<uint64_t>(id[3]) << 8) | static_cast<uint64_t>(id[5]);
}

// void S25FL129P::erase_sector(uint8_t sector)
// {
//     uint32_t address = sector * 0x10000;  // Each sector is 64KB (0x10000 bytes)
//     qspi_.send_command(QSPI::Mode::SingleLine, 0x20, {reinterpret_cast<uint8_t *>(&address), reinterpret_cast<uint8_t *>(&address) + 3});
// }

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
    while (is_write_in_progress())
        ;

    std::array<uint8_t, 1> sr_buffer{};
    std::array<uint8_t, 1> cr_buffer{};

    auto sr_value = qspi_.read_data_from_register(QSPI::Mode::SingleLine, 0x05, sr_buffer);
    auto cr_value = qspi_.read_data_from_register(QSPI::Mode::SingleLine, 0x35, cr_buffer);

    std::array<uint8_t, 2> data_to_send{sr_value[0], static_cast<uint8_t>(cr_value[0] | 0x02)};

    enable_write();

    qspi_.write_data(QSPI::Mode::SingleLine, 0x01, {data_to_send});

    while (is_write_in_progress())
        ;

    enable_write();

    qspi_.write_data(QSPI::Mode::QuadLine, 0x32, address, data);

    while (is_write_in_progress())
        ;
}

void S25FL129P::switch_to_memory_mapped_mode()
{
    while (is_write_in_progress())
        ;

    std::array<uint8_t, 1> sr_buffer{};
    std::array<uint8_t, 1> cr_buffer{};

    auto sr_value = qspi_.read_data_from_register(QSPI::Mode::SingleLine, 0x05, sr_buffer);
    auto cr_value = qspi_.read_data_from_register(QSPI::Mode::SingleLine, 0x35, cr_buffer);

    std::array<uint8_t, 2> data_to_send{sr_value[0], static_cast<uint8_t>(cr_value[0] | 0x02)};

    enable_write();

    qspi_.write_data(QSPI::Mode::SingleLine, 0x01, {data_to_send});

    while (is_write_in_progress())
        ;

    qspi_.enable_memory_mapped_mode(0x6B);
}

bool S25FL129P::is_erase_in_progress()
{
    return is_write_in_progress();
}

bool S25FL129P::is_erase_enabled()
{
    return is_write_enabled();
}

void S25FL129P::enable_erase()
{
    enable_write();
}

bool S25FL129P::is_write_in_progress()
{
    std::array<uint8_t, 1> status_buffer{};
    auto status = qspi_.read_data_from_register(QSPI::Mode::SingleLine, 0x05, status_buffer);
    return (status[0] & 0x01) != 0;
}

bool S25FL129P::is_write_enabled()
{
    std::array<uint8_t, 1> status_buffer{};
    auto status = qspi_.read_data_from_register(QSPI::Mode::SingleLine, 0x05, status_buffer);
    return (status[0] & 0x02) != 0;
}

void S25FL129P::enable_write()
{
    qspi_.send_command(QSPI::Mode::SingleLine, 0x06);
}