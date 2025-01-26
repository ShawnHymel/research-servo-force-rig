import serial

# Communication settings
SERIAL_PORT = "COM9"
BAUD_RATE = 912600
TIMEOUT = 1.0
CMD_TARE = "tare"

# Open the serial port and tare the force sensor
with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
    ser.write(CMD_TARE.encode())