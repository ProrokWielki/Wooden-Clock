
#include "bootloader.hpp"

#include <FreeRTOS.h>
#include <cstdint>
#include <task.h>

#include <stm32l452xx.h>

#include "flashing_command.pb.h"
#include "flashing_start.pb.h"
#include "page_data.pb.h"
#include "pb_decode.h"
#include "pb_encode.h"

#include "flashing_msg.pb.h"

#include <span>

#include "peripherals/internal_flash.hpp"
#include "peripherals/qspi.hpp"
#include "peripherals/s25fl129.hpp"
#include "peripherals/uart.hpp"

#include "message_handler/message_handler.hpp"

__attribute__((section(".flasher_section"), noinline)) static void external_flash_disable_memory_mapped_mode()
{
    QUADSPI->CR |= QUADSPI_CR_ABORT;

    while (QUADSPI->CR & QUADSPI_CR_ABORT)
        ;

    QUADSPI->CCR &= ~QUADSPI_CCR_FMODE;

    QUADSPI->FCR = QUADSPI_FCR_CTCF | QUADSPI_FCR_CTEF | QUADSPI_FCR_CTOF;

    S25FL129::enable_write();
}

__attribute__((section(".flasher_section"), noinline)) void flash()
{
    __disable_irq();
    vTaskSuspendAll();

    MessageHandler::send_state_message(FlashingState::FlashingState_IDLE);

    auto flashing_message = MessageHandler::get_flashing_start_message();

    if (flashing_message.flash == Flash_INTERNAL)
    {
        InternalFlash::unlock();

        for (uint32_t current_page_to_erase{flashing_message.start_page}; current_page_to_erase < flashing_message.num_of_pages; ++current_page_to_erase)
        {
            InternalFlash::erase_page(current_page_to_erase);
            MessageHandler::send_state_message(FlashingState::FlashingState_ERASING_IN_PROGRESS);
        }

        MessageHandler::send_state_message(FlashingState::FlashingState_IDLE);

        auto flashing_command = MessageHandler::get_flashing_command_message();

        while (flashing_command != FlashingCommand_FINISHED)
        {

            MessageHandler::send_state_message(FlashingState::FlashingState_WAITING_FOR_NEXT_PAGE);

            auto page_data = MessageHandler::get_write_data_message();

            InternalFlash::write_page(page_data.address, page_data.data, page_data.size);

            MessageHandler::send_state_message(FlashingState::FlashingState_IDLE);

            flashing_command = MessageHandler::get_flashing_command_message();
        }
    }

    MessageHandler::send_state_message(FlashingState::FlashingState_IDLE);

    flashing_message = MessageHandler::get_flashing_start_message();
    if (flashing_message.flash == Flash_EXTERNAL)
    {
        uint8_t num_of_pages = flashing_message.num_of_pages;
        uint32_t num_of_sectors_to_erase = num_of_pages / 128 + ((num_of_pages % 128) ? 1 : 0);

        external_flash_disable_memory_mapped_mode();
        for (uint32_t current_sector = 0; current_sector < num_of_sectors_to_erase; ++current_sector)
        {
            S25FL129::erase_256kb_sector(current_sector);
            MessageHandler::send_state_message(FlashingState::FlashingState_ERASING_IN_PROGRESS);
        }

        MessageHandler::send_state_message(FlashingState::FlashingState_IDLE);

        auto flashing_command = MessageHandler::get_flashing_command_message();

        while (flashing_command != FlashingCommand_FINISHED)
        {
            MessageHandler::send_state_message(FlashingState::FlashingState_WAITING_FOR_NEXT_PAGE);

            auto page_data = MessageHandler::get_write_data_message();

            S25FL129::write_data(page_data.address, {page_data.data, page_data.size});

            MessageHandler::send_state_message(FlashingState::FlashingState_IDLE);

            flashing_command = MessageHandler::get_flashing_command_message();
        }
    }

    MessageHandler::send_state_message(FlashingState::FlashingState_FLASHING_DONE);

    while (!(UART4->ISR & (1 << 6)))
        ;

    // reset
    SCB->AIRCR = ((0x5FAUL << 16) | (1 << 2));

    for (;;)
    {
        asm("nop");
    }
}
