import intelhex
import socket
import time

s = socket.socket()
host = "192.168.1.20"
port = 8750

s.connect((host, port))

time.sleep(5)

s.send(bytes(b'\xde\xad\xbe\xef'))

time.sleep(1)

s.shutdown(socket.SHUT_WR)
