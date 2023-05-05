#include "ChessGame.hpp"
#include <QVBoxLayout>
#include <QLabel>

ChessGame::ChessGame(QWidget* parent) : QWidget(parent) {
    setupUI();
}

void ChessGame::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* startPositionLabel = new QLabel("Select Starting Position:", this);
    layout->addWidget(startPositionLabel);

    m_startPositionComboBox = new QComboBox(this);
    populateStartPositionComboBox();
    layout->addWidget(m_startPositionComboBox);

    m_newGameButton = new QPushButton("Start New Game", this);
    connect(m_newGameButton, &QPushButton::clicked, this, &ChessGame::startNewGame);
    layout->addWidget(m_newGameButton);

    m_chessBoard = new chess_gui::ChessBoard(true, this);
    layout->addWidget(m_chessBoard);
}

void ChessGame::populateStartPositionComboBox() {
    m_startPositionComboBox->addItem("Standard", "standard");
    m_startPositionComboBox->addItem("Fischer Random", "fischer_random");
    // Add more starting positions here if desired
}

void ChessGame::startNewGame() {
    QString startPosition = m_startPositionComboBox->currentData().toString();

    if (startPosition == "standard") {
        m_chessBoard->setupStandardStartPosition();
    }
    else if (startPosition == "fischer_random") {
        m_chessBoard->setupFischerRandomStartPosition();
    } 
}
