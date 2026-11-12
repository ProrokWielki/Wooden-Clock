from enum import Enum

try:
    import sys

    sys.path.append("generated_protos")

    import generated_protos.flashing_msg_pb2 as flashing_msg
    import generated_protos.flashing_state_pb2 as flashing_state_msg
    import generated_protos.flashing_start_pb2 as flashing_start_msg
    import generated_protos.flashing_command_pb2 as flashing_command_msg
    import generated_protos.debug_msg_pb2 as debug_msg
    import generated_protos.mode_pb2 as mode_msg
except ImportError:
    raise ImportError("Could not import generated proto files. Make sure to generate them first - using make.")


class Status(Enum):
    ERROR = 0
    IDLE = 1
    ERASING_IN_PROGRESS = 2
    BUSY = 3
    WAITING_FOR_NEXT_PAGE = 4
    FLASHING_IN_PROGRESS = 5
    FLASHING_DONE = 6


class Flash(Enum):
    INTERNAL = 0
    EXTERNAL = 1


class Mode(Enum):
    FLASHING = 0
    REBOOT = 1
    NORMAL = 2


class Command(Enum):
    NEXT_TRANSFER = 0
    FINISHED = 1


status_enum_mapping = {
    flashing_state_msg.FlashingState.ERROR: Status.ERROR,
    flashing_state_msg.FlashingState.IDLE: Status.IDLE,
    flashing_state_msg.FlashingState.ERASING_IN_PROGRESS: Status.ERASING_IN_PROGRESS,
    flashing_state_msg.FlashingState.BUSY: Status.BUSY,
    flashing_state_msg.FlashingState.WAITING_FOR_NEXT_PAGE: Status.WAITING_FOR_NEXT_PAGE,
    flashing_state_msg.FlashingState.FLASHING_IN_PROGRESS: Status.FLASHING_IN_PROGRESS,
    flashing_state_msg.FlashingState.FLASHING_DONE: Status.FLASHING_DONE,
}

flash_enum_mapping = {
    Flash.INTERNAL: flashing_start_msg.Flash.INTERNAL,
    Flash.EXTERNAL: flashing_start_msg.Flash.EXTERNAL,
}

mode_enum_mapping = {
    Mode.FLASHING: mode_msg.Mode.FLASHING,
    Mode.REBOOT: mode_msg.Mode.REBOOT,
    Mode.NORMAL: mode_msg.Mode.NORMAL,
}

command_enum_mapping = {
    Command.NEXT_TRANSFER: flashing_command_msg.FlashingCommand.NEXT_TRANSFER,
    Command.FINISHED: flashing_command_msg.FlashingCommand.FINISHED,
}


class ProtobufWrapper:
    @staticmethod
    def deserialize_status(data: bytes) -> Status:
        raw_status_msg = flashing_msg.McuToPcFlashingMsg()
        raw_status_msg.ParseFromString(data)

        return status_enum_mapping[raw_status_msg.flashing_state]

    @staticmethod
    def serialize_pages_erase(flash: Flash, start_page: int, num_of_pages: int) -> bytes:
        erase_msg = flashing_msg.PcToMcuFlashingMsg()
        erase_msg.flashing_start.flash = flash_enum_mapping[flash]
        erase_msg.flashing_start.start_page = start_page
        erase_msg.flashing_start.num_of_pages = num_of_pages

        return erase_msg.SerializeToString()

    @staticmethod
    def serialize_data_write(address: int, data: bytes, size: int) -> bytes:
        write_msg = flashing_msg.PcToMcuFlashingMsg()
        write_msg.write_data.address = address
        write_msg.write_data.data = data
        write_msg.write_data.size = size

        return write_msg.SerializeToString()

    @staticmethod
    def serialize_mode(mode: Mode) -> bytes:
        message = debug_msg.PcToMcuDebugMsg()
        message.mode = mode_enum_mapping[mode]

        return message.SerializeToString()

    @staticmethod
    def serialize_command(command: Command) -> bytes:
        message = flashing_msg.PcToMcuFlashingMsg()
        message.flashing_command = command_enum_mapping[command]

        return message.SerializeToString()
