/**
 * @file King.cpp
 * @brief This file contains the implementation of the King class. It includes methods for determining valid moves for a king based on its position on the chessboard and the rules governing the king's movement.
 */

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

    QSharedPointer<Piece> destinationPiece = chessBoard->getPiece(final.x(), final.y());
    if (!destinationPiece.isNull() && destinationPiece->getColor() == getColor()) {
        return false;
    }
    // King can move one square in any direction: horizontally, vertically, or diagonally
    return (rowDiff <= 1 && colDiff <= 1);
}
void chess_model::King::resetCounter() {
    instanceCounter = 0;
}
QVector<QPoint> chess_model::King::legalMoves(const QPoint& currentPosition) const {
    QVector<QPoint> moves;
    QVector<QPoint> offsets = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };

    for (const auto& offset : offsets) {
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