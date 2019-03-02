#include <stdint.h>
#include <string.h>

#include "Display/Display.hpp"
#include "HAL.hpp"

#include "APP/Assets/Images/Images.hpp"

int main(void)
{

    NVIC_EnableIRQ(DMA1_Channel2_IRQn);
    NVIC_EnableIRQ(DMA1_Channel4_IRQn);
    NVIC_EnableIRQ(DMA2_Channel7_IRQn);
    NVIC_EnableIRQ(DMA2_Channel2_IRQn);

    HAL::init();

    SystemCoreClockUpdate();

    HAL::ROW_MULTIPLEXER::init();

    for (uint8_t i = 0; i < 32; i++)
        HAL::ROW_MULTIPLEXER::shift_bit(eHigh);

    HAL::COLUIMNS_1::init();
    HAL::COLUIMNS_2::init();
    HAL::COLUIMNS_3::init();
    HAL::COLUIMNS_4::init();

    HAL::DMA1_2::enable_interrupt(eTransferCompleted);
    HAL::DMA1_4::enable_interrupt(eTransferCompleted);
    HAL::DMA2_7::enable_interrupt(eTransferCompleted);
    HAL::DMA2_2::enable_interrupt(eTransferCompleted);

    HAL::PB13::set_mode(eOutput);
    HAL::PB13::set_speed(eVeryHighSpeed);

    uint8_t first[] = {0, 0x08};
    uint8_t second[] = {0xAA, 0xAA};

    HAL::COLUIMNS_1::set_registers_values(0x00, first, 2);
    HAL::COLUIMNS_2::set_registers_values(0x00, first, 2);
    HAL::COLUIMNS_3::set_registers_values(0x00, first, 2);
    HAL::COLUIMNS_4::set_registers_values(0x00, first, 2);

    HAL::COLUIMNS_1::set_registers_values(0x0C, second, 2);
    HAL::COLUIMNS_2::set_registers_values(0x0C, second, 2);
    HAL::COLUIMNS_3::set_registers_values(0x0C, second, 2);
    HAL::COLUIMNS_4::set_registers_values(0x0C, second, 2);

    uint32_t magic_counter = 0;

    Display display(32, 32, Arrows2);

    DMA2_CSELR->CSELR |= (5 << 24);
    DMA1_CSELR->CSELR |= ((3 << 12) | (3 << 4));

    for (;;) {

        display.draw();

        for (uint32_t i = 0; i < 2500; i++)
            ;

        if (magic_counter == 100) {
            display.set_frame_buffer(Arrows1);
        } else if (magic_counter == 200) {
            display.set_frame_buffer(Arrows2);
            magic_counter = 0;
        }
        magic_counter++;
    }
    return 0;
}
