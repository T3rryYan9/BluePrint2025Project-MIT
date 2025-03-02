const int boardRows = 4;  // 4 rows in the grid
const int boardCols = 12; // 12 columns in the grid

int currentRow = 2;  // Start at the middle row
int currentCol = 0;  // Start at the leftmost column (column 0)
int directionX = 1;  // Ball moves to the right initially
int directionY = 1;  // Ball moves diagonally down initially

const int joystickY = A3; // Y-axis (controls paddle movement)

int paddleRow = 2; // Paddle starts in the middle
const int paddleCol = 11; // Paddle is always in the rightmost column (column 11)

const int ledstartport = 1;  // Start at digital pin 1
const int ledendport = 48;   // End at digital pin 48 (so we have 48 LEDs)

void flickerLEDs() {
  for (int p = ledstartport; p <= ledendport; p++) {
    digitalWrite(p, HIGH);
    delay(20);
    digitalWrite(p, LOW);
    delay(20);
  }
}

void setup() {
  pinMode(joystickY, INPUT);
  
  // Initialize LEDs as output starting from pin 1
  for (int pin = ledstartport; pin <= ledendport; pin++) {
    pinMode(pin, OUTPUT);
  }
}

void clearBoard() {
  // Turn off all LEDs on the board
  for (int pin = ledstartport; pin <= ledendport; pin++) {
    digitalWrite(pin, LOW);
  }
}

void printBoard() {
  // Print the ball and paddle positions to the LEDs
  for (int row = 0; row < boardRows; row++) {
    for (int col = 0; col < boardCols; col++) {
      int ledIndex = row * boardCols + col;  // Calculate the LED index
      int pin = ledstartport + ledIndex;     // Map to the correct digital pin
      if ((row == currentRow && col == currentCol) || (col == paddleCol && row == paddleRow)) {
        digitalWrite(pin, HIGH);  // Ball and Paddle
      } else {
        digitalWrite(pin, LOW);
      }
    }
  }
}

void movePaddle() {
  int joystickValue = analogRead(joystickY);
  
  // Move paddle up if joystick is moved up
  if (joystickValue > 600 && paddleRow > 0) {  // Prevent paddle from going above row 0
    paddleRow--;  
  }

  // Move paddle down if joystick is moved down
  if (joystickValue < 500 && paddleRow < boardRows - 1) {  // Prevent paddle from going below last row
    paddleRow++;  
  }
}

void noise() {
  tone(52, 440, 1000);  // Play a tone on pin 52
}

bool isBallOnPaddle() {
  // Check if the ball's position and the paddle's position are both "on" (LED is HIGH)
  int ballLedIndex = currentRow * boardCols + currentCol;
  int paddleLedIndex = paddleRow * boardCols + paddleCol;

  int ballPin = ledstartport + ballLedIndex;
  int paddlePin = ledstartport + paddleLedIndex;

  // Return true if the ball and paddle LEDs are both on the same spot
  return digitalRead(ballPin) == HIGH && digitalRead(paddlePin) == HIGH;
}

void loop() {
  clearBoard();  // Turn off all LEDs to refresh the display
  movePaddle();  // Update paddle position
  printBoard();  // Update the display with the ball and paddle

  // Move the ball
  currentCol += directionX;
  currentRow += directionY;

  // Check if the ball is on the paddle (use the digitalRead check)
  if (isBallOnPaddle() && directionX == 1) {
    directionX = -1;  // Ball bounces off paddle (reverse direction)
    currentCol = 10;  // Move ball a bit away from paddle (so it doesn't overlap)
    tone(52, 440, 2000);
    delay(333);
    tone(52, 554, 1334);
    tone(52, 659, 668);
  }

  // Ball collision with right wall (Game Over)
  if (currentCol >= boardCols) { 
    currentRow = 2;  // Reset ball to middle
    currentCol = 0;  // Reset ball to start near the left side
    directionX = 1;  // Start moving right again
    directionY = 1;  // Move diagonally down initially
    tone(52, 440, 1000);  // Play game-over tone
    delay(1000);  // Pause before restarting
  }

  // Ball collision with left wall (bounces back)
  if (currentCol < 0) {
    directionX = 1;
  }

  // Ball collision with top and bottom walls
  if (currentRow <= 0 || currentRow >= boardRows - 1) {
    directionY = -directionY;
  }

  delay(500);  // Adjusted speed for smoother gameplay
}
