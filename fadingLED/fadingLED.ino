#define LED 15
void setup() {
  // put your setup code here, to run once:
  pinMode (LED, OUTPUT);
  //changes resolution to 255 (1024 by default)
  analogWriteRange(255);
  analogWrite (LED, 77);
}

void loop() {
  // put your main code here, to run repeatedly:
 //Fade in LED
 for (int i=0; i<256; i++){
  analogWrite (LED, i);
  delay (5);
  }
 for (int i=255; i<0; i--){
  analogWrite (LED, i);
  delay(5);
  }    
}
