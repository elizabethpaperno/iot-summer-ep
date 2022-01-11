//display hello world on screen 

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735

#define TFT_CS         16
#define TFT_RST        0                                           
#define TFT_DC         4

//Instantiate an object of ST7735 and naming it tft
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
  
  Serial.println("Screen Initializing");
  // Init ST7735R chip, green tab
  tft.initR(INITR_144GREENTAB);
  Serial.println("Screen Initialized");

  tft.fillScreen(0xE49F);
  tft.setTextWrap(true);

  //(xpos, ypos, w, h, color)
  tft.fillRect(20,20,80,40, ST77XX_BLACK);
  
  tft.setCursor(30,30);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE);

  tft.println("hello world");
  

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long timeElapsed = millis(); //time in ms since MCU start

  float timeElapsedFloat = float(timeElapsed) / 1000; 

   tft.setCursor(30,45);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.print ("Time Elapsed:"); tft.println(timeElapsedFloat);
}
