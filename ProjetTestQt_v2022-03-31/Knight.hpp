#ifndef KNIGHT_H
#define KNIGHT_H

#include <QWidget>
#include "Piece.hpp"
namespace chess_model {
    class Knight : public Piece {
        Q_OBJECT

    public:
        explicit Knight(Color color, QWidget* parent = nullptr);

        bool isValidMove(const QPoint& initial, const QPoint & final) const override;
        QString getName() const override {
            return pieceColor == White ? "W_Knight" : "B_Knight";
        }

    };

#endif // KNIGHT_H
}