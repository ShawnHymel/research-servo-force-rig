/**
 * Servo and Sensor Control
 *
 * Designed for the SparkFun SAM21G Mini Breakout
 * 
 * Hardware connections
 * ---
 *    Signal  | Color   | Arduino
 * Servo
 *    GND     | Brown   | GND
 *    VCC     | Red     | INA219 Vin-
 *    Control | Orange  | D6
 * Servo Sense
 *    VCC     | Red     | 1/3 voltage divider to A1
 *    Pot     | Blue    | 1/3 voltage divider to A2
 * Encoder
 *    VCC     | Red     | 3.3 V
 *    GND     | Black   | GND
 *    Shield  | Silver  | GND
 *    A       | Green   | D8
 *    B       | White   | D9
 * Load Cell
 *    VDD     | Red     | 3.3 V
 *    VCC     | Orange  | 5 V
 *    DAT     | Yellow  | D3
 *    CLK     | Green   | D4
 *    GND     | Blue    | GND
 * Current Sense (INA219)
 *    VCC     | -       | 3.3 V
 *    GND     | -       | GND
 *    SCL     | -       | D21 (SCL)
 *    SDA     | -       | D20 (SDA)
 *    Vin-    | -       | Servo VCC
 *    Vin+    | -       | 5 V
 * 
 * Libraries:
 *  https://github.com/mathertel/RotaryEncoder
 *  https://github.com/bogde/HX711
 *  https://github.com/adafruit/Adafruit_INA219
 * 
 * Run firmware/test/load_cell_calibration.ino to find calibration factor.
 * This sketch assumes force sensor units are given in millinewtons (mN).
 * 
 * License: BSD-3-Clause
 */

#include <Servo.h>
#include <Wire.h>

#include "HX711.h"
#include "RotaryEncoder.h"
#include "Adafruit_INA219.h"

/******************************************************************************
 * Constants and globals
 */

// Pin definitions
static const int LED_PIN = LED_BUILTIN;
static const int ENC_A_PIN = 8;     // Green wire
static const int ENC_B_PIN = 9;     // White wire
static const int SRV_PIN = 6;       // Servo signal
static const int LCA_DOUT_PIN = 3;  // Yellow wire
static const int LCA_CLK_PIN = 4;   // Green wire
static const int SRV_VCC_PIN = A1;  // Red wire
static const int SRV_POT_PIN = A2;  // Blue wire

// Communication constants
static const unsigned int BAUD_RATE = 921600;
static const unsigned int MSG_SIZE = 64;

// Comma-separated message values
// [start pos], [wait time (ms)], [end pos], [num readings], [enable force reading]
static const unsigned int NUM_MSG_VALUES = 5;
static const unsigned char MSG_DELIMITER = ',';

// Array constants
static const unsigned int LOG_BUF_WIDTH = 7;
static const unsigned int LOG_BUF_LENGTH = 300;
static const char HEADER[LOG_BUF_WIDTH][20] = {
  "Timestamp",
  "Desired Position",
  "Servo Current",
  "Servo Voltage",
  "Servo Potentiometer",
  "Encoder",
  "Force"
};

// Encoder constants
static const int ENC_STEPS_PER_ROTATION = 1200;
static const float ENC_START_DEG = 0.0;

// Servo constants
static const int SRV_OFFSET = 0;
static const int SRV_START = 0;

// Load cell amplifier calibration factor (get load in millinewtons)
// Obtained by running SparkFun_HX711_Calibration sketch
static const float LCA_CALIBRATION_FACTOR = 8.61;  // 84.3 for grams, 8.61 for millinewtons
static const String CMD_TARE = "tare";

// Analog input constants
static const uint32_t AIN_MAX = 1023;
static const float AIN_REF = 3.3;
static const float AIN_VOLTAGE_DIV = 0.3333;

// Globals
static RotaryEncoder *encoder = nullptr;
static Servo servo;
static HX711 lca;
static Adafruit_INA219 ina219;
static float log_buf[LOG_BUF_LENGTH][LOG_BUF_WIDTH];

/******************************************************************************
 * Interrupt service routines (ISRs)
 */

// Encoder interrupt service routine (pin change): check state
void encoderISR() {
  encoder->tick();
}

/******************************************************************************
 * Functions
 */

// Get the angle of the encoder in degrees (0 is starting position)
float get_encoder_angle() {
  
  int pos, dir;
  float deg = 0.0;

  // Get position and direction
  pos = encoder->getPosition();
  dir = (int)encoder->getDirection();

  // Convert to degrees
  pos = pos % ENC_STEPS_PER_ROTATION;
  // pos = pos >= 0 ? pos : pos + ENC_STEPS_PER_ROTATION; // Set to -180 to 180 deg
  deg = (float)pos * (360.0 / ENC_STEPS_PER_ROTATION);

  return deg;
}

// Parse comma-separated floats
// Warning: str is modified during processing
int parse_floats(
  float *out_array, 
  char *str, 
  const char delimiter, 
  int num
) {
  
  char buf[MSG_SIZE];
  char *ptr;
  char *ptr_end;
  char *token;
  int count = 0;
  double temp;

  // Make sure pointers are not null
  if (out_array == NULL || str == NULL) {
    return -1;
  }

  // Copy input to local buffer
  // strcpy(buf, str);

  // Get first token
  token = strtok_r(str, &delimiter, &ptr);

  // Go through all tokens
  while (token != NULL && count < num) {

    // Convert token to float
    temp = strtod(token, &ptr_end);
    if (token == ptr_end) {
      return -1;
    }

    // Save value and increment counter
    out_array[count] = (float)temp;
    count++;

    // Get next token
    token = strtok_r(NULL, &delimiter, &ptr);
  }

  return count;
}

