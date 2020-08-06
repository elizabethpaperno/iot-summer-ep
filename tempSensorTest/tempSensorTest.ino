#include <DHT.h>
#define DATA_PIN 13
#define DHT_TYPE DHT22

DHT dht(DATA_PIN, DHT_TYPE); 
float tempValue, humidityValue; 
float heatIndex;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  dht.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  tempValue = dht.readTemperature(true);
  humidityValue = dht.readHumidity();
  heatIndex = dht.computeHeatIndex(); 
  Serial.print ("Temp:"); Serial.print (tempValue);Serial.println("°");
  Serial.print ("Humidity:"); Serial.print (humidityValue); Serial.println("%");
  Serial.print ("HeatIndex:"); Serial.println (heatIndex); 
  delay(1000);
}
