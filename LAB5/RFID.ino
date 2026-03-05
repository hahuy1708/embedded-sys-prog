#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          
#define SS_PIN          10         
#define LED_PIN         2          

MFRC522 mfrc522(SS_PIN, RST_PIN);  

// THAY ĐỔI MÃ UID CỦA BẠN TẠI ĐÂY
byte correctUID[] = {0xA1, 0xB2, 0xC3, 0xD4}; 
int scanCount = 0; // Biến đếm số lần quét đúng liên tiếp

void setup() {
  Serial.begin(9600);
  SPI.begin();           
  mfrc522.PCD_Init();    
  pinMode(LED_PIN, OUTPUT);
  Serial.println("San sang quet the...");
}

void loop() {
  // Kiểm tra xem có thẻ mới đưa vào không
  if ( ! mfrc522.PICC_IsNewCardPresent()) return;
  if ( ! mfrc522.PICC_ReadCardSerial()) return;

  Serial.print("UID cua the: ");
  bool isMatch = true;

  // So sánh UID thẻ vừa quét với correctUID
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    
    if (mfrc522.uid.uidByte[i] != correctUID[i]) {
      isMatch = false;
    }
  }
  Serial.println();

  if (isMatch) {
    // --- YÊU CẦU 1 & 3: QUÉT ĐÚNG THẺ ---
    scanCount++; 
    
    if (scanCount == 1) {
      Serial.println("Quet dung lan 1: LED SANG");
      digitalWrite(LED_PIN, HIGH);
    } 
    else if (scanCount == 2) {
      Serial.println("Quet dung lan 2 lien tiep: LED TAT");
      digitalWrite(LED_PIN, LOW);
      scanCount = 0; // Reset lại biến đếm
    }
  } 
  else {
    // --- YÊU CẦU 2: QUÉT SAI THẺ ---
    Serial.println("Quet sai the: LED NHAP NHAY");
    scanCount = 0; // Reset biến đếm vì không còn liên tiếp
    
    // Nhấp nháy 3 lần
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_PIN, HIGH);
      delay(200);
      digitalWrite(LED_PIN, LOW);
      delay(200);
    }
  }

  mfrc522.PICC_HaltA();
}