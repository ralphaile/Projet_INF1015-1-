/**
 * @file Rook.cpp
 * @brief This file contains the implementation of the Rook class. It includes methods for determining valid moves for a rook based on its position on the chessboard and the rules governing the rook's movement.
 */
#include "Rook.hpp"
#include "ChessBoard.hpp"

chess_model::Rook::Rook(Color color, QWidget* parent) : Piece(color, parent) {
}

bool chess_model::Rook::isValidMove(const QPoint& initial, const QPoint & final) const {
    int rowDiff = initial.x() - final.x();
    int colDiff = initial.y() - final.y();

    chess_gui::ChessBoard* chessBoard = qobject_cast<chess_gui::ChessBoard*>(parentWidget());

    if (rowDiff == 0) {
        int colStep = colDiff > 0 ? -1 : 1;
        for (int col = initial.y() + colStep; col != final.y(); col += colStep) {
            if (!chessBoard->getPiece(initial.x(), col).isNull()) {
                return false;
            }
        }
    }
    else if (colDiff == 0) {
        int rowStep = rowDiff > 0 ? -1 : 1;
        for (int row = initial.x() + rowStep; row != final.x(); row += rowStep) {
            if (!chessBoard->getPiece(row, initial.y()).isNull()) {
                return false;
            }
        }
    }
    else {
        return false;
    }

    QSharedPointer<chess_model::Piece> destinationPiece = chessBoard->getPiece(final.x(), final.y());
    if (!destinationPiece.isNull() && destinationPiece->getColor() == chessBoard->getPiece(initial.x(), initial.y())->getColor()) {
        return false;
    }

    return true;
}
QVector<QPoint> chess_model::Rook::legalMoves(const QPoint& currentPosition) const {
    QVector<QPoint> moves;
    QVector<QPoint> rookOffsets = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (const auto& offset : rookOffsets) {
        for (int distance = 1; distance < 8; ++distance) {
            int newRow = currentPosition.x() + distance * offset.x();
            int newCol = currentPosition.y() + distance * offset.y();
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

                if (!board->getPiece(newRow,newCol).isNull()) {
                    break; // Stop searching in this direction if a piece is encountered
                }
            }
            else {
                break; // Stop searching in this direction if the move is not valid
            }
        }
    }

    return moves;
}