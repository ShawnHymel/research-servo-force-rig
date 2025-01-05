#include <Servo.h>
#include <Wire.h>

#include "Adafruit_INA219.h"

#include "xgb_model.h"

/******************************************************************************
 * Constants and globals
 */

#define DEBUG 0

// Pin definitions
static const int LED_PIN = 11;
static const int SRV_PIN = 6;       // Servo signal
static const int SRV_POT_PIN = A2;  // Blue wire

// Communication constants
static const unsigned int BAUD_RATE = 115200;

// Servo constants
static const int SRV_START = 0;
static const int SRV_END = 180;

// ADC constants
static const uint32_t AIN_MAX = 1023;
static const float AIN_REF = 3.3;
static const float AIN_VOLTAGE_DIV = 0.3333;
static const float MAX_POT_V = 3.3;

// Data constants
#define NUM_FEATURES 4

// Stall thresholds
static const float threshold_contact = 0.2;
static const float threshold_stall = 0.8;
#define STALL_MAF_SIZE 3

// LED brightness constants
static const int led_pwm_free = 0;
static const int led_pwm_contact = 10;
static const int led_pwm_stall = 255;

// Globals
static Servo servo;
static Adafruit_INA219 ina219;
static double features[NUM_FEATURES];
static float stall_maf_buf[STALL_MAF_SIZE];

// Moving average filter
typedef struct {
    float *buffer;                // Circular buffer
    unsigned int buf_size;        // Size of buffer
    int index;                    // Current index in the buffer
    int count;                    // Number of values added (for startup)
    float sum;                    // Running sum of the window
} MovingAverageFilter;

/******************************************************************************
 * Functions
 */

// Initialize the moving average filter
void init_maf(MovingAverageFilter *ma, float *buf, unsigned int buf_size) {
    ma->buffer = buf;
    ma->buf_size = buf_size;
    ma->index = 0;
    ma->count = 0;
    ma->sum = 0.0f;
    for (int i = 0; i < buf_size; i++) {
        ma->buffer[i] = 0.0f;
    }
}

// Update the moving average with a new value
float update_maf(MovingAverageFilter *ma, float new_value) {

    // Subtract the oldest value from the sum
    ma->sum -= ma->buffer[ma->index];

    // Add the new value to the buffer and the sum
    ma->buffer[ma->index] = new_value;
    ma->sum += new_value;

    // Move to the next index in the circular buffer
    ma->index = (ma->index + 1) % ma->buf_size;

    // Increment the count until it reaches the window size
    if (ma->count < ma->buf_size) {
        ma->count++;
    }

    // Return the average
    return ma->sum / ma->count;
}


void print_scientific(float number) {

  // Check for edge case
  if (number < 1e-12) {
    SerialUSB.print("0.0e0");
    return;
  }

  int exponent = 0;
  float mantissa = number;

  // Normalize the mantissa
  while (fabs(mantissa) >= 10.0) {
    mantissa /= 10.0;
    exponent++;
  }
  while (fabs(mantissa) < 1.0) {
    mantissa *= 10.0;
    exponent--;
  }

  // Print mantissa and exponent
  SerialUSB.print(mantissa, 2);
  SerialUSB.print("e");
  SerialUSB.print(exponent);
}

/******************************************************************************
 * Main
 */

void setup() {
  
  // Configure pins
  pinMode(LED_PIN, OUTPUT);

  // Initialize our communication interface
  SerialUSB.begin(BAUD_RATE);

  // Wait for Serial
  while (!SerialUSB) {
    delay(1);
  }

  // Configure servo and set to start position
  servo.attach(SRV_PIN);
  servo.write(SRV_START);
  delay(2000);

  // Configure current sensor
  if (!ina219.begin()) {
    SerialUSB.println("Failed to initialize INA219");
    while (1) {
      delay(1000);
    }
  }
}

void loop() {

  static int servo_target_pos = SRV_START;
  float servo_current;
  float servo_current_prev = 0.0;
  float servo_current_deriv = 0.0;
  float norm_pot;
  float norm_pot_prev = 0.0;
  float norm_pot_deriv = 0.0;
  unsigned long timestamp_us = micros();
  unsigned long timestamp_prev_us = micros();
  unsigned long inference_time_us;
  double stall;
  double stall_avg;
  MovingAverageFilter stall_maf;

  // Initialize stall MAF
  init_maf(&stall_maf, stall_maf_buf, STALL_MAF_SIZE);
  
  // Set new servo target position
  if (servo_target_pos == SRV_START) {
    servo_target_pos = SRV_END;
  } else {
    servo_target_pos = SRV_START;
  }
  servo.write(servo_target_pos);

  // Test data collection
  for (int i = 0; i < 1000; i++) {

#if DEBUG
    inference_time_us = micros();
#endif

    // Get supply current to servo
    servo_current = ina219.getCurrent_mA();

    // Get normalized voltage of servo's internal potentiometer
    norm_pot = analogRead(SRV_POT_PIN) * AIN_REF / AIN_MAX;
    norm_pot /= AIN_VOLTAGE_DIV;
    norm_pot /= MAX_POT_V;

    // Calculate the current and pot derivatives
    timestamp_us = micros();
    servo_current_deriv = (servo_current_prev - servo_current) / (float)(timestamp_us - timestamp_prev_us);
    norm_pot_deriv = (norm_pot_prev - norm_pot) / (float)(timestamp_us - timestamp_prev_us);

    // Save measurements for next iteration
    servo_current_prev = servo_current;
    norm_pot_prev = norm_pot;
    timestamp_prev_us = timestamp_us;

    // Populate feature array
    features[0] = servo_current;
    features[1] = servo_current_deriv;
    features[2] = norm_pot;
    features[3] = norm_pot_deriv;

    // Perform inference for stall value
    stall = score(features);
#if DEBUG
    inference_time_us = micros() - inference_time_us;
#endif

    // Update moving average filter
    stall_avg = update_maf(&stall_maf, stall);

    // Print contact and stall
#if DEBUG == 0
    if ((stall_avg >= threshold_contact) && (stall_avg < threshold_stall)) {
      analogWrite(LED_PIN, led_pwm_contact);
      SerialUSB.print(stall_avg);
      SerialUSB.print(" Contact");
    } else if (stall_avg >= threshold_stall) {
      analogWrite(LED_PIN, led_pwm_stall);
      SerialUSB.print(stall_avg);
      SerialUSB.print(" Stall");
    } else {
      analogWrite(LED_PIN, led_pwm_free);
    }
#endif

    // Test: print readings in scientific notation
#if DEBUG
    SerialUSB.print("[");
    print_scientific(servo_current);
    SerialUSB.print(", ");
    print_scientific(servo_current_deriv);
    SerialUSB.print(", ");
    print_scientific(norm_pot);
    SerialUSB.print(", ");
    print_scientific(norm_pot_deriv);
    SerialUSB.print("] ");

    // Print stall and average stall (MAF)
    SerialUSB.print("Stall: ");
    SerialUSB.print(stall);
    SerialUSB.print(" Average stall: ");
    SerialUSB.print(stall_avg);

    // Print data collection and inference time
    SerialUSB.print(" (Time (us): ");
    SerialUSB.print(inference_time_us);
    SerialUSB.print(")");
#endif

    SerialUSB.println();
    delay(1);
  }

  delay(1000);
}
