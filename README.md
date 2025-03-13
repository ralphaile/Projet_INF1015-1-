# Chess Game

## Installation

To run the Chess Game, you will need to have Qt 5.15 or later installed on your system. You can download Qt from the official website: [https://www.qt.io/download](https://www.qt.io/download).

Once you have Qt installed, you can clone the repository and open the project.

## Usage

To start the game, simply run the application. You can choose the starting position (standard or Fischer random) from the dropdown menu and click the "Start New Game" button.

The game supports the following features:

- Piece movement according to the rules of chess
- Highlighting of legal moves for the selected piece
- Detection of check and checkmate
- Detection of stalemate
- Support for standard and Fischer random starting positions

## API

The main classes and their functions are:

- `ChessBoard`:
  - `getPiece(int row, int col)`: Returns the piece at the specified position.
  - `isInCheck(chess_model::Piece::Color color)`: Checks if the king of the specified color is in check.
  - `isInCheckmate(chess_model::Piece::Color color)`: Checks if the player of the specified color is in checkmate.
  - `isInStalemate(chess_model::Piece::Color color)`: Checks if the player of the specified color is in stalemate.
  - `setupStandardStartPosition()`: Sets up the board with the standard starting position.
  - `setupFischerRandomStartPosition()`: Sets up the board with a Fischer random starting position.

- `Piece` (and its derived classes, e.g., `King`, `Rook`, `Knight`):
  - `isValidMove(const QPoint& initial, const QPoint& final)`: Checks if the piece can move from the initial position to the final position.
  - `legalMoves(const QPoint& currentPosition)`: Returns a vector of legal moves for the piece at the current position.

## Testing

The project includes a test suite that covers various aspects of the chess game, such as piece movement, check, checkmate, and stalemate detection. You can run the tests using the Google Test framework.

To run the tests, simply execute the following command in the project directory:
