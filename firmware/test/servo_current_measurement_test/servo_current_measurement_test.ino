#include <Wire.h>
#include <Servo.h>
#include <Adafruit_INA219.h>

static const int SRV_PIN = 6;       // Servo signal

Adafruit_INA219 ina219;
static Servo servo;



void setup(void) 
{
  SerialUSB.begin(115200);
  while (!SerialUSB) {
      // will pause Zero, Leonardo, etc until SerialUSB console opens
      delay(1);
  }
    
  SerialUSB.println("Hello!");
  
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  if (! ina219.begin()) {
    SerialUSB.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  //ina219.setCalibration_16V_400mA();

  SerialUSB.println("Measuring voltage and current with INA219 ...");

  // Configure servo and set to start position
  servo.attach(SRV_PIN);
  servo.write(0);
  delay(2000);
}

void loop(void) 
{
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

  static int servo_target_pos = 0;
  if (servo_target_pos == 0) {
    servo_target_pos = 180;
  } else {
    servo_target_pos = 0;
  }
  servo.write(servo_target_pos);
  delay(10);

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  SerialUSB.print("Bus Voltage:   "); SerialUSB.print(busvoltage); SerialUSB.println(" V");
  SerialUSB.print("Shunt Voltage: "); SerialUSB.print(shuntvoltage); SerialUSB.println(" mV");
  SerialUSB.print("Load Voltage:  "); SerialUSB.print(loadvoltage); SerialUSB.println(" V");
  SerialUSB.print("Current:       "); SerialUSB.print(current_mA); SerialUSB.println(" mA");
  SerialUSB.print("Power:         "); SerialUSB.print(power_mW); SerialUSB.println(" mW");
  SerialUSB.println("");

  delay(2000);
}
