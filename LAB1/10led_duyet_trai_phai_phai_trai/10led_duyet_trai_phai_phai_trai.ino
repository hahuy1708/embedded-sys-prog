// Khai báo mảng chân LED
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const int n = 10; 

void setup() {
  for (int i = 0; i < n; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); // Đảm bảo lúc đầu tắt hết
  }
}

void loop() {
  // --- GIAI ĐOẠN 1: BẬT DẦN TỪ 1 ĐẾN 10 ---
  for (int i = 0; i < n; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(150); // Tốc độ sáng dần (150ms)
  }

  delay(300); // Đợi một chút khi tất cả đã sáng

  // --- GIAI ĐOẠN 2: TẮT DẦN TỪ 10 VỀ 1 ---
  for (int i = n - 1; i >= 0; i--) {
    digitalWrite(ledPins[i], LOW);
    delay(150); // Tốc độ tắt dần (150ms)
  }

  delay(300); // Nghỉ một chút trước khi lặp lại vòng mới
}