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
        QString getName() const override {
            return pieceColor == White ? "W_King" : "B_King";
        }
        // We use this function after creating a test using a king so it doesnt affect our ability to create 2 kings for the game
        static void resetCounter();
    };
}