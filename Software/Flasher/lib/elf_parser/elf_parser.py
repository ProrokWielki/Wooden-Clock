from dataclasses import dataclass

import readelf


@dataclass
class Section:
    name: str
    address_in_elf: int
    address_in_flash: int
    size: int


class ElfParser:
    def __init__(self, elf_file_path):
        self.elf = readelf.readelf(elf_file_path)
        self.sections = []

        self.__parse_sections()

    def get_sections(self):
        return self.sections

    def get_section_data(self, section: Section):
        for elf_section in self.elf.sections:
            if elf_section.name == section.name:
                return elf_section.content
        raise ValueError(f"Section {section.name} not found in ELF file.")

    def get_data(self, start_address, end_address):
        self.elf.memory

    def __parse_sections(self):
        for section in self.elf.sections:
            self.sections.append(Section(section.name, section.addr, section.addr, section.size))
