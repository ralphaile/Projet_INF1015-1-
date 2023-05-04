/**
 * @file Piece.hpp
 * @brief This file contains the declaration of the Piece class and its derived classes for each specific piece type (e.g., King, Rook, Knight).
 * The base class represents a single chess piece with attributes like color and type and provides methods for determining valid moves.
 */


#pragma once
#include <QPoint>
#include <QWidget>

namespace chess_model {

    class Piece : public QWidget {
        Q_OBJECT

    public:
        enum class Color { WHITE, BLACK };
        explicit Piece(Color color, QWidget* parent = nullptr) : QWidget(parent), pieceColor(color) {}
        virtual ~Piece() {}
        Color getColor() const { return pieceColor; }

        virtual bool isValidMove(const QPoint& initial, const QPoint & final) const = 0;
        virtual QVector<QPoint> legalMoves(const QPoint& currentPosition) const = 0;
        virtual QString getName() const = 0;
    protected:
        Color pieceColor;
    };
}
