//"7b46696e232c8385ececd19ea7da7c9f"
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include "NTPClientUpdated.h"
//weather libraries
#include <OpenWeatherMapCurrent.h>
#include <OpenWeatherMapForecast.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h> 

//5day/3hr forecast
// 3hr - 6hr - 9hr
#define MAX_FORECASTS 3

// WiFi credentials
#define WIFI_SSID "Pap.Opti.Net"
#define WIFI_PASS "peach-370-900"

#define CHANNEL_CURENT  0
#define CHANNEL_FORECAST 1



#define TFT_CS         16
#define TFT_RST        0
#define TFT_DC         4

// Date and time initializations
WiFiUDP ntpUDP;
const long utcOffsetInSeconds = -4 * 3600; // (3600*4) for daylight savings, -18000 for UTC-5
NTPClientUpdated timeClient(ntpUDP, utcOffsetInSeconds);
String dateStamp, timeStamp;


// Weather Settings
String OPEN_WEATHER_MAP_LANGUAGE = "en";
String OPEN_WEATHER_MAP_APP_ID = "d4b26391d35fe98cace3b9f4e49c6ff9";
String OPEN_WEATHER_MAP_LOCATION = "New York,NY,US";
const boolean IS_METRIC = true; // Celsius data, make it false for farenheit


//weather objects
OpenWeatherMapCurrentData currentWeather;
OpenWeatherMapForecastData forecasts[MAX_FORECASTS]; // 3hr [0] - 6 hr [1] - 9 hr [2]

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void connectWiFi() {
  Serial.print("Connecting to " + String(WIFI_SSID));
  tft.print("Connecting to " + String(WIFI_SSID));
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    tft.print(".");
  }
  Serial.println("\nConnected to " + String(WIFI_SSID));
  tft.println("\nConnected to " + String(WIFI_SSID));
}

void updateWeather() {
  if (CHANNEL_CURENT) {
  OpenWeatherMapCurrent currentWeatherClient;
  currentWeatherClient.setMetric(IS_METRIC);
  currentWeatherClient.setLanguage(OPEN_WEATHER_MAP_LANGUAGE);
  currentWeatherClient.updateCurrent(&currentWeather, OPEN_WEATHER_MAP_APP_ID, OPEN_WEATHER_MAP_LOCATION);
  }
  if (CHANNEL_FORECAST) {
  OpenWeatherMapForecast forecastWeatherClient;
  forecastWeatherClient.setMetric(IS_METRIC);
  forecastWeatherClient.setLanguage(OPEN_WEATHER_MAP_LANGUAGE);
  forecastWeatherClient.updateForecasts(forecasts, OPEN_WEATHER_MAP_APP_ID, OPEN_WEATHER_MAP_LOCATION, MAX_FORECASTS);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(2000000);
    tft.initR(INITR_144GREENTAB);
  tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(10, 10);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE);
  connectWiFi();

  timeClient.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  timeClient.update();
  updateWeather();
  dateStamp = timeClient.getFormattedDate();
  timeStamp = timeClient.getFormattedTime();
  tft.setCursor(10, 10);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  if (CHANNEL_CURENT) {
  Serial.println("Time: " + timeStamp);
  Serial.println("Date: " + dateStamp);
  Serial.println("Temp: " + String(int(round(currentWeather.temp))) + "°C");
  Serial.println("Description: " + currentWeather.description);
  Serial.println("Sunrise: " + timeClient.getFormattedTime(true, currentWeather.sunrise + utcOffsetInSeconds));
  Serial.println("Sunset: " + timeClient.getFormattedTime(true, currentWeather.sunset + utcOffsetInSeconds));
  tft.println("Time: " + timeStamp);
  tft.println("Date: " + dateStamp);
  tft.println("Temp: " + String(int(round(currentWeather.temp))) + "°C");
  tft.println("Description: " + currentWeather.description);
  tft.println("Sunrise: " + timeClient.getFormattedTime(true, currentWeather.sunrise + utcOffsetInSeconds));
  tft.println("Sunset: " + timeClient.getFormattedTime(true, currentWeather.sunset + utcOffsetInSeconds));
  }
  if (CHANNEL_FORECAST) {
  Serial.println("-----------------------------------------");
  Serial.println("In 3hrs");
  Serial.println("Temp: " + String(int(round(forecasts[0].temp))) + "°C");
  Serial.println("Description: " + forecasts[0].description);
  Serial.println("-----------------------------------------");
  Serial.println("In 6hrs");
  Serial.println("Temp: " + String(int(round(forecasts[1].temp))) + "°C");
  Serial.println("Description: " + forecasts[1].description);
  Serial.println("-----------------------------------------");
  Serial.println("In 9hrs");
  Serial.println("Temp: " + String(int(round(forecasts[2].temp))) + "°C");
  Serial.println("Description: " + forecasts[2].description);
  
  tft.println("In 3hrs");
  tft.println("Temp: " + String(int(round(forecasts[0].temp))) + "°C");
  tft.println("Description: " + forecasts[0].description);
  
  tft.println("In 6hrs");
  tft.println("Temp: " + String(int(round(forecasts[1].temp))) + "°C");
  tft.println("Description: " + forecasts[1].description);
  
  tft.println("In 9hrs");
  tft.println("Temp: " + String(int(round(forecasts[2].temp))) + "°C");
  tft.println("Description: " + forecasts[2].description);
  }
  delay(10000);
}
