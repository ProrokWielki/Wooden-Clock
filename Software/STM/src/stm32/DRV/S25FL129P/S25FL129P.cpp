#include "include/DRV/S25FL129P.hpp"

S25FL129P::S25FL129P(QSPI & qspi) : qspi_(qspi)
{
}

uint16_t S25FL129P::get_manufacturer_id()
{
    auto id = qspi_.read_data_from_register(QSPI::Mode::SingleLine, 0x9F, 5);
    // uint8_t manufacturer_id_buffer[2]{};
    // spi_.read_data_from_register(cs_, 0x90, {manufacturer_id_buffer}, 2);
    return (static_cast<uint16_t>(id[0]) << 8) | id[1];
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

    auto sr_value = qspi_.read_data_from_register(QSPI::Mode::SingleLine, 0x05, 1);
    auto cr_value = qspi_.read_data_from_register(QSPI::Mode::SingleLine, 0x35, 1);

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

    auto sr_value = qspi_.read_data_from_register(QSPI::Mode::SingleLine, 0x05, 1);
    auto cr_value = qspi_.read_data_from_register(QSPI::Mode::SingleLine, 0x35, 1);

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
    auto status = qspi_.read_data_from_register(QSPI::Mode::SingleLine, 0x05, 1);
    return (status[0] & 0x01) != 0;
}

bool S25FL129P::is_write_enabled()
{
    auto status = qspi_.read_data_from_register(QSPI::Mode::SingleLine, 0x05, 1);
    return (status[0] & 0x02) != 0;
}

void S25FL129P::enable_write()
{
    qspi_.send_command(QSPI::Mode::SingleLine, 0x06);
}