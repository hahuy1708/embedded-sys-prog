#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          
#define SS_PIN          10         

MFRC522 mfrc522(SS_PIN, RST_PIN);  

void setup() {
  Serial.begin(9600);
  SPI.begin();           
  mfrc522.PCD_Init();    
  Serial.println("--- HE THONG DOC MA UID ---");
  Serial.println("Hay dua the cua ban lai gan module...");
}

void loop() {
  // Kiem tra co the moi hay khong
  if ( ! mfrc522.PICC_IsNewCardPresent()) return;
  if ( ! mfrc522.PICC_ReadCardSerial()) return;

  // In ra Serial Monitor
  Serial.print("UID cua the la: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    // In dinh dang HEX (Vi du: A1 B2 C3 D4)
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();
  Serial.println("--------------------------");

  mfrc522.PICC_HaltA(); // Dung doc the
}