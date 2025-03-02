const int boardRows = 4;  // 4 rows in the grid
const int boardCols = 12; // 12 columns in the grid

int currentRow = 2;  // Start at the middle row
int currentCol = 1;  // Start near the leftmost column
int directionX = 1;  // Ball moves to the right initially
int directionY = 1;  // Ball moves diagonally down initially

const int joystickY = A0; // Y-axis (controls paddle movement)

int paddleRow = 2; // Paddle starts in the middle
const int paddleCol = 0; // Paddle is always in the leftmost column
// int buzzerPin = 3;

void setup() {
  Serial.begin(9600);
  Serial.println("Pong Game Starting...");
  pinMode(joystickY, INPUT);
}

void printBoard() {
  Serial.println("\n\n");

  for (int row = 0; row < boardRows; row++) {
    for (int col = 0; col < boardCols; col++) {
      if (row == currentRow && col == currentCol) {
        Serial.print("O ");  // Ball
      } else if (col == paddleCol && row == paddleRow) {
        Serial.print("| ");  // Paddle (1-row height)
      } else {
        Serial.print(". ");
      }
    }
    Serial.println();
  }
}

void movePaddle() {
  int joystickValue = analogRead(joystickY);
  
  if (joystickValue > 600 && paddleRow > 0) {
    paddleRow--;  // Move up
  }
  if (joystickValue < 500 && paddleRow < boardRows - 1) {
    paddleRow++;  // Move down
  }
}

void noise(){
  tone(3,440,1000);
}

void loop() {
  movePaddle();  // Update paddle position
  printBoard();  // Print the board

  // Move the ball
  currentCol += directionX;
  currentRow += directionY;

  // Check if ball is moving past the left wall (Game Over condition)
  if (currentCol < 0) { 
    Serial.println("Game Over! Ball missed the paddle.");
    tone(3,587,2000);
    delay(333);
    tone(3,659,1334);
    tone(3,698,668);
    while (true);  // Stop game
  }

  // Ball collision with left wall (paddle area)
  if (currentCol == paddleCol && currentRow == paddleRow) {
    directionX = 1;  // Ball bounces off paddle
    currentCol = 1;  // Ensure it doesn't overlap with paddle
    tone(3,440,2000);
    delay(333);
    tone(3,554,1334);
    tone(3,659,668);
  }

  // Ball collision with right wall
  if (currentCol >= boardCols - 1) {
    directionX = -1;
  }

  // Ball collision with top and bottom walls
  if (currentRow <= 0 || currentRow >= boardRows - 1) {
    directionY = -directionY;
  }

  delay(900);
  
}
