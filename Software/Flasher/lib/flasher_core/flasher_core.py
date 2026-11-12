from lib.message_handler.message_handler import MessageHandler

import logging
import math


class Flasher:
    def __init__(self, message_handler: MessageHandler) -> None:
        self.logger = logging.getLogger(__name__)

        self.message_handler = message_handler

    def erase_external_flash(self, first_page: int, num_of_pages: int) -> None:
        self.logger.info("Requesting external flash erase")
        self.logger.debug(f"{num_of_pages=}")

        self.message_handler.send_page_erase_message(MessageHandler.Flash.EXTERNAL, first_page, num_of_pages)

        self.__print_erase_progress(num_of_pages)

    def erase_internal_flash(self, first_page: int, num_of_pages: int) -> None:
        self.logger.info("Requesting internal flash erase")
        self.logger.debug(f"{num_of_pages=}")

        self.message_handler.send_page_erase_message(MessageHandler.Flash.INTERNAL, first_page, num_of_pages)

        self.__print_erase_progress(num_of_pages)

    def flash(self, start_address: int, data_to_flash: bytes) -> None:
        num_of_bytes_to_send = len(data_to_flash)
        num_of_transfers = math.ceil(num_of_bytes_to_send / MessageHandler.TRANSFER_SIZE)
        filled_data = self.__fill_transfer_data_to_transfer_size(start_address, data_to_flash)

        for i in range(num_of_transfers):
            self.message_handler.send_command_message(MessageHandler.Command.NEXT_TRANSFER)

            received_status = self.message_handler.wait_for_status_message()
            if received_status != MessageHandler.Status.WAITING_FOR_NEXT_PAGE:
                self.logger.error("Requesting next transfer failed.")
                exit(1)

            self.logger.info_overwritable(f"Writing... {i+1}/{num_of_transfers}")

            self.message_handler.send_data_write_message(
                start_address + i * MessageHandler.TRANSFER_SIZE,
                filled_data[i * MessageHandler.TRANSFER_SIZE : (i + 1) * MessageHandler.TRANSFER_SIZE],
                min(num_of_bytes_to_send - i * MessageHandler.TRANSFER_SIZE, MessageHandler.TRANSFER_SIZE),
            )

            received_status = self.message_handler.wait_for_status_message()
            if received_status != MessageHandler.Status.IDLE:
                self.logger.error("Page program failed.")
                exit(1)

        self.message_handler.send_command_message(MessageHandler.Command.FINISHED)

        received_status = self.message_handler.wait_for_status_message()
        if received_status != MessageHandler.Status.IDLE:
            self.logger.error("Flashing failed.")
            exit(1)

        self.logger.info("Flash done.")

    def __print_erase_progress(self, num_of_pages: int) -> None:
        received_status = self.message_handler.wait_for_status_message()
        erased_page = 0
        while received_status == MessageHandler.Status.ERASING_IN_PROGRESS:
            erased_page += 1
            self.logger.info_overwritable(f"Erased page: {erased_page}/{num_of_pages}")
            received_status = self.message_handler.wait_for_status_message()

        if received_status != MessageHandler.Status.IDLE:
            self.logger.error("Page erase failed.")
            exit(1)
        self.logger.info("Erase done.")

    def __fill_transfer_data_to_transfer_size(self, start_address: int, data: bytes) -> bytes:
        num_of_full_transfers = math.ceil((start_address + len(data)) / MessageHandler.TRANSFER_SIZE)
        return data.ljust(num_of_full_transfers * MessageHandler.TRANSFER_SIZE, b"\xff")
