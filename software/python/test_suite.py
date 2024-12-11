# Run from main repo directory:
#   python software/python/test_suite.py

import serial
import os
import time

from servo_sensor_logging import run_test, read_serial_data

# Test settings
DATA_PATH = "data/sg92r/"
DISTANCE = 100              # Distance (mm) from cross bar to front of bracket
NUM_TESTS = 100             # Number of tests to run per position pair
POSITIONS = [[90, 180], [0, 180], [90, 0], [180, 90]]   # [start, end] positions
WAIT_TIME_MS = 1000         # Time (ms) to wait at start position
NUM_READINGS = 50           # Number of readings to take (let the servo cool down ~5 min between test batches!)
ENABLE_FORCE_READING = True # False: ~2 ms per reading, True: ~12.5 ms per reading
COOLDOWN_POSITION = 90      # Position to move to between tests
COOLDOWN_SEC = 2.0          # Time (sec) to wait between tests
BATCH_COOLDOWN_SEC = 120.0  # Time (sec) to wait between test batches

# Communication settings
SERIAL_PORT = "COM9"
BAUD_RATE = 912600
TIMEOUT = 1.0
CMD_TARE = "tare"

# Construct log paths
data_prefix = f"{DISTANCE}mm_"
if ENABLE_FORCE_READING:
    DATA_PATH = os.path.join(DATA_PATH, "force")

try:

    # Open the serial port
    with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:

        # Run tests for each position pair
        for start_pos, end_pos in POSITIONS:

            # Move to initial position
            msg = f"{COOLDOWN_POSITION}, 0, {COOLDOWN_POSITION}, 0, 0"
            ser.write(msg.encode())
            time.sleep(COOLDOWN_SEC)

            # Tare the force sensor
            ser.write(CMD_TARE.encode())

            # Flush serial buffer
            _ = read_serial_data(ser, TIMEOUT, TIMEOUT)

            # Run tests
            for _ in range(NUM_TESTS):
                run_test(
                    ser, 
                    start_pos, 
                    WAIT_TIME_MS, 
                    end_pos, 
                    NUM_READINGS, 
                    ENABLE_FORCE_READING,
                    data_path=DATA_PATH,
                    data_prefix=data_prefix
                )

                # Move to cooldown position
                msg = f"{COOLDOWN_POSITION}, 0, {COOLDOWN_POSITION}, 0, 0"
                ser.write(msg.encode())
                time.sleep(COOLDOWN_SEC)

                # Flush serial buffer
                _ = read_serial_data(ser, TIMEOUT, TIMEOUT)

        # Wait for the servo to cool down
        time.sleep(BATCH_COOLDOWN_SEC)

except serial.SerialException as e:
    print(f"Error opening or using the serial port: {e}")
except Exception as e:
    print(f"An error occurred: {e}")
