#pragma once

#include <span>

#include <HAL/GPIO.hpp>
#include <HAL/QSPI.hpp>

class S25FL129P
{
public:
    S25FL129P(QSPI & qspi);

    uint16_t get_manufacturer_id();
    void erase_sector(uint8_t sector);
    void erase_chip();
    void write_data(uint32_t address, std::span<uint8_t> data);
    void switch_to_memory_mapped_mode();

private:
    bool is_erase_in_progress();
    bool is_erase_enabled();
    bool is_write_in_progress();
    bool is_write_enabled();

    void enable_write();
    void enable_erase();

    QSPI & qspi_;
};