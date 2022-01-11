#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#define TFT_CS         16
#define TFT_RST        0
#define TFT_DC         4

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void animationScreen(uint16_t bgk_color, int textSize, uint16_t textColor, String words) {
  tft.fillScreen(bgk_color);
  tft.setCursor(22, 20);
  tft.setTextSize(textSize);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(words);

  for (int i = 0; i <= 100; i++) {
    tft.drawFastHLine(14, 14, i, ST77XX_WHITE);
    tft.drawFastHLine(114, 114, -i, ST77XX_WHITE);
    delay(20);
  }

  for (int i = 0; i <= 100; i++) {
    //Draw line on topleft to top right14,14
    tft.drawFastVLine(114, 14, i, ST77XX_WHITE);
    //bottom right t bottom left
    tft.drawFastVLine(14, 114, -i, ST77XX_WHITE);
    delay(20);
  }
}

void screenNow1() {
  tft.fillScreen (0x3035b0);
  tft.setCursor(0, 0);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
}
void setup() {
  // put your setup code here, to run once:
  tft.initR(INITR_144GREENTAB);
  //animationScreen(ST77XX_CYAN, 2, ST77XX_WHITE, "Welcome     to      Weather   Station!");
  tft.fillScreen (0x3035b0);
}

void loop() {
  // put your main code here, to run repeatedly:

}
