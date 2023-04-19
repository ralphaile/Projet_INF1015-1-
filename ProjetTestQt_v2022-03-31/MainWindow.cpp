#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), chessBoard(new  chess_gui::ChessBoard(false,this)) {
    setCentralWidget(chessBoard);
    setWindowTitle("Projet INF1015");
    resize(450, 450);
}
