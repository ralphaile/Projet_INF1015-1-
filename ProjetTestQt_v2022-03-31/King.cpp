#include "King.hpp"
#include "ChessBoard.hpp"

int King::instanceCounter = 0;

King::King(Color color, QWidget* parent, bool bypassLimitCheck) : Piece(color, parent)
{
    if (!bypassLimitCheck) {
        if (instanceCounter >= 2) {
            throw std::runtime_error("There can only be two kings");
        }
        instanceCounter++;
    }
}

bool King::isValidMove(const QPoint& initial, const QPoint & final) const {
    int rowDiff = abs(final.y() - initial.y());
    int colDiff = abs(final.x() - initial.x());

    chess_gui::ChessBoard* chessBoard = qobject_cast<chess_gui::ChessBoard*>(parentWidget());
    if (!chessBoard || !chessBoard->isPathClear(initial, final)) {
        return false;
    }

    // King can move one square in any direction: horizontally, vertically, or diagonally
    return (rowDiff <= 1 && colDiff <= 1);
}
