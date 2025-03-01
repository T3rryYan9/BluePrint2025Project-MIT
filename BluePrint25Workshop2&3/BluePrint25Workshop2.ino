#include <NewPing.h>

#define LED 11
#define BUTTON 12
#define POT_PIN A0 //Potentiometer
#define ULTRASONIC_TRIGGER 9
#define ULTRASONIC_ECHO 10

int max_ultrasonic_distance_cm = 400; //sets max distance on how far it will detect
NewPing sonar(ULTRASONIC_TRIGGER, ULTRASONIC_ECHO, max_ultrasonic_distance_cm); //intialization of sensor

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Something"); //Prints out something often

//Code to make the potentiometer to work
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(POT_PIN, INPUT); 


}

void read_ultrasonic_sensor(){
  int max_ultrasonic_distance_cm = sonar.ping_cm();
  Serial.print("Ultrasonic: ");
  Serial.print(max_ultrasonic_distance_cm);
}

void loop() {
  // put your main code here, to run repeatedly:

  int pot_value = analogRead(POT_PIN);
  Serial.println(pot_value);// Constantly prints out the value of the potentiometer
  int brightness = map(pot_value, 0, 1023, 0, 255); //Maps out potentiometer values
  analogWrite(LED, brightness); // writes the brightness of the led/""
  read_ultrasonic_sensor();
}
