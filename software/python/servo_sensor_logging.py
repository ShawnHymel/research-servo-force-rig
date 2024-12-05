import serial
import csv
import time
import os

# Settings
SERIAL_PORT = "COM9"
BAUD_RATE = 912600
INITIAL_TIMEOUT = 10.0
TIMEOUT = 1.0
DATA_PATH = "data"
DATA_PREFIX = "log"

#-------------------------------------------------------------------------------
# Functions

# Read data from serial port
def read_serial_data(ser, init_timeout=1.0, timeout=1.0):
    data_lines = []  # List to store received lines of data
    start_time = time.time()  # Record the start time

    # Initial timeout to wait for the first line of data
    while (time.time() - start_time) < init_timeout:
        if ser.in_waiting > 0:
            break  # Exit loop if data is available
    else:
        return data_lines  # Return empty list if no data received

    # Keep reading data until timeout
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode().strip()
            if line:  # Only add non-empty lines
                data_lines.append(line)
                start_time = time.time()  # Reset the start time after receiving data
        elif (time.time() - start_time) > timeout:
            break  # Exit loop if timeout reached with no data

    return data_lines

def run_test(
    ser, 
    start_pos, 
    wait_time_ms, 
    end_pos, 
    num_readings, 
    enable_force_reading
):
    # Construct message
    msg = f"{start_pos}, {wait_time_ms}, {end_pos}, {num_readings}, {int(enable_force_reading)}"

    # Send the data
    ser.write(msg.encode())

    # Wait for the response
    resp = read_serial_data(ser, INITIAL_TIMEOUT, TIMEOUT)

    # Create the output CSV file, increasing the index if necessary
    index = 0
    while True:
        csv_path = os.path.join(DATA_PATH, f"{DATA_PREFIX}_{index}.csv")
        if not os.path.exists(csv_path):
            break
        index += 1

    # Log the response to a CSV file
    with open(csv_path, "w", newline="") as f:
        writer = csv.writer(f)
        for line in resp:
            writer.writerow(line.split(","))
        print(f"Data logged to {csv_path}")

#-------------------------------------------------------------------------------
# Main

def main():

    # Set up the test
    start_pos = 0
    wait_time_ms = 1000
    end_pos = 90
    num_readings = 200
    enable_force_reading = False

    try:

        # Open the serial port
        with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:

            # Run the test
            run_test(
                ser, 
                start_pos, 
                wait_time_ms, 
                end_pos, 
                num_readings, 
                enable_force_reading
            )

    except serial.SerialException as e:
        print(f"Error opening or using the serial port: {e}")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()