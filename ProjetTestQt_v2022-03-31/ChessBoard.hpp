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
        QSharedPointer<Piece> getPiece(int row, int col) const;
        bool isPathClear(const QPoint& initial, const QPoint & final) const;

        bool test_isInCheck(Piece::Color color) {
            return isInCheck(color);
        }

    private:
        bool isTest;
        QVector<QVector<QPushButton*>> boardButtons;
        QGridLayout* layout;
        QPoint selectedPiece{ -1, -1 };
        QVector<QVector<QSharedPointer<Piece>>> pieces;
        Piece::Color turn;

        void initializeBoard();
        bool isInCheck(Piece::Color color);
        bool isInCheckmate(Piece::Color color);
        bool isMovePuttingKingInCheck(const QPoint& initial, const QPoint & final);

        void onButtonClicked(int row, int col);

        template<typename PieceType>
        void createPieceAtPosition(int row, int col, Piece::Color color);
        void initializeBoardForTesting();
    private slots:
        void handleButtonClicked();
    };
}
