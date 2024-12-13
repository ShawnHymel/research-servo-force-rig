#!/usr/bin/python
# SPDX-License-Identifier: BSD-3-Clause
# Run this to set the servo to a mid point so you can connect the force sensor

import serial
import sys

from servo_sensor_logging import run_test, read_serial_data

INITIAL_TIMEOUT = 10.0

# Read first argmument from command line as servo position
if len(sys.argv) < 2:
    print("Please provide the servo position as an argument")
    sys.exit(1)
servo_pos = int(sys.argv[1])

# Communication settings
SERIAL_PORT = "COM9"
BAUD_RATE = 912600
TIMEOUT = 1.0

# Construct message
msg = f"{servo_pos}, 0, {servo_pos}, 30, 1"

# Send message to Arduino
try:
    with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
        ser.write(msg.encode())

        # Wait for the response
        resp = read_serial_data(ser, INITIAL_TIMEOUT, TIMEOUT)
        for line in resp:
            print(line)

except serial.SerialException as e:
    print(f"Error opening or using the serial port: {e}")
except Exception as e:
    print(f"An error occurred: {e}")