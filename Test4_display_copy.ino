
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

void setup() {
  Serial.begin(115200);

  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED NOT FOUND!");
    while (true);
  }

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(20, 5);
  display.println("ARTHAM PROJECT");

  display.drawLine(0, 18, 127, 18, SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(15, 28);
  display.println("OLED TEST");

  display.setTextSize(1);
  display.setCursor(20, 52);
  display.println("Display Working!");

  display.display();
}

void loop() {
}
