//Basic Server

//1. Connect to Network (Soft-AP , home AP )
//2. Handles information exchange (Server library)
//3. Client can connect
//4. Information (DHT)
//5. Control (LED)
//6. HTML Page (if we want a web Graphical User Interface /GUI)

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
#include "index_page.h"


#define WIFI_SSID "PAPNET"
#define WIFI_PASS "paperno.net"

#define LED 15
#define DHT_PIN 5
#define DHTTYPE DHT22

//  Leavea param blank for port 80 and enter a num for some other port
ESP8266WebServer server(80);

DHT dht(DHT_PIN, DHTTYPE);

void connectWifi() {
  // Begin takes some time
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to ");
  Serial.println(WiFi.SSID());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected.");
}

void rootHandle() {
  //    server.send(<HTTP Response Code>,<Data Type>,<Data>);
  server.send(200, "text/html", index_ESP);
}

void LEDHandle() {
  digitalWrite(LED, !digitalRead(LED)); // Active Low Toggle
  server.send(204, "");
}

void DHTHandle() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  String dhtstr = "Temperature :" + String(temp) + " celcius \nHumidity " + String(hum) + "%";
  Serial.println(dhtstr);
  server.send(200 , "text/plain" , dhtstr);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();

  dht.begin();

  connectWifi();

  Serial.println(WiFi.localIP());

  
  
  Serial.println("Starting Server");

  // server.on (<"URL/Function">,<Function Pointer>)
  //  Links an address to a function
  server.on("/", rootHandle);
#ifdef LED
  pinMode(LED, OUTPUT);
  server.on("/LED", LEDHandle);
#endif
  server.on("/DHT", DHTHandle);
  
  //  Server start
  server.begin();
  Serial.println("Server Started");
}

void loop() {
  //  Client Listener
  server.handleClient();
}
