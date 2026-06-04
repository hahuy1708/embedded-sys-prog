const int dataPin = 11;
const int clockPin = 12;
const int latchPin = 10;

const int rowPins[8] = {2, 3, 4, 5, 6, 7, 8, 9};

byte letter[4][8] = {
  {0x7E, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x42, 0x00}, // H
  {0x7C, 0x42, 0x42, 0x7C, 0x42, 0x42, 0x7C, 0x00}, // U
  {0x7E, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x7E, 0x00}, // Y

};

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  for (int i = 0; i < 8; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }
}

void loop() {
  for (int chu = 0; chu < 4; chu++) {
    for (int lan = 0; lan < 60; lan++) {
      for (int row = 0; row < 8; row++) {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST, letter[chu][row]);
        digitalWrite(latchPin, HIGH);

        digitalWrite(rowPins[row], LOW);
        delay(2);
        digitalWrite(rowPins[row], HIGH);
      }
      
    }
  }
}