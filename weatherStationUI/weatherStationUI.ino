//"7b46696e232c8385ececd19ea7da7c9f"
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include "NTPClientUpdated.h"
//weather libraries
#include <OpenWeatherMapCurrent.h>
#include <OpenWeatherMapForecast.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "weather_icon.h"
//5day/3hr forecast
// 3hr - 6hr - 9hr
#define MAX_FORECASTS 3

// WiFi credentials
#define WIFI_SSID "Elizabeth's iPhone"
#define WIFI_PASS "elizabethpaperno"


#define TFT_CS         16
#define TFT_RST        0
#define TFT_DC         4

// Date and time initializations
WiFiUDP ntpUDP;
const long utcOffsetInSeconds = -4 * 3600; // (3600*4) for daylight savings, -18000 for UTC-5
NTPClientUpdated timeClient(ntpUDP, utcOffsetInSeconds);

Adafruit_ST7735 tft (TFT_CS, TFT_DC, TFT_RST);

String dateStamp, timeStamp;


// Weather Settings
String OPEN_WEATHER_MAP_LANGUAGE = "en";
String OPEN_WEATHER_MAP_APP_ID = "d4b26391d35fe98cace3b9f4e49c6ff9";
String OPEN_WEATHER_MAP_LOCATION = "New York,NY,US";
const boolean IS_METRIC = false; // Celsius data, make it false for farenheit


//weather objects
OpenWeatherMapCurrentData currentWeather;
OpenWeatherMapForecastData forecasts[MAX_FORECASTS]; // = 3hr [0] - 6 hr [1] - 9 hr [2]


void connectWiFi() {
  Serial.print("Connecting to " + String(WIFI_SSID));
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to " + String(WIFI_SSID));
}

void updateWeather() {
  OpenWeatherMapCurrent currentWeatherClient;
  currentWeatherClient.setMetric(IS_METRIC);
  currentWeatherClient.setLanguage(OPEN_WEATHER_MAP_LANGUAGE);
  currentWeatherClient.updateCurrent(&currentWeather, OPEN_WEATHER_MAP_APP_ID, OPEN_WEATHER_MAP_LOCATION);

  OpenWeatherMapForecast forecastWeatherClient;
  forecastWeatherClient.setMetric(IS_METRIC);
  forecastWeatherClient.setLanguage(OPEN_WEATHER_MAP_LANGUAGE);
  forecastWeatherClient.updateForecasts(forecasts, OPEN_WEATHER_MAP_APP_ID, OPEN_WEATHER_MAP_LOCATION, MAX_FORECASTS);
}

void timeAndDate() {
  tft.fillScreen ((ST77XX_BLACK));
  tft.setTextSize(2);
  tft.setCursor(20, 30);
  tft.print(timeStamp);
  tft.setCursor(6, 60);
  tft.print(dateStamp);
  tft.setCursor(16, 90);
  tft.print("Brooklyn");
}
void screenNow2() {
  tft.fillScreen ((ST77XX_BLACK));
 
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(0, 0);
  tft.print("    Now");
  tft.drawRGBBitmap(32, 20, getIcon(currentWeather.icon), ICON_WIDTH, ICON_HEIGHT);
  tft.setCursor(23, 90);
  tft.setTextSize(2);
  tft.print(round(currentWeather.temp));
  tft.print(" F");
  tft.setTextSize(1);
  tft.setCursor(33, 114);
  tft.print(currentWeather.description);
  
}
void sideBySide(int x1, int y1, int x2, int y2, int iconX, int iconY, int x3, int y3, String tempTime,  ){
  tft.fillScreen ((ST77XX_BLACK));
 //weather now on right
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.setCursor(x1, y1);
  tft.print(tempTime);
  tft.drawRGBBitmap(iconX, iconY, getIcon(currentWeather.icon), ICON_WIDTH, ICON_HEIGHT);
  tft.setCursor(3, 90);
  tft.setTextSize(2);
  tft.print(round(currentWeather.temp));
  tft.setTextSize(1);
  tft.setCursor(1, 114);
  tft.print(currentWeather.description);  
}
void nowAnd3Hours() {
  tft.fillScreen ((ST77XX_BLACK));
 //weather now on right
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.print(" Now");
  tft.drawRGBBitmap(0, 20, getIcon(currentWeather.icon), ICON_WIDTH, ICON_HEIGHT);
  tft.setCursor(3, 90);
  tft.setTextSize(2);
  tft.print(round(currentWeather.temp));
  tft.setTextSize(1);
  tft.setCursor(1, 114);
  tft.print(currentWeather.description);
  //weather in 3 hrs on left
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  tft.setCursor(66, 0);
  tft.print("3 hrs");
  tft.drawRGBBitmap(64, 20, getIcon(forecasts[0].icon), ICON_WIDTH, ICON_HEIGHT);
  tft.setCursor(67, 90);
  tft.setTextSize(2);
  tft.print(round(forecasts[0].temp));
  tft.setTextSize(1);
  tft.setCursor(65, 114);
  tft.print(forecasts[0].description); 
}

void screen6hrsAnd9hrs() {
  tft.fillScreen ((ST77XX_BLACK));
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.print("6 hrs");
  tft.drawRGBBitmap(0, 20, getIcon(forecasts[1].icon), ICON_WIDTH, ICON_HEIGHT);
  tft.setCursor(3, 90);
  tft.setTextSize(2);
  tft.print(round(forecasts[1].temp));
  tft.setTextSize(1);
  tft.setCursor(1, 114);
  tft.print(currentWeather.description);
  //weather in 3 hrs on left
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.setCursor(66, 0);
  tft.print("9 hrs");
  tft.drawRGBBitmap(64, 20, getIcon(forecasts[2].icon), ICON_WIDTH, ICON_HEIGHT);
  tft.setCursor(67, 90);
  tft.setTextSize(2);
  tft.print(round(forecasts[2].temp));
  tft.setTextSize(1);
  tft.setCursor(65, 114);
  tft.print(forecasts[2].description); 
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(2000000);
  tft.initR(INITR_144GREENTAB);
  tft.fillScreen(ST77XX_BLACK);
  connectWiFi();
  timeClient.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  timeClient.update();
  updateWeather();
  dateStamp = timeClient.getFormattedDate();
  timeStamp = timeClient.getFormattedTime();
  timeAndDate();
  delay(10000);
  screenNow2();
  delay(10000);
  nowAnd3Hours();
  delay(10000);
  screen6hrsAnd9hrs();
  delay(10000);
}
