#include "HX711.h"

#define calibration_factor 81.40

#define DOUT  3
#define CLK  4

HX711 scale;

void setup() {
  Serial.begin(115200);
  Serial.println("HX711 scale demo");

  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  Serial.println("Readings:");
}

void loop() {
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 1); //scale.get_units() returns a float
  Serial.print(" g"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();
}
