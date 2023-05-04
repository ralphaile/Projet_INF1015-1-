/**
 * @file TempPiece.hpp
 * @brief This file contains the declaration of the TempPiece class. 
 * The TempPiece class is a RAII-style helper class that temporarily swaps two pieces on the chessboard to simulate a move, and restores the original state upon its destruction
 * This is useful for validating potential moves, such as checking if a move would put the king in check.
 */
#pragma once

#include <QSharedPointer>
#include "Piece.hpp"

class TempPiece {
public:
    TempPiece(QVector<QVector<QSharedPointer<chess_model::Piece>>>& board, const QPoint& initial, const QPoint & final);
    ~TempPiece();

private:
    QVector<QVector<QSharedPointer<chess_model::Piece>>>& board;
    QPoint initial;
    QPoint final;
    QSharedPointer<chess_model::Piece> initialPiece;
    QSharedPointer<chess_model::Piece> finalPiece;
};