#define LED_5 22
#define LED_6 24
#define LED_7 26

void setup() {
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);
  pinMode(LED_7, OUTPUT);
  Serial.begin(9600);
  Serial.println("Led Starting...");

}

void blinkLED() {
  digitalWrite(LED_5,HIGH);
  delay(300);
  digitalWrite(LED_5,LOW);
  delay(300);
  digitalWrite(LED_6,HIGH);
  delay(300);
  digitalWrite(LED_6,LOW);
  delay(300);
  digitalWrite(LED_7,HIGH);
  delay(300);
  digitalWrite(LED_7,LOW);
  delay(300);
}

void loop() {
  // put your main code here, to run repeatedly:
  blinkLED();

}
