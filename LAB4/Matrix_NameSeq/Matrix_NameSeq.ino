const int dataPin  = 3;  
const int latchPin = 4;  
const int clockPin = 5;  
const int rowPins[] = {13, 12, 11, 10, 9, 8, 7, 6};

byte H[] = {0x42, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x42, 0x42};
byte U[] = {0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C};
byte Y[] = {0x42, 0x42, 0x24, 0x18, 0x18, 0x18, 0x18, 0x18};

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  
  for (int i = 0; i < 8; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }
}

void displayChar(byte character[], int duration) {
  unsigned long startTime = millis();
  
  while (millis() - startTime < duration) {
    for (int i = 0; i < 8; i++) {
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, character[i]);
      digitalWrite(latchPin, HIGH);

      digitalWrite(rowPins[i], LOW);  
      delay(2);                       
      digitalWrite(rowPins[i], HIGH); 
    }
  }
}

void loop() {
  displayChar(H, 1000); 
  
  displayChar(U, 1000); 
  
  displayChar(Y, 1000); 
  
  byte blank[] = {0,0,0,0,0,0,0,0};
  displayChar(blank, 500);
}
