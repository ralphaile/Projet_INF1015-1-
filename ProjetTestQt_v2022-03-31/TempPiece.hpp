
#ifndef PIECETEMP_H
#define PIECETEMP_H

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

#endif // PIECETEMP_H