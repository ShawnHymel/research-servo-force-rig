#include "xgb_model.h"

static double input_features[] = {2.6000, 0.5121, 2.9000, 0.5152, 3.0000, 0.5152};

void setup() {
  Serial.begin(9600);
}

void loop() {
  double prediction;
  unsigned long timestamp;
  unsigned long inference_time_ms;

  // Perfrom inference
  timestamp = millis();
  prediction = score(input_features);
  inference_time_ms = millis() - timestamp;

  Serial.print("Stall prediction: ");
  Serial.print(prediction, 4);
  Serial.print(" Inference time (ms): ");
  Serial.println(inference_time_ms);

  delay(5000);
}
