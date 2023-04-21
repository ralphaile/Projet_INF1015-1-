#include "Knight.hpp"
#include "ChessBoard.hpp"

chess_model::Knight::Knight(Color color, QWidget* parent) : Piece(color, parent) {
}

bool chess_model::Knight::isValidMove(const QPoint& initial, const QPoint & final) const {
    int dx = abs(final.x() - initial.x());
    int dy = abs(final.y() - initial.y());

    chess_gui::ChessBoard* chessBoard = qobject_cast<chess_gui::ChessBoard*>(parentWidget());
    if (!chessBoard) {
        return false;
    }

    QSharedPointer<Piece> destinationPiece = chessBoard->getPiece(final.x(), final.y());
    if (!destinationPiece.isNull() && destinationPiece->getPieceColor() == getPieceColor()) {
        return false;
    }

    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}