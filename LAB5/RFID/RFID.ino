#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          
#define SS_PIN          10         
#define LED_PIN         2    

MFRC522 mfrc522(SS_PIN, RST_PIN);  

byte correctUID[] = {0x29, 0xDC, 0x143, 0x14}; 
int mode = 0; // 0: Tắt, 1: Sáng mãi, 2: Nhấp nháy mãi

unsigned long lastCorrectTime = 0;
int scanCount = 0;
bool pendingCheck = false; 

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.println("He thong Lab 5: Cho quet the...");
}

void loop() {
  // --- PHẦN 1: HIỆU ỨNG ĐÈN (KHÔNG DÙNG DELAY) ---
  if (mode == 0) {
    digitalWrite(LED_PIN, LOW);
  } 
  else if (mode == 1) {
    digitalWrite(LED_PIN, HIGH);
  } 
  else if (mode == 2) {
    digitalWrite(LED_PIN, (millis() / 300) % 2); 
  }

  // --- PHẦN 2: LOGIC ĐỢI 1.5S ĐỂ CHỐT TẮT/MỞ (CHỈ CHẠY KHI ĐANG Ở MODE 0 HOẶC 1) ---
  if (pendingCheck && (millis() - lastCorrectTime > 1500)) {
    if (scanCount == 1) {
      mode = 1; 
      Serial.println("Ket qua: SANG MAI");
    } 
    else if (scanCount >= 2) {
      mode = 0; 
      Serial.println("Ket qua: TAT");
    }
    pendingCheck = false;
    scanCount = 0;
  }

  // --- PHẦN 3: ĐỌC THẺ RFID ---
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  bool match = true;
  for (byte i = 0; i < 4; i++) {
    if (mfrc522.uid.uidByte[i] != correctUID[i]) {
      match = false;
      break;
    }
  }

  if (match) {
    // Nếu đang nhấp nháy (sai thẻ) mà quẹt đúng -> Sáng luôn lập tức
    if (mode == 2) {
      mode = 1;
      pendingCheck = false; // Hủy bỏ bộ đợi 1.5s
      scanCount = 0;
      Serial.println("Dang nhay -> Quet dung: SANG NGAY LAP TUC");
    } 
    // Nếu đang bình thường thì mới chạy bộ đợi 1.5s để phân biệt quẹt 1 hay 2 lần
    else {
      if (!pendingCheck) {
        lastCorrectTime = millis();
        pendingCheck = true;
        scanCount = 1;
        Serial.println("Quet lan 1... Dang doi 1.5s...");
      } else {
        scanCount++;
        Serial.print("Quet lan ");
        Serial.println(scanCount);
      }
    }
    delay(300); // Chống dội thẻ
  } 
  else {
    // Quét sai thẻ: Chuyển sang nhấp nháy ngay lập tức
    mode = 2; 
    pendingCheck = false;
    scanCount = 0;
    Serial.println("Quet sai: NHAP NHAY MAI");
    delay(500);
  }

  mfrc522.PICC_HaltA();
}