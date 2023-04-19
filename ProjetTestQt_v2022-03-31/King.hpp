#pragma once

#include <QWidget>
#include "Piece.hpp"

class King : public Piece {
    Q_OBJECT

private:
    static int instanceCounter;
    bool bypassLimitCheck;

public:
    explicit King(Color color, QWidget* parent = nullptr, bool bypassLimitCheck = false);

    bool isValidMove(const QPoint& initial, const QPoint & final) const override;
    QString getName() const override {
        return pieceColor == White ? "W_King" : "B_King";
    }
};
