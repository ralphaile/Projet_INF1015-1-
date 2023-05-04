/**
 * @file King.hpp
 * @brief This file contains the declaration of the King class, which is derived from the Piece class. 
 * The King class represents the king chess piece and provides methods for determining valid moves based on the rules specific to the king.
 */

#pragma once

#include <QWidget>
#include "Piece.hpp"
namespace chess_model {
    class King : public Piece {
        Q_OBJECT

    private:
        static int instanceCounter;
        bool bypassLimitCheck;

    public:
        explicit King(Color color, QWidget* parent = nullptr);

        bool isValidMove(const QPoint& initial, const QPoint & final) const override;
        QVector<QPoint> legalMoves(const QPoint& currentPosition) const override;
        QString getName() const override {
            return pieceColor == Color::WHITE ? "W_King" : "B_King";
        }
        // We use this function after creating a test using a king so it doesnt affect our ability to create 2 kings for the game
        static void resetCounter();
    };
}