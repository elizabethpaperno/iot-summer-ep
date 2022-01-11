//Basic Server
//Connect to Network (SOft-AP, home AP)
//Handle information exchange (Server library )
//Connect client
//Informtaion (DHT)
// HTML page (for GUI)

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h> //server library
#include <DHT.h>
#include "index_page.h"

ESP8266WebServer server(80); //param represents port num, default is 80

#define WIFI_SSID "PAPNET"
#define WIFI_PASS "paperno.net"

#define LED 15

#define DHT_PIN 5
#define DHT_TYPE DHT22

DHT dht (DHT_PIN, DHT_TYPE);

void connectWiFi(){
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.println ("Connecting to: "); Serial.println(WIFI_SSID);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println ("Connected to: "); Serial.println(WIFI_SSID);
}
//function has to have no return type to be passed into server.on
void rootHandle(){
  //send(<HTTP Response code>, <data type>)
  server.send(200, "text/html", index_page);
}

void LEDHandle(){
  server.send (204, "");
  digitalWrite(LED, !digitalRead(LED));
}

void DHTHandle () {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  String dhtstr = "Temperature: " + String(temp) + "Celcius \nHumidity: " + String(hum) + "%";
  Serial.print(dhtstr);
  server.send(200, "text/plain", dhtstr);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();

  pinMode(LED, OUTPUT); 

  dht.begin(); 
  
  connectWiFi();
  
  Serial.println(WiFi.localIP()); 
  Serial.println("Starting Server");
  
  // server.on (<"URL/Function">, <Function Pointer>); 
  server.on("/", rootHandle); 
  
 #ifndef LED
  server.on("/LED", LEDHandle); 
 #endif

  server.on("/DHT", DHTHandle);
  server.begin(); 
  Serial.println("Server Started");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient(); //client listener
}
