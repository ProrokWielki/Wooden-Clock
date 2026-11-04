class STM32L452:
    INTERNAL_FLASH_START_ADDRESS = 0x08000000
    INTERNAL_FLASH_SIZE = 0x00080000
    INTERNAL_FLASH_END_ADDRESS = INTERNAL_FLASH_START_ADDRESS + INTERNAL_FLASH_SIZE - 1

    INTERNAL_FLASH_PAGE_SIZE = 0x800

    EXTERNAL_FLASH_START_ADDRESS = 0x90000000

    @staticmethod
    def get_internal_flash_page_number(address):
        if address < STM32L452.INTERNAL_FLASH_START_ADDRESS or address > STM32L452.INTERNAL_FLASH_END_ADDRESS:
            raise ValueError("Address is out of internal flash range")

        return (address - STM32L452.INTERNAL_FLASH_START_ADDRESS) // STM32L452.INTERNAL_FLASH_PAGE_SIZE

    @staticmethod
    def get_num_of_internal_pages_from_size(section_size):
        if section_size <= 0:
            raise ValueError("Section size must be positive")

        return (section_size + STM32L452.INTERNAL_FLASH_PAGE_SIZE - 1) // STM32L452.INTERNAL_FLASH_PAGE_SIZE

    @staticmethod
    def get_page_start_address(page):
        if page < 0:
            raise ValueError("Page number must be positive")

        return STM32L452.INTERNAL_FLASH_START_ADDRESS + page * STM32L452.INTERNAL_FLASH_PAGE_SIZE

    @staticmethod
    def get_page_end_address(page):
        return STM32L452.get_page_start_address(page) + STM32L452.INTERNAL_FLASH_PAGE_SIZE - 1
