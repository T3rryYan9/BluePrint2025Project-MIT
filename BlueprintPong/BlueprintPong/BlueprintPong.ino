const int boardRows = 4;  // 3 rows in the grid
const int boardCols = 12;  // 4 columns in the grid

int currentRow = 2;  // Start at the middle row
int currentCol = 0;  // Start at the leftmost column
int directionX = 1;  // Ball will move to the right initially
int directionY = 1;  // Ball will move down initially

void setup() {
  Serial.begin(9600);
  Serial.println("Pong Game Starting...");
}

void printBoard() {
  // Clear the Serial Monitor before printing the board
  Serial.println("\n\n");

  // Print the board row by row
  for (int row = 0; row < boardRows; row++) {
    for (int col = 0; col < boardCols; col++) {
      // Print 'O' where the ball is and '.' elsewhere
      if (row == currentRow && col == currentCol) {
        Serial.print("O ");
      } else {
        Serial.print(". ");
      }
    }
    Serial.println();  // Move to the next row
  }
}

void loop() {
  // Print the current board with the ball's position
  printBoard();

  // Move the ball diagonally
  currentCol += directionX;  // Move horizontally
  currentRow += directionY;  // Move vertically

  // Check for horizontal boundaries (left and right walls)
  if (currentCol < 0 || currentCol >= boardCols) {
    directionX = -directionX;  // Reverse horizontal direction
  }

  // Check for vertical boundaries (top and bottom walls)
  if (currentRow < 0 || currentRow >= boardRows) {
    directionY = -directionY;  // Reverse vertical direction
  }

  // Delay to make the ball move at a visible speed
  delay(500);
}
