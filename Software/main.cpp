#include <stdint.h>
#include <string.h>

#include "HAL.hpp"

#include "APP/Assets/Images/Images.hpp"

int main(void)
{

    NVIC_EnableIRQ(DMA1_Channel2_IRQn);
    NVIC_EnableIRQ(DMA1_Channel4_IRQn);
    NVIC_EnableIRQ(DMA1_Channel6_IRQn);
    NVIC_EnableIRQ(DMA2_Channel2_IRQn);

    HAL::init();

    SystemCoreClockUpdate();

    HAL::ROW_MULTIPLEXER::init();

    HAL::COLUIMNS_1::init();
    HAL::COLUIMNS_2::init();
    HAL::COLUIMNS_3::init();
    HAL::COLUIMNS_4::init();

    HAL::PB13::set_mode(eOutput);
    HAL::PB13::set_speed(eVeryHighSpeed);

    HAL::COLUIMNS_1::set_register_value(0, 0);
    HAL::COLUIMNS_2::set_register_value(0, 0);
    HAL::COLUIMNS_3::set_register_value(0, 0);
    HAL::COLUIMNS_4::set_register_value(0, 0);

    HAL::COLUIMNS_1::set_register_value(1, 0x08);
    HAL::COLUIMNS_2::set_register_value(1, 0x08);
    HAL::COLUIMNS_3::set_register_value(1, 0x08);
    HAL::COLUIMNS_4::set_register_value(1, 0x08);

    HAL::COLUIMNS_1::set_register_value(0x0C, 0b10101010);
    HAL::COLUIMNS_2::set_register_value(0x0C, 0xAA);
    HAL::COLUIMNS_3::set_register_value(0x0C, 0b10101010);
    HAL::COLUIMNS_4::set_register_value(0x0C, 0b10101010);

    HAL::COLUIMNS_1::set_register_value(0x0D, 0b10101010);
    HAL::COLUIMNS_2::set_register_value(0x0D, 0xAA);
    HAL::COLUIMNS_3::set_register_value(0x0D, 0b10101010);
    HAL::COLUIMNS_4::set_register_value(0x0D, 0b10101010);

    uint32_t currentLine = 0;

    //  DMA2_CSELR->CSELR;
    DMA1_CSELR->CSELR |= ((3 << 20) | (3 << 12) | (3 << 4));

    HAL::COLUIMNS_1::set_all_leds_value(&(Mario_pixel_map[0]));
    HAL::COLUIMNS_2::set_all_leds_value(&(Mario_pixel_map[8]));
    HAL::COLUIMNS_3::set_all_leds_value(&(Mario_pixel_map[16]));
    HAL::COLUIMNS_4::set_all_leds_value(&(Mario_pixel_map[24]));

    HAL::ROW_MULTIPLEXER::output_enable(false);

    HAL::ROW_MULTIPLEXER::clear();

    for (;;) {

        HAL::ROW_MULTIPLEXER::output_enable(false);

        if (0 == currentLine) {
            HAL::ROW_MULTIPLEXER::shift_bit(eLow);
        } else
            HAL::ROW_MULTIPLEXER::shift_bit(eHigh);

        HAL::ROW_MULTIPLEXER::output_enable(true);

        for (uint32_t i = 0; i < 1500; i++)
            ;

        if (32 == ++currentLine) {
            currentLine = 0;
        }
    }
    return 0;
}
