#include "xgb_model.h"

static double input_features[] = {1.3207e+03, -1.4167e+02,  5.3030e-01,  2.5253e-01};

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
