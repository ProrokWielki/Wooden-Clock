#!/usr/bin/python3

from lib.elf_parser.elf_parser import ElfParser
from lib.stm32l452_info.stm32l452_info import STM32L452
from lib.serial_wrapper.serial_wrapper import SerialWrapper
from lib.message_handler.message_handler import MessageHandler
from lib.flasher_core.flasher_core import Flasher
from lib.logger.logger import init_logging

import math
import argparse
import logging

parser = argparse.ArgumentParser(prog="Flasher")
parser.add_argument("--file", "-f", dest="file", required=True, help="File to be flashed")
parser.add_argument("--dev", "-d", dest="dev", required=True, help="COM port connected to the board")
parser.add_argument("-v", dest="verbosity", action="count", default=0, help="verbosity - -v -vv")
args = parser.parse_args()

log_level = 20 if args.verbosity == 0 else 10 - (args.verbosity - 1)
init_logging(log_level)


logger = logging.getLogger(__name__)


elf_parser = ElfParser(args.file)
serial_wrapper = SerialWrapper(args.dev, 115200)
message_handler = MessageHandler(serial_wrapper)
flasher = Flasher(message_handler)


logger.info("Requesting STM flashing mode")

message_handler.send_mode_message(MessageHandler.Mode.FLASHING)


received_status = message_handler.wait_for_status_message()

if received_status != MessageHandler.Status.IDLE:
    logger.error("Reset not approved")
    exit(1)

logger.info("Flashing mode accepted")


first_page = STM32L452.get_internal_flash_page_number(STM32L452.INTERNAL_FLASH_START_ADDRESS)
last_page = STM32L452.get_internal_flash_page_number(
    elf_parser.get_section_by_name(".data").address_in_flash + elf_parser.get_section_by_name(".data").size
)
num_of_pages = last_page - first_page + 1

flasher.erase_internal_flash(first_page, num_of_pages)

internal_flash_bytes_to_send = elf_parser.get_bytes(
    STM32L452.INTERNAL_FLASH_START_ADDRESS,
    elf_parser.get_section_by_name(".data").address_in_flash + elf_parser.get_section_by_name(".data").size - 1,
)

flasher.flash(STM32L452.INTERNAL_FLASH_START_ADDRESS, internal_flash_bytes_to_send)


external_flash_section = elf_parser.get_section_by_name(".external_flash")
external_flash_bytes = elf_parser.get_bytes(
    external_flash_section.address_in_flash, external_flash_section.address_in_flash + external_flash_section.size
)

flasher.erase_external_flash(0, math.ceil(len(external_flash_bytes) / 256000))
flasher.flash(external_flash_section.address_in_flash, external_flash_bytes)

message_handler.send_command_message(MessageHandler.Command.FINISHED)

received_status = message_handler.wait_for_status_message()
if received_status != MessageHandler.Status.FLASHING_DONE:
    logger.error("Flashing failed.")
    exit(1)

logger.info("Flashing done!")
