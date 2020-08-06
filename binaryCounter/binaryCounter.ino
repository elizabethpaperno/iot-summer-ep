//array of LED pins
  int ledPins[] = {12,16,15,13};
  void setup() {
    for (int i =0;i<4;i++){
    pinMode(ledPins[i], OUTPUT); //sets pin and output for each LED
    }
  }
  void findBinaryDisplay(byte regNum) {//pass byte parameter into function
    for (int i =0;i<4;i++) {
      if (bitRead(regNum, i)==1) //if byte is 1
      {
      digitalWrite(ledPins[i], HIGH); //turn on LED
      } else { //if bte read is not 1
        digitalWrite(ledPins[i], LOW); //turn off led
      }
    }
  }
  
  void loop() 
  {
    for (byte counter=0;counter<=15; counter++) {//runs in a loop for every number from 0-15
      findBinaryDisplay(counter); //finds display for each number
      delay(500); 
    }
  }
  
