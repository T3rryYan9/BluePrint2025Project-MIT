#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Servo.h>

#define LED 11
#define BUTTON 12
#define SERVO_PIN 6
#define POT_PIN A0
#define ULTRASONIC_TRIGGER 9
#define ULTRASONIC_ECHO 10
#define BUZZER_PIN 3

int max_ultrasonic_distance_cm = 400;
NewPing sonar(ULTRASONIC_TRIGGER, ULTRASONIC_ECHO, max_ultrasonic_distance_cm);

Servo servo;

void setup() {
  // put your setup code here, to 
  pinMode(LED, OUTPUT);
  pinMode(BUTTON,INPUT_PULLUP);
  pinMode(POT_PIN, INPUT);
  pinMode(BUZZER_PIN,OUTPUT);
  Serial.begin(9600);
  Serial.println("Serial monitor starting...");
  servo.attach(SERVO_PIN);
  servo.write(0);
  // buzz();
  // digitalWrite(BUZZER_PIN,HIGH);
  // delay(1000);
  // digitalWrite(BUZZER_PIN,LOW);
}

void potentioServo() {
  int pot_value = analogRead(POT_PIN);
  int servoMovement = map(pot_value,0,1023,0,180);
  servo.write(servoMovement); 
  // Serial.println(brightness);
}

void readUltraSensor() {
  int ultraDistance_cm = sonar.ping_cm();
  Serial.println(ultraDistance_cm);
}

void loop() {
  // fade_led();
  potentioServo();
  // readUltraSensor();
}

void buzz() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(1);
  digitalWrite(BUZZER_PIN,LOW);
}
