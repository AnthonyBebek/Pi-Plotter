#!/usr/bin/env python3
import serial
import time

ser = serial.Serial("/dev/ttyUSB0", 19200, timeout=1)
time.sleep(1)

def move(x, y):
    res = ""
    ser.reset_input_buffer()
    lines = []
    pos = str(x) + "," + str(y)
    ser.write(str("M" + pos).encode() + b"\n")
    print(pos)
    while True:
        res = ser.readline().decode().strip()
        if res == "Done":
            print(res)
            return
