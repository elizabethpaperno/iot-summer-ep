#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include "bigID.h"
#include "idImage.h"

#define TFT_CS         16
#define TFT_RST        0
#define TFT_DC         4

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
  Serial.println("Screen initializing");
  tft.initR(INITR_144GREENTAB);
  Serial.println("Screen Initialized");

  tft.fillScreen(ST77XX_WHITE);
  tft.setTextWrap(true);
  tft.setTextColor(ST77XX_BLACK);
}
unsigned long beginTime = 0;
void loop() {
  // put your main code here, to run repeatedly:
//1ST SCREEN
  tft.setCursor(10, 10);  
  tft.setTextSize(1);
  tft.print("  STUYVESANT HIGH          SCHOOL");
  tft.drawRGBBitmap(10,42, idphoto, IMAGE_WIDTH, IMAGE_HEIGHT);
  tft.setCursor(62, 42);
  tft.print("Name:                 Elizabeth            Paperno");
  tft.setCursor(62,72);
  tft.print("DOB:                  12/28/05");
  tft.setCursor(62, 102);
  tft.print("Grad Year:            2023");
  delay(20000);
  //CLEAR SCREEN AND SET 2ND SCREEN WITH JUST IMAGE
  tft.fillScreen(ST77XX_WHITE);
  tft.drawRGBBitmap(14,9, bigIdPhoto, IMAGE_WIDTH2, IMAGE_HEIGHT2);
  delay(20000);
  tft.fillScreen(ST77XX_WHITE);
   

}
