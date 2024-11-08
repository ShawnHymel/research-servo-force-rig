/**
 * Servo Force Test
 *
 * Libraries:
 *  https://github.com/mathertel/RotaryEncoder
 *  https://github.com/bogde/HX711
 */

#include <Servo.h>

#include "HX711.h"
#include "RotaryEncoder.h"

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
static const int AIN_PIN = A1;      // Analog input

// Communication constants
static const unsigned int BAUD_RATE = 115200;

// Encoder constants
static const int ENC_STEPS_PER_ROTATION = 1200;
static const float ENC_START_DEG = 0.0;

// Servo constants
static const int SRV_OFFSET = 75;
static const int SRV_START = 0;
static const int SRV_END = 90;

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
  pos = pos >= 0 ? pos : pos + ENC_STEPS_PER_ROTATION;
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
}

void loop() {

  float enc_val;
  float lca_val;
  float ain_voltage;

  // Wait before next test
  servo.write(SRV_START + SRV_OFFSET);
  delay(2000);

  // Run test
  for (int pos = SRV_START; pos <= SRV_END; pos += 1) {

    // Set servo position
    servo.write(pos + SRV_OFFSET);    

    // Get encoder value, convert to -/+180 deg from servo start position
    enc_val = 360.0 - get_encoder_angle();
    enc_val = enc_val <= 180.0 ? enc_val : enc_val - 360.0;

    // Get load cell amplifier value
    lca_val = lca.get_units();

    // Get voltage of servo supply (apply voltage divider)
    ain_voltage = analogRead(AIN_PIN) * AIN_REF / AIN_MAX;
    ain_voltage /= AIN_VOLTAGE_DIV;

    // Print values
    SerialUSB.print(pos);
    SerialUSB.print(", ");
    SerialUSB.print(enc_val, 2);
    SerialUSB.print(", ");
    SerialUSB.print(lca_val, 2);
    SerialUSB.print(", ");
    SerialUSB.println(ain_voltage);
  }
}
