/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-temperature-humidity-sensor-oled-display
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#define OLED_RESET -1
#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define DHTPIN 2 // pin connected to DHT11 sensor
#define DHTTYPE DHT11

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // create SSD1306 display object connected to I2C
DHT dht(DHTPIN, DHTTYPE);

String displayString;

void setup() {
  Serial.begin(9600);

  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display

  oled.setTextSize(2);      // text size
  oled.setTextColor(WHITE); // text color
  oled.setCursor(0, 10);    // position to display

  dht.begin();              // initialize DHT11 the temperature and humidity sensor

  displayString.reserve(10); // to avoid fragmenting memory when using String
}

void loop() {
  float humi  = dht.readHumidity();    // read humidity
  float tempC = dht.readTemperature(); // read temperature

  // check if any reads failed
  if (isnan(humi) || isnan(tempC)) {
    displayString = "Failed";
  } else {
    displayString  = String(tempC, 1); // one decimal places
    displayString += "°C";
    displayString += String(humi, 1); // one decimal places
    displayString += "%";
  }

  Serial.println(displayString);    // print the temperature in Celsius to Serial Monitor
  oledDisplayCenter(displayString); // display temperature and humidity on OLED
}

void oledDisplayCenter(String text) {
  int16_t x1;
  int16_t y1;
  uint16_t width;
  uint16_t height;

  oled.getTextBounds(text, 0, 0, &x1, &y1, &width, &height);

  // display on horizontal and vertical center
  oled.clearDisplay(); // clear display
  oled.setCursor((SCREEN_WIDTH - width) / 2, (SCREEN_HEIGHT - height) / 2);
  oled.println(text); // text to display
  oled.display();
}
