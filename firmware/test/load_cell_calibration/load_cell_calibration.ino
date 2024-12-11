/*
 Example using the SparkFun HX711 breakout board with a scale
 By: Nathan Seidle
 SparkFun Electronics
 Date: November 19th, 2014
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

 This is the calibration sketch. Use it to determine the calibration_factor that the main example uses. It also
 outputs the zero_factor useful for projects that have a permanent mass on the scale in between power cycles.

 Setup your scale and start the sketch WITHOUT a weight on the scale
 Once readings are displayed place the weight on the scale
 Press +/- or a/z to adjust the calibration_factor until the output readings match the known weight
 Use this calibration_factor on the example sketch

 This example assumes pounds (lbs). If you prefer kilograms, change the Serial.print(" lbs"); line to kg. The
 calibration factor will be significantly different but it will be linearly related to lbs (1 lbs = 0.453592 kg).

 Your calibration factor may be very positive or very negative. It all depends on the setup of your scale system
 and the direction the sensors deflect from zero state
 This example code uses bogde's excellent library: https://github.com/bogde/HX711
 bogde's library is released under a GNU GENERAL PUBLIC LICENSE
 Arduino pin 2 -> HX711 CLK
 3 -> DOUT
 5V -> VCC
 GND -> GND

 Most any pin on the Arduino Uno will be compatible with DOUT/CLK.

 The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.

*/

#include "HX711.h"

#define DOUT  3
#define CLK  4

HX711 scale;

// Settings
float calibration_factor = 8.61;  // 84.3 for grams, 8.61 for millinewtons
unsigned int avg_num = 20;
float cal_step = 0.01;

void setup() {
  SerialUSB.begin(115200);
  SerialUSB.println("HX711 calibration sketch");
  SerialUSB.println("Remove all weight from scale");
  SerialUSB.println("After readings begin, place known weight on scale");
  SerialUSB.println("Press + or a to increase calibration factor");
  SerialUSB.println("Press - or z to decrease calibration factor");

  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  SerialUSB.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  SerialUSB.println(zero_factor);
}

void loop() {

  float val = 0;

  scale.set_scale(calibration_factor); //Adjust to this calibration factor

  // Get average of several readings
  for (int i = 0; i < avg_num; i++) {
    val += scale.get_units();
  }
  val /= avg_num;

  SerialUSB.print("Reading: ");
  SerialUSB.print(val, 1);
  SerialUSB.print(" calibration_factor: ");
  SerialUSB.print(calibration_factor);
  SerialUSB.println();

  if(SerialUSB.available())
  {
    char temp = SerialUSB.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += cal_step;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= cal_step;
  }
}
