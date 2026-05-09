#include "include/HAL/Flash.hpp"

#include <HAL/types.hpp>

#include <cmsis_bridge/cmsis_bridge.hpp>

Flash::Flash() : ACR{to_address(Flash_Types::FlashRegister::ACR)}
{
}

void Flash::set_latency()
{
    // ACR.set_bit(uint8_t u8Position)

    // FLASH->ACR |= FLASH_ACR_LATENCY_4WS;  // Latency set to 4 wait states
    ACR.set_value(4, 0, 3);
}

void Flash::enable_prefetch()
{
    constexpr uint8_t PREFETCH_ENABLE_BIT_POSITION{8};
    ACR.set_bit(PREFETCH_ENABLE_BIT_POSITION);  // Prefetch enable
}

void Flash::enable_data_cache()
{
    constexpr uint8_t DATA_CACHE_ENABLE_BIT_POSITION{10};
    ACR.set_bit(DATA_CACHE_ENABLE_BIT_POSITION);  // Data cache enable
}

void Flash::enable_instruction_cache()
{
    constexpr uint8_t INSTRUCTION_CACHE_ENABLE_BIT_POSITION{9};
    ACR.set_bit(INSTRUCTION_CACHE_ENABLE_BIT_POSITION);  // Instruction cache enable
}