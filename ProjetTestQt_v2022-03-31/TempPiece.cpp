#include "TempPiece.hpp"

TempPiece::TempPiece(QVector<QVector<QSharedPointer<chess_model::Piece>>>& board, const QPoint& initial, const QPoint & final) : board(board), initial(initial), final(final) {
    initialPiece = board[initial.x()][initial.y()];
    finalPiece = board[final.x()][final.y()];

    board[final.x()][final.y()] = board[initial.x()][initial.y()];
    board[initial.x()][initial.y()].reset();
}

TempPiece::~TempPiece() {
    board[initial.x()][initial.y()] = initialPiece;
    board[final.x()][final.y()] = finalPiece;
}