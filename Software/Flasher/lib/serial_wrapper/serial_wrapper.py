import serial


class SerialWrapper:
    def __init__(self, serial_port, boudrate=115200):
        self.serial = serial.Serial(serial_port, boudrate)

    def write(self, data):
        self.serial.write(data)

    def read(self, size=1):
        return self.serial.read(size)
