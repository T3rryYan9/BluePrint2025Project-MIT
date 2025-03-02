// #define LED_22 22
// #define LED_24 24
// #define LED_26 26
// #define LED_28 28
// #define LED_30 30
// #define LED_32 32
// #define LED_34 34
// #define LED_36 36
// #define LED_38 38
// #define LED_40 40
// #define LED_42 42
// #define LED_44 44

const int ledPins[] = {22,24,26,28,30,32,34,36,38,40,42,44};
const int ledPin2d[3][4] = {
    {22,24,26,28},
    {30,32,34,36},
    {38,40,42,44}
};


void setup() {
  for (int i = 0; i < 12; i++) {
    pinMode(ledPins[i],OUTPUT);
  }
  Serial.begin(9600);
  Serial.println("Led Starting...");
  Serial.println(ledPin2d[3][4]);

}

void BlinkArray2D() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      digitalWrite(ledPin2d[i][j],HIGH);
      delay(50);
      digitalWrite(ledPin2d[i][j],LOW);
      delay(50);
    }
  }
}

void blinkLED() {
  for (int i = 0; i < 12; i++) {
    digitalWrite(ledPins[i],HIGH);
    delay(20);
    digitalWrite(ledPins[i],LOW);
    delay(20);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // blinkLED();
  BlinkArray2D();

}
