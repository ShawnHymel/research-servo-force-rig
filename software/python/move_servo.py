#!/usr/bin/python
# SPDX-License-Identifier: BSD-3-Clause
# Run this to set the servo to a mid point so you can connect the force sensor
#
# Response from Arduino should be CSV values with the following columns:
#  Timestamp - time (in ms) of reading
#  Desired Position - position of the servo (normalized [0.0, 1.0])
#  Servo Current - current draw of the servo (in mA)
#  Servo Voltage - voltage of the servo (in V)
#  Servo Potentiometer - potentiometer reading of the servo (in V)
#  Encoder - encoder reading of the servo (in degrees)
#  Force - force reading of the sensor (in N)

import serial
import sys

from servo_sensor_logging import run_test, read_serial_data

INITIAL_TIMEOUT = 10.0

# Read first argmument from command line as servo position
if len(sys.argv) < 2:
    print("Please provide the servo position as an argument")
    sys.exit(1)
servo_pos = float(sys.argv[1])

# Check to make sure servo position is within 0.0 to 1.0 (normalized)
if servo_pos < 0 or servo_pos > 1:
    print("Servo position must be between 0.0 and 1.0")
    sys.exit(1)

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