#pragma once
#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QGridLayout>
#include <QSharedPointer>
#include "Piece.hpp"
#include <QPushButton>

namespace chess_gui {

    class ChessBoard : public QWidget {
        Q_OBJECT

    public:
        explicit ChessBoard(bool isTest=false,QWidget* parent = nullptr);
        QSharedPointer<chess_model::Piece> getPiece(int row, int col) const;
        bool isPathClear(const QPoint& initial, const QPoint & final) const;

        bool test_isInCheck(chess_model::Piece::Color color) {
            return isInCheck(color);
        }

        bool test_isInCheckmate(chess_model::Piece::Color color) {
            return isInCheckmate(color);
        }

        bool test_isMovePuttingKingInCheck(const QPoint& initial, const QPoint & final) {
            return isMovePuttingKingInCheck(initial, final);
        }

        void initializeBoardForTesting();
        template<typename PieceType>
        void createPieceAtPosition(int row, int col, chess_model::Piece::Color color);
        void setPiece(int row, int col, QSharedPointer<chess_model::Piece> piece);
    private:
        bool isTest;
        QVector<QVector<QPushButton*>> boardButtons;
        QGridLayout* layout;
        QPoint selectedPiece{ -1, -1 };
        QVector<QVector<QSharedPointer<chess_model::Piece>>> pieces;
        chess_model::Piece::Color turn;

        void initializeBoard();
        bool isInCheck(chess_model::Piece::Color color);
        bool isInCheckmate(chess_model::Piece::Color color);
        bool isMovePuttingKingInCheck(const QPoint& initial, const QPoint & final);

        void onButtonClicked(int row, int col);

    private slots:
        void handleButtonClicked();
    };
}
