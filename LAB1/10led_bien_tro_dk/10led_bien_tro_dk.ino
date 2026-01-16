const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const int n = 10;
const int potPin = A0; // Chân đọc biến trở

void setup() {
  for (int i = 0; i < n; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  // Chân Analog không cần pinMode, nhưng khai báo cho rõ ràng
  pinMode(potPin, INPUT);
}

void loop() {
  // Đọc giá trị biến trở và lưu vào biến tocDo
  // Giá trị analogRead từ 0-1023ms. Bạn có thể cộng thêm một khoảng 
  // để đèn không bị tắt lịm (ví dụ + 10ms)
  int tocDo = analogRead(potPin); 

  // Chạy đi
  for (int i = 0; i < n; i++) {
    tocDo = analogRead(potPin); // Cập nhật tốc độ liên tục trong vòng lặp
    digitalWrite(ledPins[i], HIGH);
    delay(tocDo);
    digitalWrite(ledPins[i], LOW);
  }

  // Chạy về
  for (int i = n - 2; i > 0; i--) {
    tocDo = analogRead(potPin); // Cập nhật tốc độ liên tục
    digitalWrite(ledPins[i], HIGH);
    delay(tocDo);
    digitalWrite(ledPins[i], LOW);
  }
}