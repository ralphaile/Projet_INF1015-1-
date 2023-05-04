/**
 * @file Rook.hpp
 * @brief This file contains the declaration of the Rook class, which is derived from the Piece class. 
 * The Rook class represents the rook chess piece and provides methods for determining valid moves based on the rules specific to the rook.
 */

#pragma once
#include <QWidget>
#include "Piece.hpp"
namespace chess_model {
    class Rook : public Piece {
        Q_OBJECT

    public:
        explicit Rook(Color color, QWidget* parent = nullptr);

        bool isValidMove(const QPoint& initial, const QPoint & final) const override;
        QVector<QPoint> legalMoves(const QPoint& currentPosition) const override;
        QString getName() const override {
            return pieceColor == Color::WHITE ? "W_Rook" : "B_Rook";
        }
    };

}