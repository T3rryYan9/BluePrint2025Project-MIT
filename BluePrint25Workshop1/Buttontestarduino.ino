#define LED 11
#define BUTTON 12

void setup() {
  // put your setup code here, to 
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
}

void fade_led() {
  // put your main code here, to run repeatedly:
 for (int i = 0; i <= 255; i++) {
  analogWrite(LED,i);
  delay(10);
 }
 for (int i = 255; i >= 0; i--) {
  analogWrite(LED,i);
  delay(10);
 }
}

void loop() {
  //fade_led();
  int button = digitalRead(BUTTON);
  
  if (button == 0){ // When button is pressed
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }

  

}