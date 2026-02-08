const int dataPin  = 3;  // Chân DS của 74HC595
const int latchPin = 4;  // Chân ST_CP của 74HC595
const int clockPin = 5;  // Chân SH_CP của 74HC595

// Các chân nối vào Hàng (Row) của LED Ma trận
const int rowPins[] = {13, 12, 11, 10, 9, 8, 7, 6};

// H
byte letter[] = {
  0b01000010,
  0b01000010,
  0b01000010,
  0b01111110, // Gạch ngang
  0b01000010,
  0b01000010,
  0b01000010,
  0b00000000
};

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  
  for (int i = 0; i < 8; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH); 
  }
}

void loop() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(latchPin, LOW);
    
    shiftOut(dataPin, clockPin, MSBFIRST, letter[i]); 
    
    digitalWrite(latchPin, HIGH);

    digitalWrite(rowPins[i], LOW);  
    
    delay(2);                       
    
    digitalWrite(rowPins[i], HIGH); 
  }
}