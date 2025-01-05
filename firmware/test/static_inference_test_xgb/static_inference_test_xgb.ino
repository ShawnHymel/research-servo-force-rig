#include "xgb_model.h"

static double input_features[] = {9.1000e+01,  7.5455e-01, -2.0202e+00,  1.7000e+03};

void setup() {
  SerialUSB.begin(9600);
}

void loop() {
  double prediction;
  unsigned long timestamp;
  unsigned long inference_time_us;

  // Perfrom inference
  timestamp = micros();
  prediction = score(input_features);
  inference_time_us = micros() - timestamp;

  SerialUSB.print("Stall prediction: ");
  SerialUSB.print(prediction, 4);
  SerialUSB.print(" Inference time (us): ");
  SerialUSB.println(inference_time_us);

  delay(5000);
}
