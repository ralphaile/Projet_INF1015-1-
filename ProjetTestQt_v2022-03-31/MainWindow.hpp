/**
 * @file MainWindow.hpp
 * @brief This file contains the declaration of the MainWindow class. The MainWindow class is responsible for creating and managing the main application window, which includes the chessboard and other UI components.
 */

#pragma once
#include <QMainWindow>
#include "ChessBoard.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    chess_gui::ChessBoard* chessBoard;

};

