#include "King.hpp"
#include "ChessBoard.hpp"
#include "CustomExceptions.hpp"

int chess_model::King::instanceCounter = 0;

chess_model::King::King(Color color, QWidget* parent) : Piece(color, parent)
{
        if (instanceCounter >= 2) {
            throw TooManyKingsException("There can only be 2 kings on the board.");
        }
        instanceCounter++;
}

bool chess_model::King::isValidMove(const QPoint& initial, const QPoint & final) const {
    int rowDiff = abs(final.y() - initial.y());
    int colDiff = abs(final.x() - initial.x());

    chess_gui::ChessBoard* chessBoard = qobject_cast<chess_gui::ChessBoard*>(parentWidget());
    if (!chessBoard || !chessBoard->isPathClear(initial, final)) {
        return false;
    }

    // King can move one square in any direction: horizontally, vertically, or diagonally
    return (rowDiff <= 1 && colDiff <= 1);
}
void chess_model::King::resetCounter() {
    instanceCounter = 0;
}