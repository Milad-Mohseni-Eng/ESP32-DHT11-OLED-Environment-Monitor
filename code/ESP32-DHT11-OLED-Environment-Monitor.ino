/*************************************************
 * ESP32 Smart Environment Monitor
 * Author : Milad Mohseni
 * Board  : ESP32 (30-pin)
 *
 * Features:
 * -----------------------------------------------
 * DHT11 Temperature & Humidity Monitoring
 * OLED Live Display
 * Green LED  = NORMAL
 * Red LED    = WARNING
 * Blue LED   = CRITICAL
 * Sensor Error Detection
 * State Machine Design
 *************************************************/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// ------------------------------------------------
// OLED
// ------------------------------------------------

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

// ------------------------------------------------
// DHT11
// ------------------------------------------------

#define DHT_PIN 23

DHT dht11(DHT_PIN, DHT11);

// ------------------------------------------------
// LEDS
// ------------------------------------------------

#define GREEN_LED 15
#define RED_LED   2
#define BLUE_LED  4

// ------------------------------------------------
// SYSTEM STATES
// ------------------------------------------------

enum SystemState
{
  NORMAL,
  WARNING,
  CRITICAL,
  SENSOR_ERROR
};

SystemState currentState;

// ------------------------------------------------
// SETUP
// ------------------------------------------------

void setup()
{
  Wire.begin(21,22);

  dht11.begin();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    while(true);
  }

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(10,20);
  display.println("READY");

  display.display();

  delay(2000);
}

// ------------------------------------------------
// MAIN LOOP
// ------------------------------------------------

void loop()
{
  float humidity = dht11.readHumidity();

  float temperature = dht11.readTemperature();

  // --------------------------------------------
  // SENSOR ERROR CHECK
  // --------------------------------------------

  if(isnan(humidity) || isnan(temperature))
  {
    currentState = SENSOR_ERROR;
  }

  else
  {
    // --------------------------------------------
    // CRITICAL CONDITIONS
    // --------------------------------------------

    if(temperature > 35 || humidity > 70)
    {
      currentState = CRITICAL;
    }

    // --------------------------------------------
    // WARNING CONDITIONS
    // --------------------------------------------

    else if(temperature > 30 || humidity > 60)
    {
      currentState = WARNING;
    }

    // --------------------------------------------
    // NORMAL CONDITIONS
    // --------------------------------------------

    else
    {
      currentState = NORMAL;
    }
  }

  // --------------------------------------------
  // OUTPUTS
  // --------------------------------------------

  switch(currentState)
  {
    case NORMAL:

      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, LOW);
      digitalWrite(BLUE_LED, LOW);

      break;

    case WARNING:

      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, HIGH);
      digitalWrite(BLUE_LED, LOW);

      break;

    case CRITICAL:

      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, LOW);
      digitalWrite(BLUE_LED, HIGH);

      break;

    case SENSOR_ERROR:

      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, HIGH);
      digitalWrite(BLUE_LED, HIGH);

      break;
  }

  // --------------------------------------------
  // OLED DISPLAY
  // --------------------------------------------

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0,0);
  display.println("SMART ENVIRONMENT");

  display.setCursor(0,15);
  display.print("Humidity: ");
  display.print(humidity);
  display.println("%");

  display.setCursor(0,30);
  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");

  display.setCursor(0,50);

  switch(currentState)
  {
    case NORMAL:
      display.println("STATUS: NORMAL");
      break;

    case WARNING:
      display.println("STATUS: WARNING");
      break;

    case CRITICAL:
      display.println("STATUS: CRITICAL");
      break;

    case SENSOR_ERROR:
      display.println("STATUS: ERROR");
      break;
  }

  display.display();

  delay(2000);
}