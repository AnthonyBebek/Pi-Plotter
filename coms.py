import serial
import time
res = ""
ser = serial.Serial("/dev/ttyUSB1", 19200, timeout=1)
ser.reset_input_buffer()
lines = []
pos = input("Type the x coordinate and then the y coordinate seperated by a comma: ")
print("Moving to", pos)
time.sleep(1)
ser.write(str("M" + pos).encode() + b"\n")
ser.close()
print(res)
