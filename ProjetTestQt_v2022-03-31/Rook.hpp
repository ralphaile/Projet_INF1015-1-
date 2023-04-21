#ifndef ROOK_H
#define ROOK_H

#include <QWidget>
#include "Piece.hpp"
namespace chess_model {
    class Rook : public Piece {
        Q_OBJECT

    public:
        explicit Rook(Color color, QWidget* parent = nullptr);

        bool isValidMove(const QPoint& initial, const QPoint & final) const override;
        QString getName() const override {
            return pieceColor == White ? "W_Rook" : "B_Rook";
        }
    };

#endif // ROOK_H
}