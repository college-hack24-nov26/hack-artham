
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// =====================================
// ARTHAM SMART SIGN LANGUAGE GLOVE
// ESP32 + 5 FLEX SENSORS + OLED
// =====================================

// OLED configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

// =====================================
// FLEX SENSOR GPIO CONNECTIONS
// =====================================

// Order: Thumb, Index, Middle, Ring, Little

const int flexPins[5] = {
  34, 32, 35, 33, 36
};

// =====================================
// YOUR LATEST CALIBRATION VALUES
// =====================================

// HELLO: All fingers straight
const int HELLO[5] = {
  180, 540, 260, 540, 470
};

// WATER: Thumb and little bent
const int WATER[5] = {
  60, 510, 190, 520, 350
};

// FOOD: All fingers partially curled
const int FOOD[5] = {
  110, 370, 60, 360, 420
};

// YES: Thumb straight, four fingers bent
const int YES[5] = {
  220, 100, 300, 110, 270
};

// NO: Index and middle straight
const int NO[5] = {
  70, 310, 270, 320, 390
};

// =====================================
// GESTURE DATABASE
// =====================================

const char* gestureNames[5] = {
  "HELLO",
  "WATER",
  "FOOD",
  "YES",
  "NO"
};

const int* gesturePatterns[5] = {
  HELLO,
  WATER,
  FOOD,
  YES,
  NO
};

// =====================================
// RECOGNITION SETTINGS
// =====================================

// Initial tolerance for each finger.
// These values must be tuned through testing.

const int tolerance[5] = {
  65, 75, 75, 75, 75
};

// Number of consecutive matching readings
const int STABLE_COUNT = 5;

// =====================================
// SENSOR READING FUNCTION
// =====================================

int readFlexSensor(int pin) {

  long total = 0;

  for (int i = 0; i < 10; i++) {
    total += analogRead(pin);
    delay(2);
  }

  return total / 10;
}

// =====================================
// READ ALL FIVE SENSORS
// =====================================

void readAllSensors(int readings[]) {

  for (int i = 0; i < 5; i++) {
    readings[i] = readFlexSensor(flexPins[i]);
  }
}

// =====================================
// GESTURE RECOGNITION
// =====================================

// Returns:
// 0 = HELLO
// 1 = WATER
// 2 = FOOD
// 3 = YES
// 4 = NO
// -1 = UNKNOWN

int recognizeGesture(int readings[]) {

  int bestGesture = -1;
  float bestScore = 999999.0;

  for (int g = 0; g < 5; g++) {

    float score = 0;
    bool matches = true;

    for (int i = 0; i < 5; i++) {

      int difference = abs(
        readings[i] - gesturePatterns[g][i]
      );

      // Reject pattern if any finger
      // is outside its tolerance.

      if (difference > tolerance[i]) {
        matches = false;
        break;
      }

      score +=
        (float)difference / tolerance[i];
    }

    // Select the closest matching gesture
    if (matches) {

      score = score / 5.0;

      if (score < bestScore) {
        bestScore = score;
        bestGesture = g;
      }
    }
  }

  return bestGesture;
}

// =====================================
// OLED DISPLAY FUNCTION
// =====================================

void showGesture(const char* word) {

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(12, 5);
  display.println("ARTHAM SMART GLOVE");

  display.drawLine(
    0, 18, 127, 18, SSD1306_WHITE
  );

  display.setTextSize(2);

  int16_t x = 10;

  if (strcmp(word, "UNKNOWN") == 0) {
    display.setTextSize(1);
    display.setCursor(5, 32);
    display.println("UNKNOWN GESTURE");
  }
  else {
    display.setCursor(x, 30);
    display.println(word);
  }

  display.display();
}

// =====================================
// SETUP
// =====================================

void setup() {

  Serial.begin(115200);

  analogReadResolution(12);

  Wire.begin(21, 22);

  if (!display.begin(
    SSD1306_SWITCHCAPVCC,
    OLED_ADDRESS
  )) {

    Serial.println("OLED NOT FOUND!");

    while (true) {
      delay(100);
    }
  }

  showGesture("READY");

  Serial.println("==========================");
  Serial.println(" ARTHAM GESTURE SYSTEM");
  Serial.println("==========================");

  Serial.println("Thumb | Index | Middle | Ring | Little");

  delay(1500);
}

// =====================================
// MAIN LOOP
// =====================================

void loop() {

  int readings[5];

  // Read all sensors
  readAllSensors(readings);

  // Recognize gesture
  int detected = recognizeGesture(readings);

  static int previousGesture = -2;
  static int stableCounter = 0;
  static int displayedGesture = -2;

  // Check whether the same gesture
  // is detected continuously.

  if (detected == previousGesture) {
    stableCounter++;
  }
  else {
    previousGesture = detected;
    stableCounter = 1;
  }

  // Display only after stable recognition
  if (
    stableCounter >= STABLE_COUNT &&
    displayedGesture != detected
  ) {

    displayedGesture = detected;

    if (detected == -1) {

      showGesture("UNKNOWN");

      Serial.println("UNKNOWN GESTURE");

    }
    else {

      showGesture(gestureNames[detected]);

      Serial.print("RECOGNIZED WORD: ");
      Serial.println(gestureNames[detected]);

    }
  }

  // =================================
  // SERIAL MONITOR DEBUGGING
  // =================================

  Serial.print("T:");
  Serial.print(readings[0]);

  Serial.print(" | I:");
  Serial.print(readings[1]);

  Serial.print(" | M:");
  Serial.print(readings[2]);

  Serial.print(" | R:");
  Serial.print(readings[3]);

  Serial.print(" | L:");
  Serial.print(readings[4]);

  Serial.print(" | RESULT:");

  if (detected == -1) {
    Serial.println("UNKNOWN");
  }
  else {
    Serial.println(gestureNames[detected]);
  }

  delay(100);
}
