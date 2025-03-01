#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_SSD1306>
#include <Adafruit_GFX.h>

#define LED 11
#define BUTTON 12
#define POT_PIN A0
#define ULTRASONIC_TRIGGER 9
#define ULTRASONIC_ECHO 10

int max_ultrasonic_distance_cm = 400;
NewPing sonar(ULTRASONIC_TRIGGER, ULTRASONIC_ECHO, max_ultrasonic_distance_cm);

void setup() {
  // put your setup code here, to 
  pinMode(LED, OUTPUT);
  pinMode(BUTTON,INPUT_PULLUP);
  pinMode(POT_PIN, INPUT);
  Serial.begin(9600);
  Serial.println("Serial monitor starting...");
}

void potentioLight() {
  int pot_value = analogRead(POT_PIN);
  int brightness = map(pot_value,0,1023,0,255);
  analogWrite(LED,brightness);
  // Serial.println(brightness);
}

void readUltraSensor() {
  int ultraDistance_cm = sonar.ping_cm();
  Serial.println(ultraDistance_cm);
}

void loop() {
  // fade_led();
  potentioLight();
  readUltraSensor();
}

