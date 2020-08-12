#define LDR_PIN A0
int sensorValue;
int ledPins[] = {12,16,15,13}; //array of LED pins
void setup() {
  // put your setup code here, to run once:
  pinMode (LDR_PIN, INPUT);
  for (int i =0;i<4;i++){
    pinMode(ledPins[i], OUTPUT); //sets pin and output for each LED
  }

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(LDR_PIN); 
  Serial.println("LDR Value:" + String (sensorValue));
  if (sensorValue < 180) {
    int cls[4]={1,1,1,1};
    for (int i =0;i<4;i++){
      digitalWrite(ledPins[i], cls[i]);
    } 
  }
  else if (sensorValue >= 180 && sensorValue < 300) {
    int cls[4]={1,1,1,0};
    for (int i =0;i<4;i++){
      digitalWrite(ledPins[i], cls[i]);
    }
  } 
  else if (sensorValue >= 300 && sensorValue < 600) {
    int cls[4]={1,1,0,0};
    for (int i =0;i<4;i++){
      digitalWrite(ledPins[i], cls[i]);
    }
  } 
  else if (sensorValue >=  600 && sensorValue < 900) {
    int cls[4]={1,0,0,0};
    for (int i =0;i<4;i++){
      digitalWrite(ledPins[i], cls[i]);
    }
  } 
  else if (sensorValue >= 900){
    int cls[4]={0,0,0,0};
    for (int i =0;i<4;i++){
      digitalWrite(ledPins[i], cls[i]);
    } 
  }
}  
