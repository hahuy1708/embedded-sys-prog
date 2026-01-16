const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const int n = 10;
const int potPin = A0;

void setup() {
  for (int i = 0; i < n; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  int potValue = analogRead(potPin);
  int brightness = map(potValue, 0, 1023, 0, 1000); // Thang 1000 cho mịn

  // Bật tất cả
  for (int i = 0; i < n; i++) digitalWrite(ledPins[i], HIGH);
  delayMicroseconds(brightness); // Thời gian sáng tỉ lệ với biến trở

  // Tắt tất cả
  for (int i = 0; i < n; i++) digitalWrite(ledPins[i], LOW);
  delayMicroseconds(1000 - brightness); // Thời gian tắt
}