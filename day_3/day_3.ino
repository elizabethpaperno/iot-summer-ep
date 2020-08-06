#define RED_LED 15
#define YELLOW_LED 16
#define GREEN_LED 12
void setup() {
  // Setting pin 15 as output
  pinMode (RED_LED, OUTPUT);
  pinMode (YELLOW_LED, OUTPUT);
  pinMode (GREEN_LED, OUTPUT);
}

void loop() {
  // Toggling LED
  digitalWrite (RED_LED,HIGH);
  delay(10000);
  digitalWrite (RED_LED, LOW);
  digitalWrite (GREEN_LED,HIGH);
  delay(20000);
  digitalWrite (GREEN_LED,LOW);
   digitalWrite (YELLOW_LED,HIGH);
  delay(2000);
  digitalWrite (YELLOW_LED,LOW);
  
  
}
