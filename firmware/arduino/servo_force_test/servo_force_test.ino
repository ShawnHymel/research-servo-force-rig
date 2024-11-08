#include <Servo.h>

#include "RotaryEncoder.h"

/******************************************************************************
 * Constants and globals
 */

// Pin definitions
static const int LED_PIN = LED_BUILTIN;
static const uint16_t ENC_A_PIN = 8;     // Green wire
static const uint16_t ENC_B_PIN = 9;     // White wire
static const uint16_t SERVO_PIN = 6

// Communication constants
static const unsigned int BAUD_RATE = 115200;

// Encoder constants
const int ENC_STEPS_PER_ROTATION = 1200;

// Globals
RotaryEncoder *encoder = nullptr;
Servo servo;

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

  // Configure encoder
  encoder = new RotaryEncoder(
    ENC_A_PIN, 
    ENC_B_PIN, 
    RotaryEncoder::LatchMode::TWO03
  );
  encoder->setPosition(0);

  // Configure servo
  servo.attach(SERVO_PIN);

  // Configure encoder interrupts
  attachInterrupt(digitalPinToInterrupt(ENC_A_PIN), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B_PIN), encoderISR, CHANGE);

}

void loop() {

  float enc_val;

  for (int pos = 0; pos <= 180; pos += 1) {

    // Set servo position
    servo.write(pos);

    // Watch encoder

  }
  
  // Print encoder value
  enc_val = get_encoder_angle();
  SerialUSB.println(enc_val);

}
