#define RED_PIN   9
#define GREEN_PIN 10
#define BLUE_PIN  11

int R = 0, G = 0, B = 0;

int clamp(int v) {
  if (v > 255) return 255;
  if (v < 0) return 0;
  return v;
}

void applyLED() {
  analogWrite(RED_PIN, R);
  analogWrite(GREEN_PIN, G);
  analogWrite(BLUE_PIN, B);
}

void setup() {
  Serial.begin(9600);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    String s = Serial.readStringUntil('\n');
    s.trim();

    int r = s.indexOf('R');
    int g = s.indexOf('G');
    int b = s.indexOf('B');
    int d = s.indexOf('D');

    if (r != -1 && g != -1)
      R = clamp(s.substring(r + 1, g).toInt());

    if (g != -1 && b != -1)
      G = clamp(s.substring(g + 1, b).toInt());

    if (b != -1 && d != -1)
      B = clamp(s.substring(b + 1, d).toInt());

    applyLED();

    if (d != -1) {
      int t = s.substring(d + 1).toInt();
      delay(t);
      R = G = B = 0;
      applyLED();
    }
  }
}
