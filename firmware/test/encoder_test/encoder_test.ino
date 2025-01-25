#include "RotaryEncoder.h"

/******************************************************************************
 * Constants and globals
 */

// Pin definitions
const int LED_PIN = LED_BUILTIN;
const uint16_t ENC_A_PIN = 8;     // Green wire
const uint16_t ENC_B_PIN = 9;     // White wire

// Communication constants
static const unsigned int BAUD_RATE = 115200;

// Encoder constants
const int ENC_STEPS_PER_ROTATION = 1200;

// Globals
RotaryEncoder *encoder = nullptr;

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

  // Configure encoder
  encoder = new RotaryEncoder(
    ENC_A_PIN, 
    ENC_B_PIN, 
    RotaryEncoder::LatchMode::TWO03
  );
  encoder->setPosition(0);

  // Configure encoder interrupts
  attachInterrupt(digitalPinToInterrupt(ENC_A_PIN), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B_PIN), encoderISR, CHANGE);

}

void loop() {
  
  // Get encoder value
  float enc_val = get_encoder_angle();

  // Print encoder value
  SerialUSB.println(enc_val);

  delay(100);
}
