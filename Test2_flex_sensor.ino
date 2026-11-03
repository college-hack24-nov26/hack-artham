
// ARTHAM - Five Flex Sensor Live Monitoring
// Board: ESP32-WROOM-32

const int flexPins[5] = {
  34,  // Thumb
  35,  // Index Finger
  32,  // Middle Finger
  33,  // Ring Finger
  36   // Little Finger
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

  Serial.println("ARTHAM - FLEX SENSOR MONITOR");
  Serial.println("---------------------------------------------");
}

void loop() {
  for (int i = 0; i < 5; i++) {
    int sensorValue = analogRead(flexPins[i]);

    Serial.print(sensorNames[i]);
    Serial.print(": ");
    Serial.print(sensorValue);
    Serial.print("    ");
  }

  Serial.println();

  delay(200);
}
