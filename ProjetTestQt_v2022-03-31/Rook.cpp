#include "Rook.hpp"
#include "ChessBoard.hpp"

Rook::Rook(Color color, QWidget* parent) : Piece(color, parent) {
}

bool Rook::isValidMove(const QPoint& initial, const QPoint & final) const {
    int rowDiff = initial.x() - final.x();
    int colDiff = initial.y() - final.y();

    if ((rowDiff == 0) == (colDiff == 0)) {
        return false;
    }

    chess_gui::ChessBoard* chessBoard = qobject_cast<chess_gui::ChessBoard*>(parentWidget());
    if (!chessBoard || !chessBoard->isPathClear(initial, final)) {
        return false;
    }

    return true;
}
