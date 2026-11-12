from lib.serial_wrapper.serial_wrapper import SerialWrapper
from lib.protobuf_wrapper import protobuf_wrapper

import logging


class MessageHandler:
    Mode = protobuf_wrapper.Mode
    Status = protobuf_wrapper.Status
    Flash = protobuf_wrapper.Flash
    Command = protobuf_wrapper.Command

    STATUS_MESSAGE_LENGTH = 2

    TRANSFER_SIZE = 2048

    def __init__(self, serial_wrapper: SerialWrapper) -> None:
        self.serial_wrapper = serial_wrapper
        self.protobuf_wrapper = protobuf_wrapper.ProtobufWrapper()
        self.logger = logging.getLogger(__name__)

    def wait_for_status_message(self) -> Status:
        received_bytes = self.serial_wrapper.read(self.STATUS_MESSAGE_LENGTH)
        self.logger.debugv(f"bytes received: {received_bytes}, len: {len(received_bytes)}")

        received_status = self.protobuf_wrapper.deserialize_status(received_bytes)
        self.logger.debug(f"state received: {received_status}")

        return received_status

    def send_mode_message(self, message: Mode) -> None:
        self.logger.debug(f"sending mode: {message}")
        bytes_to_send = self.protobuf_wrapper.serialize_mode(message)

        self.logger.debugv(f"sending bytes: {bytes_to_send}, len: {len(bytes_to_send)}")
        self.serial_wrapper.write(bytes_to_send)

    def send_page_erase_message(self, flash: Flash, first_page: int, num_of_pages: int) -> None:
        self.logger.debug(f"sending page erase: {flash=} {first_page=} {num_of_pages=}")
        bytes_to_send = self.protobuf_wrapper.serialize_pages_erase(flash, first_page, num_of_pages)

        self.logger.debugv(f"sending bytes: {bytes_to_send}, len: {len(bytes_to_send)}")
        self.serial_wrapper.write(bytes_to_send)

    def send_command_message(self, command: Command) -> None:
        self.logger.debug(f"sending command: {command}")
        bytes_to_send = self.protobuf_wrapper.serialize_command(command)

        self.logger.debugv(f"sending bytes: {bytes_to_send}, len: {len(bytes_to_send)}")
        self.serial_wrapper.write(bytes_to_send)

    def send_data_write_message(self, address: int, data: bytes, size: int) -> None:
        self.logger.debug(f"sending data: {address=} {size=}")
        bytes_to_send = self.protobuf_wrapper.serialize_data_write(address, data, size)

        self.logger.debugv(f"sending bytes: {bytes_to_send}, len: {len(bytes_to_send)}")
        self.serial_wrapper.write(bytes_to_send)
