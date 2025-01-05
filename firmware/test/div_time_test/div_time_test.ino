// ADC
static const int ADC_PIN = A0;
static const uint32_t AIN_MAX = 1023;
static const float AIN_REF = 3.3;
static const float AIN_VOLTAGE_DIV = 0.3333;

// Constants
static const int NUM_DIVS = 1000;

void setup() {
  SerialUSB.begin(115200);
  pinMode(ADC_PIN, INPUT);
}

void loop() {
  float vcc_voltage;
  unsigned long timestamp;
  unsigned long div_time_us;
  
  // Get some random value so we don't optimize out the divisions
  vcc_voltage = analogRead(ADC_PIN) * AIN_REF / AIN_MAX;

  // Time floating point divisions
  timestamp = micros();
  for (int i = 0; i < NUM_DIVS; i++) {
    vcc_voltage /= 0.23;
  }
  div_time_us = micros() - timestamp;

  // Print results
  SerialUSB.print("Div: ");
  SerialUSB.print(vcc_voltage);
  SerialUSB.print(" Time (us) for ");
  SerialUSB.print(NUM_DIVS);
  SerialUSB.print(" divs: ");
  SerialUSB.println(div_time_us);

  delay(1000);
}
