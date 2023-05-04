/**
 * @file ChessBoard.hpp
 * @brief This file contains the declaration of the ChessBoard class. The class is responsible for managing and displaying the chessboard's state, which includes pieces, their positions, and user interactions.
 * The file also declares helper methods for determining game state, such as checking for check, checkmate, and valid moves.
 */

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

        bool test_isInCheck(chess_model::Piece::Color color) {
            return isInCheck(color);
        }

        bool test_isInCheckmate(chess_model::Piece::Color color) {
            return isInCheckmate(color);
        }

        bool test_isMovePuttingKingInCheck(const QPoint& initial, const QPoint & final) {
            return isMovePuttingKingInCheck(initial, final);
        }
        bool test_isInStalemate(chess_model::Piece::Color color) {
            return isInStalemate(color);
        }

        void initializeBoardForTesting();
        template<typename PieceType>
        void createPieceAtPosition(int row, int col, chess_model::Piece::Color color);
    private:
        bool isTest;
        QVector<QVector<QPushButton*>> boardButtons;
        QGridLayout* layout;
        QPoint selectedPiece{ -1, -1 };
        QVector<QVector<QSharedPointer<chess_model::Piece>>> pieces;
        chess_model::Piece::Color turn;

        void GUI_DeselectPiece();
        void highlightLegalMoves(const QPoint& initial);
        void resetHighlight();

        void initializeBoard();
        bool isInCheck(chess_model::Piece::Color color);
        bool isInCheckmate(chess_model::Piece::Color color);
        bool isMovePuttingKingInCheck(const QPoint& initial, const QPoint & final);
        bool onlyKingsRemain();
        bool isInStalemate(chess_model::Piece::Color color);

        void onButtonClicked(int row, int col);

    private slots:
        void handleButtonClicked();
    };
}
