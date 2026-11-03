
const int audioPin = 25;

const int SAFE_VOLUME = 5;  // Initial test setting only
const int TEST_FREQUENCY = 500;

void setup() {
  Serial.begin(115200);

  if (!ledcAttach(audioPin, 1000, 8)) {
    Serial.println("PWM setup failed!");
    while (true);
  }

  Serial.println("ARTHAM - Low Level Speaker Test");

  if (SAFE_VOLUME == 0) {
    ledcWriteTone(audioPin, 0);
  } else {
    ledcWriteTone(audioPin, TEST_FREQUENCY);
    ledcWrite(audioPin, (SAFE_VOLUME * 255) / 100);
  }
}

void loop() {
  // Keep the initial test setting fixed.
}
