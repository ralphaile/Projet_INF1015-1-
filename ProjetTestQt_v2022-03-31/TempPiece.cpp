/**
 * @file TempPiece.cpp
 * @brief This file contains the implementation of the TempPiece class. 
 * It includes the constructor for creating a temporary placeholder piece by swapping two pieces on the chessboard and the destructor that restores the original state of the board upon its destruction.
 * This functionality aids in the validation of potential moves and game logic.
 */

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