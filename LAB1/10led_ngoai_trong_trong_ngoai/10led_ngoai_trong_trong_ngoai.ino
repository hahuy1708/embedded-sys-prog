const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const int n = 10;

void setup() {
  for (int i = 0; i < n; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void loop() {
  // 1. Sáng dần từ hai bên vào trong
  // i chạy từ 0 đến 4 (5 cặp)
  for (int i = 0; i < n / 2; i++) {
    digitalWrite(ledPins[i], HIGH);           // LED bên trái
    digitalWrite(ledPins[n - 1 - i], HIGH);   // LED bên phải đối xứng
    delay(200);
  }

  delay(300); // Nghỉ một chút khi tất cả đã sáng

  // 2. Tắt dần từ trong ra hai bên
  // i chạy ngược từ 4 về 0
  for (int i = (n / 2) - 1; i >= 0; i--) {
    digitalWrite(ledPins[i], LOW);            // Tắt LED bên trái
    digitalWrite(ledPins[n - 1 - i], LOW);    // Tắt LED bên phải đối xứng
    delay(200);
  }

  delay(500); // Nghỉ trước khi lặp lại
}