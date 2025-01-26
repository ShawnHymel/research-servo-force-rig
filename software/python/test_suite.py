# SPDX-License-Identifier: BSD-3-Clause

# Set up sequence:
#   1. Adjust "Test settings" below to match your test setup
#   2. Run "python ./software/python/move_servo.py 0.0" to set the servo to the initial position
#   3. Cycle power on the Arduino to reset the encoder
#   4. Run "python ./software/python/move_servo.py 0.5" to put the servo in the middle position
#   5. Attach the load sensor hook to the servo/encoder coupler
#   6. Run "python ./software/python/test_suite.py" to run the test suite
#   7. Swap hook positions and repeat steps 4-6 (uncomment out necessary POSITIONS below)

import serial
import os
import time

from servo_sensor_logging import run_test, read_serial_data

# Test settings
DATA_PATH = "data/p1s/180_deg/0mm/6_0V"
NUM_TESTS = 20             # Number of tests to run per position pair
WAIT_TIME_MS = 1000         # Time (ms) to wait at start position
NUM_READINGS = 50           # Number of readings to take (let the servo cool down ~1 min between test batches!)
ENABLE_FORCE_READING = True # False: ~2 ms per reading, True: ~12.5 ms per reading
COOLDOWN_POSITION = 1.0   # Position to move to between tests
COOLDOWN_SEC = 2.0          # Time (sec) to wait between tests
BATCH_COOLDOWN_SEC = 60.0  # Time (sec) to wait between test batches

# Select test positions [start, end]. Comment out unused positions
# POSITIONS = [[0.0, 1.0], [0.0, 0.333], [0.333, 0.0], [0.333, 1.0], [1.0, 0.333], [1.0, 0.0]] # Hook facing down
# POSITIONS = [[1.0, 0.0]] # Hook facing up
POSITIONS = [[1.0, 0.66], [0.66, 1.0]]  # Redo positions

# Communication settings
SERIAL_PORT = "COM9"
BAUD_RATE = 912600
TIMEOUT = 1.0
CMD_TARE = "tare"

# Construct log paths
data_prefix = ""
# if ENABLE_FORCE_READING:
#     DATA_PATH = os.path.join(DATA_PATH, "force")

try:

    # Open the serial port
    with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:

        # Run tests for each position pair
        num_positions = len(POSITIONS)
        for idx, (start_pos, end_pos) in enumerate(POSITIONS):

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

                # Move to cooldown position between tests
                msg = f"{COOLDOWN_POSITION}, 0, {COOLDOWN_POSITION}, 0, 0"
                ser.write(msg.encode())
                time.sleep(COOLDOWN_SEC)

                # Flush serial buffer
                _ = read_serial_data(ser, TIMEOUT, TIMEOUT)

            # Let the servo cool on all but final test
            if idx < num_positions - 1:
                print(f"Waiting {BATCH_COOLDOWN_SEC} seconds before next test...")
                time.sleep(BATCH_COOLDOWN_SEC)

except serial.SerialException as e:
    print(f"Error opening or using the serial port: {e}")
except Exception as e:
    print(f"An error occurred: {e}")
