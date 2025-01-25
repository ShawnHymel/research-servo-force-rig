/**
 * Servo Force Test
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

// Encoder constants
static const int ENC_STEPS_PER_ROTATION = 1200;
static const float ENC_START_DEG = 0.0;
static const int ENC_FLIP = -1;

// Servo constants
static const float SRV_START = 0.0;
static const float SRV_END = 1.0;
static const float SRV_MAX = 180.0; // Arduino's servo library assumes 180 deg max for all servos

// Load cell amplifier calibration factor (get load in grams)
// Obtained by running SparkFun_HX711_Calibration sketch
static const float LCA_CALIBRATION_FACTOR = 81.40;

// Analog input constants
static const uint32_t AIN_MAX = 1023;
static const float AIN_REF = 3.3;
static const float AIN_VOLTAGE_DIV = 0.3333;

// Globals
static RotaryEncoder *encoder = nullptr;
static Servo servo;
static HX711 lca;
static Adafruit_INA219 ina219;

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

  // Get position and direction (disable interrupts)
  noInterrupts();
  pos = encoder->getPosition();
  dir = (int)encoder->getDirection();
  interrupts();

  // Convert to degrees
  // pos = pos % ENC_STEPS_PER_ROTATION;
  // pos = pos >= 0 ? pos : pos + ENC_STEPS_PER_ROTATION;
  deg = (float)pos * (360.0 / ENC_STEPS_PER_ROTATION);

  return deg;
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
  servo.write(SRV_START * SRV_MAX);
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

  float enc_val;
  float lca_val;
  float srv_vcc_voltage;
  float srv_pot_voltage;
  float current_ma;

  // Wait before next test
  servo.write(SRV_START * SRV_MAX);
  delay(2000);

  // Run test (about 1 deg steps)
  for (float pos = SRV_START; pos <= SRV_END; pos += 0.0056) {

    // Set servo position
    servo.write(pos * SRV_MAX);    

    // Correct for encoder being mirrored
    enc_val = ENC_FLIP * get_encoder_angle();

    // OR: convert to -/+180 deg from servo start position
    // enc_val = 360.0 - get_encoder_angle();
    // enc_val = enc_val <= 180.0 ? enc_val : enc_val - 360.0;

    // Get load cell amplifier value
    lca_val = lca.get_units();

    // Get voltage of servo supply (apply voltage divider)
    srv_vcc_voltage = analogRead(SRV_VCC_PIN) * AIN_REF / AIN_MAX;
    srv_vcc_voltage /= AIN_VOLTAGE_DIV;

    // Get voltage of servo's internal potentiometer (apply voltage divider)
    srv_pot_voltage = analogRead(SRV_POT_PIN) * AIN_REF / AIN_MAX;
    srv_pot_voltage /= AIN_VOLTAGE_DIV;

    // Get supply current to servo
    current_ma = ina219.getCurrent_mA();

    // Print values
    SerialUSB.print(pos, 2);
    SerialUSB.print(", ");
    SerialUSB.print(enc_val, 2);
    SerialUSB.print(", ");
    SerialUSB.print(lca_val, 2);
    SerialUSB.print(", ");
    SerialUSB.print(srv_vcc_voltage);
    SerialUSB.print(", ");
    SerialUSB.print(srv_pot_voltage);
    SerialUSB.print(", ");
    SerialUSB.println(current_ma);
  }
}
