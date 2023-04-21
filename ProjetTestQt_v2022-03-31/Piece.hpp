#ifndef PIECE_H
#define PIECE_H

#include <QPoint>
#include <QWidget>

namespace chess_model {
    class Piece : public QWidget {
        Q_OBJECT

    public:
        enum Color { White, Black };
        explicit Piece(Color color, QWidget* parent = nullptr) : QWidget(parent), pieceColor(color) {}
        virtual ~Piece() {}
        Color getPieceColor() const { return pieceColor; }

        virtual bool isValidMove(const QPoint& initial, const QPoint & final) const = 0;
        virtual QString getName() const = 0;
    protected:
        Color pieceColor;
    };
}

#endif // PIECE_H