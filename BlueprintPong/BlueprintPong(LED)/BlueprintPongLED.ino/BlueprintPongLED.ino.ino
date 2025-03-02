const int boardRows = 4;  // 4 rows in the grid
const int boardCols = 12; // 12 columns in the grid

int currentRow = 2;  // Start at the middle row
int currentCol = 1;  // Start near the leftmost column
int directionX = 1;  // Ball moves to the right initially
int directionY = 1;  // Ball moves diagonally down initially

const int joystickY = A3; // Y-axis (controls paddle movement)

int paddleRow = 2; // Paddle starts in the middle
const int paddleCol = 0; // Paddle is always in the leftmost column
const int ledstartport = 0;
const int ledendport = 48;

void flickerLEDs() {
  for (int p = ledstartport; p <= ledendport; p++) {
    digitalWrite(p, HIGH);
    delay(20);
    digitalWrite(p, LOW);
    delay(20);
  }
}

void setup() {
  // Serial.begin(9600);  // Uncomment if you want debugging
  pinMode(joystickY, INPUT);
  
  // Initialize LEDs as output
  for (int pin = ledstartport; pin <= ledendport; pin++) {
    pinMode(pin, OUTPUT);
  }

  // flickerLEDs();  // Flicker LEDs on startup
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
      int ledIndex = row * boardCols + col;
      if ((row == currentRow && col == currentCol) || (col == paddleCol && row == paddleRow)) {
        digitalWrite(ledIndex, HIGH);  // Ball and Paddle
      } else {
        digitalWrite(ledIndex, LOW);
      }
    }
  }
}

void movePaddle() {
  int joystickValue = analogRead(joystickY);
  
  if (joystickValue > 600 && paddleRow >= 0) {
    paddleRow--;  // Move paddle up
  }
  if (joystickValue < 500 && paddleRow < boardRows) {
    paddleRow++;  // Move paddle down
  }
}

void noise() {
  tone(52, 440, 1000);  // Play a tone on pin 52
}

void loop() {
  clearBoard();  // Turn off all LEDs to refresh the display
  movePaddle();  // Update paddle position
  printBoard();  // Update the display with the ball and paddle

  // Move the ball
  currentCol += directionX;
  currentRow += directionY;

  // Ball collision with paddle area (left side)
  if (currentCol == paddleCol && currentRow == paddleRow && directionX == -1) {
    directionX = 1;  // Ball bounces off paddle
    currentCol = 1;  // Ensure it doesn't overlap with paddle
    tone(52, 440, 2000);
    delay(333);
    tone(52, 554, 1334);
    tone(52, 659, 668);
  }

  // Ball collision with right wall (Game Over)
  if (currentCol >= boardCols) { 
loop // Stop game
  }

  // Ball collision with left wall (bounces back)
  if (currentCol < 0) {
    directionX = 1;
  }

  // Ball collision with top and bottom walls
  if (currentRow <= 0 || currentRow >= boardRows - 1) {
    directionY = -directionY;
  }

  delay(900);  // Adjusted speed for smoother gameplay
}
