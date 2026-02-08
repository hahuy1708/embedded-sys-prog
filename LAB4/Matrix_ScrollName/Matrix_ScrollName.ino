const int dataPin  = 3;
const int latchPin = 4;
const int clockPin = 5;
const int rowPins[] = {13, 12, 11, 10, 9, 8, 7, 6};

const int totalCols = 32; 

byte bigMap[8][totalCols] = {
  // Trống   H              U              Y            Trống
  {0,0,0,0,  1,0,0,0,1,0,  1,0,0,0,0,1,  1,0,0,0,1,0,  0,0,0,0},
  {0,0,0,0,  1,0,0,0,1,0,  1,0,0,0,0,1,  0,1,0,1,0,0,  0,0,0,0},
  {0,0,0,0,  1,0,0,0,1,0,  1,0,0,0,0,1,  0,0,1,0,0,0,  0,0,0,0},
  {0,0,0,0,  1,1,1,1,1,0,  1,0,0,0,0,1,  0,0,1,0,0,0,  0,0,0,0}, // Giữa
  {0,0,0,0,  1,0,0,0,1,0,  1,0,0,0,0,1,  0,0,1,0,0,0,  0,0,0,0},
  {0,0,0,0,  1,0,0,0,1,0,  1,0,0,0,0,1,  0,0,1,0,0,0,  0,0,0,0},
  {0,0,0,0,  1,0,0,0,1,0,  1,0,0,0,0,1,  0,0,1,0,0,0,  0,0,0,0},
  {0,0,0,0,  1,0,0,0,1,0,  0,1,1,1,1,0,  0,0,1,0,0,0,  0,0,0,0}
};

byte buffer[8];

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
  for (int step = 0; step < (totalCols - 8); step++) {
    
    for (int r = 0; r < 8; r++) {
      byte rowByte = 0;
      for (int c = 0; c < 8; c++) {
        if (bigMap[r][step + c] == 1) {
          rowByte |= (1 << (7 - c)); 
        }
      }
      buffer[r] = rowByte;
    }

    int speed = 90;
    unsigned long startFrame = millis();
    
    while (millis() - startFrame < speed) {
      for (int i = 0; i < 8; i++) {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST, buffer[i]);
        digitalWrite(latchPin, HIGH);

        digitalWrite(rowPins[i], LOW);
        delay(1);
        digitalWrite(rowPins[i], HIGH);
      }
    }
  }
}
