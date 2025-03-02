#include <NewPing.h> // include the ultrasonic sensor library
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define RED_LED 11
#define BUTTON 12
#define POT_PIN A0
#define ULTRASONIC_TRIGGER 9
#define ULTRASONIC_ECHO 10
int max_ultrasonic_distance_cm = 400; // set the maximum measureable distance for the ultrasonic sensor to 400cm 
NewPing sonar(ULTRASONIC_TRIGGER, ULTRASONIC_ECHO, max_ultrasonic_distance_cm); 

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// game settings
const int num_tasks = 3; // set the number of tasks to 3
long game_score = 0; // set the player's game score to 0

// define the game actions the player needs to do:
// press a button, twist a potentiometer, or trigger an ultrasonic sensor

long PUSH_BUTTON = 0;
long POTENTIOMETER = 1;
long ULTRASONIC_SENSOR = 2;

long task;

long task_timer = 0; // variable to keep track of how much time has elapsed
long task_time_limit = 3000; // set the amount of time a player has to complete the task (3000 milliseconds = 3 seconds)
long task_pause = 1000; // set the amount of pause time between tasks

// helper function to write to display
void write_to_display(String message) {
  display.clearDisplay();
  display.setCursor(0, 10);
  display.println(message);
  display.display();
}

void blink_led(int num_blinks){
  for (int i =0; i < num_blinks; i++){
    digitalWrite(RED_LED, HIGH);
    delay(300);
    digitalWrite(RED_LED, LOW);
    delay(300);
  }
}


void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  Serial.println("Starting program...");
  pinMode(RED_LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(POT_PIN, INPUT);

  // initialize display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  randomSeed(analogRead(5)); // initialize the random number generator with arbitrary data noise from a digital pin

  set_new_task();
}

void loop() {
  // put your main code here, to run repeatedly:

  // main game state check
   if (millis() - task_timer > task_time_limit) {
    end_game();
  } else {
    check_user_action();
  }
}

int last_pot_value = 0;
void set_new_task() {
  delay(task_pause);
  write_to_display("Hello");
  task = random(num_tasks); //0, 1, 2
  blink_led(task+1);


  task_timer = millis();
  if (task == POTENTIOMETER){
    last_pot_value = analogRead(POT_PIN);
  }

}

void end_game() {
  digitalWrite(RED_LED, LOW);
  write_to_display("Game over! \n\nYour score: " + String(game_score));
  game_score=0;
  set_new_task();
}

void check_user_action() {
  if(task == PUSH_BUTTON){
    int button_value = digitalRead(BUTTON);
    if(button_value == 0){
      game_score += 5;
      write_to_display("+5");
      set_new_task();
      
    }
  } else if (task == POTENTIOMETER){
    int pot_val = analogRead(POT_PIN);

    if ((last_pot_value < 512 && pot_val > 700) || 
        (last_pot_value >= 512 && pot_val <300 )){
        game_score += 7;
          write_to_display("+7");
          set_new_task();
    }}

   else if (task == ULTRASONIC_SENSOR){
    int distance = sonar.ping_cm();
    if (distance > 0 && distance < 10){
      game_score += 10;
      write_to_display("+10");
      set_new_task();
    }
  }

}