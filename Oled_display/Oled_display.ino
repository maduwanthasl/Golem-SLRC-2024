#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

int x = 500;

void loop() {
  display.clearDisplay();

  // Set text color to black
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("GONO");

  // Set text color to white
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(20, 22);
  display.print("I love u");
  delay(100);

  display.display();
}
