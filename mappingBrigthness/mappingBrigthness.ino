#define LDR_PIN A0
#define LED 15
int sensorValue;
void setup() {
  // put your setup code here, to run once:
  pinMode (LDR_PIN, INPUT);
  pinMode (LED, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(LDR_PIN); 
  int mappedBrightness = map (sensorValue, 0, 1024, 256, 0);
  analogWrite(15, mappedBrightness); 
}
