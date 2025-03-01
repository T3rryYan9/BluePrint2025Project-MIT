#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Servo.h>

#define LED 11
#define BUTTON 12
#define SERVO_PIN 6
#define POT_PIN A0 //Potentiometer
#define ULTRASONIC_TRIGGER 9
#define ULTRASONIC_ECHO 10
#define BUZZER 3

int max_ultrasonic_distance_cm = 400; //sets max distance on how far it will detect
NewPing sonar(ULTRASONIC_TRIGGER, ULTRASONIC_ECHO, max_ultrasonic_distance_cm); //intialization of sensor

Servo servo;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Something"); //Prints out something often

//Code to make the potentiometer to work
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(POT_PIN, INPUT); 
  pinMode(BUZZER, OUTPUT);

  servo.attach(SERVO_PIN);
  servo.write(0);
  
  digitalWrite(BUZZER, HIGH);
  delay(1000);
  digitalWrite(BUZZER, LOW);
}

void read_ultrasonic_sensor(){
  int max_ultrasonic_distance_cm = sonar.ping_cm();
  Serial.print("Ultrasonic: ");
  Serial.print(max_ultrasonic_distance_cm);
}

void buzz() {
  digitalWrite(BUZZER, HIGH);
  delay(1);
  digitalWrite(BUZZER, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  int pot_value = analogRead(POT_PIN);
  Serial.println(pot_value);// Constantly prints out the value of the potentiometer
  int brightness = map(pot_value, 0, 1023, 0, 255); //Maps out potentiometer values
  analogWrite(LED, brightness); // writes the brightness of the led/""
  // read_ultrasonic_sensor();

  int angle = map(pot_value, 0, 1023, 0, 180); 
  // Serial.println(a)
  servo.write(angle);

}
