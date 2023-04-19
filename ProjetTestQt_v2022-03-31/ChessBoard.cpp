#include "ChessBoard.hpp"
#include <QMouseEvent>
#include "King.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>

using namespace chess_gui;

ChessBoard::ChessBoard(bool isTest,QWidget* parent) : QWidget(parent), layout(new QGridLayout(this)) {
    turn = Piece::Color::White;
    if (isTest)
         initializeBoardForTesting();
    else
        initializeBoard();

}

bool ChessBoard::isPathClear(const QPoint& initial, const QPoint & final) const {
    int rowDiff = initial.x() - final.x();
    int colDiff = initial.y() - final.y();

    if (rowDiff == 0) {
        int colStep = colDiff > 0 ? -1 : 1;
        for (int col = initial.y() + colStep; col != final.y(); col += colStep) {
            if (!getPiece(initial.x(), col).isNull()) {
                return false;
            }
        }
    }
    else {
        int rowStep = rowDiff > 0 ? -1 : 1;
        for (int row = initial.x() + rowStep; row != final.x(); row += rowStep) {
            if (!getPiece(row, initial.y()).isNull()) {
                return false;
            }
        }
    }
    QSharedPointer<Piece> destinationPiece = getPiece(final.x(), final.y());
    if (!destinationPiece.isNull() && destinationPiece->getPieceColor() == pieces[initial.x()][initial.y()]->getPieceColor()) {
        return false;
    }

    return true;
}


QSharedPointer<Piece> ChessBoard::getPiece(int row, int col) const {
    if (row >= 0 && row < 8 && col >= 0 && col < 8) {
        return pieces[row][col];
    }
    return QSharedPointer<Piece>();
}

