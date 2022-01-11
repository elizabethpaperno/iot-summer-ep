#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#define DATA_PIN 12
#define DHT_TYPE DHT22

#define WIFI_SSID "PAPNET"
#define WIFI_PASS "paperno.net"

const char host [] = "maker.ifttt.com";
const int httpsPort = 443;

WiFiClientSecure client; 

DHT dht(DATA_PIN, DHT_TYPE);

float tempValue, humidityValue;
float heatIndex;

String url = "/trigger/temp-alert/with/key/jj-V5mRSRUtv6FqfvV0fa";
boolean currentVal = true;
boolean preVal = false;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  WiFi.begin (WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to"); Serial.print (WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nConnected to "); Serial.println (WIFI_SSID);

}

void triggerEmail() {
    client.setInsecure(); //Just connect don't authenticate
  
  if (!client.connect(host, httpsPort)){
    Serial.println ("Connection Error"); 
    return;
  }
  
 
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + String(host) + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n\r\n");
  

  while (client.connected()) {
  String line = client.readStringUntil('\n');
  if (line == "\r"){
    Serial.println("Header Recieved"); 
    break;
  } 
  }
  String line = client.readStringUntil('\n');
  Serial.println (line); 
  client.stop();
}

void loop() {
  // put your main code here, to run repeatedly:
  tempValue = dht.readTemperature(true);
  currentVal = (tempValue > 81.6);
  Serial.print ("Temp:"); Serial.print (tempValue); Serial.println("°");
  if (tempValue > 81.6 && preVal != currentVal){
    triggerEmail();
  }
  preVal = currentVal;
  delay(1000);
}
