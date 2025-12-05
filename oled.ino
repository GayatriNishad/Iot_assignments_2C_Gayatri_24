#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define the display resolution
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
const int SCREEN_ADDRESS = 0x3C; // Most common I2C address for 128x64, try 0x3D if this doesn't work.

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  // Initialize the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the display buffer
  display.clearDisplay();

  // Set text properties
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner

  // Print text
  display.println("Hello World!");

  // Display the buffer on the screen
  display.display();
}

void loop() {
  // Your main loop code goes here (e.g., updating a sensor value)
  // To update the display, you would use:
  // display.clearDisplay();
  // display.setCursor(0, 10);
  // display.println("New Value: " + String(millis()));
  // display.display();
  // delay(100);
}