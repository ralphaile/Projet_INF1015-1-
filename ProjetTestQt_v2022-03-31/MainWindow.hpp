#include <QMainWindow>
#include "ChessBoard.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    chess_gui::ChessBoard* chessBoard;

    // Add any other necessary methods and member variables here
};

