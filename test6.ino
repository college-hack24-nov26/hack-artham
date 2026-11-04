
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET
);

// Flex sensor pins
#define THUMB_PIN  34
#define INDEX_PIN  32
#define MIDDLE_PIN 35
#define RING_PIN   33
#define LITTLE_PIN 36

// Your calibrated thresholds
#define THUMB_THRESHOLD  165
#define INDEX_THRESHOLD  400
#define MIDDLE_THRESHOLD 195
#define RING_THRESHOLD   435
#define LITTLE_THRESHOLD 375

String previousWord = "";

void showWord(String word) {
  if (word == previousWord) return;

  previousWord = word;

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(20, 8);
  display.println("ARTHAM SMART GLOVE");

  display.drawLine(0, 22, 127, 22, SSD1306_WHITE);

  display.setTextSize(2);
  int16_t x = (128 - word.length() * 12) / 2;
  display.setCursor(x, 34);
  display.println(word);

  display.display();

  Serial.print("Detected Word: ");
  Serial.println(word);
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("OLED not detected!");
    while (true) {
      delay(100);
    }
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(20, 20);
  display.println("ARTHAM");
  display.display();

  delay(1500);
}

void loop() {

  int thumb  = analogRead(THUMB_PIN);
  int index  = analogRead(INDEX_PIN);
  int middle = analogRead(MIDDLE_PIN);
  int ring   = analogRead(RING_PIN);
  int little = analogRead(LITTLE_PIN);

  // 0 = Straight, 1 = Bent
  int T = (thumb < THUMB_THRESHOLD);
  int I = (index < INDEX_THRESHOLD);
  int M = (middle < MIDDLE_THRESHOLD);
  int R = (ring < RING_THRESHOLD);
  int L = (little < LITTLE_THRESHOLD);

  String word = "UNKNOWN";

  // Five test gestures
  if (T == 0 && I == 0 && M == 0 && R == 0 && L == 0) {
    word = "HELLO";
  }
  else if (T == 1 && I == 0 && M == 0 && R == 0 && L == 0) {
    word = "THANK YOU";
  }
  else if (T == 1 && I == 1 && M == 0 && R == 0 && L == 0) {
    word = "YES";
  }
  else if (T == 1 && I == 1 && M == 1 && R == 0 && L == 0) {
    word = "NO";
  }
  else if (T == 0 && I == 0 && M == 1 && R == 1 && L == 1) {
    word = "HELP";
  }

  showWord(word);

  delay(200);
}
