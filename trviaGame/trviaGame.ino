#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "JsonParser.h"
#include <Fonts/FreeMono12pt7b.h>
#define WIFI_SSID "PAPNET"
#define WIFI_PASS "paperno.net"

#define TFT_CS         16
#define TFT_RST        0
#define TFT_DC         4

const char host[] = "opentdb.com";
const int httpsPort = 443;

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

WiFiClientSecure client;

String url = "/api.php?amount=1&type=multiple";

JsonParser j;

void connectWiFi () {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.setCursor(30, 40);
  tft.println("Welcome to");
  tft.setCursor(30, 50);
  tft.println("Summer IoT");
  tft.setCursor(20, 120);
  tft.print("Elizabeth");

  tft.setCursor(10, 80);
  tft.setTextSize (1);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
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

void get_trivia() {
  client.setInsecure(); // Do connections whatsoever don't try to authenticate
  if (!client.connect(host, httpsPort)) {
    Serial.println("Connection error");
    return;
  }


  client.println(String("GET ") + url + " HTTP/1.1");
  client.println("Host: " + String(host));
  client.println("User-Agent: ESP8266");
  client.println("Connection: close");
  client.println();

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("Header received");
      break;
    }

  }
  String line = client.readStringUntil('\n');
  line = client.readStringUntil('\n');
  Serial.println(line);
  j.convertArray(line);
  client.stop();
}

void drawProgress(int percentage) {
  if (percentage == 0) {
    tft.fillRect(7, 62, 100, 10, ST77XX_BLACK);
  }
  tft.drawRect(5, 60, 118, 14, ST77XX_WHITE);
  tft.fillRect(7, 62, percentage * 114 / 100, 10, ST77XX_BLUE);
}

void animationScreen(uint16_t bgk_color, int textSize, uint16_t textColor, String words) {
  tft.fillScreen(bgk_color);
  tft.setCursor(30, 55);
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

void wrongScreen(){
  animationScreen(ST77XX_RED, 2, ST77XX_WHITE, "WRONG!");
  Serial.print ("The correct answer is "); Serial.println(j.getCorrectAnswer());
  tft.setCursor(20, 80);
  tft.setTextSize(1);
  tft.print ("  The correct        answer is "); tft.println(j.getCorrectAnswer());
  delay(4000);
}

void rightScreen() {
  animationScreen(ST77XX_GREEN, 2, ST77XX_WHITE, "RIGHT!");
  Serial.println("You are right!");
  delay(3000);
}

void invalidScreen() {
  animationScreen(ST77XX_BLACK, 1, ST77XX_WHITE, "  Invalid              Response");
  Serial.println("Invalid Response");
  delay(3000);
}

void printTrivia() {
  //clear any extra values
  while (Serial.available()) {
    Serial.read();
  }

  tft.fillScreen (ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.println("Q: " + j.question);
  tft.println("1: " + j.answers[0]);
  tft.println("2: " + j.answers[1]);
  tft.println("3: " + j.answers[2]);
  tft.println("4: " + j.answers[3]);

  Serial.println("Q: " + j.question);
  Serial.println("1: " + j.answers[0]);
  Serial.println("2: " + j.answers[1]);
  Serial.println("3: " + j.answers[2]);
  Serial.println("4: " + j.answers[3]);
  int score;
  //wait for user input
  while (!Serial.available());
  char answerGiven = Serial.read();
  //inavlid respinse
  if (answerGiven - '1' > 3 || answerGiven - '1' < 0) {
    invalidScreen();
    printTrivia();
  } else { //valid response
    if (j.answers [answerGiven - '1'] == j.getCorrectAnswer()) {
      rightScreen();

    } else {
      wrongScreen();
    }
  }
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  tft.initR(INITR_144GREENTAB);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextWrap(true);
  Serial.println();
  connectWiFi();
  delay(500);
  animationScreen(ST77XX_CYAN, 2, ST77XX_WHITE, "TRIVIA");
  delay(1000);
}

void loop() {
  get_trivia();
  printTrivia();
  delay(10);
}
