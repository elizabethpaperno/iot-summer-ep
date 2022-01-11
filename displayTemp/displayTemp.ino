#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <DHT.h>// temp and humidity sensor library

#define TFT_CS         16
#define TFT_RST        0                                           
#define TFT_DC         4

#define DATA_PIN 5
#define DHT_TYPE DHT22

//Instantiate an object of ST7735 and naming it tft
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

//Instantiate an object of DHT and name it dht
DHT dht(DATA_PIN, DHT_TYPE);


unsigned long loopBeginTime = 0; 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
  dht.begin();
  Serial.println("Screen Initializing");
  // Init ST7735R chip, green tab
  tft.initR(INITR_144GREENTAB);
  Serial.println("Screen Initialized");

  tft.fillScreen(ST77XX_BLACK);
  tft.setTextWrap(true);



  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  loopBeginTime = millis(); 

}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  if (millis()-loopBeginTime >2000) {
    loopBeginTime = millis(); 
    tft.setCursor(10,34);
    tft.print("Temp (F): ");
  tft.println(String(dht.readTemperature(true)));
    tft.setCursor(5,54);
   tft.print("Humidity(%): ");
  tft.println(String(dht.readHumidity()));    
  }
}
