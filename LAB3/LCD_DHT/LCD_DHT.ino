#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

#define DHTPIN 2     
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.init();
  lcd.backlight();
  
  dht.begin();
  
  lcd.setCursor(0, 0);
  lcd.print("Nhiet do:");
}

void loop() {
  delay(2000);

  float t = dht.readTemperature();

  if (isnan(t)) {
    lcd.setCursor(0, 1);
    lcd.print("Loi cam bien!");
  } else {
    lcd.setCursor(0, 1);
    lcd.print(t);
    lcd.print((char)223); 
    lcd.print("C   ");    
  }
}