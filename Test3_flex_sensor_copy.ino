
/*
  ARTHAM - Five Flex Sensor Monitoring
  Board: ESP32-WROOM-32
  Voltage divider: 10k ohm per sensor
*/

const int flexPins[5] = {
  34,  // Thumb
  32,  // Index
  35,  // Middle
  33,  // Ring
  36   // Little
};

const char* sensorNames[5] = {
  "THUMB",
  "INDEX",
  "MIDDLE",
  "RING",
  "LITTLE"
};

void setup() {
  Serial.begin(115200);

  analogReadResolution(12);

  for (int i = 0; i < 5; i++) {
    analogSetPinAttenuation(flexPins[i], ADC_11db);
  }

  Serial.println();
  Serial.println("======================================");
  Serial.println(" ARTHAM - FLEX SENSOR LIVE MONITOR");
  Serial.println("======================================");
  Serial.println("Keep your Serial Monitor at 115200 baud.");
  Serial.println();
}

void loop() {

  for (int i = 0; i < 5; i++) {

    int sensorValue = analogRead(flexPins[i]);

    Serial.print(sensorNames[i]);
    Serial.print(" = ");
    Serial.print(sensorValue);

    if (i < 4) {
      Serial.print("   |   ");
    }
  }

  Serial.println();

  delay(200);
}
