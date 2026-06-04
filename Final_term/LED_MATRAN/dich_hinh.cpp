const int dataPin = 3;
const int latchPin = 4;
const int clockPin = 5;
const int rowPins[] = {13, 12, 11, 10, 9, 8, 7, 6};

byte letter[8] = {
  0x42, // Hàng 1
  0x42, // Hàng 2
  0x42, // Hàng 3
  0x7E, // Hàng 4 (Thanh ngang)
  0x7E, // Hàng 5 (Thanh ngang)
  0x42, // Hàng 6
  0x42, // Hàng 7
  0x00  // Hàng 8 (Trống)
};

byte buffer[8]; // Mảng trung gian cho hình động

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

void loop() {
  for (int step = 0; step <= 8; step++) {
    
    // DỊCH SANG TRÁI
    for (int i = 0; i < 8; i++) {
      buffer[i] = letter[i] << step;
    }

    // DỊCH SANG PHẢI
    // for (int i = 0; i < 8; i++) {
    //   buffer[i] = letter[i] >> step;
    // }

    // DỊCH LÊN TRÊN
    // for (int i = 0; i < 8; i++) {
    //   if (i + step < 8) buffer[i] = letter[i + step];
    //   else buffer[i] = 0x00;
    // }

    // DỊCH XUỐNG DƯỚI
    // for (int i = 0; i < 8; i++) {
    //   if (i - step >= 0) buffer[i] = letter[i - step];
    //   else buffer[i] = 0x00;
    // }

    // ============================================================

    for (int k = 0; k < 20; k++) {
      for (int i = 0; i < 8; i++) {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST, buffer[i]);
        digitalWrite(latchPin, HIGH);

        digitalWrite(rowPins[i], LOW);
        delay(2);
        digitalWrite(rowPins[i], HIGH);
      }
    }
  }
}