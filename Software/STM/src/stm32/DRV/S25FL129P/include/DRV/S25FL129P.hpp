#pragma once

#include <span>

#include <HAL/GPIO.hpp>
#include <HAL/QSPI.hpp>

class S25FL129P
{
public:
    S25FL129P(QSPI & qspi);

    uint64_t get_manufacturer_id();
    void erase_256kb_sector(uint8_t sector);
    void erase_chip();
    void write_data(uint32_t address, std::span<uint8_t> data);
    void switch_to_memory_mapped_mode();

private:
    [[nodiscard]] bool is_erase_in_progress() const;
    [[nodiscard]] bool is_erase_enabled() const;
    [[nodiscard]] bool is_write_in_progress() const;
    [[nodiscard]] bool is_write_enabled() const;

    void switch_to_quad_mode();
    void write_register(const std::span<const uint8_t> data);
    [[nodiscard]] uint8_t get_status_register_value() const;
    [[nodiscard]] uint8_t get_configuration_register_value() const;

    void enable_write();
    void enable_erase();

    QSPI & qspi_;
};