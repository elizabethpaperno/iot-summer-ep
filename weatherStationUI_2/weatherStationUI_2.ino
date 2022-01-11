//"7b46696e232c8385ececd19ea7da7c9f"
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include "NTPClientUpdated.h"
//weather libraries
#include <OpenWeatherMapCurrent.h>
#include <OpenWeatherMapForecast.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "weathericon.h"
//5day/3hr forecast
// 3hr - 6hr - 9hr
#define MAX_FORECASTS 3

// WiFi credentials
#define WIFI_SSID "PAPNET"
#define WIFI_PASS "paperno.net"

//Screen pins
#define TFT_CS         16
#define TFT_RST        0
#define TFT_DC         4

// Date and time initializations
WiFiUDP ntpUDP;
const long utcOffsetInSeconds = -4 * 3600; // (3600*4) for daylight savings, -18000 for UTC-5
NTPClientUpdated timeClient(ntpUDP, utcOffsetInSeconds);

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

String dateStamp, timeStamp;


// Weather Settings
String OPEN_WEATHER_MAP_LANGUAGE = "en";
String OPEN_WEATHER_MAP_APP_ID = "d4b26391d35fe98cace3b9f4e49c6ff9";
String OPEN_WEATHER_MAP_LOCATION = "New York,NY,US";
const boolean IS_METRIC = true; // Celsius data, make it false for farenheit


//weather objects
OpenWeatherMapCurrentData currentWeather;
OpenWeatherMapForecastData forecasts[MAX_FORECASTS]; // 3hr [0] - 6 hr [1] - 9 hr [2]

//custom colors

#define CUSTOM_WHITE  0XFFFF
#define CUSTOM_BLACK  0X0000
#define CUSTOM_ORANGE 0XFE00
#define CUSTOM_RED  0XF00A
#define CUSTOM_BLUE 0X055E
#define CUSTOM_GREY 0X2124


void updateWeather() {
  OpenWeatherMapCurrent currentWeatherClient;
  currentWeatherClient.setMetric(IS_METRIC);
  currentWeatherClient.setLanguage(OPEN_WEATHER_MAP_LANGUAGE);
  currentWeatherClient.updateCurrent(&currentWeather, OPEN_WEATHER_MAP_APP_ID, OPEN_WEATHER_MAP_LOCATION);

//  OpenWeatherMapForecast forecastWeatherClient;
//  forecastWeatherClient.setMetric(IS_METRIC);
//  forecastWeatherClient.setLanguage(OPEN_WEATHER_MAP_LANGUAGE);
//  forecastWeatherClient.updateForecasts(forecasts, OPEN_WEATHER_MAP_APP_ID, OPEN_WEATHER_MAP_LOCATION, MAX_FORECASTS);
}

void drawProgress(int percentage) {
  if (percentage == 0) {
    tft.fillRect(7, 62, 100, 10, ST77XX_BLACK);
  }
  tft.drawRect(5, 60, 118, 14, ST77XX_WHITE);
  tft.fillRect(7, 62, percentage * 114 / 100, 10, ST77XX_BLUE);
}

void connectWiFi () {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  tft.fillScreen(CUSTOM_GREY);
  tft.setTextSize(1);
  tft.setTextColor(CUSTOM_WHITE);
  tft.setCursor(20, 30);
  tft.println("Weather Station");
  tft.setCursor(25, 110);

  tft.print("Elizabeth");

  tft.setCursor(20, 80);
  tft.setTextSize (1);
  tft.setTextColor(CUSTOM_WHITE, CUSTOM_BLACK);
  tft.print("Connecting to WiFI");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    drawProgress(i);
    i += 20;
    if (i > 99) {
      i = 0;
    }
    delay(500);
  }
  tft.setCursor(10, 80);
  tft.setTextSize (1);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.print("Connected to WiFI");
}

void welcomeScreen () {
  int hour_val = timeclient.getHours();
  tft.setTextSize(2);
  if (hour_val >= 7 && hourVal < 12){
    tft.fillScreen(CUSTOM_BLUE);
    tft.setCursor(40,40);
    tft.print("GOOD"); 
    tft.setCursor(25,40);
    tft.print("MORNING"); 
  }else if (hour_val >= 7 && hourVal < 12){
    tft.fillScreen(CUSTOM_RED);
    tft.setCursor(40,40);
    tft.print("GOOD"); 
    tft.setCursor(20,60);
    tft.print("AFTERNOON"); 
  } else {
    tft.fillScreen(CUSTOM_GREY);
    tft.setCursor(40,40);
    tft.print("GOOD"); 
    tft.setCursor(25,60);
    tft.print("GOOD NIGHT"); 
}
delay(5000);
}

void currentScreen() {
  timeCLient.update();
  updateWeather();
  dateStamp = timeClient.getFormattedDate();
  timeStamp = timeClient.getFormattedTime();
  tft.fillScreen(CUSTOM_ORANGE);
  tft.fillRect(10,10,108,44
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(2000000);
  tft.initR(INITR_144GREENTAB);
  tft.fillScreen(ST77XX_BLACK);
  connectWiFi();
  timeClient.begin()
  timeClient.forceUpdate();
  welcomeScreen();
}

void loop() {
  // put your main code here, to run repeatedly:

  
  delay(10000);
}
