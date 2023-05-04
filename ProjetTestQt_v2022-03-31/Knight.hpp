/**
 * @file Knight.hpp
 * @brief This file contains the declaration of the Knight class, which is derived from the Piece class. T
 * he Knight class represents the knight chess piece and provides methods for determining valid moves based on the rules specific to the knight.
 */

#pragma once
#include <QWidget>
#include "Piece.hpp"
namespace chess_model {
    class Knight : public Piece {
        Q_OBJECT

    public:
        explicit Knight(Color color, QWidget* parent = nullptr);

        bool isValidMove(const QPoint& initial, const QPoint & final) const override;
        QVector<QPoint> legalMoves(const QPoint& currentPosition) const override;
        QString getName() const override {
            return pieceColor == Color::WHITE ? "W_Knight" : "B_Knight";
        }

    };

}