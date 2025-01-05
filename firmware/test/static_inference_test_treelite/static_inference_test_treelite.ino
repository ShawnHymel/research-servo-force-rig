#include "header.h"

static const float input_features[] = {2.8000e+00, 7.5758e-02, 3.0000e+00, 5.1818e-01, 4.7200e+02, 5.3939e-01};
static const int num_features = 6;

void setup() {
  SerialUSB.begin(9600);
}

void loop() {
  float prediction;
  unsigned long timestamp;
  unsigned long inference_time_us;

  // Create an array of Entry unions for the input
  union Entry data[num_features];
  for (int i = 0; i < num_features; ++i) {
    data[i].fvalue = input_features[i];
  }

  // Perfrom inference
  timestamp = micros();
  predict(data, 0, &prediction);
  inference_time_us = micros() - timestamp;

  SerialUSB.print("Stall prediction: ");
  SerialUSB.print(prediction, 4);
  SerialUSB.print(" Inference time (us): ");
  SerialUSB.println(inference_time_us);

  delay(5000);
}
