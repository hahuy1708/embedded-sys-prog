#include <LiquidCrystal.h>
#include <DHT.h>

// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define DHTPIN 6
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

const int buttonPin = 7;
const int backlightPin = 8; 
bool isCelsius = true;
bool lcdPower = true;

int clickCount = 0;
unsigned long lastClickTime = 0;
const unsigned long gapTimeout = 500; 

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  pinMode(buttonPin, INPUT_PULLUP);
  
  pinMode(backlightPin, OUTPUT);
  digitalWrite(backlightPin, HIGH); 
  
  lcd.clear();
}

void loop() {
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (digitalRead(buttonPin) == LOW) {
    delay(50); 
    if (digitalRead(buttonPin) == LOW) {
      clickCount++;
      lastClickTime = millis();
      while (digitalRead(buttonPin) == LOW); 
      delay(50); 
    }
  }

  if (clickCount > 0 && (millis() - lastClickTime > gapTimeout)) {
    if (clickCount >= 2) {
      // NHẤN 2 LẦN -> TẮT/BẬT LCD
      lcdPower = !lcdPower;
      if (lcdPower) {
        lcd.display();
        digitalWrite(backlightPin, HIGH); // Bật đèn nền
        lcd.clear();
      } else {
        lcd.noDisplay();
        digitalWrite(backlightPin, LOW);  // Tắt đèn nền
      }
    } 
    else if (clickCount == 1) {
      if (!lcdPower) {
        // ĐANG TẮT -> NHẤN 1 LẦN -> BẬT LẠI
        lcdPower = true;
        lcd.display();
        digitalWrite(backlightPin, HIGH);
        lcd.clear();
      } else {
        // ĐANG BẬT -> NHẤN 1 LẦN -> ĐỔI ĐƠN VỊ
        isCelsius = !isCelsius;
        lcd.clear();
      }
    }
    clickCount = 0; 
  }

  if (lcdPower) {
    lcd.setCursor(0, 0);
    lcd.print("Nhiet do:       "); 
    
    lcd.setCursor(0, 1);
    if (isnan(t)) {
      lcd.print("Loi cam bien!  ");
    } else {
      if (isCelsius) {
        lcd.print(t); 
        lcd.print((char)223); // Ký hiệu độ
        lcd.print("C         ");
      } else {
        lcd.print(f); 
        lcd.print((char)223); 
        lcd.print("F         ");
      }
    }
  }
}