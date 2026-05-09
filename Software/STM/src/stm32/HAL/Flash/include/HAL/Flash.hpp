#pragma once

#include <cstdint>

#include <HAL/Register.hpp>

class Flash
{
public:
    Flash();

    void set_latency();
    void enable_prefetch();
    void enable_data_cache();
    void enable_instruction_cache();

private:
    Register<uint32_t> ACR;
};