template<typename PieceType>
void ChessBoard::createPieceAtPosition(int row, int col, Piece::Color color) {
    try {
        QSharedPointer<Piece> piece = QSharedPointer<Piece>(new PieceType(color, this));
        QPushButton* button = boardButtons[row][col];
        QString buttonText =piece->getName();
        button->setText(buttonText);
        pieces[row][col] = piece;
    }
    catch (const std::runtime_error& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void ChessBoard::initializeBoard() {
    for (int row = 0; row < 8; ++row) {
        QVector<QPushButton*> buttonRow;
        QVector<QSharedPointer<Piece>> pieceRow;

        for (int col = 0; col < 8; ++col) {
            QPushButton* button = new QPushButton(this);
            button->setFixedSize(50, 50);

            // Set the background color to black or blue based on the position
            QColor backgroundColor = ((row + col) % 2 == 0) ? Qt::white : Qt::darkGreen;
            QString color = QString("background-color: %1").arg(backgroundColor.name());
            button->setStyleSheet(color);

            buttonRow.push_back(button);

            layout->addWidget(button, row, col);
            connect(button, &QPushButton::clicked, this, &ChessBoard::handleButtonClicked);

            // Add chess pieces to the board
            QSharedPointer<Piece> piece;
            pieceRow.push_back(piece);
        }

        boardButtons.push_back(buttonRow);
        pieces.push_back(pieceRow);
    }

    // Create pieces using createPieceAtPosition
    createPieceAtPosition<King>(0, 4, Piece::White);
    createPieceAtPosition<King>(7, 4, Piece::Black);
    createPieceAtPosition<Knight>(0, 5, Piece::White);
    createPieceAtPosition<Rook>(0, 3, Piece::White);
    createPieceAtPosition<Knight>(7, 5, Piece::Black);
    createPieceAtPosition<Rook>(7, 3, Piece::Black);
}

void ChessBoard::initializeBoardForTesting() {
    for (int row = 0; row < 8; ++row) {
        QVector<QPushButton*> buttonRow;
        QVector<QSharedPointer<Piece>> pieceRow;

        for (int col = 0; col < 8; ++col) {
            QPushButton* button = new QPushButton(this);
            button->setFixedSize(50, 50);

            // Set the background color to black or blue based on the position
            QColor backgroundColor = ((row + col) % 2 == 0) ? Qt::white : Qt::darkGreen;
            QString color = QString("background-color: %1").arg(backgroundColor.name());
            button->setStyleSheet(color);

            buttonRow.push_back(button);

            layout->addWidget(button, row, col);
            connect(button, &QPushButton::clicked, this, &ChessBoard::handleButtonClicked);

            pieceRow.push_back(QSharedPointer<Piece>());
        }

        boardButtons.push_back(buttonRow);
        pieces.push_back(pieceRow);
    }
}

void ChessBoard::onButtonClicked(int row, int col) {
    // Check if a piece is already selected
    if (selectedPiece == QPoint(-1, -1)) {
        // If the clicked position has a piece, select it
        if (!pieces[row][col].isNull() && pieces[row][col]->getPieceColor() == turn) {
            selectedPiece = QPoint(row, col);
            QColor backgroundColor = ((row + col) % 2 == 0) ? Qt::white : Qt::darkGreen;
            boardButtons[row][col]->setStyleSheet(QString("background-color: %1; border: 2px solid red").arg(backgroundColor.name()));
        }
    }
    else {
        // If the clicked button is the same as the selected button, deselect the piece and return
        if (selectedPiece.x() == row && selectedPiece.y() == col) {
            QColor backgroundColor = ((selectedPiece.x() + selectedPiece.y()) % 2 == 0) ? Qt::white : Qt::darkGreen;
            boardButtons[selectedPiece.x()][selectedPiece.y()]->setStyleSheet(QString("background-color: %1").arg(backgroundColor.name()));
            selectedPiece = QPoint(-1, -1);
            return;
        }

        QPoint destination(row, col);

        // Check if the move is valid for the selected piece
        if (pieces[selectedPiece.x()][selectedPiece.y()]->isValidMove(selectedPiece, destination)) {
            if (isMovePuttingKingInCheck(selectedPiece, destination)) {
                // Deselect the piece
                QMessageBox::information(this, "Illegal Move", "This move would put your king in check.");
                QColor backgroundColor = ((selectedPiece.x() + selectedPiece.y()) % 2 == 0) ? Qt::white : Qt::darkGreen;
                boardButtons[selectedPiece.x()][selectedPiece.y()]->setStyleSheet(QString("background-color: %1").arg(backgroundColor.name()));
                selectedPiece = QPoint(-1, -1);
                return;
            }
            // Move the piece
            pieces[row][col] = pieces[selectedPiece.x()][selectedPiece.y()];
            pieces[selectedPiece.x()][selectedPiece.y()].reset();

            // Update the GUI
            boardButtons[row][col]->setText(boardButtons[selectedPiece.x()][selectedPiece.y()]->text());
            boardButtons[selectedPiece.x()][selectedPiece.y()]->setText("");
            QColor backgroundColor = ((selectedPiece.x() + selectedPiece.y()) % 2 == 0) ? Qt::white : Qt::darkGreen;
            boardButtons[selectedPiece.x()][selectedPiece.y()]->setStyleSheet(QString("background-color: %1").arg(backgroundColor.name()));

            // Check if the move puts the opponent in check
            Piece::Color opponentColor = pieces[row][col]->getPieceColor() == Piece::Color::White ? Piece::Color::Black : Piece::Color::White;
            if (isInCheckmate(opponentColor)) {
                //qDebug() << (opponentColor) << "is in checkmate";
                QMessageBox::information(this, "Checkmate", "Checkmate! The game is over.");
                for (const auto& row : boardButtons) {
                    for (auto button : row) {
                        button->setEnabled(false);
                    }
                }
                return;
            }
            else if (isInCheck(opponentColor)) {
                QMessageBox::information(this, "Check", "Check! Your opponent's king is in check.");
            }

            turn = (turn == Piece::Color::White) ? Piece::Color::Black : Piece::Color::White;


            // Deselect the piece
            selectedPiece = QPoint(-1, -1);
        }
        else {
            // If the move is not valid, deselect the selected piece
            QColor backgroundColor = ((selectedPiece.x() + selectedPiece.y()) % 2 == 0) ? Qt::white : Qt::darkGreen;
            boardButtons[selectedPiece.x()][selectedPiece.y()]->setStyleSheet(QString("background-color: %1").arg(backgroundColor.name()));
            selectedPiece = QPoint(-1, -1);
        }
    }
}


void ChessBoard::handleButtonClicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        int row = -1;
        int col = -1;
        for (int r = 0; r < 8; ++r) {
            for (int c = 0; c < 8; ++c) {
                if (boardButtons[r][c] == button) {
                    row = r;
                    col = c;
                    break;
                }
            }
            if (row != -1) {
                break;
            }
        }
        if (row != -1 && col != -1) {
            onButtonClicked(row, col);
        }
    }
}
bool ChessBoard::isInCheck(Piece::Color color) {
    //qDebug() << "Checking if" << (color == Piece::Color::White ? "White" : "Black") << "is in check";
    QPoint kingPosition;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QSharedPointer<Piece> piece = pieces[row][col];

            if (!piece.isNull() && piece->getPieceColor() == color && dynamic_cast<King*>(piece.data())) {
                kingPosition = QPoint(row, col);
                break;
            }
        }
    }
    //qDebug() << "King position: " << kingPosition;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QSharedPointer<Piece> piece = pieces[row][col];

            if (!piece.isNull() && piece->getPieceColor() != color && piece->isValidMove(QPoint(row, col), kingPosition)) {
               // qDebug() << "Checking piece at" << QPoint(row, col) << "with type" << typeid(*piece).name() << "for valid move to king";
                return true;
            }
        }
    }

    return false;
}

bool ChessBoard::isInCheckmate(Piece::Color color) {
    // Check if the king is in check first
    if (!isInCheck(color)) {
        return false;
    }

    // Loop through all the pieces on the board
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (!pieces[row][col].isNull() && pieces[row][col]->getPieceColor() == color) {
                // For each piece of the given color, loop through all possible destination squares
                for (int newRow = 0; newRow < 8; ++newRow) {
                    for (int newCol = 0; newCol < 8; ++newCol) {
                        QPoint currentPos(row, col);
                        QPoint destination(newRow, newCol);
                        // If the move is valid and does not put the king in check, it means it's not checkmate
                        if (pieces[row][col]->isValidMove(currentPos, destination) && !isMovePuttingKingInCheck(currentPos, destination)) {
                            return false;
                        }
                    }
                }
            }
        }
    }

    // If no valid moves are found, it's checkmate
    return true;
}


bool ChessBoard::isMovePuttingKingInCheck(const QPoint& initial, const QPoint & final) {
    // Temporarily move the piece
    QSharedPointer<Piece> tempPiece = pieces[final.x()][final.y()];
    pieces[final.x()][final.y()] = pieces[initial.x()][initial.y()];
    pieces[initial.x()][initial.y()].reset();

    // Check if the king is in check
    Piece::Color currentPlayerColor = pieces[final.x()][final.y()]->getPieceColor();
    bool kingInCheck = isInCheck(currentPlayerColor);

    // Undo the temporary move
    pieces[initial.x()][initial.y()] = pieces[final.x()][final.y()];
    pieces[final.x()][final.y()] = tempPiece;

    return kingInCheck;
}