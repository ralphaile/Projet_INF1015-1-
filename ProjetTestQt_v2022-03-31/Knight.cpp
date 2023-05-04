/**
 * @file Knight.cpp
 * @brief This file contains the implementation of the Knight class. 
 * It includes methods for determining valid moves for a knight based on its position on the chessboard and the rules governing the knight's movement.
 */

#include "Knight.hpp"
#include "ChessBoard.hpp"

chess_model::Knight::Knight(Color color, QWidget* parent) : Piece(color, parent) {
}

bool chess_model::Knight::isValidMove(const QPoint& initial, const QPoint & final) const {
    int dx = abs(final.x() - initial.x());
    int dy = abs(final.y() - initial.y());

    chess_gui::ChessBoard* chessBoard = qobject_cast<chess_gui::ChessBoard*>(parentWidget());

    QSharedPointer<Piece> destinationPiece = chessBoard->getPiece(final.x(), final.y());
    if (!destinationPiece.isNull() && destinationPiece->getColor() == getColor()) {
        return false;
    }

    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}
QVector<QPoint> chess_model::Knight::legalMoves(const QPoint& currentPosition) const {
    QVector<QPoint> moves;
    QVector<QPoint> knightOffsets = { {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1} };

    for (const auto& offset : knightOffsets) {
        int newRow = currentPosition.x() + offset.x();
        int newCol = currentPosition.y() + offset.y();
        if (newRow > 7) newRow = 7;
        if (newRow < 0) newRow = 0;
        if (newCol > 7) newCol = 7;
        if (newCol < 0) newCol = 0;
        QPoint destination(newRow, newCol);

        if (isValidMove(currentPosition, destination)) {
            chess_gui::ChessBoard* board = qobject_cast<chess_gui::ChessBoard*>(parentWidget());
            if (board && !board->test_isMovePuttingKingInCheck(currentPosition, destination)) {
                moves.push_back(destination);
            }
        }
    }

    return moves;
}