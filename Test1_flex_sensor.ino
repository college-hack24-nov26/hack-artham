
/*
  ARTHAM - Flex Sensor Calibration
  Controller: ESP32-WROOM-32
  Sensors: 5 Flex Sensors

  GPIO 34 - Thumb
  GPIO 35 - Index
  GPIO 32 - Middle
  GPIO 33 - Ring
  GPIO 36 - Little
*/

const int thumbPin  = 34;
const int indexPin  = 35;
const int middlePin = 32;
const int ringPin   = 33;
const int littlePin = 36;

void setup() {
  Serial.begin(115200);
  delay(1000);

  analogReadResolution(12);

  Serial.println();
  Serial.println("================================");
  Serial.println("       ARTHAM FLEX CALIBRATION");
  Serial.println("================================");
  Serial.println("Keep your fingers straight and bent");
  Serial.println("to observe the sensor readings.");
  Serial.println();
}

void loop() {

  int thumbValue  = analogRead(thumbPin);
  int indexValue  = analogRead(indexPin);
  int middleValue = analogRead(middlePin);
  int ringValue   = analogRead(ringPin);
  int littleValue = analogRead(littlePin);

  float thumbVoltage  = thumbValue * 3.3 / 4095.0;
  float indexVoltage  = indexValue * 3.3 / 4095.0;
  float middleVoltage = middleValue * 3.3 / 4095.0;
  float ringVoltage   = ringValue * 3.3 / 4095.0;
  float littleVoltage = littleValue * 3.3 / 4095.0;

  Serial.println("--------------------------------");

  Serial.print("Thumb  : ");
  Serial.print(thumbValue);
  Serial.print(" | ");
  Serial.print(thumbVoltage, 2);
  Serial.println(" V");

  Serial.print("Index  : ");
  Serial.print(indexValue);
  Serial.print(" | ");
  Serial.print(indexVoltage, 2);
  Serial.println(" V");

  Serial.print("Middle : ");
  Serial.print(middleValue);
  Serial.print(" | ");
  Serial.print(middleVoltage, 2);
  Serial.println(" V");

  Serial.print("Ring   : ");
  Serial.print(ringValue);
  Serial.print(" | ");
  Serial.print(ringVoltage, 2);
  Serial.println(" V");

  Serial.print("Little : ");
  Serial.print(littleValue);
  Serial.print(" | ");
  Serial.print(littleVoltage, 2);
  Serial.println(" V");

  delay(500);
}
