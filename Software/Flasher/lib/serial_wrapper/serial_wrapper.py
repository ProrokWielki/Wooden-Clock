import serial


class SerialWrapper:
    def __init__(self, serial_port: str, boudrate: int = 115200) -> None:
        self.serial = serial.Serial(serial_port, boudrate)

    def write(self, data: bytes) -> None:
        self.serial.write(data)

    def read(self, size: int = 1) -> bytes:
        return self.serial.read(size)
