const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const int n = 10;

// Kịch bản thứ tự: 1, 3, 5, 7, 9, 10, 8, 6, 4, 2
// Chỉ số mảng (index): 0, 2, 4, 6, 8, 9, 7, 5, 3, 1
const int sequence[] = {0, 2, 4, 6, 8, 9, 7, 5, 3, 1};

void setup() {
  for (int i = 0; i < n; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void loop() {
  // Chạy đuổi theo thứ tự đã định nghĩa
  for (int i = 0; i < n; i++) {
    int currentPin = ledPins[sequence[i]]; // Xác định chân đèn hiện tại
    
    digitalWrite(currentPin, HIGH);        // Bật đèn hiện tại
    delay(300);                           // Giữ sáng trong 0.3 giây
    digitalWrite(currentPin, LOW);         // Tắt ngay đèn hiện tại để chuẩn bị cho đèn sau
  }

  // Tùy chọn: Bạn có thể thêm một khoảng nghỉ nhỏ trước khi lặp lại từ đầu
  delay(200);
}