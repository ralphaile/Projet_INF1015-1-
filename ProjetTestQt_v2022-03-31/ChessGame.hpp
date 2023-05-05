#ifndef CHESSGAME_HPP
#define CHESSGAME_HPP

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include "ChessBoard.hpp"

class ChessGame : public QWidget {
    Q_OBJECT

public:
    ChessGame(QWidget* parent = nullptr);

private slots:
    void startNewGame();

private:
    void setupUI();
    void populateStartPositionComboBox();

    chess_gui::ChessBoard* m_chessBoard;
    QComboBox* m_startPositionComboBox;
    QPushButton* m_newGameButton;
};

#endif // CHESSGAME_HPP
