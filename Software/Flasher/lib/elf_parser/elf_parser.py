from dataclasses import dataclass

import readelf
import logging


@dataclass
class Section:
    name: str
    address_in_elf: int
    address_in_flash: int
    size: int


@dataclass
class Symbol:
    name: str
    address: int


class ElfParser:
    def __init__(self, elf_file_path: str) -> None:
        self.logger = logging.getLogger(__name__)

        self.elf = readelf.readelf(elf_file_path)

        self.sections = []

        self.__parse_sections()

    def get_sections(self) -> list[Section]:
        return self.sections

    def get_section_by_name(self, name: str) -> Section:
        for section in self.sections:
            if section.name == name:
                return section

        self.logger.error(f"Section {name} not found in ELF file.")
        raise ValueError(f"Section {name} not found in ELF file.")

    def get_sections_in_range(self, start_address: int, end_address: int) -> list[Section]:
        sections_in_range = list(
            filter(
                lambda section: section.address_in_flash >= start_address and section.address_in_flash < end_address,
                self.sections,
            )
        )
        sections_in_range.sort(key=lambda section: section.address_in_flash)

        self.logger.debug(f"fond {len(sections_in_range)} sections in range {start_address} {end_address}")

        return sections_in_range

    def get_bytes(self, start_address: int, end_address: int) -> bytes:
        sections_to_merge = self.get_sections_in_range(start_address, end_address)

        if len(sections_to_merge) == 0:
            self.logger.warning("No data found.")

        bytes_to_return = bytes()
        previous_section_end = start_address

        for section in sections_to_merge:
            is_disconnected_from_previous_section = section.address_in_flash > previous_section_end

            if is_disconnected_from_previous_section:
                num_of_missing_bytes = section.address_in_flash - previous_section_end
                bytes_to_return += num_of_missing_bytes * b"\xff"

            self.elf.memory.seek(section.address_in_elf)
            self.logger.debug(f"Adding bytes for: {section.name} - {section.size} bytes")

            bytes_to_return += self.elf.memory.read(section.size)

            previous_section_end = section.address_in_flash + section.size

        bytes_to_return += (end_address - previous_section_end) * b"\xff"

        return bytes_to_return

    def __parse_sections(self) -> None:
        for segment in self.elf.segments:
            for section in segment.sections:
                self.logger.debug(f"Parsed section: {section.name}")
                self.sections.append(
                    Section(section.name, section.addr, section.addr + segment.paddr - segment.vaddr, section.size)
                )