/******************************************************************************
 * Main
 */

void setup() {

  // Configure pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(ENC_A_PIN, INPUT_PULLUP);
  pinMode(ENC_B_PIN, INPUT_PULLUP);

  // Initialize our communication interface
  SerialUSB.begin(BAUD_RATE);

  // Wait for Serial
  while (!SerialUSB) {
    delay(1);
  }

  // Configure servo and set to start position
  servo.attach(SRV_PIN);
  servo.write(SRV_START + SRV_OFFSET);
  delay(2000);

  // Configure encoder and set current position as 0
  encoder = new RotaryEncoder(
    ENC_A_PIN, 
    ENC_B_PIN, 
    RotaryEncoder::LatchMode::TWO03
  );
  encoder->setPosition(0);

  // Configure load cell amplifier
  lca.begin(LCA_DOUT_PIN, LCA_CLK_PIN);
  lca.set_scale(LCA_CALIBRATION_FACTOR);
  lca.tare();

  // Configure encoder interrupts
  attachInterrupt(digitalPinToInterrupt(ENC_A_PIN), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B_PIN), encoderISR, CHANGE);

  // Configure current sensor
  if (!ina219.begin()) {
    SerialUSB.println("Failed to initialize INA219");
    while (1) {
      delay(1000);
    }
  }
}

void loop() {

  unsigned long timestamp;
  float enc_val;
  float lca_val;
  float srv_vcc_voltage;
  float srv_pot_voltage;
  float current_ma;
  unsigned int idx = 0;
  String msg_str;
  char msg[MSG_SIZE];
  int num_parsed;
  float msg_values[NUM_MSG_VALUES];
  float pos_start;
  unsigned int pos_wait_ms;
  float pos_end;
  unsigned int num_readings;
  bool enable_force_reading;

  // Parse parameters from serial
  if (SerialUSB.available() > 0) {

    // Capture line from serial and convert to char array
    msg_str = SerialUSB.readStringUntil('\n');
    msg_str.toCharArray(msg, MSG_SIZE);

    // If "tare" is seen, zero the force sensor
    if (msg_str.startsWith(CMD_TARE)) {
      lca.tare();
      return;

    // Otherwise, pares the numbers
    } else {
      num_parsed = parse_floats(msg_values, msg, MSG_DELIMITER, NUM_MSG_VALUES);
    }

  } else {
    return;
  }

  if (num_parsed != NUM_MSG_VALUES) {
    SerialUSB.println("ERROR: Could not parse input message.");
    return;
  }

  // Save the parsed values
  pos_start = msg_values[0];
  pos_wait_ms = (unsigned int)(msg_values[1] + 0.5);
  pos_end = msg_values[2];
  num_readings = (unsigned int)(msg_values[3] + 0.5);
  enable_force_reading = (msg_values[4] != 0);

  // Debug the parsed values
  // SerialUSB.print(pos_start);
  // SerialUSB.print(", ");
  // SerialUSB.print(pos_wait_ms);
  // SerialUSB.print(", ");
  // SerialUSB.print(pos_end);
  // SerialUSB.print(", ");
  // SerialUSB.println(num_readings);

  // Wait before next test
  servo.write(SRV_OFFSET + pos_start);
  delay(pos_wait_ms);

  // Run test
  timestamp = millis();
  servo.write(SRV_OFFSET + pos_end);
  for (int i = 0; i < num_readings; i++) {

    // Get encoder value, convert to -/+180 deg from servo start position
    enc_val = 360.0 - get_encoder_angle();
    enc_val = enc_val <= 180.0 ? enc_val : enc_val - 360.0;

    // Get load cell amplifier value
    if (enable_force_reading) {
      lca_val = lca.get_units();
    } else {
      lca_val = 0.0;
    }

    // Get voltage of servo supply (apply voltage divider)
    srv_vcc_voltage = analogRead(SRV_VCC_PIN) * AIN_REF / AIN_MAX;
    srv_vcc_voltage /= AIN_VOLTAGE_DIV;

    // Get voltage of servo's internal potentiometer (apply voltage divider)
    srv_pot_voltage = analogRead(SRV_POT_PIN) * AIN_REF / AIN_MAX;
    srv_pot_voltage /= AIN_VOLTAGE_DIV;

    // Get supply current to servo
    current_ma = ina219.getCurrent_mA();

    // Store readings in log buffer
    log_buf[idx][0] = (float)(millis() - timestamp);
    log_buf[idx][1] =pos_end;
    log_buf[idx][2] = current_ma;
    log_buf[idx][3] = srv_vcc_voltage;
    log_buf[idx][4] = srv_pot_voltage;
    log_buf[idx][5] = enc_val;
    log_buf[idx][6] = lca_val;

    // Increase index
    idx++;
    if (idx >= LOG_BUF_LENGTH) {
      idx = LOG_BUF_LENGTH - 1;
    }
  }

  // Print header
  for (int i = 0; i < LOG_BUF_WIDTH; i++) {
    SerialUSB.print(HEADER[i]);
    if (i < LOG_BUF_WIDTH - 1) {
      SerialUSB.print(", ");
    }
  }
  SerialUSB.println();

  // Print values
  for (int i = 0; i < idx; i++) {
    for (int j = 0; j < LOG_BUF_WIDTH; j++) {
      SerialUSB.print(log_buf[i][j]);
      if (j < LOG_BUF_WIDTH - 1) {
        SerialUSB.print(", ");
      } else {
        SerialUSB.println();
      }
    }
  }
  SerialUSB.println();
}
