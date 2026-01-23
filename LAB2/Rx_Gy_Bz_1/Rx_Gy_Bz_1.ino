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
  Serial.println("Nhap: RxGyBz hoac Rx,Gy,Bz");
} 

void loop() { 
  if (Serial.available() > 0) { 
    String input = Serial.readStringUntil('\n'); 
    input.trim(); 

    if (input.indexOf('R') != -1) { 
      currentR = constrain(parseValue(input, 'R'), 0, 255);
      analogWrite(redPin, currentR); 
    } 

    if (input.indexOf('G') != -1) { 
      currentG = constrain(parseValue(input, 'G'), 0, 255);
      analogWrite(greenPin, currentG); 
    } 

    if (input.indexOf('B') != -1) { 
      currentB = constrain(parseValue(input, 'B'), 0, 255);
      analogWrite(bluePin, currentB); 
    } 

    Serial.print("Trang thai - R:");
    Serial.print(currentR);
    Serial.print(" G:");
    Serial.print(currentG);
    Serial.print(" B:");
    Serial.println(currentB);
  } 
} 

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