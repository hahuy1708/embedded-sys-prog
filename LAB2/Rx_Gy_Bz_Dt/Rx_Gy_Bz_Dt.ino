const int redPin = 9; 
const int greenPin = 10; 
const int bluePin = 11; 

int currentR = 0; 
int currentG = 0; 
int currentB = 0; 

void setup() { 
  Serial.begin(9600); 
  pinMode(redPin, OUTPUT); 
  pinMode(greenPin, OUTPUT); 
  pinMode(bluePin, OUTPUT); 

  Serial.println("He thong da san sang.");
  Serial.println("Nhap: RxGyBz (sang mai mai)");
  Serial.println("Hoac: RxGyBzDt (t la thoi gian ms, neu t=0 den khong sang)");
} 

void loop() { 
  if (Serial.available() > 0) { 
    String input = Serial.readStringUntil('\n'); 
    input.trim(); 

    // 1. TÁCH GIÁ TRỊ MÀU (Lưu vào biến, CHƯA BẬT ĐÈN NGAY)
    if (input.indexOf('R') != -1) { 
      currentR = constrain(parseValue(input, 'R'), 0, 255);
    } 

    if (input.indexOf('G') != -1) { 
      currentG = constrain(parseValue(input, 'G'), 0, 255);
    } 

    if (input.indexOf('B') != -1) { 
      currentB = constrain(parseValue(input, 'B'), 0, 255);
    } 

    // 2. KIỂM TRA THỜI GIAN (D)
    bool hasDuration = (input.indexOf('D') != -1);
    int duration = 0;
    
    if (hasDuration) {
      duration = parseValue(input, 'D');
    }

    if (hasDuration && duration == 0) {
      analogWrite(redPin, 0); 
      analogWrite(greenPin, 0); 
      analogWrite(bluePin, 0);
      
      currentR = 0; currentG = 0; currentB = 0;
      
      Serial.println("Phat hien D0 -> Den KHONG sang.");
    } 
    else {
      
      analogWrite(redPin, currentR); 
      analogWrite(greenPin, currentG); 
      analogWrite(bluePin, currentB); 

      Serial.print("Trang thai ON - R:"); Serial.print(currentR);
      Serial.print(" G:"); Serial.print(currentG);
      Serial.print(" B:"); Serial.println(currentB);

      if (hasDuration && duration > 0) {
        delay(duration); // Chờ
        
        // Tắt đèn
        analogWrite(redPin, 0); 
        analogWrite(greenPin, 0); 
        analogWrite(bluePin, 0); 

        // Reset biến về 0
        currentR = 0; currentG = 0; currentB = 0;
        Serial.println("-> Da tat den sau thoi gian cho.");
      }
    }
  } 
} 

// Hàm tách số 
int parseValue(String data, char identifier) { 
  int index = data.indexOf(identifier); 
  if (index == -1) return -1; 

  String valueStr = ""; 

  for (int i = index + 1; i < data.length(); i++) { 
    char c = data.charAt(i); 
    if (isDigit(c) || c == '-') { 
      valueStr += c; 
    } else { 
      break; 
    } 
  } 

  if (valueStr.length() > 0) { 
    return valueStr.toInt(); 
  } 
  return 0;  
}