#!/usr/bin/python3

from lib.elf_parser.elf_parser import ElfParser
from lib.stm32l452_info.stm32l452_info import STM32L452

import time
elf_parser = ElfParser("/workspaces/Wooden-Clock/Software/STM/build/Debug/src/stm32/WoodenClock.elf")

sections = elf_parser.get_sections()

internal_flash_sections_to_flash = list(
    filter(lambda section: section.name != ".flasher_section", internal_flash_sections)
)

time.sleep(1)
for i, section in enumerate(internal_flash_sections_to_flash):
    address = section.address_in_elf

    elf_parser.elf.memory.seek(address)
